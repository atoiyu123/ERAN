#include <Wire.h>
#include <i2c_keypad.h>
#include <LCDI2C.h>

#define PASSWORD1 "1"
#define PASSWORD2 "2"
#define PASSWORD3 "3"

int led_green =PIN_PB0;
int led_red = PIN_PB1;
int sensor_pin =PIN_PD0;
int sensorPin = PIN_PC3;
int sensorValue = 0;
int percentValue = 0;


I2CKEYPAD keypad;
LCDI2C lcd(0x27);

String bufPassword = "";

void onKeypad(char key) {
  sensorValue = analogRead(sensorPin);
  percentValue = map(sensorValue, 1023, 200, 0, 100);
  pinMode(led_green, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(sensor_pin, INPUT);
  bufPassword += key;
  
  if (bufPassword.length() == 1) {
    keypad.on(PRESS, NULL);
    bool PasswordCorrect1 = bufPassword == PASSWORD1;
    bool PasswordCorrect2 = bufPassword == PASSWORD2;
    bool PasswordCorrect3 = bufPassword == PASSWORD3;
    lcd.clear();

    lcd.setCursor(0,0);
    if (PasswordCorrect1){
      lcd.print("Cactus  ");
      lcd.setCursor(0,1);
      lcd.print("Percent: ");
      lcd.print(percentValue);
      lcd.print("%");
      if ((percentValue >= 15)&&(percentValue <= 100)){
      digitalWrite(led_green, HIGH);
      digitalWrite(led_red, LOW);
    }
        else if ((percentValue >= 0)&&(percentValue<=5)){
        digitalWrite(led_green, LOW);
        digitalWrite(led_red, HIGH);
        }
      delay(3000);
      digitalWrite(led_green, LOW);
      digitalWrite(led_red, LOW);
    }
    if (PasswordCorrect2){
      lcd.print("  Pereskiopsis   ");
      lcd.setCursor(0,1);
      lcd.print("Percent: ");
      lcd.print(percentValue);
      lcd.print("%");
      if ((percentValue >= 70)&&(percentValue <= 100)){
      digitalWrite(led_green, HIGH);
      digitalWrite(led_red, LOW);
    }
        else if ((percentValue >= 0)&&(percentValue<=30)){
        digitalWrite(led_green, LOW);
        digitalWrite(led_red, HIGH);
        }
      delay(3000);
      digitalWrite(led_green, LOW);
      digitalWrite(led_red, LOW);
    }
    if (PasswordCorrect3){
      lcd.print("  Myrtillocacyus  ");
      lcd.setCursor(0,1);
      lcd.print("Percent: ");
      lcd.print(percentValue);
      lcd.print("%");
       if ((percentValue >= 50)&&(percentValue <= 100)){
      digitalWrite(led_green, HIGH);
      digitalWrite(led_red, LOW);
    }
        else if ((percentValue >= 0)&&(percentValue<=15)){
        digitalWrite(led_green, LOW);
        digitalWrite(led_red, HIGH);
        }
      delay(3000);
      digitalWrite(led_green, LOW);
      digitalWrite(led_red, LOW);
    }
    else{ 
      lcd.print("     NO WAY      ");
      delay(3000);
    }

    reset();
    bufPassword = "";
  }
}

void reset() {
  lcd.clear();

  lcd.setCursor(0);
  lcd.print("  Enter Plant ");
  lcd.setCursor(6, 1);
  keypad.on(PRESS, onKeypad);
}

void setup() {
  lcd.begin(16, 2);
  keypad.begin(0x20, 100);

  reset();
}

void loop() {
  keypad.scand();
}
