#include <stdio.h>

int main() {
int thrust = 1000;
while (1) {
    thrust = thrust + 1;
    printf("0%d\n", thrust);
    fflush(stdout);
    sleep(0.5);
}
return 0;
}
