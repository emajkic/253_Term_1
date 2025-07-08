#include <Arduino.h>

#define QRD_PIN_L 33
#define QRD_PIN_R 32

int ref_right;
int ref_left;

void setup() {
  Serial.begin(9600);

  pinMode(QRD_PIN_L, INPUT);
  pinMode(QRD_PIN_R, INPUT);
}

void loop() {
  ref_left = digitalRead(QRD_PIN_L);
  ref_right = digitalRead(QRD_PIN_R);

  Serial.print("Left: ");
  Serial.println(ref_left);

  Serial.print("Right: ");
  Serial.println(ref_right);
  
  delay(100);
}