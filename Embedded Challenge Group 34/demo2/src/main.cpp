#include <mbed.h>
#include "drivers/LCD_DISCO_F429ZI.h"
#include "stm32f4xx.h"

// Gyroscope registers
#define L3GD20_CTRL_REG1        0x20
#define L3GD20_CTRL_REG4        0x23
#define L3GD20_OUT_X_L          0x28
#define L3GD20_OUT_X_H          0x29
#define L3GD20_OUT_Y_L          0x2A
#define L3GD20_OUT_Y_H          0x2B
#define L3GD20_OUT_Z_L          0x2C
#define L3GD20_OUT_Z_H          0x2D

// Gyroscope scaling factor
#define GYRO_SCALE_FACTOR       (17.5f * 0.017453292519943295769236907684886f / 1000.0f)

// Recording duration in ms
#define RECORDING_DURATION      2000

// Tolerance for gesture comparison
#define GESTURE_TOLERANCE      500

// Press duration for recording (in ms)
#define LONG_PRESS_DURATION     2000

// Samples per second and total samples
#define SAMPLES_PER_SECOND 100
#define NUM_SAMPLES (RECORDING_DURATION / 1000 * SAMPLES_PER_SECOND)

// LCD
LCD_DISCO_F429ZI lcd;

// BUTTON for recording and entering key
DigitalIn button(PA_0);

// LED for indicating success
DigitalOut led(LED1);
I2C_HandleTypeDef hi2c;

// Variables to store key gestures
int16_t key_x[NUM_SAMPLES], key_y[NUM_SAMPLES], key_z[NUM_SAMPLES];
bool key_recorded = false;

// Function prototypes
void gyroscope_init(void)
{
    // Enable the gyroscope
    uint8_t ctrl_reg1 = 0x0F; // Output data rate = 95 Hz, bandwidth = 25 Hz, enable X/Y/Z axis
    uint8_t ctrl_reg4 = 0x30; // Full-scale selection = +/- 250 dps
    
    // Configure the gyroscope
    HAL_I2C_Mem_Write(&hi2c, 0xD6, L3GD20_CTRL_REG1, 1, &ctrl_reg1, 1, 10);
    HAL_I2C_Mem_Write(&hi2c, 0xD6, L3GD20_CTRL_REG4, 1, &ctrl_reg4, 1, 10);
}


void gyroscope_read(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t data[6];
    
    // Read X/Y/Z gyroscope data
    HAL_I2C_Mem_Read(&hi2c, 0xD6, L3GD20_OUT_X_L | 0x80, 1, data, 6, 10);
    
    // Combine the low and high bytes of each axis
    *x = (int16_t)(data[1] << 8 | data[0]);
    *y = (int16_t)(data[3] << 8 | data[2]);
    *z = (int16_t)(data[5] << 8 | data[4]);
}

void delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}


// Main program
int main() {
    // Initialize the gyroscope and LCD
    gyroscope_init();
    lcd.DisplayOn();
    lcd.Clear(LCD_COLOR_WHITE);

    // Initialize hi2c
    hi2c.Instance = I2C1;
    hi2c.Init.ClockSpeed = 400000;
    hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c.Init.OwnAddress1 = 0;
    hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c.Init.OwnAddress2 = 0;
    hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    
    // Main loop
    while (1) {
        // Check button press
        if (button.read() == 1) {
            uint32_t press_time = HAL_GetTick();

            // Wait for button release
            while (button.read() == 1) {}

            // Determine if it was a short press or long press
            if ((HAL_GetTick() - press_time) >= LONG_PRESS_DURATION) {
                // Long press - Record key gesture
                lcd.Clear(LCD_COLOR_BLUE);
                lcd.DisplayStringAt(0, LINE(4), (uint8_t *)"RECORDING", CENTER_MODE);
                delay_ms(1000);  // Give user a chance to get ready

                for (int i = 0; i < NUM_SAMPLES; i++) {
                    gyroscope_read(&key_x[i], &key_y[i], &key_z[i]);
                    delay_ms(1000 / SAMPLES_PER_SECOND);
                }

                key_recorded = true;

                lcd.Clear(LCD_COLOR_WHITE);
                lcd.DisplayStringAt(0, LINE(4), (uint8_t *)"RECORDING COMPLETE", CENTER_MODE);
                delay_ms(1000);
            } else {
                // Short press - Enter key
                if (!key_recorded) {
                    lcd.Clear(LCD_COLOR_RED);
                    lcd.DisplayStringAt(0, LINE(4), (uint8_t *)"NO KEY RECORDED", CENTER_MODE);
                    delay_ms(1000);
                    continue;
                }

                lcd.Clear(LCD_COLOR_BLUE);
                lcd.DisplayStringAt(0, LINE(4), (uint8_t *)"ENTER KEY", CENTER_MODE);
                delay_ms(1000);  // Give user a chance to get ready

                int16_t x[NUM_SAMPLES], y[NUM_SAMPLES], z[NUM_SAMPLES];
                for (int i = 0; i < NUM_SAMPLES; i++) {
                    gyroscope_read(&x[i], &y[i], &z[i]);
                    delay_ms(1000 / SAMPLES_PER_SECOND);
                }

                // Compare entered key with recorded key
                bool success = false;
                for (int i = 0; i < NUM_SAMPLES; i++) {
                    if (abs(x[i] - key_x[i]) < GESTURE_TOLERANCE || 
                        abs(y[i] - key_y[i]) < GESTURE_TOLERANCE || 
                        abs(z[i] - key_z[i]) < GESTURE_TOLERANCE) {
                            success = true;
                            break;
                    }
                }

                if (success) {

                    // Successful unlock
                    lcd.Clear(LCD_COLOR_GREEN);
                    lcd.DisplayStringAt(0, LINE(4), (uint8_t *)"UNLOCK SUCCESSFUL", CENTER_MODE);
                    led = 1;  // Turn on LED
                    delay_ms(2000);  // Display success for 2 seconds
                    led = 0;  // Turn off LED
                } else {
                    // Unsuccessful unlock
                    lcd.Clear(LCD_COLOR_RED);
                    lcd.DisplayStringAt(0, LINE(4), (uint8_t *)"UNLOCK FAILED", CENTER_MODE);
                    delay_ms(2000);  // Display failure for 2 seconds
                }
            }
        }
    }
}

