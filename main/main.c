#include <stdio.h>
#include <inttypes.h>  // 用于正确的格式化输出
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_heap_caps.h"
#include "esp_chip_info.h"  // ESP-IDF v5.x 需要单独包含这个头文件
#include "esp_flash.h"      // 用于 flash 相关函数

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
    
    // 获取 flash 大小
    uint32_t flash_size;
    if (esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Failed to get flash size\n");
        flash_size = 0;
    }
    
    printf("Flash: %" PRIu32 "MB %s\n", flash_size / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    
    // 获取内存信息
    size_t heap_total = heap_caps_get_total_size(MALLOC_CAP_DEFAULT);
    size_t heap_free = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
    
    printf("Heap total: %zu bytes\n", heap_total);
    printf("Heap free: %zu bytes\n", heap_free);
    printf("Minimum free heap: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());
    
    // 获取芯片ID等信息
    printf("Chip model: %" PRIu32 "\n", chip_info.model);
    printf("Chip features: 0x%" PRIX32 "\n", chip_info.features);
    
    // 简单的闪烁任务
    // gpio_set_direction(48, GPIO_MODE_OUTPUT);
    
    int count = 0;
    while (1) {
        // gpio_set_level(48, count % 2);
        printf("Blink count: %d, Heap free: %zu bytes\n", 
               ++count, 
               heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
