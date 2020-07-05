#ifndef DS4DRIVER_IO_UTILITY_H
#define DS4DRIVER_IO_UTILITY_H
#define SEND_BUFFER_LENGTH 32
#include "button_press.h"
#include <stdio.h>
int fill_default_buffer(unsigned char* default_buffer, const int* rgb, int buffer_length) {
    if(buffer_length < 32) {
        return -1;
    }
    for(int i = 0; i < buffer_length; i++) {
        default_buffer[i] = 0;
    }
    default_buffer[0] = 0x5;
    default_buffer[1] = 0x3F;
    default_buffer[4] = 0;
    default_buffer[5] = 0;
    default_buffer[6] = rgb[0];
    default_buffer[7] = rgb[1];
    default_buffer[8] = rgb[2];
    return 1;
}
int fill_sending_buffer(const struct button_press* bp, unsigned char* buffer, int buffer_length) {
    if(buffer_length < 32) {
        return -1;
    }
    for(int i = 0; i < buffer_length; i++) {
        buffer[i] = 0;
    }
    buffer[0] = 0x5;
    buffer[1] = 0x3F;
    buffer[4] = bp->l_motor_v;
    buffer[5] = bp->h_motor_v;
    buffer[6] = bp->RGB[0];
    buffer[7] = bp->RGB[1];
    buffer[8] = bp->RGB[2];
    return 1;
}

int read_config_file(const char* file_name, struct button_press* buttons, struct button_press* axes, int* rgb) {
    int count = 0;
    char local_buffer[CFGLINE_BUFFER_SIZE];
    FILE* handle = fopen(file_name,"r");
    if(handle == NULL) {
        return -1;
    }
    while(fgets(local_buffer,CFGLINE_BUFFER_SIZE,handle) != NULL) {
        if(strstr(local_buffer,"default:")) {
            sscanf(local_buffer,"default: #%02x%02x%02x",&rgb[0],&rgb[1],&rgb[2]);
            continue;
        }
        if(count < 6 || (count > 7 && count < 13)) {
            struct button_press temp_bp = generate_button_press_struct(local_buffer);
            buttons[temp_bp.key_no] = temp_bp;
        }
        else if(count > 12 && count < 17) {
            struct button_press temp_bp = generate_button_press_struct(local_buffer);
            axes[temp_bp.key_no - 13] = temp_bp;
        }
        else if(count > 16 && count < 21) {
            struct button_press temp_bp = generate_button_press_struct(local_buffer);
            axes[temp_bp.key_no - 12] = temp_bp;
        }
        else if(count > 20 && count < 25) {
            struct button_press temp_bp = generate_button_press_struct(local_buffer);
            axes[temp_bp.key_no - 11] = temp_bp;
        }
        else if(count == 6) {
            struct button_press temp_bp = generate_button_press_struct(local_buffer);
            buttons[temp_bp.key_no] = temp_bp;
            axes[4] = temp_bp;
        }
        else if(count == 7) {
            struct button_press temp_bp = generate_button_press_struct(local_buffer);
            buttons[temp_bp.key_no] = temp_bp;
            axes[9] = temp_bp;
        }
        count++;
    }
    fclose(handle);
    return 1;
}

void add_default_colors(struct button_press* buttons, struct button_press* axes, const int* rgb) {
    for(int i = 0; i < DS4_BUTTON_NO; i++) {
        if(buttons[i].RGB[0] == 0 && buttons[i].RGB[1] == 0 && buttons[i].RGB[2] == 0) {
            buttons[i].RGB[0] = rgb[0];
            buttons[i].RGB[1] = rgb[1];
            buttons[i].RGB[2] = rgb[2];
        }
    }
    for(int i = 0; i < DS4_AXES_NO; i++) {
        if(axes[i].RGB[0] == 0 && axes[i].RGB[1] == 0 && axes[i].RGB[2] == 0) {
            axes[i].RGB[0] = rgb[0];
            axes[i].RGB[1] = rgb[1];
            axes[i].RGB[2] = rgb[2];
        }
    }
}

void emit(int fd, int type, int code, int val){
    struct input_event ie;
    ie.type = type;
    ie.code = code;
    ie.value = val;
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;
    write(fd, &ie, sizeof(ie));
}

void prepare_uinput_io(int fd, struct button_press* buttons, struct button_press* axes) {
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    short alt_marked = 0, ctrl_marked = 0, shift_marked = 0;
    for(int i = 0; i < DS4_BUTTON_NO; i++) {
        if(alt_marked == 0 && buttons[i].modifiers.alt_mod == 1) {
            alt_marked = 1;
            ioctl(fd,UI_SET_KEYBIT,KEY_LEFTALT);
        }
        else if(ctrl_marked == 0 && buttons[i].modifiers.ctrl_mod == 1) {
            ctrl_marked = 1;
            ioctl(fd,UI_SET_KEYBIT,KEY_LEFTCTRL);
        }
        else if(shift_marked == 0 && buttons[i].modifiers.shift_mod == 1) {
            shift_marked = 1;
            ioctl(fd,UI_SET_KEYBIT,KEY_LEFTSHIFT);
        }
        ioctl(fd,UI_SET_KEYBIT,buttons[i].key_code);
    }
    for(int i = 0; i < DS4_AXES_NO; i++) {
        if(alt_marked == 0 && axes[i].modifiers.alt_mod == 1) {
            alt_marked = 1;
            ioctl(fd,UI_SET_KEYBIT,KEY_LEFTALT);
        }
        else if(ctrl_marked == 0 && axes[i].modifiers.ctrl_mod == 1) {
            ctrl_marked = 1;
            ioctl(fd,UI_SET_KEYBIT,KEY_LEFTCTRL);
        }
        else if(shift_marked == 0 && axes[i].modifiers.shift_mod == 1) {
            shift_marked = 1;
            ioctl(fd,UI_SET_KEYBIT,KEY_LEFTSHIFT);
        }
        ioctl(fd,UI_SET_KEYBIT,axes[i].key_code);
    }
}
#endif //DS4DRIVER_IO_UTILITY_H
