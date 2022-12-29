#include <Servo.h>
#define serwo 3
#define fotorez A5

Servo silniczek;
int foto = 0;
int pozycjaPoprzednia = 0;
int pozycja = 0;

void setup() {
  silniczek.attach(serwo);
  silniczek.write(15);
  Serial.begin(9600);
}

void loop() {
  delay(2000);
  foto = analogRead(fotorez);
  pozycja = map(foto, 0, 900, 190, 20);

  if(abs(pozycja - pozycjaPoprzednia) > 10){
    silniczek.write(pozycja);
    pozycjaPoprzednia = pozycja;
  }

  Serial.println("Wskazania fotorezystora: " + String(foto) + "|" + String(pozycja));
}
