### What goes in configuration file

DUALSHOCK®4 has 13 buttons:
+ X
+ Circle
+ Triangle
+ Square
+ L1
+ R1
+ L2
+ R2
+ Share
+ Options
+ PS
+ L3
+ R3

It also has 8 axes:
+ left/right L3 (L3L, L3R)
+ up/down L3 (L3U, L3D)
+ L2 (how much you pressed it) (L2A)
+ left/right R3 (R3L, R3R)
+ up/down R3 (R3U, R3D)
+ R2 (how much you pressed it) (R3A)
+ left/right D-pad (DPADL, DPADR)
+ up/down D-pad (DPADU, DPADD)

Configuration file should contain lines which describe in what do these buttons map.    
Generally speaking each valid line consists of following:
1. Controller's key (mandatory)
2. Modifiers(ctrl,alt,shift in any combination separated by +) (optional)
3. Keyboard key (mandatory)
4. 6 digit hex color code (optional)
5. 3 digits indicating heavy rumble strength (optional)
6. 3 digits indicating light rumble strength (optional)

Here are 2 examples of valid lines.
Here are few examples of valid lines:

+ R1 Ctrl+R #ff0000 - (Pressing R1 on controller simulates Ctrl+R on keyboard, turns light to red)

+ S Ctrl+Shift+Alt+T 120 120 - (Pressing Square on controller simulates Ctrl+Shift+Alt+T on keyboard, rumbles heavy and
    light motor with strength of 120)
    
If you wish to see a complete file check config.txt

### How to use config_converter.py

Since "linux/input-event-codes.h" defines a number for each key on keyboard,
this script converts keys to designated numbers. 

To run config_converter.py on a configuration file named input.txt:

```
$ python3 config_converter.py ./input.txt
```

Converted output will be placed in folder where the script is and 
it will be named converted_config.txt.
If you wish to specify your output file name, add it as a second argument:

```
$ python3 config_converted.py ./input.txt ~/my_special_output.txt
```
