// Board: STM32 BluePill
// OLED:  SSD1306 128x64 I2C
// SDA -> PB7
// SCL -> PB6
// VCC -> 3.3V ONLY
// GND -> GND
//
// Libraries required (install via Arduino Library Manager):
//   Adafruit SSD1306
//   Adafruit GFX Library
//
// Note: Uses STM32duino core. I2C1 default pins. 3.3V logic only.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../../assets/image_bitmap.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET   -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void slideInFromRight() {
  for (int x = SCREEN_WIDTH; x >= 0; x -= 4) {
    display.clearDisplay();
    display.drawBitmap(x, 0, myImage, IMG_WIDTH, IMG_HEIGHT, WHITE);
    display.display();
    delay(15);
  }
  display.clearDisplay();
  display.drawBitmap(0, 0, myImage, IMG_WIDTH, IMG_HEIGHT, WHITE);
  display.display();
}

void setup() {
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    while (true);   // Halt — check wiring or I2C address
  }

  display.clearDisplay();
  slideInFromRight();
}

void loop() {
  // Image stays on screen until the board is reset
}
