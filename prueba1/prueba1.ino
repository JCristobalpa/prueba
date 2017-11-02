#ifndef BUTTON_H
#define BUTTON_H
#define PULLUP HIGH
#define PULLDOWN LOW
#define CURRENT 0
#define PREVIOUS 1
#define CHANGED 2
class Button{
 public:
 Button(uint8_t buttonPin, uint8_t buttonMode=PULLDOWN);
 void pullup();
 void pulldown();
 bool isPressed();
 bool wasPressed();
 bool stateChanged();
bool uniquePress();
 private: 
  uint8_t pin;
 uint8_t mode;
 uint8_t state;
};
#endif
Button::Button(uint8_t buttonPin, uint8_t buttonMode){
this->pin=buttonPin;
 pinMode(pin,INPUT);
buttonMode==PULLDOWN ? pulldown() : pullup();
 state = 0;
 bitWrite(state,CURRENT,!mode);
}
/*
|| Set pin HIGH as default
*/
void Button::pullup(void){
mode=PULLUP;
digitalWrite(pin,HIGH);
}
/*
|| Set pin LOW as default
*/
void Button::pulldown(void){
mode=PULLDOWN;
//digitalWrite(pin,LOW);
}
/*
|| Return the bitWrite(state,CURRENT, of the switch
*/
bool Button::isPressed(void){
 bitWrite(state,PREVIOUS,bitRead(state,CURRENT));
 if (digitalRead(pin) == mode){
 bitWrite(state,CURRENT,false);
 } else {
 bitWrite(state,CURRENT,true);
 }
 if (bitRead(state,CURRENT) != bitRead(state,PREVIOUS)){
 bitWrite(state,CHANGED,true);
 }else{
 bitWrite(state,CHANGED,false);
 }
return bitRead(state,CURRENT);
}
/*
|| Return true if the button has been pressed
*/
bool Button::wasPressed(void){
 if (bitRead(state,CURRENT)){
 return true;
 } else {
 return false;
 }
}
/*
|| Return true if state has been changed
*/
bool Button::stateChanged(void){
 return bitRead(state,CHANGED);
}
/*
|| Return true if the button is pressed, and was not pressed before
*/
bool Button::uniquePress(void){
 return (isPressed() && stateChanged());
}
Button b1 = Button(2,PULLUP);
Button b2 = Button(3,PULLUP);
unsigned long t1, t2;
int cuentaled;
int tblink;
int cc=0;
void setup() {
 Serial.begin(9600);
 pinMode(13, OUTPUT);
 pinMode(4, OUTPUT);
 t1=millis();
}
// la parte anterior corresponde con la biblioteca button
// el código principal comienza aquí
void blink (int x,int y,int t) {
 for (int i=0; i<x; i++) {
 digitalWrite(y, HIGH);
 delay(t);
 digitalWrite(y, LOW);
 delay(t);
 }
}
void blink13 (int t){
 if (millis()-t1>=t){
 t1 = millis();
 digitalWrite(13, !digitalRead(13));
  }
}
void compruebaparpadeo(){
 if (cuentaled!=0){
 if (millis()-t2>=tblink){
 t2 = millis();
 digitalWrite(4, !digitalRead(4));
 --cuentaled;
 }
 }
}
void loop() {
blink13(500);
compruebaparpadeo();
if (cuentaled == 0 && b1.uniquePress()) {
 Serial.println(++cc);
 cuentaled = 5*2;
 tblink = 500;
 t2 = millis();
 }
 if (cuentaled == 0 && b2.uniquePress()) {
 Serial.println(--cc);
 cuentaled = 3*2;
 tblink = 300;
 t2 = millis();
 }
delay(10);

}
