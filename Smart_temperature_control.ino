#define BLYNK_TEMPLATE_ID "TMPL3jeeJBNq0"
#define BLYNK_TEMPLATE_NAME "Smart Temperature Control"
#define BLYNK_AUTH_TOKEN "1Me5tfdux5fR2P_n_6Urk-aAjCpyEn7i"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi
char ssid[] = "Redmi Note 13 Pro+ 5G";
char pass[] = "MyHotspot@123";

// DHT11
#define DHTPIN 4
#define DHTTYPE DHT11

// Ultrasonic
#define TRIG_PIN 18
#define ECHO_PIN 19

// LED
#define LED_PIN 2

// Object detection distance
#define DETECTION_DISTANCE 50

DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

bool manualMode = false;
bool manualLED = false;


// Measure distance
float getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 3000);

  if (duration == 0)
  {
    return -1;
  }

  float distance = duration * 0.0343 / 2;

  return distance;
}


// Main system
void checkSystem()
{
  float distance = getDistance();

  // Send distance to Blynk
  if (distance > 0)
  {
    Blynk.virtualWrite(V1, distance);
  }

  Serial.print("Distance: ");

  if (distance > 0)
  {
    Serial.print(distance);
    Serial.println(" cm");
  }
  else
  {
    Serial.println("No reading");
  }


  // =========================
  // MANUAL MODE
  // =========================

  if (manualMode)
  {
    if (manualLED)
    {
      digitalWrite(LED_PIN, HIGH);
      Blynk.virtualWrite(V2, 1);

      Serial.println("MANUAL: LED ON");
    }
    else
    {
      digitalWrite(LED_PIN, LOW);
      Blynk.virtualWrite(V2, 0);

      Serial.println("MANUAL: LED OFF");
    }

    return;
  }


  // =========================
  // AUTOMATIC MODE
  // =========================

  bool objectDetected =
    (distance > 0 && distance <= DETECTION_DISTANCE);


  if (objectDetected)
  {
    Serial.println("Object detected!");

    float temperature = dht.readTemperature();

    if (isnan(temperature))
    {
      Serial.println("DHT11 reading failed!");

      digitalWrite(LED_PIN, LOW);
      Blynk.virtualWrite(V2, 0);

      return;
    }

    // Send temperature to Blynk
    Blynk.virtualWrite(V0, temperature);

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");


    // Temperature condition
    if (temperature > 30)
    {
      digitalWrite(LED_PIN, HIGH);
      Blynk.virtualWrite(V2, 1);

      Serial.println("Temperature > 30°C");
      Serial.println("LED ON");
    }
    else
    {
      digitalWrite(LED_PIN, LOW);
      Blynk.virtualWrite(V2, 0);

      Serial.println("Temperature <= 30°C");
      Serial.println("LED OFF");
    }
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    Blynk.virtualWrite(V2, 0);

    Serial.println("No object detected");
    Serial.println("LED OFF");
  }

  Serial.println("-----------------------");
}


// =========================
// BLYNK MANUAL BUTTON
// =========================

BLYNK_WRITE(V3)
{
  manualLED = param.asInt();

  if (manualMode)
  {
    if (manualLED)
    {
      digitalWrite(LED_PIN, HIGH);
      Blynk.virtualWrite(V2, 1);
    }
    else
    {
      digitalWrite(LED_PIN, LOW);
      Blynk.virtualWrite(V2, 0);
    }
  }
}


// =========================
// BLYNK AUTO / MANUAL
// =========================

BLYNK_WRITE(V4)
{
  manualMode = param.asInt();

  if (manualMode)
  {
    Serial.println("MANUAL MODE");
  }
  else
  {
    Serial.println("AUTOMATIC MODE");

    // Turn LED OFF when switching back to automatic
    digitalWrite(LED_PIN, LOW);
    Blynk.virtualWrite(V2, 0);
  }
}


void setup()
{
  Serial.begin(115200);

  // Pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  // Start DHT
  dht.begin();

  // Connect Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Check sensors every 2 seconds
  timer.setInterval(2000L, checkSystem);
}


void loop()
{
  Blynk.run();
  timer.run();
}
