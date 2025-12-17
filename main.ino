#include <Arduino.h>
#include <Wire.h>
#include <pas-co2-ino.hpp>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------------------------
// I2C + OLED settings
// -------------------------
#define I2C_FREQ_HZ 400000
#define SDA_PIN 8
#define SCL_PIN 9

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------------------------
// NeoPixel ring
// -------------------------
#define LED_PIN     3
#define NUMPIXELS   12
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// -------------------------
// CO₂ Sensor
// -------------------------
PASCO2Ino cotwo;
int16_t co2ppm;

void setup()
{
  Serial.begin(9600);
  Serial.println("Booting...");

  // I2C
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(I2C_FREQ_HZ);

  // OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("CO2 Meter Booting...");
  display.display();

  // NeoPixels
  pixels.begin();
  pixels.setBrightness(5);
  pixels.fill(pixels.Color(255, 255, 255));
  pixels.show();

  // -------------------------
  // IMPORTANT: sensor power-up time
  // -------------------------
  delay(1500); // PAS CO2 needs ~1–2 seconds

  // -------------------------
  // Try to start the sensor ONCE
  // -------------------------
  bool ok = cotwo.begin();

  if (!ok)
  {
    Serial.println("CO2 sensor failed to start!");
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("CO2 sensor error!");
    display.println("Check wiring.");
    display.display();
    // continue anyway (avoid blocking)
  }
  else
  {
    Serial.println("CO2 sensor ready");
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("CO2 sensor OK");
    display.display();
  }

  delay(800);
}

void loop()
{
  cotwo.startMeasure();

  // wait for measurement
  int16_t value = 0;
  unsigned long t0 = millis();
  while (value == 0 && millis() - t0 < 1500)
  {
    cotwo.getCO2(value);
  }

  // fallback if still zero
  if (value == 0) value = co2ppm;

  co2ppm = value;

  Serial.print("CO2: ");
  Serial.println(co2ppm);

  // -------------------------
  // NeoPixel color mapping
  // -------------------------
  uint8_t red   = constrain(map(co2ppm, 800, 2000, 0, 255), 0, 255);
  uint8_t green = constrain(map(co2ppm, 800, 2000, 255, 0), 0, 255);

  pixels.fill(pixels.Color(red, green, 0));
  pixels.show();

  // -------------------------
  // OLED
  // -------------------------
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("CO2 Level:");

  display.setTextSize(2);
  display.setCursor(0, 16);
  display.print(co2ppm);
  display.println(" ppm");

  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print(" = ");
  display.print(co2ppm / 10000.0, 2);
  display.println(" %");

  display.display();

  delay(5000);
}
