#include<WiFi.h>
#include<HTTPClient.h>
#include<DHT.h>

const char* ssid= "Redmi Note 13 Pro+ 5G";
const char* password= "MyHotspot@123";
const char* server="https://thingspeak.mathworks.com/channels/3466737/private_show";
const char* apiKey="BHOIBFHB4OEJG23R";

#define DHT_PIN 4
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);
#define MQ135_PIN 34

const float ADC_REFERENCE = 3.3;
const int ADC_RESOLUTION = 4095;
unsigned long lastUploadTime=0;
const unsigned long uploadInterval=20000;

void setup() {
  Serial.begin(115200);
  dht.begin();
  analogReadResolution(12);
  analogSetPinAttenuation(MQ135_PIN, ADC_11db);
  Serial.println();
  Serial.println("ESP32 + MQ-135 + DHT11");
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serail.print(".");
  }
  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(millis() - lastUploadTime >= uploadInterval){
    lastUploadTime = millis();
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int mq135Raw = analogRead(MQ135_PIN);
    float mq135Voltage = (mq135Raw * ADC_REFERENCE) / ADC_RESOLUTION;
    if (isnan(temperature) || isnan(humidity)){
      Serial.println("Failed to read from DHT11!");
      return;
    }
  }
}
