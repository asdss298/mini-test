#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_heap_caps.h"

void app_main(void)
{
    printf("================================\n");
    printf("ESP32-S3 Minimal Test Program\n");
    printf("================================\n");
    
    // 获取芯片信息
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    
    printf("Chip: %s Rev %d\n", CONFIG_IDF_TARGET, chip_info.revision);
    printf("CPU cores: %d\n", chip_info.cores);
    printf("Flash: %dMB %s\n", spi_flash_get_chip_size() / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    
    // 获取内存信息
    size_t heap_total = heap_caps_get_total_size(MALLOC_CAP_DEFAULT);
    size_t heap_free = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
    
    printf("Heap total: %d bytes\n", heap_total);
    printf("Heap free: %d bytes\n", heap_free);
    printf("Minimum free heap: %d bytes\n", esp_get_minimum_free_heap_size());
    
    // 简单的闪烁任务
    // gpio_set_direction(48, GPIO_MODE_OUTPUT);
    
    int count = 0;
    while (1) {
        // gpio_set_level(48, count % 2);
        printf("Blink count: %d, Heap free: %d\n", ++count, heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}
