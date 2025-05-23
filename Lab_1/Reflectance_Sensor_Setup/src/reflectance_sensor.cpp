#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "driver/gpio.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define PIN_REFLECTANCE_OUTPUT 12

#define WHITE 0
#define BLACK 1

volatile bool reflectance;

void IRAM_ATTR reflectance_change_ISR() {
  reflectance = gpio_get_level((gpio_num_t)PIN_REFLECTANCE_OUTPUT);
}

void OledSetup(){
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
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
  pinMode(PIN_REFLECTANCE_OUTPUT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_REFLECTANCE_OUTPUT), reflectance_change_ISR, CHANGE);
  reflectance = digitalRead(PIN_REFLECTANCE_OUTPUT);
}


void loop() {
  if (reflectance == WHITE) {
    // means that we are somewhat on high reflectance ie "white" by definition in hardware
    display_handler.setCursor(0,0);
    display_handler.clearDisplay();
    display_handler.print("High reflectance (white)"); 
    display_handler.display();
  } else {
    display_handler.setCursor(0,0);
    display_handler.clearDisplay();
    display_handler.print("Low reflectance (black)"); 
    display_handler.display();
  }

  delay(500);
}

