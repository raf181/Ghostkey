#include <Wire.h>   // Include the Wire library for I2C
#include <WiFi.h>   // Include the WiFi library

const char* ssid = "CASA-PONVI";  // Replace with your WiFi network name (SSID)
const char* password = "Famili@_9once_Vivanco$";  // Replace with your WiFi password
// const int LED_BUILTIN = 6;

const int I2C_SLAVE_ADDR = 0x08;  // Replace with your I2C slave device address

WiFiServer server(80);  // Create a server instance on port 80

void setup() {
  Wire.begin();     // Initialize I2C communication
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  connectToWiFi();
}

void loop() {
  WiFiClient client = server.accept(); // Changed to accept() due to deprecation

  if (client) {
    Serial.println("New client connected");

    String currentLine = ""; // Make a String to hold incoming data from the client
    String command = "";     // Variable to hold the command
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c); // Print it to the Serial Monitor
        if (c == '\n') {
          // If the current line is blank, you got two newline characters in a row.
          // That's the end of the HTTP request from the client, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Check if the command is valid
            if (command.length() > 0) {
              if (isValidCommand(command)) {
                // Send command over I2C
                Wire.beginTransmission(I2C_SLAVE_ADDR);
                Wire.write((const uint8_t *)command.c_str(), command.length());
                Wire.endTransmission();

                Serial.println("Sent command: " + command);
                client.println("Command received: " + command);
              } else {
                // Invalid command handling
                Serial.println("Invalid command");
                blinkLED(10, 50); // Blink LED 10 times rapidly (50ms on, 50ms off)
                client.println("Invalid command");
              }
            } else {
              // Invalid request handling
              client.println("Invalid request");
            }

            // The HTTP response ends with another blank line
            client.println();
            break;
          } else { // If you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') { // If you got anything else but a carriage return character,
          currentLine += c; // Add it to the end of the currentLine
        }

        // Check for the command in the GET request
        if (currentLine.startsWith("GET /command?cmd=")) {
          int start = currentLine.indexOf('=');
          int end = currentLine.indexOf(' ', start);
          if (start != -1 && end != -1) {
            command = currentLine.substring(start + 1, end);
            command.trim();
          }
        }
      }
    }

    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("HTTP server started");

  // Blink LED to indicate successful connection
  blinkLED(2, 250);
}

void blinkLED(int numBlinks, int blinkInterval) {
  for (int i = 0; i < numBlinks; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(blinkInterval);
    digitalWrite(LED_BUILTIN, LOW);
    delay(blinkInterval);
  }
}

bool isValidCommand(String command) {
  // Implement your command validation logic here
  // For example, check if the command is within a valid range or format
  // Replace with your actual validation logic
  return !command.isEmpty(); // Simple example: command is valid if not empty
}