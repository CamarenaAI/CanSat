#include <BMP280_DEV.h>                           // Include the BMP280_DEV library

// Declare variables to store temperature, pressure, and altitude
float temperature, pressure, altitude;            
BMP280_DEV bmp280;                                // Create an instance of BMP280_DEV for I2C operation

void setup(){
  Serial.begin(115200);                           // Initialize serial communication at 115200 baud rate
  bmp280.begin(BMP280_I2C_ALT_ADDR);              // Initialize BMP280 with alternate I2C address (0x76) in SLEEP_MODE
  bmp280.setTimeStandby(TIME_STANDBY_2000MS);     // Set standby time to 2 seconds
  bmp280.startNormalConversion();                 // Start continuous conversion in NORMAL_MODE
}

void loop(){
  if (bmp280.getMeasurements(temperature, pressure, altitude)){   // Check if measurement is complete
    // Print measurement results to the serial monitor
    Serial.print(temperature);
    Serial.print(F("*C   "));
    Serial.print(pressure);
    Serial.print(F("hPa   "));
    Serial.print(altitude);
    Serial.println(F("m"));
  }
}