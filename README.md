# 📡 CanSat - Mini Satellite in a Can

A CanSat is a miniature satellite with the size and shape of a soda can ("Can" in English). It is used to conduct scientific and technological experiments in the atmosphere or space.

Once launched from a rocket or drone, the CanSat deploys and begins transmitting data and measurements to Earth via radios and other communication systems.

## 🛰 CanSat Components

A CanSat typically includes the following essential components:

- 🔬 Sensors (pressure, temperature, humidity, acceleration, GPS)
- 📊 Measurement devices to collect environmental data
- 📡 Communication systems to transmit real-time telemetry
- ⚙️ Other electronic equipment depending on the experiment design


## 🔌 Arduino Libraries Used

This project utilizes the following Arduino libraries to interface with the sensors:

| 📚 Library  | 📌 Description                                     | 🧑‍💻 Author     |
| ----------- | --------------------------------------------------- | --------------- |
| BMP280_DEV  | Controls the BMP280 pressure and temperature sensor | Martin Lindupp  |
| TinyGPSPlus | Processes GPS data from the VK16E module            | Mikal Hart      |
| DTH22       | Controls the DTH22 Humidity and temparature sensor  | Adafruit        |
| INA129      | Measure battery voltage and current consumption     | Adafruit        |