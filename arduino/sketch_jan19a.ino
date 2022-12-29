#define zielona 8
#define czerwona 9

String odebraneDane = "";

void setup() {
  Serial.begin(9600);
  pinMode(zielona, OUTPUT);
  pinMode(czerwona, OUTPUT);

  digitalWrite(zielona, LOW);
  digitalWrite(czerwona, LOW);
}

void loop() {
  if(Serial.available() > 0) {
    odebraneDane = Serial.readStringUntil('\n');
    
    if(odebraneDane == "zielona" || odebraneDane == "czerwona") {
      
      if(odebraneDane == "zielona"){
        digitalWrite(zielona, HIGH);
        delay(1000);
        digitalWrite(zielona, LOW);
      }

      if(odebraneDane == "czerwona"){
        digitalWrite(czerwona, HIGH);
        delay(1000);
        digitalWrite(czerwona, LOW);
      }
      
    } else {
      Serial.println("Bledny wybor !!! (zielona/czerwona)");
    }
  }
}
