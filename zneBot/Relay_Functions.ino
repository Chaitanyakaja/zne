#include <Arduino.h>

void relayOn(int s){
  digitalWrite(relayPin, HIGH);
  analogWrite(fanPin, s);
}

void relayOff(){
  digitalWrite(relayPin, LOW);
}

