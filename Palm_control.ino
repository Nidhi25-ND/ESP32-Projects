#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Redmi Note 13 Pro+ 5G";
const char* password = "MyHotspot@123";

#define LED_PIN 2

WebServer server(80);

bool ledState = false;

// ================= LED ON =================

void handleLEDOn() {

  digitalWrite(LED_PIN, HIGH);
  ledState = true;

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "LED ON");
}

// ================= LED OFF =================

void handleLEDOff() {

  digitalWrite(LED_PIN, LOW);
  ledState = false;

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "LED OFF");
}

// ================= LED STATUS =================

void handleStatus() {

  server.sendHeader("Access-Control-Allow-Origin", "*");

  if (ledState) {
    server.send(200, "text/plain", "ON");
  }
  else {
    server.send(200, "text/plain", "OFF");
  }
}

// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  // Connect to WiFi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi Connected!");

  Serial.print("ESP32 IP Address: ");

  Serial.println(WiFi.localIP());

  // Web server routes
  server.on("/on", handleLEDOn);

  server.on("/off", handleLEDOff);

  server.on("/status", handleStatus);

  server.begin();

  Serial.println("Web Server Started");
}

// ================= LOOP =================

void loop() {

  server.handleClient();
}

