#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/joystick.h>                             /* lots of included headers because */
#include <pigpio.h>                                     /*  I wasn't sure which I needed!   */

#define JS_EVENT_AXIS           0x02                    /* joystick moved */

void mygpioSetup() {
    if (gpioGetMode(18) != PI_OUTPUT) {
        (gpioSetMode(18, PI_OUTPUT));
    }
    if (gpioGetMode(17) != PI_OUTPUT) {
        (gpioSetMode(17, PI_OUTPUT));
    }
    if (gpioGetPWMrange(18) != 2000) {
        (gpioSetPWMrange(18, 2000));
    }
    if (gpioGetPWMrange(17) != 2000) {
        (gpioSetPWMrange(17, 2000));
    }
    if (gpioGetPWMfrequency(18) != 8000) {
        (gpioSetPWMfrequency(18, 8000));
    }
    if (gpioGetPWMfrequency(17) != 8000) {
        (gpioSetPWMfrequency(17, 8000));
   }
}

int open_joystick(int fd) {                             /* function to open the joystick */

    fd = open ("/dev/input/js0", O_RDONLY | O_NONBLOCK);         /* setting fd to open the joystick    */
        if (fd >= 0)                                             /* in non blocking mode    */
            printf("Open Joystick Successful\n");
        if (fd < 0)
            perror("/dev/input/js0");
    return fd;                                                   /* functions like to return something */
}

void read_joystick_thrust_axis(int fd, struct js_event js, int ythrust ) {    /* another function, including the integer fd  */
                                                                              /* and the instance js from struct js_event    */

    while (read (fd, &js, sizeof(js)) > 0) {                    /* while there is a joystick event to read */
        if (js.type == JS_EVENT_AXIS && js.number == 1) {       /* and if that event is an axis event on the right axis */
            //printf ("Thrust Reading: %8hd\n", js.value        /* print the values of it                  */
            ythrust = -(js.value);
            ythrust = ((ythrust+32767)/65.534)*2;               /* black magic here, I just wanted to make this value out of 2000 */
            printf ("Pwm Value: %d\n", ythrust);
       }
    }
}
int main() {
    int fd;
    struct js_event js;
    int ythrust;
    gpioInitialise();
    mygpioSetup();
    fd = open_joystick(fd);
    while (1) {
        read_joystick_thrust_axis(fd, js, ythrust);
        gpioPWM(17, ythrust);
              }
    gpioTerminate();
    return 0;
           }
