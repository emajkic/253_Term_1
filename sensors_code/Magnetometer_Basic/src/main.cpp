#include <Wire.h>
#include <QMC5883LCompass.h>

QMC5883LCompass compass;

void setup() {
  Wire.begin(21, 22);      // Use default or adjust SDA/SCL pins as needed
  Serial.begin(115200);
  compass.init();

  // Optional: configure modes/smoothing
  compass.setMode(0x01, 0x08, 0x10, 0xC0);  // continuous, 100 Hz ODR, 2 G, OSR = 64
  compass.setSmoothing(5, true);
}

void loop() {
  compass.read();
  int x = compass.getX();
  int y = compass.getY();
  int z = compass.getZ();
  int az = compass.getAzimuth();

  // Normalize to 0–360°
  if (az < 0) az += 360;

  char dir[4];
  compass.getDirection(dir, az);

  Serial.printf("X:%d Y:%d Z:%d → Heading: %03d° (%s)\n", x, y, z, az, dir);
  delay(200);
}
