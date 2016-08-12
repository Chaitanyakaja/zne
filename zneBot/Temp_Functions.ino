#include <Arduino.h>

float getTemp(char x){

    float mv;
    float cel;
    float fahr;

    val = analogRead(tempPin);
    mv = ( val/1024.0)*5000;
    cel = mv/10;
    fahr = (cel*9)/5 + 32;
    switch(x){
      case 'f' :
        return fahr;
        break;
      case 'c' :
        return cel;
        break;
    }
}
