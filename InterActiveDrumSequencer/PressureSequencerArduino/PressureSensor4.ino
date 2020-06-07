/******************************************************************************
Force_Sensitive_Resistor_Example.ino
Example sketch for SparkFun's force sensitive resistors
  (https://www.sparkfun.com/products/9375)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Create a voltage divider circuit combining an FSR with a 3.3k resistor.
- The resistor should connect from A0 to GND.
- The FSR should connect from A0 to 3.3V
As the resistance of the FSR decreases (meaning an increase in pressure), the
voltage at A0 should increase.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
const int FSR_PIN = A0; // Pin connected to FSR/resistor divider
const int FSR_PIN2 = A1;
const int FSR_PIN3 = A2;
const int FSR_PIN4 = A3;
const int buttonPin = 19;
int buttonState = 0;
const int SENSOR_PIN = A4;      // Analog input pin
int sensorValue = 0;
// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
// their value's below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0; // Measured resistance of 3.3k resistor
const float VCC2 = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV2 = 3230.0; // Measured resistance of 3.3k resistor
const float VCC3 = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV3 = 3230.0; // Measured resistance of 3.3k resistor
const float VCC4 = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV4 = 3230.0; // Measured resistance of 3.3k resistor
void setup() 
{
  Serial.begin(9600);
  pinMode(FSR_PIN, INPUT);
  pinMode(FSR_PIN2, INPUT);
  pinMode(FSR_PIN3, INPUT);
  pinMode(FSR_PIN4, INPUT);
   pinMode(buttonPin, INPUT);
  digitalWrite(SENSOR_PIN, INPUT); //enable pullup resistor
}

void loop() 
{
 buttonState = digitalRead(buttonPin);
   Serial.println(buttonState);


  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:

  // Read the voltage from the softpot (0-1023)
 sensorValue = analogRead(SENSOR_PIN);
//int softpotReading = analogRead(SENSOR_PIN);
int currentpotRead;
int lastRead;
currentpotRead = sensorValue;
if (currentpotRead > 5) 
{ 
  if (abs(lastRead - currentpotRead) > 5)
  {
      
      usbMIDI.sendControlChange(9, map(currentpotRead, 0, 1023, 0, 127), 1);
      lastRead = currentpotRead;
  }
}
Serial.println(sensorValue);
//delay(200);
  
  int fsrADC = analogRead(FSR_PIN);
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (fsrADC != 0) // If the analog reading is non-zero
  {
    // Use ADC reading to calculate voltage:
    float fsrV = fsrADC * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR = R_DIV * (VCC / fsrV - 1.0);
    Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    float force;
    float fsrG = 1.0 / fsrR; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR <= 600) 
      force = (fsrG - 0.00075) / 0.00000032639;
    else
      force =  fsrG / 0.000000642857;
      force = map(force, 0, 6000, 0, 127);
      if (force > 0) {
      usbMIDI.sendControlChange(5, force, 1);
      }
    Serial.println("Force: " + String(force) + " g");
    Serial.println();
//delay(100);
  }
    int fsrADC2 = analogRead(FSR_PIN2);
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (fsrADC2 != 0) // If the analog reading is non-zero
  {
    // Use ADC reading to calculate voltage:
    float fsrV2 = fsrADC2 * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR2 = R_DIV2 * (VCC / fsrV2 - 1.0);
    Serial.println("Resistance: " + String(fsrR2) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    float force2;
    float fsrG2 = 1.0 / fsrR2; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR2 <= 600) 
      force2 = (fsrG2 - 0.00075) / 0.00000032639;
    else
      force2 =  fsrG2 / 0.000000642857;
      force2 = map(force2, 0, 6000, 0, 127);
      if (force2 > 0) {
      usbMIDI.sendControlChange(6, force2, 1);
      }
    Serial.println("Force2: " + String(force2) + " g");
    Serial.println();
    

  // delay(100);
  }
  else
  {
    // No pressure detected
  }

   int fsrADC3 = analogRead(FSR_PIN3);
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (fsrADC3 != 0) // If the analog reading is non-zero
  {
    // Use ADC reading to calculate voltage:
    float fsrV3 = fsrADC3 * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR3 = R_DIV3 * (VCC / fsrV3 - 1.0);
    Serial.println("Resistance: " + String(fsrR3) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    float force3;
    float fsrG3 = 1.0 / fsrR3; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR3 <= 600) 
      force3 = (fsrG3 - 0.00075) / 0.00000032639;
    else
      force3 =  fsrG3 / 0.000000642857;
      force3 = map(force3, 0, 6000, 0, 127);
       if (force3 > 0) {
      usbMIDI.sendControlChange(7, force3, 1);
       }
    Serial.println("Force3: " + String(force3) + " g");
    Serial.println();
    

  //delay(100);
  }
  else
  {
    // No pressure detected
  }
   int fsrADC4 = analogRead(FSR_PIN4);
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (fsrADC4 != 0) // If the analog reading is non-zero
  {
    // Use ADC reading to calculate voltage:
    float fsrV4 = fsrADC4 * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR4 = R_DIV4 * (VCC / fsrV4 - 1.0);
    Serial.println("Resistance: " + String(fsrR4) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    float force4;
    float fsrG4 = 1.0 / fsrR4; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR4 <= 600) 
      force4 = (fsrG4 - 0.00075) / 0.00000032639;
    else
      force4 =  fsrG4 / 0.000000642857;
      force4 = map(force4, 0, 6000, 0, 127);
       if (force4 > 0) {
      usbMIDI.sendControlChange(8, force4, 1);
       }
    Serial.println("Force4: " + String(force4) + " g");
    Serial.println();
    
  }
  else
  {
    // No pressure detected
  }
   if (buttonState == HIGH) {
  //  int on;
   // on = 1;
          usbMIDI.sendControlChange(10, 1, 1);
  }
  if (buttonState == LOW)  {
  //  int off;
   // off = 0;
     usbMIDI.sendControlChange(10, 0, 1);
  }
  
   delay(100);
  }
  
