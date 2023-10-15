#include "AS726X.h"

AS726X sensor;
const short decimals = 3;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  sensor.begin();
  sensor.setGain(3);
  sensor.setIntegrationTime(50);
}

void loop() {
  if (Serial.available() && Serial.readString() == "get") {
    String buff = "";
    sensor.takeMeasurementsWithBulb();
    buff += String(sensor.getCalibratedR(), decimals) + ",";
    buff += String(sensor.getCalibratedS(), decimals) + ",";
    buff += String(sensor.getCalibratedT(), decimals) + ",";
    buff += String(sensor.getCalibratedU(), decimals) + ",";
    buff += String(sensor.getCalibratedV(), decimals) + ",";
    buff += String(sensor.getCalibratedW(), decimals);
    Serial.println(buff);
  }
}
