#include "SparkFun_AS7265X.h"

AS7265X sensor;

const short decimals = 3;

void setup() {
  Serial.begin(115200);

  if (sensor.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
    while (1)
      ;
  }

  sensor.setGain(3);
  sensor.setIntegrationCycles(50);

  sensor.disableIndicator();
}

void loop() {
  if (Serial.available() && Serial.readString() == "get") {
    String buff = "";
    
    // Take UV measurements
    sensor.enableBulb(AS7265x_LED_UV);
    sensor.takeMeasurements();
    sensor.disableBulb(AS7265x_LED_UV);

    buff += String(sensor.getCalibratedA(), decimals) + ","; //410nm
    buff += String(sensor.getCalibratedB(), decimals) + ","; //435nm
    buff += String(sensor.getCalibratedC(), decimals) + ","; //460nm
    buff += String(sensor.getCalibratedD(), decimals) + ","; //485nm
    buff += String(sensor.getCalibratedE(), decimals) + ","; //510nm
    buff += String(sensor.getCalibratedF(), decimals) + ","; //535nm

    // Take VIS measurements
    sensor.enableBulb(AS7265x_LED_WHITE);
    sensor.takeMeasurements();
    sensor.disableBulb(AS7265x_LED_WHITE);

    buff += String(sensor.getCalibratedG(), decimals) + ","; //560nm
    buff += String(sensor.getCalibratedH(), decimals) + ","; //585nm
    buff += String(sensor.getCalibratedR(), decimals) + ","; //610nm
    buff += String(sensor.getCalibratedI(), decimals) + ","; //645nm
    buff += String(sensor.getCalibratedS(), decimals) + ","; //680nm
    buff += String(sensor.getCalibratedJ(), decimals) + ","; //705nm

    // Take IR measurements
    sensor.enableBulb(AS7265x_LED_IR);
    sensor.takeMeasurements();
    sensor.disableBulb(AS7265x_LED_IR);

    buff += String(sensor.getCalibratedT(), decimals) + ","; //730nm
    buff += String(sensor.getCalibratedU(), decimals) + ","; //760nm
    buff += String(sensor.getCalibratedV(), decimals) + ","; //810nm
    buff += String(sensor.getCalibratedW(), decimals) + ","; //860nm
    buff += String(sensor.getCalibratedK(), decimals) + ","; //900nm
    buff += String(sensor.getCalibratedL(), decimals) + ","; //940nm

    // Get temperature
    buff += String(sensor.getTemperatureAverage(), decimals);

    Serial.println(buff);
  }
}
