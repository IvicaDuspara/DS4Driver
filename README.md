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

This is a Linux userspace driver for DUALSHOCK®4. It provides
user with ability to map controller's buttons to keyboard buttons, assign macros to buttons, provide 
ability to change color and add rumble on button press.
 
<a name="Config"></a>
## Configuration
Configuration files describe button mapping. This is described in detail
in ./tools/README.md

<a name="Building"></a>
<a name="Running"></a>

<a name="FAQ"></a>
## FAQ
**Q**: I thought that DUALSHOCK®4 works out of the box on Linux machines.

**A**: You are correct. Once you plug in controller light bar turns blue,
and even touchpad works on your machine! 

**Q**: Then what is the purpose of this program?

**A**: Imagine that you are playing some game.
When you click a button on controller you can never have the motors rumble
or color change. This is simply because no program or driver told controller to do this.
Linux recognizes (and game probably) your controller but not all of the features
of it. Furthermore some games might not support gamepads/joysticks at all.
Wouldn't it be cool to play those games by emulating "keys and mouse"
on controller?


**Q**: When is feature __insert_name__ coming?

**A**: I do not know. Please understand that I have never written a device driver 
before. I might try and add those features down the line.

