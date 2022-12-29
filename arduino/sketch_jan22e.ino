#include <Servo.h>

Servo silniczek;

void setup() {
  silniczek.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*for(int a = 0; a >= 90; a++){
    silniczek.write(a);
    delay(100);
  }
  
  for(int a = 90; a <= 45; a--){
    silniczek.write(a);
    delay(300);
  }
  
  for(int a = 45; a >= 180; a++){
    silniczek.write(a);
    delay(100);
  }
  
  silniczek.write(0);
  delay(500);
  */
  silniczek.write(0);
  delay(2000);
  /*delay(10000);
  silniczek.write(180);
  delay(10000);
  silniczek.write(-90);
  delay(10000);
  silniczek.write(90);
  delay(10000);*/
  /*silniczek.write(-40);
  delay(300);
  silniczek.write(0);
  delay(300);*/
}
