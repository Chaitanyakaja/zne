#include <Arduino.h>

/*******************Demo for MG-811 Gas Sensor Module V1.1*****************************
Author:  Tiequan Shao: tiequan.shao@sandboxelectronics.com
         Peng Wei:     peng.wei@sandboxelectronics.com
         Modified by Leff from DFRobot, leff.wei@dfrobot.com, 2016-4-21, make the algorithm clearer to user
Lisence: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 
Note:    This piece of source code is supposed to be used as a demostration ONLY. More
         sophisticated calibration is required for industrial field application.

                                                            Sandbox Electronics    2012-05-31
**************************************Pins**********************************************/
 int relayPin = 6;
 int tempPin = 1;  //for temp
 #define         MG_PIN                       (0)     //c02; define which analog input channel you are going to use
 int fanPulse = 5;
 int fanPin = 7;
 

/************************Hardware Related Macros (C02) *********|***************************/
#define         BOOL_PIN                     (2)     //Arduino D2-CO2 sensor digital pinout, labled with "D" on PCB
#define         DC_GAIN                      (8.5)   //define the DC gain of amplifier

/***********************Software Related Macros (C02) ************************************/
#define         READ_SAMPLE_TIMES            (10)     //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_INTERVAL         (50)    //define the time interval(in milisecond) between each samples in
//normal operation

/**********************Application Related Macros (C02) **********************************/
//These values differ from sensor to sensor. User should derermine this value.
#define         ZERO_POINT_X                 (2.602) //lg400=2.602, the start point_on X_axis of the curve
#define         ZERO_POINT_VOLTAGE           (0.324) //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define         MAX_POINT_VOLTAGE            (0.265) //define the output of the sensor in volts when the concentration of CO2 is 10,000PPM
#define         REACTION_VOLTGAE             (0.059) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2

/*****************************Globals***********************************************/
int c02;
float           CO2Curve[3]  =  {ZERO_POINT_X, ZERO_POINT_VOLTAGE, (REACTION_VOLTGAE / (2.602 - 4))};
int previous = 400;  //sets c02 start value at its lowermost reading
int getC02();
float MGRead(int mg_pin);
int  MGGetPercentage(float volts, float *pcurve);

float temp;
int val;  //for temp]
float getTemp(char x);

void relayOn();
void relayOff();
//Two points are taken from the curve.With these two points, a line is formed which is
//"approximately equivalent" to the original curve. You could use other methods to get more accurate slope

//CO2 Curve format:{ x, y, slope};point1: (lg400=2.602, 0.324), point2: (lg10000=4, 0.265)
//slope = (y1-y2)(i.e.reaction voltage)/ x1-x2 = (0.324-0.265)/(log400 - log10000)

void setup() {
  Serial.begin(9600);                              //UART setup, baudrate = 9600bps
  pinMode(BOOL_PIN, INPUT);                        //set pin to input
  digitalWrite(BOOL_PIN, HIGH);                    //turn on pullup resistors
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(relayPin,OUTPUT);
  relayOff();
  pinMode(fanPulse, INPUT);
  digitalWrite(fanPulse,LOW);
}

void loop() {
 //*
//CO2
  c02 = getC02();
  Serial.print("Co2"); //how node red tells what sensor this is
  if (c02 == -1) {          //if C02 value is out of sensor range
      if (previous>6000){
        previous = 10000;    // if higher, sensor value will be interpreted as upper bound (10,000)
      } else{
        previous = 400;       // if lower, sensor value will be interpreted as lower bound (400)
      }
      Serial.println(previous);
  }else{

    previous = c02; //saves this value for next loop to determine if out of range is upper or lower bound
    
    if(c02 > 5000){  //if CO2 is above threshold, turn on fan, otherwise turn/keep it off
      relayOn(200);   //number is fan speed, 0 is lowest, 255 is highest  
    }else if(c02 < 2000){
      relayOff();
    }
    Serial.println(c02);
  }

  //temp
  temp = getTemp('f');//f for fahrenheit, c for celsius
  Serial.print("Temp"); //for node-red to know which sensor
  Serial.println(temp);
//*/
  delay(1000);
}
