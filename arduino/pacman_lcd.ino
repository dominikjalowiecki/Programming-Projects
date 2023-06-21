#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2);

uint8_t pacman[8] =
{
    0b01110,
    0b11111,
    0b11110,
    0b11100,
    0b11110,
    0b11111,
    0b01110,
    0b00000,
};

uint8_t pacmanReverse[8] =
{
    0b01110,
    0b11111,
    0b01111,
    0b00111,
    0b01111,
    0b11111,
    0b01110,
    0b00000,
};

uint8_t pacmanClosed[8] =
{
    0b01110,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00000,
};

uint8_t point[8] =
{
    0b00000,
    0b00000,
    0b01110,
    0b11111,
    0b11111,
    0b01110,
    0b00000,
    0b00000,
};

const int buttonPin = 2;

volatile bool isReversed;

void drawPoints(byte startCol, byte startRow)
{ 
  if(isReversed)
  {
    lcd.setCursor(0,0);

    if(startRow == 1)
      for(int _ = 0; _ < 16; _++)
        lcd.write(2);

    lcd.setCursor(0, startRow);
    for(int _ = 0; _ < startCol; _++)
        lcd.write(2);
  } else
  {
    int n = 16 - startCol;
    
    lcd.setCursor(startCol, startRow);
    for(int _ = 0; _ < n; _++)
        lcd.write(2);
    
    if(startRow == 0)
    {
      lcd.setCursor(0, 1);
      for(int _ = 0; _ < 16; _++)
        lcd.write(2);
    }
  }
}

void directionIndicator()
{
  int inputValue = analogRead(A1);
  Serial.println(inputValue / 25.575);
  inputValue /= 25.575;
  //Serial.println(inputValue);
  byte pdelay = 20 + inputValue;
  
  if(isReversed)
  {
    for(int i = 3; i < 13; i++)
    {
      digitalWrite(i, HIGH);
      delay(pdelay);
      digitalWrite(i, LOW);
    }
  } else
  {
    for(int i = 12; i > 2; i--)
    {
      digitalWrite(i, HIGH);
      delay(pdelay);
      digitalWrite(i, LOW);
    }
  }
}

void buttonPress()
{
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  // Ignore debounce
  if(interruptTime - lastInterruptTime > 200) 
    isReversed = !isReversed;

  lastInterruptTime = interruptTime;
}

void printPacmanStats(byte col, byte row)
{
  Serial.print("Pacman position: ");
  Serial.print(col);
  Serial.print(" :: ");
  Serial.println(row);
  Serial.print("Pacman direction: ");
  Serial.println(isReversed ? "Reversed" : "Normal");
  Serial.println("====================\n");
}

void setup()
{
    for(int i = 3; i < 13; i++)
      pinMode(i, OUTPUT);

    isReversed = false;
    
    lcd.begin();
    lcd.backlight();
    lcd.createChar(0, pacman);
    lcd.createChar(1, pacmanReverse);
    lcd.createChar(2, point);
    lcd.createChar(3, pacmanClosed);

    Serial.begin(9600);
    while(!Serial)
      delay(10);
      
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPress, RISING);
}

void loop()
{  
  if(isReversed)
  {
    for(int i = 1; i >= 0; i--)
    {
      for(int j = 15; j >= 0; j--)
      {
        drawPoints(j, i);
        lcd.setCursor(j, i);
        if(j % 2)
          lcd.write(1);
        else
          lcd.write(3);
        
        printPacmanStats(j, i);
        directionIndicator(); // 180ms delay
        lcd.clear();

        if(!isReversed) break;
      }
  
      if(!isReversed) break;
    }
  } else
  {
    for(int i = 0; i < 2; i++)
    {
      for(int j = 0; j < 16; j++)
      {  
        drawPoints(j, i);
        lcd.setCursor(j, i);
        if(j % 2)
          lcd.write(0);
        else
          lcd.write(3);
        
        printPacmanStats(j, i);
        directionIndicator(); // 180ms delay
        lcd.clear();

        if(isReversed) break;
      }
  
      if(isReversed) break;
    }
  }
}
