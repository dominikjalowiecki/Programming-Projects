int odebraneDane = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Wpisz litere: d, b, o, lub h, aby dostac wartosci wskazania ADC w systemie: dziesietnym, binarnym, osemkowym lub szesnastkowym.");
}

void loop() {
 int potencjometr = analogRead(A5);

 if(Serial.available() > 0){
  odebraneDane = Serial.read();

 switch (odebraneDane){
  case 'd':
    Serial.println(potencjometr, DEC);
  break;
  case 'b':
    Serial.println(potencjometr, BIN);
  break;
  case 'o':
    Serial.println(potencjometr, OCT);
  break;
  case 'h':
    Serial.println(potencjometr, HEX);
  break;
  default:
    Serial.println("Blad wybierz: d, b, o lub h !");
  break;
 }
 }
 delay(1000);
}
