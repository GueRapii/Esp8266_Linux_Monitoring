#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "MyServer";
const char* password = "23052008";
const char* serverIp = "192.168.1.72";

void setup() {
    Serial.begin(115200);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Connect To WiFi...");
    display.display();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi Connected!");
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("WiFi Connected!");
    display.display();
    delay(500);
}

String formatUptime(String uptime) {
    int dotIndex = uptime.indexOf('.');
    return (dotIndex != -1) ? uptime.substring(0, dotIndex) : uptime;
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, String("http://") + serverIp + ":5000/status");

        int httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            Serial.println("API LOGS: " + payload);
            
            StaticJsonDocument<512> doc;
            DeserializationError error = deserializeJson(doc, payload);
            
            if (!error) {
                float cpu = doc["cpu"];
                float temp = doc["temp"];
                String ram = doc["ram"];
                long sent_speed = doc["sent_speed"];
                long recv_speed = doc["recv_speed"];
                float root_used = doc["root_used"];
                float root_total = doc["root_total"];
                float data_used = doc["data_used"];
                float data_total = doc["data_total"];
                String uptime = formatUptime(doc["uptime"]);

                char cpu_str[6], temp_str[6];
                dtostrf(cpu, 4, 1, cpu_str);
                dtostrf(temp, 4, 1, temp_str);

                display.clearDisplay();
                display.setCursor(0, 0);
                display.println("MyServer Monitoring");
                display.println("--------------------");

                display.printf("CPU: %s%% / %sC\n", cpu_str, temp_str);
                display.printf("Uptime: %s\n", uptime.c_str());
                display.printf("RAM: %s\n", ram.c_str());
                display.printf("Upload: %.2f Mbps\n", (sent_speed * 8) / 1000.0);
                display.printf("Download: %.2f Mbps\n", (recv_speed * 8) / 1000.0);
                display.printf("NAS: %.2f / %.2f GB\n", data_used, data_total);

                display.display();
            } else {
                Serial.println("fail parsing JSON");
            }
        } else {
            Serial.println("API ERROR");
        }

        http.end();
    }

    delay(1000);
}
