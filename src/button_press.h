#ifndef DS4DRIVER_BUTTON_PRESS_H
#define DS4DRIVER_BUTTON_PRESS_H
#define DS4_BUTTON_NO 13
#define DS4_AXES_NO 14
#define CFGLINE_BUFFER_SIZE 50
#include <linux/string.h>
struct button_press {
    int key_code;
    unsigned char RGB[3];
    struct button_modifiers {
        unsigned char ctrl_mod : 1;
        unsigned char shift_mod : 1;
        unsigned char alt_mod : 1;
    }modifiers;
    short key_no;
    unsigned char h_motor_v;
    unsigned char l_motor_v;
};

struct button_press generate_button_press_struct(char* parsed_input) {
    struct button_press bp;
    int i = 0;
    char *split = strsep(&parsed_input, " ");
    unsigned char hm_marked = 0;
    while(split != NULL) {
        if(i == 0) {
            sscanf(split, "%hd", &bp.key_no);
        }
        else if(i == 1) {
            char *second_split = strsep(&split, "+");
            if(second_split == NULL) {
                sscanf(second_split, "%d", &bp.key_code);
            }
            else {
                while(second_split != NULL) {
                    if(strcmp(second_split, "ctrl") == 0) {
                        bp.modifiers.ctrl_mod = 1;
                    }
                    else if(strcmp(second_split, "shift") == 0) {
                        bp.modifiers.shift_mod = 1;
                    }
                    else if(strcmp(second_split, "alt") == 0) {
                        bp.modifiers.alt_mod = 1;
                    }
                    else {
                        sscanf(second_split, "%d", &bp.key_code);
                    }
                    second_split = strsep(&split, "+");
                }
            }
        }
        else {
            if(strchr(split,'#') != NULL) {
                int red,green,blue;
                sscanf(split, "#%02x%02x%02x", &red, &green, &blue);
                bp.RGB[0] = red;
                bp.RGB[1] = green;
                bp.RGB[2] = blue;
            }
            else {
                int m_val;
                sscanf(split, "%d", &m_val);
                if(hm_marked == 0) {
                    hm_marked = 1;
                    bp.h_motor_v = m_val;
                }
                else {
                    bp.l_motor_v = m_val;
                }
            }
        }
        split = strsep(&parsed_input, " ");
        i++;
    }
    return bp;
}

#endif //DS4DRIVER_BUTTON_PRESS_H
