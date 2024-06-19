void WificonectingLED() {
  //Serial.println("Connecting to Wi-Fi...");
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

void WificonectLED() {
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
  digitalWrite(LED_BUILTIN, LOW);
}