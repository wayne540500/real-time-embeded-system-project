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
3. Press and hold the blue button for longer than 2 seconds, the recording procedure will
start and last for 2 seconds. The screen will display “Recording Complete” after the key
is recorded.
4. Click the blue button to verify the key. If it matches the recorded result, the screen will
display in green with “Unlock Successful” on it.
5. If the result does not match the recorded key, the screen will display in red with “Unlock
Failed” on it.
6. Press and hold the blue button for longer than 2 seconds to reset the key. The new key
will be recorded in 2 seconds.
