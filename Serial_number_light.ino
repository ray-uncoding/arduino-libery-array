#include <FastLED.h>
#define NUM_LEDS  16 // 假設有16個LED燈
#define DATA_PIN  3
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];
bool groupA[NUM_LEDS]; // 儲存A組LED的狀態
bool groupB[NUM_LEDS]; // 儲存B組LED的狀態

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600); // 開始序列通信，設定波特率為9600
  resetGroups(); // 初始化LED組的狀態
}

void resetGroups() {
  for (int i = 0; i < NUM_LEDS; i++) {
    groupA[i] = false;
    groupB[i] = false;
  }
}

void loop() { 
  if (Serial.available() > 0) { // 檢查是否有可用的序列數據
    String command = Serial.readStringUntil(' '); // 讀取命令
    if (command == "A") {
      while (Serial.available()) {
        int ledNum = Serial.parseInt(); // 讀取LED號碼
        if (ledNum >= 0 && ledNum < NUM_LEDS) {
          groupA[ledNum] = true; // 設定A組LED狀態
        }
      }
    } else if (command == "B") {
      while (Serial.available()) {
        int ledNum = Serial.parseInt(); // 讀取LED號碼
        if (ledNum >= 0 && ledNum < NUM_LEDS) {
          groupB[ledNum] = true; // 設定B組LED狀態
        }
      }
    } else if (command == "O") {
      String groupName = Serial.readStringUntil(' '); // 讀取要開啟的組別
      if (groupName == "A") {
        for (int i = 0; i < NUM_LEDS; i++) {
          if (groupA[i]) {
            leds[i] = CRGB::Red; // 使用紅色表示亮起的LED
          }
        }
      } else if (groupName == "B") {
        for (int i = 0; i < NUM_LEDS; i++) {
          if (groupB[i]) {
            leds[i] = CRGB::Blue; // 使用藍色表示亮起的LED
          }
        }
      }
      FastLED.show(); // 顯示LED效果
    } else if (command == "R") {
      resetGroups(); // 重置組的狀態
      FastLED.show(); // 顯示LED效果
    }
  }
}
