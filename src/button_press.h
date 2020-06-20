#ifndef DS4DRIVER_BUTTON_PRESS_H
#define DS4DRIVER_BUTTON_PRESS_H
#define DS4_FIRST_BUTTON 0
#define DS4_LAST_BUTTON 24
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

int parse_to_base10_integer(const char* number, unsigned long length) {
    int base = 1;
    int result = 0;
    if(strlen(number) == length) {
        for(unsigned long i = strlen(number) - 1; i >= 0; i--) {
            int val = *(number + i) - '0';
            result += base*val;
            base*=10;
        }
        return result;
    }
    else {
        return -1;
    }
}

void parse_rgb(const char* number, struct button_press* bp) {
    if(strlen(number) != 7) {
        //TODO handle error
    }
    bp->RGB[0] = *(number + 1) * 10 + *(number + 2);
    bp->RGB[1] = *(number + 3) * 10 + *(number + 4);
    bp->RGB[2] = *(number + 5) * 10 + *(number + 6);
}

struct button_press generate_button_press_struct(char* parsed_input) {
    struct button_press bp;
    int i = 0;
    char *split = strsep(&parsed_input, " ");
    unsigned char hm_marked = 0;
    while(split != NULL) {
        if(i == 0) {
            int parsed = parse_to_base10_integer(split,strlen(split));
            if(parsed < DS4_FIRST_BUTTON || parsed > DS4_LAST_BUTTON) {
                //TODO error handling.
            }
            else {
                bp.key_no = (short) parsed;
            }
        }
        else if(i == 1) {
            char *second_split = strsep(&split, "+");
            if(second_split == NULL) {
              int parsed = parse_to_base10_integer(second_split,strlen(second_split));
              bp.key_code = parsed;
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
                        int parsed = parse_to_base10_integer(second_split,strlen(second_split));
                        bp.key_code = parsed;
                    }
                    second_split = strsep(&split, "+");
                }
            }
        }
        else {
            if(strlen(split) == 3) {
                int mval = parse_to_base10_integer(split,strlen(split));
                if(hm_marked == 0) {
                    hm_marked = 1;
                    bp.h_motor_v = mval;
                }
                else {
                    bp.l_motor_v = mval;
                }
            }
            else {
               parse_rgb(split,&bp);
            }
        }
        split = strsep(&parsed_input, " ");
        i++;
    }
    return bp;
}

#endif //DS4DRIVER_BUTTON_PRESS_H
