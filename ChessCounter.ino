//Chess Timer: Two timers controlled by one button
//Code Written by Scott Faulkner on 06/18/2026

//Setting up LCD display
#include <LiquidCrystal.h>
int rs=7;
int en=8;
int d4=9;
int d5=10;
int d6=11;
int d7=12;
int buttonCounter=0;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

//Other variables
int buttonPin=5;
int Counter=0;
bool Timer1Running = false;
bool Timer2Running = false;
unsigned long startTime1;
unsigned long startTime2;
unsigned long accumulatedTime1=0;
unsigned long accumulatedTime2=0;
unsigned long countdownFrom1=15000;
unsigned long countdownFrom2=15000;
int lastButtonState=HIGH; //

void setup() {
  lcd.begin(16,2);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
 
}

void loop() {

//Game displays
lcd.setCursor(0,0);
lcd.print("Player 1: ");
lcd.setCursor(0,1);
lcd.print("Player 2: ");
  int buttonState=digitalRead(buttonPin);

  if (buttonState==LOW && lastButtonState==HIGH) { //If button pressed
    delay(50); //debounce
    Counter++; 
    Timer1Running = !Timer1Running;
    Timer2Running = !Timer1Running;

    if (Counter==1) { //First button press
      startTime1=millis();
      accumulatedTime2 += (millis()-startTime2)-startTime1;
    }
    else if (Timer1Running) { //All subsequent presses
      startTime1=millis();
      accumulatedTime2 += (millis()-startTime2);
      Serial.println(accumulatedTime2);
    }
    else {
      startTime2=millis();
      accumulatedTime1 += (millis()-startTime1);
      }
    
  }

lastButtonState=buttonState;


  if(Timer1Running) { //Player 1 Countdown
    unsigned long currentElapsed1 = accumulatedTime1 + (millis()-startTime1);
    
    if (currentElapsed1 < countdownFrom1) {
      long timeLeft1 = (countdownFrom1 - currentElapsed1)/1000;
      if (timeLeft1>=10){
      lcd.setCursor(10,0);
      lcd.print(1+timeLeft1);
      }
      else if(timeLeft1<10){
        lcd.setCursor(10,0);
        lcd.print(" ");
      lcd.print(timeLeft1);
      }
  
      }
    
   else {
      Timer1Running=false;
      accumulatedTime1=countdownFrom1;
      lcd.clear();
      lcd.print("Player 2 wins!");
      delay(5000);
      lcd.clear();
    }
  }

  if(Timer2Running) { //Player 2 countdown
    unsigned long currentElapsed2 = accumulatedTime2 + (millis()-startTime2);
    
    if (currentElapsed2 < countdownFrom2) {
      long timeLeft2 = (countdownFrom2 - currentElapsed2)/1000;
      if (timeLeft2>=10){
      lcd.setCursor(10,1);
      lcd.print(1+timeLeft2);
      }
      else if(timeLeft2<10){
        lcd.setCursor(10,1);
        lcd.print(" ");
      lcd.print(timeLeft2);
      }
  
      }
    
   else {
      Timer2Running=false;
      accumulatedTime2=countdownFrom2;
      lcd.clear();
      lcd.print("Player 1 wins!");
      delay(5000);
      lcd.clear();
    }
  }

  }

