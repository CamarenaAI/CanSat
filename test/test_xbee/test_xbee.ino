#define Temperature 25
#define Humidity 42
#define Pressure 1020.3
#define Altitude 0
#define Lat 20.286389
#define Lon -103.336389
#define Battery 82

#include <SoftwareSerial.h>
SoftwareSerial xbee(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);
  Serial.println("XBee Ready...");
}

void loop() {
  // Build the entire message into a single string
  String data = "T:" + String(Temperature) +
                   ", H:" + String(Humidity) +
                   ", P:" + String(Pressure) +
                   ", A:" + String(Altitude) +
                   ", Lat:" + String(Lat, 6) +
                   ", Lon:" + String(Lon, 6) +
                   ", B:" + String(Battery);

  // Display on serial monitor
  Serial.println(data);

  // Send via XBee to the coordinator
  xbee.println(data);

  delay(1000);
}