#include <FastLED.h>
#define NUM_LEDS  10
#define DATA_PIN  3
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600); // 開始序列通信，設定波特率為9600
}

void loop() { 
  if (Serial.available() > 0) {         // 檢查是否有可用的序列數據
    int intensity = Serial.parseInt();  // 讀取序列數據並轉換為整數
    // 確保強度在1到10之間
    if (intensity < 1) {
      intensity = 1;
    } else if (intensity > 10) {
      intensity = 10;
    }
    // 開啟1到10顆LED燈，其餘關閉
    for (int i = 0; i < NUM_LEDS; i++) {
      if (i < intensity) {
        leds[i] = CRGB::Red;    // 使用紅色表示亮起的LED
      } else {
        leds[i] = CRGB::Black;  // 使用黑色表示關閉的LED
      }
    }
    FastLED.show(); // 顯示LED效果
  }
}
