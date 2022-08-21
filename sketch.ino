#include <LiquidCrystal.h>
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262
// portas
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int plusButton = 13;
int plusLed = 8;
int minusButton = 10;
int minusLed = 9;
int buzzer = 6;
// melodia
int pauseBetweenNotes = 200;
int totalNotes = 8;
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};
int number = 0;
void setup() {
  lcd.begin(16, 3);
  pinMode(minusButton, INPUT);
  pinMode(plusButton, INPUT);
  pinMode(plusLed, OUTPUT);
  pinMode(minusLed, OUTPUT);
  lcd.print("APERTE O BOTAO");
}
void loop() {
  lcd.setCursor(4, 0);
  checkPlusButton();
  checkMinusButton();
}
 
void checkMinusButton() {
  if(digitalRead(minusButton) == HIGH) {
    number--;
    onAndOffLed(minusLed, plusLed);
    displayNumberInLCD();
  }
}
void checkPlusButton() {
  if(digitalRead(plusButton) == HIGH) {
    number++;
    onAndOffLed(plusLed, minusLed);
    displayNumberInLCD();
  }
}
void displayNumberInLCD() {
  lcd.clear();
  lcd.print(number);
  checkIfMultipleOf100();
  delay(100);
}
void onAndOffLed(int p1, int p2) {
  digitalWrite(p1, HIGH);
  digitalWrite(p2, LOW);
}
void checkIfMultipleOf100() {
  if (number % 100 == 0 && number != 0){
    makeBeepSound();
    returnNumberToCenter();
  }
}
void returnNumberToCenter() {
  for (int posicao = 0; posicao < totalNotes; posicao++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }
}
void makeBeepSound() {
  for (int i = 0; i < totalNotes; i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(buzzer, melody[i], noteDuration);
    lcd.scrollDisplayRight();
    delay(pauseBetweenNotes);
    noTone(buzzer);
  }
}