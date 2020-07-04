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
    struct button_press buttons[13];
    struct button_press axes[14];
    unsigned char local_buffer[32];
    int hidraw_fd, js_fd;
    if(read_config_file("../../src/tools/converted_config.txt",buttons,axes) == -1 ) {
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
            fill_sending_buffer(&buttons[js.number],local_buffer,32);
            write(hidraw_fd,local_buffer,sizeof(local_buffer));
        }
    }

    return 0;
}