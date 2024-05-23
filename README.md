# arcade machine arduino code
 
First, install this new bootloader called Hoodloader2. It turns the arduino uno into 2 separate microcontrollers that communicate via serial. From there, follow the instructions there to find out how to choose which one to upload to. Can also refer to other examples on the Hoodloader2 and HID github pages, which my code is based on.

https://github.com/NicoHood/HoodLoader2
https://github.com/NicoHood/HID

There's 2 folders of arduino code, install Gamepad to the Hoodloader2 Uno, and arcade_machine_arduino_code to the Hoodloader2 16u2.

arcade_machine_arduino_code is installed to the Hoodloader Uno as that's the one which has access to the input pins, which the buttons and joysticks are connected to. The code creates and sends a message via serial, which is read by Gamepad. This one takes the message and acts as a HID to the computer (devices like mouse, keyboard, or in this case, gamepad), running functions taken from https://github.com/NicoHood/HID to emulate the gamepad.

Test inputs here: https://gamepadtester.net/