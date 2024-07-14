// master board
#include <Wire.h>        // Include the Wire library for I2C
#include <WiFi.h>        // Include the WiFi library
#include <ArduinoJson.h> // Include ArduinoJson library

const char *ssid = "CASA-PONVI";                 // Replace with your WiFi network name (SSID)
const char *password = "Famili@_9once_Vivanco$"; // Replace with your WiFi password

const int I2C_SLAVE_ADDR = 0x08; // Replace with your I2C slave device address

WiFiServer server(80); // Create a server instance on port 80

// API Configuration
const char *apiHost = "192.168.10.62";      // Replace with your API host address
const int apiPort = 5000;                  // Replace with your API port
const String apiEndpoint = "/get_command"; // Replace with your API endpoint for fetching commands

unsigned long lastApiCheckTime = 0;           // Variable to store the last time API was checked
const unsigned long apiCheckInterval = 30000; // Interval in milliseconds (e.g., 30 seconds)

// ESP Device ID and Secret Key
const String esp_id = "esp32_1";                     // Replace with your ESP ID
const String esp_secret_key = "your_esp_secret_key"; // Replace with your ESP Secret Key

void fetchCommandFromAPI()
{
  WiFiClient client;
  if (client.connect(apiHost, apiPort))
  {
    Serial.println("Connected to API");

    // Send GET request
    client.print(String("GET ") + apiEndpoint + "?esp_id=" + esp_id + "&esp_secret_key=" + esp_secret_key + " HTTP/1.1\r\n" +
                 "Host: " + apiHost + "\r\n" +
                 "Connection: close\r\n\r\n");

    // Wait for response
    while (client.connected() && !client.available())
      delay(1);

    // Read response headers
    String response = "";
    boolean headersEnd = false;
    while (client.available())
    {
      String line = client.readStringUntil('\r');
      if (line == "\n")
      {
        headersEnd = true;
        break; // End of headers found
      }
    }

    // Read response body (JSON)
    if (headersEnd)
    {
      while (client.available())
      {
        response += client.readStringUntil('\r');
      }
    }
    client.stop();

    Serial.println("Raw JSON response:");
    Serial.println(response);

    // Parse JSON
    StaticJsonDocument<1024> jsonDoc; // Adjust size as necessary
    DeserializationError error = deserializeJson(jsonDoc, response);

    if (error)
    {
      Serial.print("JSON parse error: ");
      Serial.println(error.c_str());
      return;
    }

    // Extract command
    String commandFromAPI = jsonDoc["command"].as<String>();
    commandFromAPI.trim();

    // Send command over I2C
    Wire.beginTransmission(I2C_SLAVE_ADDR);
    Wire.write((const uint8_t *)commandFromAPI.c_str(), commandFromAPI.length());
    Wire.endTransmission();

    Serial.println("Sent command from API: " + commandFromAPI);
  }
  else
  {
    Serial.println("Failed to connect to API");

    for (int i = 0; i < 5; i++)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
    }
  }
}

void setup()
{
  Wire.begin(); // Initialize I2C communication
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  connectToWiFi();
  server.begin(); // Start HTTP server
}

void loop()
{
  unsigned long currentMillis = millis();

  // Check if it's time to fetch command from API
  if (currentMillis - lastApiCheckTime >= apiCheckInterval)
  {
    lastApiCheckTime = currentMillis;
    fetchCommandFromAPI();
  }

  handleDirectMode(); // Handle direct mode concurrently
}

void handleDirectMode()
{
  WiFiClient client = server.accept(); // Accept incoming client connections

  if (client)
  {
    Serial.println("New client connected");

    String currentLine = ""; // String to hold incoming data from the client
    String command = "";     // Variable to hold the command

    // Read client request
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c); // Print to the Serial Monitor
        if (c == '\n')
        {
          // If the current line is blank, end of HTTP request is reached
          if (currentLine.length() == 0)
          {
            // Send HTTP response headers
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Check if the command is valid
            if (command.length() > 0)
            {
              if (isValidCommand(command))
              {
                // Send command over I2C
                Wire.beginTransmission(I2C_SLAVE_ADDR);
                Wire.write((const uint8_t *)command.c_str(), command.length());
                Wire.endTransmission();

                Serial.println("Sent command: " + command);
                client.println("Command received: " + command);
              }
              else
              {
                // Invalid command handling
                Serial.println("Invalid command");
                blinkLED(10, 50); // Blink LED 10 times rapidly (50ms on, 50ms off)
                client.println("Invalid command");
              }
            }
            else
            {
              // Invalid request handling
              client.println("Invalid request");
            }

            // End client connection
            client.stop();
            Serial.println("Client disconnected");
            break;
          }
          else
          {
            currentLine = ""; // Clear currentLine for next request
          }
        }
        else if (c != '\r')
        { // Add to currentLine if not end of line
          currentLine += c;
        }

        // Check for command in the GET request
        if (currentLine.startsWith("GET /command?cmd="))
        {
          int start = currentLine.indexOf('=');
          int end = currentLine.indexOf(' ', start);
          if (start != -1 && end != -1)
          {
            command = currentLine.substring(start + 1, end);
            command.trim();
          }
        }
      }
    }
  }
}

void connectToWiFi()
{
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
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
  Serial.println("HTTP server started");

  blinkLED(2, 250); // Blink LED to indicate successful connection
  digitalWrite(LED_BUILTIN, LOW);
}

void blinkLED(int numBlinks, int blinkInterval)
{
  for (int i = 0; i < numBlinks; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(blinkInterval);
    digitalWrite(LED_BUILTIN, LOW);
    delay(blinkInterval);
  }
  digitalWrite(LED_BUILTIN, LOW);
}

bool isValidCommand(String command)
{
  // Implement your command validation logic here
  // For example, check if the command is within a valid range or format
  // Replace with your actual validation logic
  return !command.isEmpty(); // Simple example: command is valid if not empty
}