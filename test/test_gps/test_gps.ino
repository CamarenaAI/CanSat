#include <TinyGPS++.h>          // Include the GPS library
#include <SoftwareSerial.h>     // Include the library for serial communication

const int RX1 = 3, TX1 = 4;     // Define the pins used for the serial port
SoftwareSerial vk16e(RX1, TX1); // RX=pin 3, TX=pin 4
TinyGPSPlus gps;                // Create a TinyGPSPlus object to process GPS data

void setup() {
  Serial.begin(9600);           // Initialize serial communication at 9600 baud rate
  vk16e.begin(9600);            // Open communication with the GPS module
  Serial.println("Connecting"); // Print a message indicating connection
}

void loop() {
  while (vk16e.available()){     // Check if there are incoming characters from the GPS module
    gps.encode(vk16e.read());    // Feed NMEA serial data into the library one character at a time
  }
  
  if (gps.location.isUpdated()){ // Check if new GPS data has been received and processed
    // Retrieve the latest GPS information
    Serial.print("Latitude: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" Longitude: ");
    Serial.print(gps.location.lng(), 6);
    Serial.print(" Speed (MPH): ");
    Serial.print(gps.speed.mph());
    Serial.print(" Altitude (m): ");
    Serial.print(gps.altitude.meters());
    Serial.println("");
  }
}