/** 
 @author Mateusz Szpot
 @brief My first code using RTOS in ESP32. 
 @brief It is only a demo to test functionality.
*/ 

#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


static uint8_t enable = 0;  // Global variable shared amongs tasks

// task for blinking red LED every second
void blinkRed(void* arg){
    while(1){
        gpio_set_level(GPIO_NUM_14, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_14, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// task for blinking yellow LED every 1/4 of a second if enable is set
void blinkYellow(void* arg){
    while(1){
        if(enable){
            gpio_set_level(GPIO_NUM_26, 1);
            vTaskDelay(250 / portTICK_PERIOD_MS);
            gpio_set_level(GPIO_NUM_26, 0);
            vTaskDelay(250 / portTICK_PERIOD_MS);
        }else{
            vTaskDelay(500 / portTICK_PERIOD_MS);   // prevents loop from taking too much CPU time 
        }
    }
    
}


void app_main(void){
    
    gpio_config_t pinConfig;

    // output pin configuration (14 and 26)
    pinConfig.pin_bit_mask = ((1ULL << 14) | (1ULL << 26));
    pinConfig.mode = GPIO_MODE_OUTPUT;
    pinConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
    pinConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    pinConfig.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&pinConfig);

    // input pin configuration
    pinConfig.pin_bit_mask = (1ULL << 25);
    pinConfig.mode = GPIO_MODE_INPUT;
    pinConfig.pull_up_en = GPIO_PULLUP_ENABLE;
    pinConfig.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&pinConfig);
    
    // dumping info into monitor
    gpio_dump_io_configuration(stdout, (1ULL << 14) | (1ULL << 26) | (1ULL << 25) );

    // tasks creation
    xTaskCreatePinnedToCore(blinkRed, "RED", 2048, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(blinkYellow, "YELLOW", 2048, NULL, 2, NULL, 0);

    while(1){
        // here the button hooked up to pin 25 is setting variable button
        if(gpio_get_level(GPIO_NUM_25) == 0){
            enable = 1;
        }else{
            enable = 0;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);

    }

}