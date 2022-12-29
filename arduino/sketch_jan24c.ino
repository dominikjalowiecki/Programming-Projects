#define przycisk 2
#define fotorezL A3
#define fotorezR A4
#define potencjo A5

int fotoL = 0;
int fotoR = 0;
int poten = 0;

int buttonpress = 0;

void setup() {
  Serial.begin(9600);
  pinMode(przycisk, INPUT_PULLUP);
}

void loop() {
  fotoL = analogRead(fotorezL);
  fotoR = analogRead(fotorezR);
  poten = analogRead(potencjo);

  if(digitalRead(przycisk) == LOW){
    buttonpress++;
    Serial.println("Fotorezystor 1: " + String(fotoL) + "\tFotorezystor 2: " + String(fotoR) + "\tPotencjometr: " + String(poten) + "\tPrzycisk wcisnieto: " + String(buttonpress)); 
    delay(1000);
  }
}
