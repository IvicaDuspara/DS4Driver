# DS4Driver
Linux driver for DUALSHOCK®4

[1. Introduction](#Introduction)

[2. Configuration files](#Config)

[3. Building instructions](#Building)

[4. Running instructions](#Running)

[5. FAQ](#FAQ)

<a name="Introduction"></a>
## Introduction
For questions and answers please see [FAQ](#FAQ). 

This is a Linux user space driver for DUALSHOCK®4. It provides
user with ability to map controller's buttons to keyboard buttons, assign macros to buttons, provide 
ability to change color and add rumble on button press.
 
<a name="Config"></a>
## Configuration
Configuration files describe button mapping. This is described in detail
in ./tools/README.md

<a name="Building"></a>
## Building
To build this project you need CMake installed. Following code is an example which assumes you have downloaded source
code into your home folder.
```
username@user: ~$ cd DS4Driver
username@user: ~/DS4Driver$ mkdir build
username@user: ~/DS4Driver$ cd build
username@user: ~/DS4Driver/build$ cmake ..
username@user: ~/DS4Driver/build cmake --build .
```
After executing commands above, you will see generated folder inside build folder. Navigate to bin folder inside build 
folder. There you will find executable. Once built generated executable can be moved anywhere and run from that directory.
<a name="Running"></a>
## Running
Once you have completed build step you can run the program. By default, executable requires running in superuser
mode because it communicates with /dev/hidraw*. 

Program requires 3 arguments:
 1. Path to /dev/js*, where * is a number which identifies connected joystick.
 2. Path to /dev/hidraw*, where * is a number which identifies connected joystick.
 3. Path to configuration file
 
 Here is an example of how one would run this program:
 ```
root@PC:/home/user# ./DS4Driver /dev/js0 /dev/hidraw1 ./config.txt
```

<a name="FAQ"></a>
## FAQ
**Q**: I thought that DUALSHOCK®4 works out of the box on Linux machines.

**A**: You are correct. Once you plug in controller light bar turns blue,
and even touchpad works on your machine! 

**Q**: Then what is the purpose of this program?

**A**: You can do the following:
+ When a button on joystick is pressed, light bar color changes or a motor rumbles. This program allows you to do that.
+ If you are playing an old game which has no joystick support, you can emulate keyboard button press/release on
joystick button press/release. 


**Q**: When is feature __insert_name__ coming?

**A**: I do not know. Please understand that I have never written a device driver 
before. I might try and add those features down the line.

