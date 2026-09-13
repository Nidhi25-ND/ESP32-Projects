#include<DHT.h>
#include<LiquidCrystal_I2C.h>
#define DHT_PIN 5
#define DHT_TYPE DHT11
#define LED1 8
#define LED2 9
#define LED3 10
DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  Serial.println("DHT Sensor Test");
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temp sensor");
  delay(1500);
  lcd.clear();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature= dht.readTemperature();
  float humidity= dht.readHumidity();
  if(isnan(temperature) || isnan(humidity)){
    Serial.println("Failed to read from DHT11");
    delay(2000);
    return;
  }
  Serial.println("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.println("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  delay(2000);

  if(temperature<=25){
    digitalWrite(LED1, HIGH);
   
  }
  else if(temperature>=25 || temperature<= 30){
    digitalWrite(LED2, HIGH);
   
  }
  else{
    digitalWrite(LED3, HIGH);
   
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp:  ");
  lcd.setCursor(10, 0);
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity:  ");
  lcd.print(humidity);
  lcd.print(" %");
  delay(1000);
}
