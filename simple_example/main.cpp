#include <stdio.h>
#include "pico/stdlib.h"

#include "dfPlayerDriver.h"

int main()
{
    stdio_init_all();

    DfPlayerPico dfp;

    dfp.reset();
    sleep_ms(2000);

    dfp.specifyVolume(18);
    sleep_ms(200);

    dfp.setRepeatPlay(true);
    sleep_ms(200);

    dfp.next();
    sleep_ms(200);

    puts("Hello, world!");

    while(1)
    {
        sleep_ms(1000);
    }
}
