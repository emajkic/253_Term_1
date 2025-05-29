#include <Arduino.h>
#include "driver/ledc.h"
#include "driver/adc.h"
#include <Wire.h>
#include "driver/gpio.h"

String reflectance;

// reads an analog signal on pin 36 (ADC1_CHANNEL_0)
// writes a pwm signal to pin 4 (with LED and series resistor connected from LAB 0) whos dutycycle is proportional to the read analog value 

void setup() {
  Serial.begin(115200);
  adc1_config_width(ADC_WIDTH_12Bit);
  adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_12); // ADC1_CHANNEL_6 = pin 34
}

void loop() {
  reflectance = adc1_get_raw(ADC1_CHANNEL_6); // reads the analog value of ADC1_CHANNEL_0 (pin 36)
  delay(10); // brief delay of 10ms

  Serial.println(reflectance);

  delay(500);
}
