#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/joystick.h>                             // lots of included headers because
                                                        //  I wasn't sure which I needed!

#define JS_EVENT_AXIS           0x02                    // joystick moved

int open_joystick(int fd) {                             // function to open the joystick

    fd = open ("/dev/input/js0", O_RDONLY | O_NONBLOCK);         // setting fd to open the joystick
        if (fd >= 0)                                             // in non blocking mode
            printf("Open Joystick Successful\n");                // should be commented out when implemented
        if (fd < 0)
            perror("/dev/input/js0");
    return fd;                                                   // functions like to return something
}

void read_joystick_axis(int fd, struct js_event js, int thrust, int js_range, float js_d, int js_m, int rudder) {    // another function, including the integer fd
                                                                              // and the instance js from struct js_event

    while (read (fd, &js, sizeof(js)) > 0) {                    // while there is a joystick event to read
        if (js.type == JS_EVENT_AXIS && js.number == 1) {       // and if that event is an axis event on the right axis */
            // printf ("Thrust Reading: %8hd\n", js.value          // print the values of it if uncommented
            thrust = -(js.value);
            thrust = (thrust/js_d)*js_m;               // variables used to make this value out of 2000
            printf ("0%d\n", thrust);
        }
        else if (js.type == JS_EVENT_AXIS && js.number == 2) {       // and if that event is an axis event on the right axis */
            // printf ("Rudder Reading: %8hd\n", js.value          // print the values of it if uncommented
            rudder = -(js.value);
            rudder = ((rudder+js_range)/js_d)*js_m;               // variables used to make this value out of 2000
            printf ("1%d\n", rudder);
        }
    }
}

void js_maths(int js_range, float js_d, int js_m) {            // giving the variables for the maths their values
    js_range = 32767;                                          // joystick base value
    js_d = 65.534;
    js_m = 2;
}

int main() {
    int fd;
    struct js_event js;
    int thrust;
    int rudder;
    int js_range;
    float js_d;
    int js_m;
    js_maths(js_range, js_d, js_m);
    fd = open_joystick(fd);
    while (1) {
        read_joystick_axis(fd, js, thrust, js_range, js_d, js_m, rudder);
        fflush(stdout);
    }
    return 0;
}
