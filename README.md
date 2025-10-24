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

## XBee Configuration Guide
### Requirements
- 2x XBee Series 2 (XB24-B) modules  
- 1x XBee USB adapter (for the Coordinator)  
- 1x XBee adapter or shield (for the Router + Microcontroller)  
- 1x Microcontroler (Atmega328P)  
- Digi XCTU software (Linux, macOS, or Windows)  
- USB cables

---

### Add your modules in XCTU
1. Open **XCTU**.  
2. Click the **“Add radio module (+)”** icon.

<p align="center">
  <img src="/images/xctu_home.png" alt="add_module" />
</p>
<p align=center><em>Image 1. Add module</em></p>

3. Select the COM port of your XBee and click **Finish**.

<p align="center">
  <img src="/images/add_module.png" alt="select_port" />
</p>
<p align=center><em>Image 2. Select port</em></p>

4. Repeat for both modules (Coordinator and Router).  
5. Verify both appear in the **Radio Modules** list.
    - Click the **“Discover radio module (browse)”** icon.

<p align="center">
  <img src="/images/xbee_ports.png" alt="select_port" />
</p>
<p align=center><em>Image 3. Select ports to found XBee modules</em></p>

<p align="center">
  <img src="/images/xbee_port_parameters.png" alt="select_port_parameters" />
</p>
<p align=center><em>Image 4. Select port parameters</em></p>

<p align="center">
  <img src="/images/xbee.png" alt="select_xbee_module" />
</p>
<p align=center><em>Image 5. Select the Xbee module</em></p>

<p align="center">
  <img src="/images/xbee_modules.png" alt="xbee_modules" />
</p>
<p align=center><em>Image 6. Xbee modules</em></p>

---

### Identify firmware
In the **Radio Configuration** tab, check:
- **Product family:** XB24-ZB, XB24-B, or similar.  
- **Function set:** choose according to your firmware version:
  - *ZigBee Coordinator AT*
  - *ZigBee Router AT*
  - *(or ZNet 2.5 variants if available)*

<p align="center">
  <img src="/images/module_configuration.png" alt="module_configuration" />
</p>
<p align=center><em>Image 7. Radio Configuration</em></p>

---

### Coordinator configuration
Select the Coordinator module and set the following parameters:

| Parameter | Command | Value | Description |
|------------|----------|--------|--------------|
| PAN ID | `ID` | `1234` | Same network ID for all devices |
| Channel | `CH` | `C` | Common channel |
| Coordinator Enable | `CE` | `1` | Set as Coordinator |
| Destination Address High | `DH` | `0` | — |
| Destination Address Low | `DL` | `0` or `FFFF` | Receive from all routers |
| API Enable | `AP` | `0` | Transparent (text) mode |
| Baud Rate | `BD` | `3` (= 9600 bps) | Must match Arduino |
| Node Identifier | `NI` | `COORD` | Optional name |

Click **Write (pencil icon)** to save configuration.

---

### Router configuration
Select the Router module and set the following parameters:

| Parameter | Command | Value | Description |
|------------|----------|--------|--------------|
| PAN ID | `ID` | `1234` | Must match Coordinator |
| Channel | `CH` | `C` | Must match Coordinator |
| Coordinator Enable | `CE` | `0` | Router mode |
| Destination Address High | `DH` | `0` | — |
| Destination Address Low | `DL` | `0` or `FFFF` | Broadcast |
| API Enable | `AP` | `0` | Transparent mode |
| Baud Rate | `BD` | `3` (= 9600) | Must match Arduino |
| Node Identifier | `NI` | `ROUTER1` | Optional name |
| Sleep Mode | `SM` | `0` | Always on |
| Join Verification | `JV` | `1` | Auto rejoin on power-up |

Click **Write** to save.

---

### Check network association
1. Disconnect and reconnect both XBee modules.  
2. In XCTU, click the **Network Working Mode** icon (mesh symbol).  
3. Click **Discover radio network**.  
4. You should see:
   - The **Coordinator** in the center.  
   - The **Router** connected to it.  
5. The **ASSOC LED** on the Router should blink **once per second** (associated successfully).

---

### Test communication
1. Select the **Coordinator** → open **Console** → click **Open**.  
2. Select the **Router** → open **Console** → click **Open**.  
3. Type in one console window — the message should appear in the other.  

If you can send and receive messages both ways, your XBee network is configured correctly.

<p align="center">
  <img src="/images/data_test.png" alt="data_test" />
</p>
<p align=center><em>Image 8. Data Test</em></p>

---

### Connect the Router to Microcontroller

#### 🔹 Wiring

| XBee pin | Microcontroller pin | Description |
|-----------|------------------|--------------|
| VCC (3.3 V) | 3.3 V | Power supply |
| GND | GND | Common ground |
| TX (pin 2) | D2 | RX of Microcontroller |
| RX (pin 3) | D3 | TX of Microcontroller |

### Arduino code example

```cpp
#include <SoftwareSerial.h>
SoftwareSerial xbee(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);
  Serial.println("XBee Router Ready...");
}

void loop() {
  xbee.println("Hello from Arduino Router!");
  delay(1000);
}
```

### Save & reuse configuration
- You can save and reuse your configuration:
    - Click the gear icon → Save profile (Coordinator and Router separately).
    - Load it later with Import profile for new modules.

⚙️ [Alonso Ismael Camarena](https://www.linkedin.com/in/camarenaai/)