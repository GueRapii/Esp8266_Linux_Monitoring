
# Esp8266 Linux Monitoring

This project helps you build a small IoT device using an ESP8266 and OLED display to monitor a Linux server in real-time. Data such as CPU usage, temperature, RAM usage, disk status, network speeds, and uptime are fetched from the server and shown on the screen.

## Table of Contents

- [ESP8266 Setup](#esp8266-setup)
- [Linux Server Setup](#linux-server-setup)
- [Libraries](#libraries)
- [License](#license)

---

## ESP8266 Setup

### 1. Requirements
- ESP8266 board (e.g., NodeMCU, Wemos D1 Mini)
- OLED display 0.98Inch (SSD1306 128x64 I2C)
- Arduino IDE

### 2. Arduino IDE Configuration
- Install the **ESP8266 Board Support**  
  Go to `File > Preferences`, and in the "Additional Boards Manager URLs", add:  
  ```
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  ```
  Then go to `Tools > Board > Boards Manager`, search for **esp8266**, and install it.

- Select your board:  
  `Tools > Board > NodeMCU 1.0 (ESP-12E Module)` (or according to your board model)

### 3. Install Required Libraries
Open `Sketch > Include Library > Manage Libraries`, then search and install:
- **Adafruit GFX Library**
- **Adafruit SSD1306**
- **ArduinoJson**
- **ESP8266HTTPClient**
- **ESP8266WiFi**

### 4. Upload Sketch
Edit the following part of the code:

```cpp
const char* ssid = "your wifi";
const char* password = "your wifi password";
const char* serverIp = "your server IP";
```

Then upload the code to your ESP8266. Make sure your Linux server is running the `/status` API described below.

---

## Linux Server Setup

### 1. Requirements
- Python 3
- Pip (Python package installer)

### 2. Install Python Dependencies
Open your terminal and run:

```bash
sudo apt update
sudo apt install python3-pip
pip3 install flask psutil
```

### 3. Run the Monitoring Server

Create a new file called `server_monitor.py` and paste the server code available in this repository.

Run it with:

```bash
python3 server_monitor.py
```

Ensure that port `5000` is open in your firewall if you're accessing it from another device on the network.

---

## Libraries

### Arduino Libraries
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [ESP8266WiFi](https://arduino-esp8266.readthedocs.io/en/latest/)
- [ESP8266HTTPClient](https://arduino-esp8266.readthedocs.io/en/latest/)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

### Python Libraries (Linux Server)
- Flask
- psutil

---

## License

This project is licensed under the MIT License.  
Feel free to use, share, and modify it as needed.
