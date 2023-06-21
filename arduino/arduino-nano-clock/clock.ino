#include <LCD_I2C.h>

/**
*   Deklaracja stanow i podstanow zegara
*/
enum mode {
    clock,
    alarm,
    setTime,
    setAlarm,
};

enum setTimeAlarmMode {
    second,
    minute,
    hour,
};


/**
*   Definicja wykorzystywanych wejsc i wyjsc modulu Arduino Nano
*/
const byte LCD_I2C_ADDRESS = 0x3F;

const byte LED_STRIP_PINS_COUNT = 3;
const byte LED_STRIP_PINS[] = {3, 5, 6};

const byte OK_BUTTON = 8;
const byte SET_TIME_NEXT_BUTTON = 9;
const byte SET_ALARM_EXIT_BUTTON = 10;

const byte ULTRASONIC_ECHO = 11;
const byte ULTRASONIC_TRIG = 12;

const byte POTENTIOMETER_INPUT = A0;

/**
*   Inicjalizacja wyswietlacza LCD podlaczanego przez konwerter I2C
*/
LCD_I2C lcd(LCD_I2C_ADDRESS, 16, 2);



/**
*   Definicja poczatkowych wartosci zegara
*/
volatile mode currentMode = clock;
volatile setTimeAlarmMode currentSetTimeAlarmMode = second;

volatile byte currentHour = 0, currentMinute = 0, currentSecond = 0;
byte hourToSet = 0, minuteToSet = 0, secondToSet = 0;

byte alarmHour = 0, alarmMinute = 0, alarmSecond = 0;
volatile boolean alarmSet = false;


/**
*   Obsluga przerwania pin-change-interrupt dla portow grupy B
*/
ISR(PCINT0_vect)
{
    static unsigned long lastInterruptTime = 0;
    unsigned long interruptTime = millis();

    /**
    *   Programowa eliminacja drgania stykow
    */
    if (interruptTime - lastInterruptTime > 200)
    {
        /**
        *   Obsluga przyciskow na opadajacym zboczu
        */
        if (digitalRead(OK_BUTTON) == LOW)
        {
            /**
            *   Obsluga przejsc stanow dla przycisku OK
            */
            if (currentMode == alarm)
            {
                // Wyjscie z trybu ALARM
                alarmSet = false;
                turnOffAlarmLed();
                currentMode = clock;
            } else if(currentMode == setTime)
            {
                // Potwierdzenie ustawienia czasu zegara
                cli();
                currentSecond = secondToSet;
                currentMinute = minuteToSet;
                currentHour = hourToSet;

                currentMode = clock;
                sei();

                currentSetTimeAlarmMode = second;
            } else if(currentMode == setAlarm)
            {
                // Potwierdzenie ustawienia alarmu
                alarmSet = true;
                currentMode = clock;

                currentSetTimeAlarmMode = second;
            }
        } else if (digitalRead(SET_TIME_NEXT_BUTTON) == LOW)
        {
            /**
            *   Obsluga przejsc stanow dla przycisku SET TIME/NEXT
            */
            if (currentMode == clock)
            {
                // Przejscie do trybu SET TIME
                secondToSet = currentSecond;
                minuteToSet = currentMinute;
                hourToSet = currentHour;

                currentMode = setTime;
            } else if (currentMode == setTime || currentMode == setAlarm)
            {
                // Przejscie miedzy ustawianiem sekund/minut/godzin
                currentSetTimeAlarmMode = (setTimeAlarmMode)((currentSetTimeAlarmMode + 1) % 3);
            }
        } else if (digitalRead(SET_ALARM_EXIT_BUTTON) == LOW) 
        {
            /**
            *   Obsluga przejsc stanow dla przycisku SET ALARM/EXIT
            */
            if (currentMode == clock)
            {
                // Przejscie do trybu SET ALARM
                currentMode = setAlarm;
            } else if (currentMode == setTime)
            {
                // Wyjscie z trybu SET TIME
                currentMode = clock;

                currentSetTimeAlarmMode = second;
            } else if (currentMode == setAlarm)
            {
                // Wyjscie z trybu SET ALARM
                alarmSet = false;
                currentMode = clock;

                currentSetTimeAlarmMode = second;
            }
        }
    }

    lastInterruptTime = interruptTime;
}

/**
*   Obsluga przerwania 16 bitowego licznika 1 dla czestotliwosci 1Hz
*/
ISR(TIMER1_COMPA_vect)
{
    // Inkrementacja wskazan zegara
    ++currentSecond;
    if(currentSecond >= 60)
    {
        currentSecond = 0;
        ++currentMinute;
    }

    if(currentMinute >= 60)
    {
        currentMinute = 0;
        ++currentHour;
    }

    if(currentHour >= 24)
        currentHour = 0;

    // Warunkowe przejscie do trybu ALARM
    if(
        currentHour == alarmHour &&
        currentMinute == alarmMinute &&
        currentSecond == alarmSecond &&
        alarmSet == true &&
        currentMode != setAlarm &&
        currentMode != alarm
    )
        currentMode = alarm;
}

/**
*   Konfiguracja wyprowadzen modulu Arduino Nano
*/
void setup() {
    // Konfiguracja wejsc dla przyciskow zegara
    pinMode(OK_BUTTON, INPUT_PULLUP);
    pinMode(SET_TIME_NEXT_BUTTON, INPUT_PULLUP);
    pinMode(SET_ALARM_EXIT_BUTTON, INPUT_PULLUP);

    // Konfiguracja wyprowadzen dla paska led
    for(int i = 0; i < LED_STRIP_PINS_COUNT; i++) pinMode(LED_STRIP_PINS[i], OUTPUT);

    // Konfiguracja wyjscia dla sensora odleglosci
    pinMode(ULTRASONIC_TRIG, OUTPUT);

    // Inicjalizacja wyswietlacza LCD
    lcd.begin();
    lcd.backlight(); 

    noInterrupts();
    // Konfiguracja przerwan pin-change-interrupt
    PCICR |= 0b00000001; // Aktywacja PCI dla portow grupy B (PCIE0)
    PCMSK0 |= 0b00000111; // Aktywacja przerwan dla pinow D8, D9 i D10 (PCINT0, PCINT1, PCINT2)

    // Konfiguracja przerwania porownania wartosci 16 bitowego licznika 1
    TCCR1A = 0; // Czyszczenie rejestrow kontroli licznika
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12); // Wlaczenie trybu czyszczenia wartosci licznika przy porownaniu (CTC)
    TCCR1B |= (1 << CS12) | (1 << CS10); // Konfiguracja dzielnika czestotliwosci licznika na wartosc 1024
    TCNT1 = 0; // Ustawienie poczatkowej wartosci licznika
    OCR1A = 15624; // Ustawienie wartosci porownania licznika dla docelowej czestotliwosci 1Hz [(16MHz / (1024 * 1Hz)) - 1]
    TIMSK1 |= (1 << OCIE1A); // Wlaczenie TCI

    interrupts();
}

/**
*   Obsluga sekwencji alarmu PWM paska ledowego
*/
void alarmLedSequence()
{
    static boolean sequenceInit = false;

    for (int i = 0; i < LED_STRIP_PINS_COUNT; i++) {
      for (int _ = 0; _ < 256; _ += 10) {
        analogWrite(LED_STRIP_PINS[i], _);
        delay(1);
      }

      if (i < 1) {
        if (sequenceInit) {
          for (int _ = 255; _ >= 0; _ -= 10) {
            analogWrite(LED_STRIP_PINS[i + 2], _);
            delay(1);
          }
        }
      } else {
        if (!sequenceInit) sequenceInit = true;
        for (int _ = 255; _ >= 0; _ -= 10) {
          analogWrite(LED_STRIP_PINS[i - 1], _);
          delay(1);
        }
      }
    }
}

/**
*   Wylaczenie diod paska ledowego alarmu
*/
void turnOffAlarmLed()
{
    for(int i = 0; i < LED_STRIP_PINS_COUNT; i++) analogWrite(LED_STRIP_PINS[i], 0);
}

/**
*   Aktywacja sensora odleglosci
*/
void triggerUltrasonic()
{
    digitalWrite(ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG, LOW);
}

/**
*   Glowna petla programu - obsluga trybow zegara
*/
void loop() {
    static boolean isBacklightOn = false;
    
    if (currentMode == clock || currentMode == alarm)
    {
        /**
        *   Obsluga trybu CLOCK i ALARM
        */

        // Dla trybu ALARM wlacz sekwencje led
        if (currentMode == alarm)
            alarmLedSequence();

        // Pomiar odleglosci przez sensor
        long t, distance;
                
        triggerUltrasonic();

        t = pulseIn(ULTRASONIC_ECHO, HIGH);
        distance = t / 58; // Konwersja na odleglosc w centrymetrach

        // Tryb oszczedzania energii - wlacz podswietlenie ekranu przy odleglosciach < 50 cm oraz dla trybu ALARM
        if (distance > 50 && currentMode != alarm)
        {
            if (isBacklightOn)
            {
                lcd.noBacklight();
                isBacklightOn = false;
            }
        } else
        {
            if (!isBacklightOn)
            {
                lcd.backlight();
                isBacklightOn = true;
            }
        }

        // Wyswietlenie aktualnego czasu na wyswietlaczu
        lcd.clear();

        char buffer[8];
        sprintf(buffer, "%02d:%02d:%02d", currentHour, currentMinute, currentSecond);
        lcd.print(buffer);
    } else if (currentMode == setTime)
    {
        /**
        *   Obsluga trybu SET TIME
        */

        // Wlaczenie podswietlenia ekranu
        if (!isBacklightOn)
        {
            lcd.backlight();
            isBacklightOn = true;
        }

        // Obsluga ustawiania czasu zegara na podstawie wartosci potencjometru obrotowego
        int potentiometerValue = analogRead(POTENTIOMETER_INPUT);
        if (currentSetTimeAlarmMode == second) secondToSet = map(potentiometerValue, 0, 1024, 0, 60);
        else if (currentSetTimeAlarmMode == minute) minuteToSet = map(potentiometerValue, 0, 1024, 0, 60);
        else if (currentSetTimeAlarmMode == hour) hourToSet = map(potentiometerValue, 0, 1024, 0, 24);

        // Wyswietlenie ustawianego czasu zegara na wyswietlaczu
        lcd.clear();

        char buffer[8];
        sprintf(buffer, "%02d:%02d:%02d", hourToSet, minuteToSet, secondToSet);
        lcd.print(buffer);
        
        lcd.setCursor(0,1);
        lcd.print("Set clock mode");
    } else if (currentMode == setAlarm)
    {
        /**
        *   Obsluga trybu SET ALARM
        */

        // Wlaczenie podswietlenia ekranu
        if (!isBacklightOn)
        {
            lcd.backlight();
            isBacklightOn = true;
        }

        // Obsluga ustawiania czasu alarmu na podstawie wartosci potencjometru obrotowego
        int potentiometerValue = analogRead(POTENTIOMETER_INPUT);
        if (currentSetTimeAlarmMode == second) alarmSecond = map(potentiometerValue, 0, 1024, 0, 60);
        else if (currentSetTimeAlarmMode == minute) alarmMinute = map(potentiometerValue, 0, 1024, 0, 60);
        else if (currentSetTimeAlarmMode == hour) alarmHour = map(potentiometerValue, 0, 1024, 0, 24);

        // Wyswietlenie ustawianego czasu alarmu na wyswietlaczu
        lcd.clear();

        char buffer[8];
        sprintf(buffer, "%02d:%02d:%02d", alarmHour, alarmMinute, alarmSecond);
        lcd.print(buffer);
                
        lcd.setCursor(0,1);
        lcd.print("Set alarm mode");
    }

    delay(250);
}