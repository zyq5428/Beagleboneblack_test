#include <stdlib.h>
#include <stdio.h> // printf
#include <unistd.h> // sleep
#include <pthread.h>

#include "linux_hw.h"
#include "oled_display.h"
#include "sht3x_example_usage.h"

typedef struct SHT3x_Sensor_Param {
    int32_t temperature;
    int32_t humidity;
} SHT3x_Sensor_Param;

SHT3x_Sensor_Param Sht3x_Param;

pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *oled_p(void *p)
{
    oled_init();
    for (;;) {
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&has_product, &lock);
        sht3x_display(Sht3x_Param.temperature, Sht3x_Param.humidity);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
}

void *sht3x_p(void *p)
{
    sht3x_init();
    for (;;) {
        pthread_mutex_lock(&lock);
        sht3x_detect(&(Sht3x_Param.temperature), &(Sht3x_Param.humidity));
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&has_product);
        sleep(1);
    }
}

int main(void) 
{ 
    pthread_t oid, sid;

    pthread_create(&oid, NULL, oled_p, NULL);
    pthread_create(&sid, NULL, sht3x_p, NULL);
    pthread_join(oid, NULL);
    pthread_join(sid, NULL);

    return 0;
}