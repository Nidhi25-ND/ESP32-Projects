#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 5
#define ECHO_PIN 18

#define LED_PIN 2
#define BUZZER_PIN 4

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Distance Alert");
  delay(1500);
  lcd.clear();
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  float distance = duration * 0.0343 / 2;

  // Display distance
  lcd.setCursor(0, 0);
  lcd.print("Distance:  ");
  lcd.setCursor(10, 0);

  if (distance == 0) {
    lcd.print("--");
  } else {
    lcd.print(distance, 1);
  }

  lcd.print("cm");

  // More than 30 cm
  if (distance > 30 || distance == 0) {

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    lcd.setCursor(0, 1);
    lcd.print("SAFE            ");

    delay(200);
  }

  // 20 to 30 cm
  else if (distance > 20) {

    digitalWrite(LED_PIN, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("CAUTION         ");

    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
  }

  // 10 to 20 cm
  else if (distance > 10) {

    digitalWrite(LED_PIN, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("WARNING         ");

    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(150);
  }

  // Less than 10 cm
  else {

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("STOP!           ");

    delay(100);
  }
}