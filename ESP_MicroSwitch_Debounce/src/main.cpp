#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>#include "driver/gpio.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define PIN_LIMIT_SWITCH 15

bool switchPressed;

void OledSetup(){
  display_handler.display();
  delay(2000);
 
  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.display();
}

void setup() {
  OledSetup(); //setup OLED
  pinMode(PIN_LIMIT_SWITCH, INPUT_PULLUP);
  switchPressed = false;
}

void loop() {
  switchPressed = digitalRead(PIN_LIMIT_SWITCH);

  if (switchPressed) {
    display_handler.println("Switch pressed!");  
  } else {
    display_handler.println("Switch not pressed...");
  }

  delay(500);
}

