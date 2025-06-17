#include <Arduino.h>
#include "driver/ledc.h"
#include "driver/adc.h"
#include <Wire.h>
#include "driver/gpio.h"
#include <chrono>
#include <iostream>
#include <math.h>

using namespace std;

// reads an analog signal on pin 34 (ADC1_CHANNEL_0)
// writes a pwm signal to pin 4 (with LED and series resistor connected from LAB 0) whos dutycycle is proportional to the read analog value 

void setup() {
  Serial.begin(9600);
  adc1_config_width(ADC_WIDTH_12Bit);
  adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_12); // ADC1_CHANNEL_6 = pin 34
}

void loop() {
  int analog_signal[20];
  int n = 0;
  
  while (n < 20) {
    analog_signal[n] = adc1_get_raw(ADC1_CHANNEL_6);
    n++;
    delay(0.5);
  }

  double samples_per_time = n / 0.002;

  double one_kHz[2*n];
  double ten_kHz[2*n];

  //Generate 1kHz and 10kHz waves
  for (int i=0; i < 2*n; i++) {
    one_kHz[i] = sin(i*2*PI/samples_per_time);
    ten_kHz[i] = sin(i*10*2*PI/samples_per_time);
  }

  double one_kHz_corr[n];
  double ten_kHz_corr[n];

  //Perform correlation
  for (int k=0; k < n; k++) {
    one_kHz_corr[k] = 0;
    ten_kHz_corr[k] = 0;

    for (int i = 0; i < n; i++) {
      one_kHz_corr[k] += analog_signal[i]*one_kHz[k+i];
      ten_kHz_corr[k] += analog_signal[i]*ten_kHz[k+i];
    }
  }

  double max_1kHz_corr = 0;
  double max_10kHz_corr = 0;

  for (int i=0; i < n; i++) {
    if (one_kHz_corr[i] > max_1kHz_corr) {
      max_1kHz_corr = one_kHz_corr[i];
    } else if (ten_kHz_corr[i] > max_10kHz_corr) {
      max_10kHz_corr = ten_kHz_corr[i];
    } 
  }

  if (max_10kHz_corr > max_1kHz_corr) {
    Serial.println("10kHz (TEN)");
  } else if (max_1kHz_corr > max_10kHz_corr) {
    Serial.println("1 kHz (ONE)");
  } else {
    Serial.println("Weird");
  }

  delay(500);
}