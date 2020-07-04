import sys
joystick_button_dict = {'X' : 0, 'x' : 0, 'C' : 1, 'c' : 1, 'T' : 2, 't' : 2, 'S' : 3, 's' : 3, 'L1' : 4, 'l1' : 4, 'R1' : 5, 'r1' : 5,
                        'l2' : 6, 'L2' : 6, 'r2' : 7, 'R2' : 7, 'Share' : 8, 'share' : 8, 'Options' : 9, 'options' : 9, 'PS' : 10, 'ps' : 10,
                        'L3' : 11, 'l3' : 11, 'R3' : 12, 'r3' : 12, 'l3l' : 13, 'l3L' : 13, 'L3l' : 13, 'L3L' : 13, 'l3r' : 14, 'l3R' : 14,
                        'L3r' : 14, 'L3R' : 14, 'l3u' : 15, 'l3U' : 15, 'L3u' : 15, 'L3U' : 15, 'l3d' : 16, 'l3D' : 16, 'L3d' : 16, 'L3D' : 16,
                        'r3l' : 17, 'r3L' : 17, 'R3l' : 17, 'R3L' : 17, 'r3r' : 18, 'r3R' : 18, 'R3r' : 18, 'R3R' : 18, 'r3u' : 19, 'r3U' : 19,
                        'R3u' : 19, 'R3U' : 19, 'r3d' : 20, 'r3D' : 20, 'R3d' : 20, 'R3D' : 20, 'dpadl' : 21, 'dpadL' : 21, 'dpadr' : 22, 'dpadR' : 22, 'dpadu' : 23,
                        'dpadU' : 23, 'dpadd' : 24, 'dpadD' : 24}

hr_key_code_dict = {'esc' : 1, '1' : 2, '2' : 3, '3' : 4, '4' : 5, '5' : 6, '6' : 7, '7' : 8, '8' : 9, '9' : 10, '0' : 11,
                 '\'' : 12, '+' : 13, 'backspace' : 14, 'Backspace' : 14, 'BACKSPACE' : 14, 'tab' : 15, 'Tab' : 15, 'TAB' : 15,
                 'q' : 16, 'Q' : 16, 'w' : 17, 'W' : 17, 'e' : 18, 'E' : 18, 'r' : 19, 'R' : 19, 't' : 20, 'T' : 20,
                 'y' : 21, 'Y' : 21, 'u' : 22, 'U' : 22, 'i' : 23, 'I' : 23, 'o' : 24, 'O' : 24, 'p' : 25, 'P' : 25,
                 'š' : 26, 'Š' : 26, 'đ' : 27, 'Đ' : 27, 'enter' : 28, 'Enter' : 28, 'ENTER' : 28, 'lctrl' : 29, 'Lctrl' : 29, 'LCTRL' : 29,
                 'a' : 30, 'A' : 30, 's' : 31, 'S' : 31, 'd' : 32, 'D' : 32, 'f' : 33, 'F' : 33, 'g' : 34, 'G' : 34,
                 'h' : 35, 'H' : 35, 'j' : 36, 'J' : 36, 'k' : 37, 'K' : 37, 'l' : 38, 'L' : 38, 'č' : 39, 'Č' : 39,
                 'ć' : 40, 'Ć' : 40, '`' : 41, 'lshift' : 42, 'Lshift' : 42, 'LSHIFT' : 42, 'ž' : 43, 'Ž' : 43,
                 'z' : 44, 'Z' : 44, 'x' : 45, 'X' : 45, 'c' : 46, 'C' : 46, 'v' : 47, 'V' : 47, 'b' : 48, 'B' : 48,
                 'n' : 49, 'N' : 49, 'm' : 50, 'M' : 50, ',' : 51, '.' : 52, '-' : 53, 'rshift' : 54, 'Rshift' : 54,
                 'RSHIFT' : 54, 'lalt' : 56, 'Lalt' : 56, 'LALT' : 56, 'space' : 57, 'Space' : 57, 'SPACE' : 57,
                 'f1' : 59, 'F1' : 59, 'f2' : 60, 'F2' : 60, 'f3' : 61, 'F3' : 61, 'f4' : 62, 'F4' : 62, 'f5' : 63,
                 'F5' : 63, 'f6' : 64, 'F6' : 64, 'f7' : 65, 'F7' : 65, 'f8' : 66, 'F8' : 66, 'f9' : 67, 'F9' : 67,
                 'f10' : 68, 'F10' : 68, 'capslock' : 58, 'Capslock' : 58, 'CAPSLOCK' : 58, 'numlock' : 69, 'Numlock' : 69,
                 'NUMLOCK' : 69, 'scrolllock' : 70, 'Scrolllock' : 70, 'SCROLLLOCK' : 70, 'KP7' : 71, 'kp7' : 71, 'KP8' : 72,
                 'kp8' : 72, 'KP9' : 73, 'kp9' : 73, 'kpminus' : 74, 'Kpminus' : 74, 'KPMINUS' : 74, 'kp4' : 75, 'KP4' : 75,
                 'kp5' : 76, 'KP5' : 76, 'kp6' : 77, 'KP6' : 77, 'kpplus' : 78, 'Kpplus' : 78, 'KPPLUS' : 78, 'kp1' : 79,
                 'KP1' : 79, 'kp2' : 80, 'KP2' : 80, 'kp3' : 81, 'KP3' : 81, 'kp0' : 82, 'KP0' : 82, 'Left' : 105, 'LEFT' : 105,
                 'left' : 105, 'Right' : 106, 'RIGHT' : 106, 'right' : 106, 'up' : 103 , 'UP' : 103, 'Up' : 103, 'down' : 108,
                 'Down' : 108, 'DOWN' : 108, 'end' : 107, 'End' : 107, 'END' : 107, 'home' : 102, 'Home' : 102, 'HOME' : 102,
                 'pageup' : 104, 'Pageup' : 104, 'PAGEUP' : 104, 'pagedown' : 109, 'Pagedown' : 109, 'PAGEDOWN' : 109, 'insert' : 110,
                 'Insert' : 110, 'INSERT' : 110, 'delete' : 111, 'Delete' : 111, 'DELETE' : 111, 'ralt' : 100, 'Ralt' : 100, 'RALT' : 100,
                 'rctrl' : 97, 'RCtrl' : 97, 'RCTRL' : 97, 'f11' : 87, 'F11' : 87, 'f12' : 88, 'F12' : 88}

en_key_code_dict = {'esc' : 1, '1' : 2, '2' : 3, '3' : 4, '4' : 5, '5' : 6, '6' : 7, '7' : 8, '8' : 9, '9' : 10, '0' : 11,
                 '-' : 12, '=' : 13, 'backspace' : 14, 'Backspace' : 14, 'BACKSPACE' : 14, 'tab' : 15, 'Tab' : 15, 'TAB' : 15,
                 'q' : 16, 'Q' : 16, 'w' : 17, 'W' : 17, 'e' : 18, 'E' : 18, 'r' : 19, 'R' : 19, 't' : 20, 'T' : 20,
                 'y' : 21, 'Y' : 21, 'u' : 22, 'U' : 22, 'i' : 23, 'I' : 23, 'o' : 24, 'O' : 24, 'p' : 25, 'P' : 25,
                 '{' : 26, '{' : 26, '}' : 27, '}' : 27, 'enter' : 28, 'Enter' : 28, 'ENTER' : 28, 'lctrl' : 29, 'Lctrl' : 29, 'LCTRL' : 29,
                 'a' : 30, 'A' : 30, 's' : 31, 'S' : 31, 'd' : 32, 'D' : 32, 'f' : 33, 'F' : 33, 'g' : 34, 'G' : 34,
                 'h' : 35, 'H' : 35, 'j' : 36, 'J' : 36, 'k' : 37, 'K' : 37, 'l' : 38, 'L' : 38, ';' : 39, ';' : 39,
                 '\'' : 40, '\'' : 40, '`' : 41, 'lshift' : 42, 'Lshift' : 42, 'LSHIFT' : 42, '\\' : 43, '\\' : 43,
                 'z' : 44, 'Z' : 44, 'x' : 45, 'X' : 45, 'c' : 46, 'C' : 46, 'v' : 47, 'V' : 47, 'b' : 48, 'B' : 48,
                 'n' : 49, 'N' : 49, 'm' : 50, 'M' : 50, ',' : 51, '.' : 52, '/' : 53, 'rshift' : 54, 'Rshift' : 54,
                 'RSHIFT' : 54, 'lalt' : 56, 'Lalt' : 56, 'LALT' : 56, 'space' : 57, 'Space' : 57, 'SPACE' : 57,
                 'f1' : 59, 'F1' : 59, 'f2' : 60, 'F2' : 60, 'f3' : 61, 'F3' : 61, 'f4' : 62, 'F4' : 62, 'f5' : 63,
                 'F5' : 63, 'f6' : 64, 'F6' : 64, 'f7' : 65, 'F7' : 65, 'f8' : 66, 'F8' : 66, 'f9' : 67, 'F9' : 67,
                 'f10' : 68, 'F10' : 68, 'capslock' : 58, 'Capslock' : 58, 'CAPSLOCK' : 58, 'numlock' : 69, 'Numlock' : 69,
                 'NUMLOCK' : 69, 'scrolllock' : 70, 'Scrolllock' : 70, 'SCROLLLOCK' : 70, 'KP7' : 71, 'kp7' : 71, 'KP8' : 72,
                 'kp8' : 72, 'KP9' : 73, 'kp9' : 73, 'kpminus' : 74, 'Kpminus' : 74, 'KPMINUS' : 74, 'kp4' : 75, 'KP4' : 75,
                 'kp5' : 76, 'KP5' : 76, 'kp6' : 77, 'KP6' : 77, 'kpplus' : 78, 'Kpplus' : 78, 'KPPLUS' : 78, 'kp1' : 79,
                 'KP1' : 79, 'kp2' : 80, 'KP2' : 80, 'kp3' : 81, 'KP3' : 81, 'kp0' : 82, 'KP0' : 82, 'Left' : 105, 'LEFT' : 105,
                 'left' : 105, 'Right' : 106, 'RIGHT' : 106, 'right' : 106, 'up' : 103 , 'UP' : 103, 'Up' : 103, 'down' : 108,
                 'Down' : 108, 'DOWN' : 108, 'end' : 107, 'End' : 107, 'END' : 107, 'home' : 102, 'Home' : 102, 'HOME' : 102,
                 'pageup' : 104, 'Pageup' : 104, 'PAGEUP' : 104, 'pagedown' : 109, 'Pagedown' : 109, 'PAGEDOWN' : 109, 'insert' : 110,
                 'Insert' : 110, 'INSERT' : 110, 'delete' : 111, 'Delete' : 111, 'DELETE' : 111, 'ralt' : 100, 'Ralt' : 100, 'RALT' : 100,
                 'rctrl' : 97, 'RCtrl' : 97, 'RCTRL' : 97, 'f11' : 87, 'F11' : 87, 'f12' : 88, 'F12' : 88}


def convert(in_file, out_file, use_en = True):
     i_handle = open(in_file,'r')
     o_handle = open(out_file,'w')
     default_dict = {}
     if use_en:
        default_dict = en_key_code_dict
     else:
        default_dict = hr_key_code_dict
     for line in i_handle:
        splits = line.rstrip().lower().split(" ")
        new_s = ""
        for i in range(0,len(splits)):
            if i == 0:
                new_s += str(joystick_button_dict[splits[i]])
            elif "+" in splits[i]:
                secondsplits = splits[i].rstrip().split("+")
                for j in range(0,len(secondsplits)-1):
                    new_s += secondsplits[j]
                    new_s += "+"
                new_s += str(default_dict[secondsplits[-1]])
            else:
                if splits[i] in default_dict:
                    new_s += str(default_dict[splits[i]])
                else:
                    new_s += splits[i]
            if i != (len(splits) - 1):
                new_s += ' '
        o_handle.write(new_s)
        o_handle.write('\n')


n = len(sys.argv)
if n < 2 or n > 3:
    print("Script takes one or two arguments. Input file path and output file path")
elif n == 2:
    convert(sys.argv[1],'./converted_config.txt')
else:
    convert(sys.argv[1],sys.argv[2])

