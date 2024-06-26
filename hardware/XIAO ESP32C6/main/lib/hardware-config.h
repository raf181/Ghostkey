void internal() {
  //Serial.println("Using internal antenna");
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
}

void external() {
  //Serial.println("Using external antenna");
  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);
}

void longRange() {
  Serial.println("Using long range mode");
  // WiFiGenericClass::enableLongRange(bool enable)
}
