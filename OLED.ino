#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// ESP32 I2C pins
#define OLED_SDA 21
#define OLED_SCL 22

// OLED object
Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

void setup()
{
  Serial.begin(115200);

  // Initialize I2C
  Wire.begin(OLED_SDA, OLED_SCL);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED not found!");
    while (1);
  }

  // Clear OLED screen
  display.clearDisplay();

  // Set text color
  display.setTextColor(SSD1306_WHITE);

  // Set text size
  display.setTextSize(2);

  // Set cursor position
  display.setCursor(10, 25);

  // Display text
  display.println("HELLO");

  display.setCursor(10, 45);
  display.println("WORLD");

  // Update OLED
  display.display();
}

void loop()
{
  // Nothing required here
}
