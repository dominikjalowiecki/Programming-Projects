#define fotorLeft A4
#define fotorRight A5

int resLeft = 0;
int resRight = 0;

void setup() {
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  resLeft = analogRead(fotorLeft);
  resRight = analogRead(fotorRight);
  Serial.print(resLeft);
  Serial.print("|");
  Serial.println(resRight);
  delay(1000);

  if (abs(resLeft - resRight) < 5){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
  } else if(resLeft - resRight >= 5 && resLeft - resRight <= 10){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  } else if(resLeft - resRight <= -5 && resLeft - resRight >= -10){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
  } else if(resLeft - resRight > 10){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  } else if(resLeft - resRight < -10){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
  }
  delay(25);
}
