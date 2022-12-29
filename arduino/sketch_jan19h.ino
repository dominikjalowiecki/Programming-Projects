//Przypisanie numerow portow do nazw mnemonicznych.
#define button 7
#define yellow1 6
#define yellow2 5
#define yellow3 4
#define green 3
#define red 2
#define resistor A5

int dac = 0; //Wskazania przetwornika DAC (0-1023).
int guess = 0; //Liczba wpisana przez uzytkownika.
int threshold = 50; //Margines bledu.
int thresholdFalse = 0; //Blad uzytkownika.
int generalFalse = 0; //Bledne odpowiedzi.
int yellowLed = 4; //Kolejne numery portow, do ktorych podpiete sa zolte ledy (symbolizujace ostale szanse).

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(yellow1, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(yellow3, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);

  Serial.begin(9600);

  digitalWrite(yellow1, HIGH);
  digitalWrite(yellow2, HIGH);
  digitalWrite(yellow3, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
}

void gra(){ //Glowna funkcja gry.
  Serial.println("Zgadnij wskazanie potencjometru. Wybierz liczbe z zakresu 0-1023. Mozesz sie pomylic maksymalnie o " + String(threshold) + "."); //Wyswietla instrukcje gry
  while(true) {
    if(Serial.available() > 0){ //Jesli w buforze portu szeregowego UART znajduja sie jakies bity to...
      guess = Serial.readStringUntil('/n').toInt(); //Przypisanie wpisanej przez uzytkownika wartosci 'String' do zmiennej 'guess'. Metoda 'toInt' zamienia wynik podany jako String w liczbe calkowita.
      
      delay(1000);
      if(guess >= 0 && guess <= 1023 + threshold){ //Jezeli wpisana przez uzytkownika liczba jest zgodna z glownym zakresem to...
        if(guess >= abs(dac - threshold) && guess <= dac + threshold){ //Jezeli wpisana przez uzytkownika liczba jest zgodna ze zwycieskim zakresem to...
          digitalWrite(green, HIGH);
          delay(1000);
          digitalWrite(green, LOW); //Migniecie zielonym ledem.
          
          delay(500);
          
          Serial.println("Brawo ! Udalo Ci sie odgadnac wskazania potencjometru.");
          Serial.println("Twoje przewidywania: " + String(guess));
          Serial.println("Wskazania potencjometru: " + String(dac));
          thresholdFalse = abs(dac - guess);
          Serial.println("Wartosc bledu: " + String(thresholdFalse));
          Serial.println("Zrestartuj urzadzenie, aby zagrac ponownie."); //Informacje w przypadku wygranej.
          while(true){}
        } else{ //Jezeli wpisana przez uzytkownika liczba nie jest zgodna ze zwycieskim zakresem to...
    
          generalFalse++;  //Zwieksza liczbe porazem (max. 3).
          digitalWrite(red, HIGH);
          delay(1000);
          digitalWrite(red, LOW); //Migniecie czerwonym ledem.

          delay(500);
          
          digitalWrite(yellowLed, LOW); //Zgaszenie zoltego led'a na znak utraty szansy.
          yellowLed++; //Oznaczenie kolejnego zoltego led'a w razie porazki.

          delay(500);
          if(generalFalse == 3){ //Jezeli liczba przegranych wyniosla 3 to...
            Serial.println("Przegrales :( Zrestartuj urzadzenie, aby zagrac ponownie.");
            while(true){} //Informacja w razie calkowitej porazki.
          } else{ //Jezeli liczba przegranych nie wyniosla 3 to...
          Serial.println("Bledna odpowiedz ! Sproboj ponownie... \n \n");
          gra(); //Informacja w razie pojedynczej porazki. Przejscie do kolejnego podejscia.
          }
        }
      } else{ //Jezeli wpisana przez uzytkownika liczba nie jest zgodna z glownym zakresem to...
        Serial.println("Wybierz liczbe z przedzialu 0-1023...");
        delay(1000);
        gra(); //Instrukcja dotyczaca przedzialu.
      }
    }
  }
}

void loop() {
  if(digitalRead(button) == (LOW)){ //Jezeli przycisk zostanie wcisniety...
    dac = analogRead(resistor); //Odczytanie wskazania DAC.
    delay(1000);
    gra(); //Przejscie do glownej funkcji.
  }
}
