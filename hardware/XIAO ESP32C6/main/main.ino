#include <Wire.h>
#include "lib/led-indicators.h"
#include "lib/hardware-config.h"
#include "lib/cred.h"
#include "lib/wifi-config.h"

#include <HardwareSerial.h>

const int I2C_SLAVE_ADDR = 0x08; // I2C address of the SAMD21
const int ledPin = 13;

void setup()
{
  Wire.begin();         // Initialize I2C
  Serial.begin(115200); // Initialize Serial for debugging
  wificred();
  // ============= WiFi Configuration =============
  // longRange(); // Enable long range mode
  internal(); // Use internal antenna (default)
  // external(); // Use external antenna
  // ============= WiFi Configuration =============
  WificonectingLED(); // Blink the LED while connecting to WiFi
  Wificonect();       // Connect to WiFi
  WificonectLED();    // Blink the LED to indicate successful connection
}

void loop()
{
  // Example command to send
  String command = "typ";

  Wire.beginTransmission(I2C_SLAVE_ADDR);
  Wire.write((const uint8_t *)command.c_str(), command.length());
  Wire.endTransmission();

  Serial.println("Sent command: " + command);

  delay(1000); // Delay for demonstration purposes
}
