#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pigpio.h>

/*struct gpiovalues {
        int pin;     // Which pin to use
        int range;   // PWM range of pin
        int freq;    // PWM frequency
        int neutral; // Neutral position
        int pwm;     // Current pwm setting
        int change;  // Value to change pwm by
}; */

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
    if (gpioGetPWMfrequency(17, != 8000) {
        (gpioSetPWMfrequency(17, 8000));
   }
}

void value_reconfig(int rudder) {
    if (rudder > 2000) {
    rudder = rudder - 10000;
    }
}

int main(int argc, char const* argv[]) {
    char input[7];
    int thrust;
    int rudder;
    gpioInitialise();
    mygpioSetup();
//    while (1) {
    while (fgets(input, sizeof(input), stdin) != NULL) {
//        fgets(input, sizeof(input), stdin);
        int i;
        int len = strlen(input);
        int rem = 6;

        /* remove rem'th char from input */
        for (i = rem; i < len - 1; i++) input[i] = input[i + 1];
        if(i < len) input[i] = '\0';

        int rem2 = 6;

        /* remove rem2'th char from input */
        for (i = rem2; i < len - 1; i++) input[i] = input[i + 1];
        if(i < len) input[i] = '\0';


        int number = atoi(input);
        if (number > 2000){
           (rudder = number);
        }
        else if (number <= 2000){
            (thrust = number);
        }
        value_reconfig(rudder);
        
        gpioPWM(18, rudder);
        gpioPWM(17, thrust);
        
//        prinf("%d = rudder, %d + thrust", rudder, thrust);
//        fflush(stdout);    
   }
    gpioTerminate();
    return 0;
}
