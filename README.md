
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
- OLED display (SSD1306 128x64 I2C)
- Arduino IDE

### 2. Arduino IDE Configuration
- Install the **ESP8266 Board Support**  
  Go to `File > Preferences`, and in the "Additional Boards Manager URLs", add:  
  ```
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  ```
  Then go to `Tools > Board > Boards Manager`, search for **esp8266**, and install it.

- Select your board:  
  `Tools > Board > NodeMCU 1.0 (ESP-12E Module)` (or sesuai board kamu)

### 3. Install Required Libraries
Go to `Sketch > Include Library > Manage Libraries`, dan cari dan install:
- **Adafruit GFX Library**
- **Adafruit SSD1306**
- **ArduinoJson**
- **ESP8266HTTPClient**
- **ESP8266WiFi**

### 4. Upload Sketch
Edit bagian berikut di kodenya:

```cpp
const char* ssid = "your wifi";
const char* password = "your pass wifi";
const char* serverIp = "your ip server";
```

Lalu upload ke ESP8266. Pastikan server Linux kamu sudah berjalan dengan API `/status` yang disiapkan di bagian bawah.

---

## Linux Server Setup

### 1. Requirements
- Python 3
- Pip (Python package installer)

### 2. Install Required Python Libraries
Buka terminal dan jalankan:

```bash
sudo apt update
sudo apt install python3-pip
pip3 install flask psutil
```

### 3. Jalankan Server API

Buat file baru bernama `server_monitor.py` dan isi dengan kode server yang tersedia di repository ini. Lalu jalankan dengan:

```bash
python3 server_monitor.py
```

Pastikan port `5000` terbuka di firewall jika kamu mengakses dari jaringan lain.

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
Feel free to use and modify it as you like.
