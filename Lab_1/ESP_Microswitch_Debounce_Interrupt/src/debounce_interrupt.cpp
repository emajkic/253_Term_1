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

#define PIN_LIMIT_SWITCH 15

volatile bool switchPressed;
volatile bool lastState;
volatile int count;

void IRAM_ATTR switchPressedISR() {
  switchPressed = gpio_get_level((gpio_num_t)PIN_LIMIT_SWITCH);
  if (switchPressed && lastState == 0) {
    count++;
  }
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
  pinMode(PIN_LIMIT_SWITCH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_LIMIT_SWITCH), switchPressedISR, CHANGE);

  switchPressed = false;
  count = 0;
  lastState = 0;
}


void loop() {
  if (switchPressed) {
    display_handler.setCursor(0,0);
    display_handler.clearDisplay();
    display_handler.print("count: ");   
    display_handler.println(count);   
    display_handler.display();

    lastState = 1;
  } else {
    display_handler.setCursor(0,0);
    display_handler.clearDisplay();
    display_handler.print("count: ");
    display_handler.println(count);    
    display_handler.display();

    lastState = 0;
  }

  delay(500);
}

