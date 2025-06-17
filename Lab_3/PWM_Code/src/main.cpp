// reads an analog signal on pin 36 (ADC1_CHANNEL_0)
// writes a pwm signal to pin 4 (with LED and series resistor connected from LAB 0) whos dutycycle is proportional to the read analog value 

#include <Arduino.h>
#include "driver/ledc.h"
#include "driver/adc.h"

#define pwmChannel1 1

#define dir 4
#define pwm 2

#define CW HIGH
#define CCW LOW

int pot_read = 0;

void setup() {
  adc1_config_width(ADC_WIDTH_12Bit);
  adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_12); // ADC1_CHANNEL_0 = pin 36
  ledcSetup(pwmChannel1,5000,12); // (pwmchannel to use,  frequency in Hz, number of bits)
  ledcAttachPin(pwm,pwmChannel1);
}

void loop() {
  pot_read = adc1_get_raw(ADC1_CHANNEL_0); // reads the analog value of ADC1_CHANNEL_0 (pin 36)
  ledcWrite(pwmChannel1,pot_read); // writes a dutycycle to the specified pwmchannel (which in this case was linked to pin 4)
  
  delay(10); // brief delay of 10ms
}