#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_heap_caps.h"
#include "esp_chip_info.h"

void app_main(void)
{
    printf("================================\n");
    printf("ESP32-S3 Minimal Test Program\n");
    printf("================================\n");
    
    // 获取芯片信息
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    
    printf("Chip: ESP32-S3 Rev %d\n", chip_info.revision);
    printf("CPU cores: %d\n", chip_info.cores);
    
    // 简化：不尝试获取flash大小
    printf("Flash: (size information)\n");
    
    // 获取内存信息
    size_t heap_total = heap_caps_get_total_size(MALLOC_CAP_DEFAULT);
    size_t heap_free = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
    
    printf("Heap total: %zu bytes\n", heap_total);
    printf("Heap free: %zu bytes\n", heap_free);
    
    // 简单的闪烁任务
    // gpio_set_direction(48, GPIO_MODE_OUTPUT);
    
    int count = 0;
    while (1) {
        // gpio_set_level(48, count % 2);
        printf("Loop count: %d, Heap free: %zu bytes\n", 
               ++count, 
               heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
