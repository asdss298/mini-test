#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_chip_info.h"
// 新增：堆内存特性定义，用于区分片内/片外内存（部分IDF版本需显式引入，兼容用）
#include "esp_heap_caps.h"

// 日志标签，方便串口过滤
#define TAG "S3-MINI-TEST"
// ESP32-S3最小系统测试LED引脚（自定义，无硬件可注释下方宏和LED相关代码）
#define LED_GPIO GPIO_NUM_48

void app_main(void)
{
    // 1. 基础信息打印（原功能保留）
    ESP_LOGI(TAG, "ESP32-S3 Minimal System Test Start!");
    // ESP_LOGI(TAG, "Chip Model: %s", esp_get_chip_model_name());
    ESP_LOGI(TAG, "IDF Version: %s", esp_get_idf_version());

    // 2. 新增：详细内存状态打印（核心：SPRAM+片内DRAM+默认堆）
    size_t spiram_total = esp_get_spiram_size();          // SPRAM总大小
    size_t spiram_free  = esp_get_free_spiram_size();     // SPRAM可用大小
    size_t dram_free    = heap_caps_get_free_size(MALLOC_CAP_INTERNAL); // 片内DRAM可用
    size_t heap_free    = esp_get_free_heap_size();       // 默认堆可用（片内+SPRAM）

    // 打印SPRAM核心状态（无SPRAM时会提示“未配置SPRAM”）
    if (spiram_total > 0)
    {
        ESP_LOGI(TAG, "================= SPRAM STATUS =================");
        ESP_LOGI(TAG, "SPRAM Total Size: %d KB (%.2f MB)", spiram_total/1024, (float)spiram_total/1024/1024);
        ESP_LOGI(TAG, "SPRAM Free Size : %d KB (%.2f MB)", spiram_free/1024, (float)spiram_free/1024/1024);
        ESP_LOGI(TAG, "SPRAM Used Rate : %.1f %%", (1 - (float)spiram_free/spiram_total) * 100);
    }
    else
    {
        ESP_LOGW(TAG, "================= SPRAM STATUS =================");
        ESP_LOGW(TAG, "No SPRAM configured on this ESP32-S3 module!");
    }

    // 打印片内DRAM和默认堆信息（对比片内/片外内存使用）
    ESP_LOGI(TAG, "================= DRAM/HEAP STATUS =================");
    ESP_LOGI(TAG, "Internal DRAM Free: %d KB", dram_free/1024);
    ESP_LOGI(TAG, "Default Heap Free : %d KB (Internal + SPRAM)", heap_free/1024);
    ESP_LOGI(TAG, "====================================================");

    // 3. LED闪烁配置（原功能保留，无硬件可注释）
    //gpio_reset_pin(LED_GPIO);
    //gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    // 4. 无限循环（原功能保留）
    while (1)
    {
        //gpio_set_level(LED_GPIO, 1); // LED亮
        ESP_LOGI(TAG, "LED ON");
        vTaskDelay(pdMS_TO_TICKS(1000)); // 延时1秒

        //gpio_set_level(LED_GPIO, 0); // LED灭
        ESP_LOGI(TAG, "LED OFF");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}