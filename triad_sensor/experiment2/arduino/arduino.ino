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

  sensor.disableIndicator();
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();

    // Getting temperature
    if (input == "temp") {
      
        String temp = String(sensor.getTemperatureAverage(), decimals);
        Serial.println(temp);
        
    //Input format get:[GAIN(1,2,3)],[LED_INTENSITY(min,mid,max)]
    } else if (input.substring(0, 4) == "get:") {
      
      int gain = input.substring(4, 5).toInt();
      String intensity = input.substring(6);

      if (gain >= 1 && gain <= 3) {
        String buff = "";

        sensor.setGain(gain);

        if(intensity == "min"){
            sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_12_5MA, AS7265x_LED_WHITE);
            sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_12_5MA, AS7265x_LED_IR);
        } else if(intensity == "mid"){
            sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_50MA, AS7265x_LED_WHITE);
            sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_25MA, AS7265x_LED_IR);
        } else if(intensity == "max") {
            sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_100MA, AS7265x_LED_WHITE);
            sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_50MA, AS7265x_LED_IR);
        }
        
        sensor.enableBulb(AS7265x_LED_WHITE);
        sensor.enableBulb(AS7265x_LED_IR);
      
        sensor.takeMeasurements();
      
        sensor.disableBulb(AS7265x_LED_WHITE); //Turn off bulb to avoid heating sensor
        sensor.disableBulb(AS7265x_LED_IR);

        buff += String(sensor.getCalibratedG(), decimals) + ","; //560nm
        buff += String(sensor.getCalibratedH(), decimals) + ","; //585nm
        buff += String(sensor.getCalibratedI(), decimals) + ","; //610nm
        buff += String(sensor.getCalibratedJ(), decimals) + ","; //645nm
        buff += String(sensor.getCalibratedK(), decimals) + ","; //680nm
        buff += String(sensor.getCalibratedL(), decimals) + ","; //705nm
        buff += String(sensor.getCalibratedR(), decimals) + ","; //730nm
        buff += String(sensor.getCalibratedS(), decimals) + ","; //760nm
        buff += String(sensor.getCalibratedT(), decimals) + ","; //810nm
        buff += String(sensor.getCalibratedU(), decimals) + ","; //860nm
        buff += String(sensor.getCalibratedV(), decimals) + ","; //900nm
        buff += String(sensor.getCalibratedW(), decimals) + ","; //940nm

        // Get temperature
        buff += String(sensor.getTemperatureAverage(), decimals);

        Serial.println(buff);
      }
    }
  }
}
