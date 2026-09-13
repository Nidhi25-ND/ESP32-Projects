#define BLYNK_TEMPLATE_ID "TMPL30tQVuMCy"
#define BLYNK_TEMPLATE_NAME "LED ON OFF"
#define BLYNK_AUTH_TOKEN "EI27608ERMOIgwoMUz96uD1wqdDIDDPc"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Wi-Fi credentials
char ssid[] = "Redmi Note 13 Pro+ 5G";
char pass[] = "MyHotspot@123";

// GPIO pins
#define LED_PIN 2
#define FAN_PIN 5

void setup()
{
  Serial.begin(115200);

  // Configure GPIO pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // Initially OFF
  digitalWrite(LED_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("ESP32 Blynk Control Started");
}

// Blynk V0 controls LED
BLYNK_WRITE(V0)
{
  int ledState = param.asInt();

  digitalWrite(LED_PIN, ledState);

  if (ledState == 1)
  {
    Serial.println("LED ON");
  }
  else
  {
    Serial.println("LED OFF");
  }
}

// Blynk V1 controls Fan
BLYNK_WRITE(V1)
{
  int fanState = param.asInt();

  digitalWrite(FAN_PIN, fanState);

  if (fanState == 1)
  {
    Serial.println("FAN ON");
  }
  else
  {
    Serial.println("FAN OFF");
  }
}

void loop()
{
  Blynk.run();
}
