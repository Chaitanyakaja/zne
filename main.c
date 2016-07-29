void setup() {
  Serial.begin(9600);                              //UART setup, baudrate = 9600bps
  pinMode(BOOL_PIN, INPUT);                        //set pin to input
  digitalWrite(BOOL_PIN, HIGH);                    //turn on pullup resistors
  Serial.print("MG-811 Demostration\n");
}

void loop() {
  int percentage;
  float volts;

  volts = MGRead(MG_PIN);
  Serial.print( "SEN0159:" );
  Serial.print(volts);
  Serial.print( "V           " );

  percentage = MGGetPercentage(volts, CO2Curve);
  Serial.print("CO2:");
  if (percentage == -1) {
    Serial.print("Under heating/beyond range(400~10,000)");
  } else {
    Serial.print(percentage);
  }
  Serial.print( "ppm" );

  Serial.print( "       Time point:" );
  Serial.print(millis());
  Serial.print("\n");

  if (digitalRead(BOOL_PIN) ) {
    Serial.print( "=====BOOL is HIGH======" );
  } else {
    Serial.print( "=====BOOL is LOW======" );
  }
  Serial.print("\n");
  delay(1000);
}
