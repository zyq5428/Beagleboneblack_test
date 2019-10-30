#include <stdio.h> // printf
#include <unistd.h> // sleep

#include "oled_display.h"
#include "sht3x_example_usage.h"

/**
 * TO USE CONSOLE OUTPUT (PRINTF) AND WAIT (SLEEP) PLEASE ADAPT THEM TO YOUR
 * PLATFORM
 */

int main(void) {
    /* Initialize the i2c bus for the current platform */
    oled_init();
    sht3x_init();

    while (1) {
	    sleep(1);
    }
    return 0;
}