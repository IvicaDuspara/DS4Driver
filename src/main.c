#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/joystick.h>
#include "IO_utility.h"

int main (int argc, char** argv) {
    if(argc != 4 || strcmp("--help",argv[1]) == 0) {
        printf("Usage: ./ds4driver <path to /dev/js*> <path to /dev/hidraw*> <path to configuration file>");
        return 1;
    }
    struct button_press buttons[DS4_BUTTON_NO];
    struct button_press axes[DS4_AXES_NO];
    unsigned char local_buffer[SEND_BUFFER_LENGTH];
    int hidraw_fd, js_fd;
    if(read_config_file(argv[3],buttons,axes) == -1 ) {
        printf("Could not open configuration file at: %s\n",argv[3]);
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
    while(1) {
        if(read(js_fd,&js,sizeof(struct js_event)) != sizeof(struct js_event)) {
            perror("\nError in reading from joystick.\n");
            return 1;
        }
        if(js.type == 1) {
            if(fill_sending_buffer(&buttons[js.number],local_buffer,SEND_BUFFER_LENGTH) == -1) {
                printf("Error in filling buffer. Buffer is not large enough.\n");
                return 1;
            }
            write(hidraw_fd,local_buffer,sizeof(local_buffer));
        }
    }

    return 0;
}