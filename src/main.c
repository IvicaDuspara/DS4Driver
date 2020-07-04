#include <fcntl.h>
#include <linux/joystick.h>
#include <stdio.h>
#include <unistd.h>
#include "IO_utility.h"

int main (int argc, char** argv) {
    if(argc != 4 || strcmp("--help",argv[1]) == 0) {
        printf("Usage: ./ds4driver <path to /dev/js*> <path to /dev/hidraw*> <path to configuration file>");
        return 1;
    }
    struct button_press buttons[DS4_BUTTON_NO];
    struct button_press axes[DS4_AXES_NO];
    int default_rgb[3] = {0,0,255};
    int axes_offsets[] = {0,2,4,5,7,9,10,12};

    unsigned char local_buffer[SEND_BUFFER_LENGTH];
    int hidraw_fd, js_fd;
    if(read_config_file("../../tools/converted_config.txt",buttons,axes,default_rgb) == -1 ) {
        printf("Could not open configuration file at: %s\n",argv[3]);
        return 1;
    }

    unsigned char default_buffer[SEND_BUFFER_LENGTH];
    if(fill_default_buffer(default_buffer,default_rgb,SEND_BUFFER_LENGTH) == -1){
        printf("Error in filling buffer. Buffer is not large enough.\n");
        return 1;
    }

    js_fd = open(argv[1],O_RDONLY);
    if(js_fd == -1) {
        printf("Could not open %s. Can not communicate with joystick.\n",argv[1]);
        return 1;
    }
    hidraw_fd = open(argv[2],O_RDWR);
    if(hidraw_fd == -1) {
        printf("Could not open %s. Can not communicate with joystick.\n",argv[2]);
        return 1;
    }
    struct js_event js;
    write(hidraw_fd,default_buffer,sizeof(default_buffer));

    while(1) {
        if(read(js_fd,&js,sizeof(struct js_event)) != sizeof(struct js_event)) {
            perror("\nError in reading from joystick.\n");
            return 1;
        }
        if(js.type == 1) {
            if(js.value == 1) {
                if(fill_sending_buffer(&buttons[js.number],local_buffer,SEND_BUFFER_LENGTH) == -1) {
                    printf("Error in filling buffer. Buffer is not large enough.\n");
                    return 1;
                }
                write(hidraw_fd,local_buffer,sizeof(local_buffer));
            }
            else if(js.value == 0) {
                write(hidraw_fd,default_buffer,sizeof(default_buffer));
            }
        }
        else if(js.type == 2) {
            if(js.number != 2 && js.number != 5) {
                if(js.value < 0) {
                    if(fill_sending_buffer(&axes[axes_offsets[js.number]],local_buffer,SEND_BUFFER_LENGTH) == -1) {
                        printf("Error in filling buffer. Buffer is not large enough.\n");
                        return 1;
                    }
                    write(hidraw_fd,local_buffer,sizeof(local_buffer));
                }
                else if(js.value > 0) {
                    if(fill_sending_buffer(&axes[axes_offsets[js.number] + 1],local_buffer,SEND_BUFFER_LENGTH) == -1) {
                        printf("Error in filling buffer. Buffer is not large enough.\n");
                        return 1;
                    }
                    write(hidraw_fd,local_buffer,sizeof(local_buffer));
                }
                else {
                    write(hidraw_fd,default_buffer,sizeof(default_buffer));
                }
            }
            else if(js.number == 2 || js.number == 5) {
                if(js.value > -32767) {
                    if(fill_sending_buffer(&axes[axes_offsets[js.number]],local_buffer,SEND_BUFFER_LENGTH) == -1) {
                        printf("Error in filling buffer. Buffer is not large enough.\n");
                        return 1;
                    }
                    write(hidraw_fd,local_buffer,sizeof(local_buffer));
                }
                else {
                    write(hidraw_fd,default_buffer,sizeof(default_buffer));
                }
            }
        }
    }

    return 0;
}