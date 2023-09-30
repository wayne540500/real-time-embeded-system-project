# “Embedded Sentry”
Objective:

● Use the data collected from a single accelerometer and/or gyro to record a hand 
movement sequence as a means to generally “unlock” a resource.

● Recorded sequence must be saved on the microcontroller, using a “Record Key” 
feature.

● User then must replicate the key sequence within sufficient tolerances to unlock 
the resource.

● A successful unlock must be indicated by a visual indication, such as an LED or 
similar indicator.

Demo: https://youtu.be/Y5AhhtOK0g8
![image](https://github.com/wayne540500/real-time-embeded-system-project/assets/69573286/7d775bb0-462f-4d62-aa24-0a3f53d82868)

User Manual:
Procedure:
1. After the code is uploaded to the board and is ready to run, the user can press the blue
button to activate the system.
2. The screen will indicate to users that no key is recorded with red background.
![image](https://github.com/wayne540500/real-time-embeded-system-project/assets/69573286/a2079914-d719-4e30-8abf-f7c9cba4095b)

3. Press and hold the blue button for longer than 2 seconds, the recording procedure will
start and last for 2 seconds. The screen will display “Recording Complete” after the key
is recorded.
![image](https://github.com/wayne540500/real-time-embeded-system-project/assets/69573286/ee84140b-6928-4399-89d4-6d76fce61149)
![image](https://github.com/wayne540500/real-time-embeded-system-project/assets/69573286/64da0daa-8b99-4f15-8697-fef241153fb9)

4. Click the blue button to verify the key. If it matches the recorded result, the screen will
display in green with “Unlock Successful” on it.
![image](https://github.com/wayne540500/real-time-embeded-system-project/assets/69573286/ca659395-a555-4224-a6f8-ff57f8eda5c1)
![image](https://github.com/wayne540500/real-time-embeded-system-project/assets/69573286/5e2d5fbc-dc6b-4397-865a-3c659c9bc2aa)

5. If the result does not match the recorded key, the screen will display in red with “Unlock
Failed” on it.
![image](https://github.com/wayne540500/real-time-embeded-system-project/assets/69573286/9277d3ce-8a86-478d-b1ca-99781a48c7fc)

6. Press and hold the blue button for longer than 2 seconds to reset the key. The new key
will be recorded in 2 seconds.
