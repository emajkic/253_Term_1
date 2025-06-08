#include <Arduino.h>
#include "driver/ledc.h"
#include "driver/adc.h"
#include <Wire.h>
#include <iostream>

using namespace std;

// reads an analog signal on pin 34 (ADC1_CHANNEL_0)

void setup() {
  Serial.begin(9600);
  adc1_config_width(ADC_WIDTH_12Bit);
  adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_12); // ADC1_CHANNEL_6 = pin 34
}

void loop() {
  int hall_reading = adc1_get_raw(ADC1_CHANNEL_6);// reads an analog signal on pin 34 (ADC1_CHANNEL_0)

  Serial.println(hall_reading);
  
  delay(250);
    
}