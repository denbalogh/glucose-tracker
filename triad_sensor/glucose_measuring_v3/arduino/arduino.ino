#include "SparkFun_AS7265X.h"

AS7265X sensor;

const short decimals = 2;
String sep = "|";

void setup() {
  Serial.begin(115200);

  if (sensor.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
    while (1)
      ;
  }

  sensor.disableIndicator();
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();

    // Getting temperature
    if (input == "temp") {
      
        String temp = String(sensor.getTemperatureAverage(), decimals);
        Serial.println(temp);
        
    // Getting VIS measurements
    } else if (input.substring(0, 3) == "get") {

        if(input == "get:UV"){
            sensor.enableBulb(AS7265x_LED_UV);
        } else if(input == "get:VIS"){
            sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_100MA, AS7265x_LED_WHITE);
            sensor.enableBulb(AS7265x_LED_WHITE);
        } else if(input == "get:IR"){
            sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_50MA, AS7265x_LED_IR);
            sensor.enableBulb(AS7265x_LED_IR);
        }

        sensor.takeMeasurements();

        sensor.disableBulb(AS7265x_LED_UV);
        sensor.disableBulb(AS7265x_LED_WHITE); //Turn off bulb to avoid heating sensor
        sensor.disableBulb(AS7265x_LED_IR);

        String buff = "";
        buff += String(sensor.getCalibratedA(), decimals) + sep; //410nm
        buff += String(sensor.getCalibratedB(), decimals) + sep; //435nm
        buff += String(sensor.getCalibratedC(), decimals) + sep; //460nm
        buff += String(sensor.getCalibratedD(), decimals) + sep; //485nm
        buff += String(sensor.getCalibratedE(), decimals) + sep; //510nm
        buff += String(sensor.getCalibratedF(), decimals) + sep; //535nm
        buff += String(sensor.getCalibratedG(), decimals) + sep; //560nm
        buff += String(sensor.getCalibratedH(), decimals) + sep; //585nm
        buff += String(sensor.getCalibratedI(), decimals) + sep; //610nm
        buff += String(sensor.getCalibratedJ(), decimals) + sep; //645nm
        buff += String(sensor.getCalibratedK(), decimals) + sep; //680nm
        buff += String(sensor.getCalibratedL(), decimals) + sep; //705nm
        buff += String(sensor.getCalibratedR(), decimals) + sep; //730nm
        buff += String(sensor.getCalibratedS(), decimals) + sep; //760nm
        buff += String(sensor.getCalibratedT(), decimals) + sep; //810nm
        buff += String(sensor.getCalibratedU(), decimals) + sep; //860nm
        buff += String(sensor.getCalibratedV(), decimals) + sep; //900nm
        buff += String(sensor.getCalibratedW(), decimals) + sep; //940nm

        // Get temperature
        buff += String(sensor.getTemperatureAverage(), decimals);

        Serial.println(buff);
    }
  }
}
