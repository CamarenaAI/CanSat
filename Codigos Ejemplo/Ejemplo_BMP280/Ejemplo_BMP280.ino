#include <BMP280_DEV.h>                           // Incluimos la libreria BMP280_DEV.h
float temperature, pressure, altitude;            // Creamos las variable de temperatura, presion y altitud
BMP280_DEV bmp280;                                // Instanciar (crear) un objeto BMP280_DEV y configurarlo para la operación I2C

void setup(){
  Serial.begin(115200);                           // Inicializamos el puerto serial
  bmp280.begin(BMP280_I2C_ALT_ADDR);              // Inicialización predeterminada con dirección I2C alternativa (0x76), coloque el BMP280 en SLEEP_MODE
  bmp280.setTimeStandby(TIME_STANDBY_2000MS);     // Set the standby time to 2 seconds
  bmp280.startNormalConversion();                 // Inicie la conversión continua BMP280 en NORMAL_MODE
}

void loop(){
  if (bmp280.getMeasurements(temperature, pressure, altitude)){   // Comprobar si la medición está completa
    // Mostrar los resultados
    Serial.print(temperature);
    Serial.print(F("*C   "));
    Serial.print(pressure);
    Serial.print(F("hPa   "));
    Serial.print(altitude);
    Serial.println(F("m"));
  }
}
