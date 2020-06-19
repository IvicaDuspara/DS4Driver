#ifndef DS4DRIVER_MAPPER_H
#define DS4DRIVER_MAPPER_H
#include "button_press.h"
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
#endif //DS4DRIVER_MAPPER_H
