#define button 7
#define ledRed 8
#define ledGreen 9
#define speaker 11

void setup() {
  pinMode(button, INPUT_PULLUP);

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(speaker, OUTPUT);

  Serial.begin(9600);

  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(speaker, LOW);
}

void loop() {
  if (digitalRead(button) == (LOW)) {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    Serial.println("Okno zamkniete.");
    
    digitalWrite(speaker, LOW);
    delay(100);
    digitalWrite(speaker, HIGH);
    delay(100);
    digitalWrite(speaker, LOW);
    delay(100);
    digitalWrite(speaker, HIGH);
    delay(100);
    digitalWrite(speaker, LOW);
    delay(100);
    digitalWrite(speaker, HIGH);
    delay(100);
    digitalWrite(speaker, LOW);

    while (digitalRead(button) == (LOW)) {}
  } else {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    Serial.println("Okno nie jest zamknięte !");
    while (digitalRead(button) == (HIGH)) {
      digitalWrite(speaker, HIGH);
    }
  }
}
