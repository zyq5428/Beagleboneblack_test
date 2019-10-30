#include "sht3x.h"

/**
 * TO USE CONSOLE OUTPUT (PRINTF) AND WAIT (SLEEP) PLEASE ADAPT THEM TO YOUR
 * PLATFORM
 */

int sht3x_init(void) {
    /* Initialize the i2c bus for the current platform */
    sensirion_i2c_init();

    /* Busy loop for initialization, because the main loop does not work without
     * a sensor.
     */
    while (sht3x_probe() != STATUS_OK) {
        printf("SHT sensor probing failed\n");
    }
    	printf("SHT sensor probing successful\n");

    while (1) {
        int32_t temperature, humidity;
        /* Measure temperature and relative humidity and store into variables
         * temperature, humidity (each output multiplied by 1000).
         */
        int8_t ret = sht3x_measure_blocking_read(&temperature, &humidity);
        if (ret == STATUS_OK) {
            printf("measured temperature: %0.2f degreeCelsius, "
                      "measured humidity: %0.2f percentRH\n",
                      temperature / 1000.0f,
                      humidity / 1000.0f); 
        } else {
            printf("error reading measurement\n");
        }
	
	sleep(1);
    }
    return 0;
}
