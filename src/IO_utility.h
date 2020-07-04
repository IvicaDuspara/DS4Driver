#ifndef DS4DRIVER_IO_UTILITY_H
#define DS4DRIVER_IO_UTILITY_H
#define SEND_BUFFER_LENGTH 32
#include "button_press.h"
#include <stdio.h>
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

int read_config_file(const char* file_name, struct button_press* buttons, struct button_press* axes) {
    int count = 0;
    char local_buffer[CFGLINE_BUFFER_SIZE];
    FILE* handle = fopen(file_name,"r");
    if(handle == NULL) {
        return -1;
    }
    while(fgets(local_buffer,CFGLINE_BUFFER_SIZE,handle) != NULL) {
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
}
#endif //DS4DRIVER_IO_UTILITY_H
