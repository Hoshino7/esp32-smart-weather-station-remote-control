#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

// Config Wi-Fi Network
const char* ssid     = "NAMA_WIFI_KAMU";
const char* password = "PASSWORD_WIFI_KAMU";

// Pin Definition
#define DHTPIN 23
#define DHTTYPE DHT22
#define RELAY_PIN 19
#define LED_HIJAU 18
#define LED_MERAH 5
#define BUZZER_PIN 17

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

bool relayState = false;

void handleRoot() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    temp = 0.0;
    hum = 0.0;
  }

  String html = "<!DOCTYPE html><html><head><title>ESP32 Weather Station</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body{font-family:Arial;text-align:center;background:#f4f6f7;margin-top:40px;}";
  html += ".card{background:white;padding:20px;border-radius:10px;display:inline-block;box-shadow:0 4px 8px rgba(0,0,0,0.1);}";
  html += ".btn{padding:12px 24px;font-size:16px;color:white;border:none;border-radius:5px;cursor:pointer;}";
  html += ".btn-on{background-color:#2ecc71;} .btn-off{background-color:#e74c3c;}</style></head><body>";
  html += "<div class='card'><h2>ESP32 Smart Weather Station</h2>";
  html += "<p>Suhu: <b>" + String(temp, 1) + " &deg;C</b></p>";
  html += "<p>Kelembapan: <b>" + String(hum, 1) + " %RH</b></p>";
  html += "<p>Status Relay: <b>" + String(relayState ? "ON (MENYALA)" : "OFF (MATI)") + "</b></p>";
  
  if (relayState) {
    html += "<a href='/relay/off'><button class='btn btn-off'>Matikan Relay</button></a>";
  } else {
    html += "<a href='/relay/on'><button class='btn btn-on'>Nyalakan Relay</button></a>";
  }
  
  html += "</div></body></html>";
  server.send(200, "text/html", html);
}

void handleRelayOn() {
  relayState = true;
  digitalWrite(RELAY_PIN, LOW); // Active LOW Relay
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleRelayOff() {
  relayState = false;
  digitalWrite(RELAY_PIN, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH); // Off default (Active LOW)
  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Connected!");
  Serial.print("IP Address ESP32: ");
  Serial.println(WiFi.localIP());

  // Web Server Routes
  server.on("/", handleRoot);
  server.on("/relay/on", handleRelayOn);
  server.on("/relay/off", handleRelayOff);
  server.begin();
}

void loop() {
  server.handleClient();

  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 2000) {
    lastCheck = millis();

    float temp = dht.readTemperature();
    if (!isnan(temp)) {
      if (temp > 30.0) {
        digitalWrite(LED_MERAH, HIGH);
        digitalWrite(LED_HIJAU, LOW);
        tone(BUZZER_PIN, 1000, 200);
      } else {
        digitalWrite(LED_MERAH, LOW);
        digitalWrite(LED_HIJAU, HIGH);
        noTone(BUZZER_PIN);
      }
    }
  }
}
