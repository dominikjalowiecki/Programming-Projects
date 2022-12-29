#define dioda 3

byte wypelnienie = 0;
int zmiana = 5;

void setup() {
  pinMode(dioda, OUTPUT);
}

void loop() {
  analogWrite(dioda, wypelnienie);
  
  if(wypelnienie < 255){
    wypelnienie += zmiana;
  } else if(wypelnienie >= 255){
    while(wypelnienie > 0){
      wypelnienie -= zmiana;
      delay(50);
      analogWrite(dioda, wypelnienie);
    }
  }
  delay(50);
}
