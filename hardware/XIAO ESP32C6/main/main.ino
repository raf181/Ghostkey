#include <Wire.h>
#include <WiFi.h>
#include "lib/led-indicators.h"
#include "lib/hardware-config.h"
#include "lib/cred.h"
#include "lib/wifi-config.h"

#include <HardwareSerial.h>

const int I2C_SLAVE_ADDR = 0x08; // I2C address of the SAMD21
const int ledPin = 13;

void setup()
{
  pinMode(ledPin, OUTPUT);

  Wire.begin();         // Initialize I2C
  Serial.begin(115200); // Initialize Serial for debugging
  // ============= WiFi Configuration =============
  // longRange(); // Enable long range mode
  internal(); // Use internal antenna (default)
  // external(); // Use external antenna
  // ============= WiFi Configuration =============
  connectToWiFi();
  // Display IP address in serial monitor
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("New client connected");
    
    while (client.connected()) {
      if (client.available()) {
        String command = client.readStringUntil('\n');
        command.trim(); // Remove any whitespace
        
        Serial.println("Received command: " + command);
        
        // Send command over I2C
        Wire.beginTransmission(I2C_SLAVE_ADDR);
        Wire.write((const uint8_t *)command.c_str(), command.length());
        Wire.endTransmission();
        
        Serial.println("Sent command: " + command);
        
        // Respond to client (optional)
        client.println("Command received: " + command);
      }
    }
    
    client.stop();
    Serial.println("Client disconnected");
  }
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Blink LED to indicate successful connection
  blinkLED(2, 250);
}

void blinkLED(int numBlinks, int blinkInterval) {
  for (int i = 0; i < numBlinks; i++) {
    digitalWrite(ledPin, HIGH);
    delay(blinkInterval);
    digitalWrite(ledPin, LOW);
    delay(blinkInterval);
  }
}