#include <stdio.h> // printf
#include <unistd.h> // sleep

#include "linux_hw.h"
#include "oled_display.h"
#include "sht3x_example_usage.h"

/**
 * TO USE CONSOLE OUTPUT (PRINTF) AND WAIT (SLEEP) PLEASE ADAPT THEM TO YOUR
 * PLATFORM
 */

typedef struct SHT3x_Sensor_Param {
    int32_t temperature;
    int32_t humidity;
} SHT3x_Sensor_Param;

SHT3x_Sensor_Param Sht3x_Param;

int main(void) {
    /* Initialize the i2c bus for the current platform */
    oled_init();
    sht3x_init();

    while (1) {
        sht3x_detect(&(Sht3x_Param.temperature), &(Sht3x_Param.humidity));
        sht3x_display(Sht3x_Param.temperature, Sht3x_Param.humidity);
	    sleep(1);
    }
    return 0;
}