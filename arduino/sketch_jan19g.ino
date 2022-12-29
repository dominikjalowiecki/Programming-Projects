int variable = 0;
int variable2 = 0;
float fotovoltage = 0;
boolean voltageDisplay = false;

void setup() {
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  variable = analogRead(A5);
  variable2 = analogRead(A4);

  variable2 = map(variable2, 0, 1023, 0, 200);

  fotovoltage = variable * 5.0/1024.0;
  
  while(voltageDisplay == false){
    Serial.print(fotovoltage);
    Serial.println(" V na foto-dzielniku");
    voltageDisplay = true;
  }

  Serial.print(variable);
  Serial.print(" fotorezystor| ");
  Serial.print(variable2);
  Serial.println(" potencjometr| ");
  
  if (variable < variable2){
    digitalWrite(8, HIGH);
  } else{
    digitalWrite(8, LOW);
  }

  delay(500);
}
