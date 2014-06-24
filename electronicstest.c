#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pigpio.h>                                     /*  I wasn't sure which I needed!   */


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

int main() {
    int ythrust;
    gpioInitialise();
    mygpioSetup();
    printf("gpio setup");
    while (1) {
        ythrust = 2000;
        gpioPWM(18, ythrust);
        printf("gpio 18 at 2000");
        sleep(5);
        ythrust = 1500;
        gpioPWM(18, ythrust);
        printf("gpio 18 at 1500");
        sleep(5);
        ythrust = 1000;
        gpioPWM(18, ythrust);
        printf("gpio 18 at 1000");
        sleep(5);
              }
    gpioTerminate();
    return 0;
           }
