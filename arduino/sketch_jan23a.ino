#import <Servo.h>

Servo silniczek;
int obrot = 0;
int adc = 0;

/*
void main(){
  while(true){
    if(Serial.available() > 0){
      obrot = Serial.readStringUntil('/n').toInt();
      delay(1000);
      if(obrot >= 0 && obrot <= 180){
        silniczek.write(obrot);
        delay(1000);
      } else{
        Serial.println("Wybierz liczbe z zakresu 0-180 !");
        delay(1000);
        main(){
      }
    }
  }
}
*/

void setup() {
  silniczek.attach(9);
  silniczek.write(15);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Wybierz liczbe z przedzialu 0-180, aby obrocic serwo.");
  delay(1000);
  
  //main();
  
  while(true){
    if(Serial.available() > 0){
      obrot = Serial.readStringUntil('/n').toInt();
      delay(1000);
      
      if(obrot >= 0 && obrot <= 180){
        silniczek.write(obrot + 15);
        delay(1000);
      } else{
        Serial.println("Wybierz liczbe z zakresu 0-180 !");
        delay(1000);
        loop();
      }
    }
  }
}
