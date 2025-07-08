#include <Arduino.h>
#include <QMC5883LCompass.h>

QMC5883LCompass compass;

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22); // if needed, specify pins like Wire.begin(SDA, SCL);

    compass.init();
}

void loop() {
    compass.read(); // Updates internal X, Y, Z and azimuth values
    int heading = compass.getAzimuth();

    Serial.print("Heading: ");
    Serial.print(heading);
    Serial.println("°");

    delay(500);
}
