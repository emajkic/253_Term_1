#include <Arduino.h>
#include "driver/ledc.h"
#include "driver/adc.h"
#include "driver/gpio.h"

int left_read;
int right_read;

#define LEFT ADC1_CHANNEL_6
#define RIGHT ADC1_CHANNEL_7

void setup() {
  Serial.begin(9600);
  adc1_config_width(ADC_WIDTH_12Bit);
  adc1_config_channel_atten(LEFT,ADC_ATTEN_DB_12); // pin 34
  adc1_config_channel_atten(RIGHT,ADC_ATTEN_DB_12); // pin 35
}

void loop() {
  left_read = adc1_get_raw(LEFT); 
  //delay(10);
  right_read = adc1_get_raw(RIGHT);
  delay(10); 

  Serial.print("LEFT: ");
  Serial.println(left_read);
  Serial.print("RIGHT: ");
  Serial.println(right_read);

  delay(600);
}
