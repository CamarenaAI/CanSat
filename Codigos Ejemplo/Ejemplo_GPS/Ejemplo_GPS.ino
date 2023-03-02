#include <TinyGPS++.h>          // Incluimos la libreria del GPS
#include <SoftwareSerial.h>     // Incluimos la libreria para el puerto serial

const int RX1 = 3, TX1 = 4;     // Definimos los pines que funcionaran como puerto serial
SoftwareSerial vke16(RX1, TX1); // RX=pin 3, TX=pin 4
TinyGPSPlus gps;                // azul       verde

void setup() {
  Serial.begin(9600);
  vke16.begin(9600);            // Esto abre las comunicaciones con el GPS.
  Serial.println("Conectando");
}

void loop() {
  while (vke16.available()){     // Si bien hay caracteres que vienen del GPS
    gps.encode(vke16.read());    // Esto alimenta los datos seriales NMEA en la biblioteca un carácter a la vez
  }
  if (gps.location.isUpdated()){ // De todos modos, esto se activará casi todo el tiempo, pero al menos lo reducirá solo después de que ingrese un paquete de datos NMEA
    // Obtenga la información más reciente del objeto GPS que se deriva de los datos enviados por la unidad GPS
    // Serial.println("Satellite Count:");
    // Serial.println(gps.satellites.value());
    Serial.print("L: ");
    Serial.print(gps.location.lat(), 6);
    // Serial.println(gps.location.lat(), 6);
    Serial.print("l: ");
    Serial.print(gps.location.lng(), 6);
    Serial.print(" Speed MPH: ");
    Serial.print(gps.speed.mph());
    Serial.print(" A: ");
    Serial.print(gps.altitude.meters());
    Serial.println("");
    // Serial.println(" ");
    // delay(1000);
  }
}
