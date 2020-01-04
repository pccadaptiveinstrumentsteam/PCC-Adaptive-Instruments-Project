#include <Bounce.h>

/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"
#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
// single one
//Adafruit_MPR121 cap = Adafruit_MPR121();
//multiple
Adafruit_MPR121 cap1 = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
//Adafruit_MPR121 cap3 = Adafruit_MPR121();
//Adafruit_MPR121 cap4 = Adafruit_MPR121();
// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;

uint16_t lasttouched2 = 0;
uint16_t currtouched2 = 0;

#define BUTTON1 0
#define BUTTON2 1
// Instantiate a Bounce object with a 5 millisecond debounce time
Bounce bouncer1 = Bounce(BUTTON1, 5); 
// Instantiate a Bounce object with a 5 millisecond debounce time
Bounce bouncer2 = Bounce(BUTTON2, 5); 


int noteValsArray [] [51] = {  
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
{0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24, 0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24, 26, 28, 29, 31, 33, 35, 36, 38, 40, 41, 43, 45, 47, 48, 50, 52, 53, 55, 57, 59, 60},
{0, 2, 3, 5, 7, 9, 10, 12, 14, 15, 17, 19, 21, 22, 24, 0, 2, 3, 5, 7, 9, 10, 12, 14, 15, 17, 19, 21, 22, 24, 26, 27, 29, 31, 33, 34, 36, 38, 39, 41, 43, 45, 46, 48, 50, 51, 53, 55, 57, 58, 60},
{0, 1, 3, 5, 7, 8, 10, 12, 13, 15, 17, 19, 20, 22, 24, 0, 1, 3, 5, 7, 8, 10, 12, 13, 15, 17, 19, 20, 22, 24, 25, 27, 29, 31, 32, 34, 36, 37, 39, 41, 43, 44, 46, 48, 49, 51, 53, 55, 56, 58, 60},
{0, 2, 4, 6, 7, 9, 11, 12, 14, 16, 18, 19, 21, 23, 24, 0, 2, 4, 6, 7, 9, 11, 12, 14, 16, 18, 19, 21, 23, 24, 26, 28, 30, 31, 33, 35, 36, 38, 40, 42, 43, 45, 47, 48, 50, 52, 54, 55, 57, 59, 60},
{0, 2, 4, 5, 7, 9, 10, 12, 14, 16, 17, 19, 21, 22, 24, 0, 2, 4, 5, 7, 9, 10, 12, 14, 16, 17, 19, 21, 22, 24, 26, 28, 29, 31, 33, 34, 36, 38, 40, 41, 43, 45, 46, 48, 50, 52, 53, 55, 57, 58, 60},
{0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 20, 22, 24, 0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 20, 22, 24, 26, 27, 29, 31, 32, 34, 36, 38, 39, 41, 43, 44, 46, 48, 50, 51, 53, 55, 56, 58, 60},
{0, 1, 3, 5, 6, 8, 10, 12, 13, 15, 17, 18, 20, 22, 24, 0, 1, 3, 5, 6, 8, 10, 12, 13, 15, 17, 18, 20, 22, 24, 25, 27, 29, 30, 32, 34, 36, 37, 39, 41, 42, 44, 46, 48, 49, 51, 53, 54, 56, 58, 60},
{0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70},
{0, 3, 7, 10, 14, 17, 21, 24, 27, 31, 34, 38, 41, 45, 48, 0, 3, 7, 10, 14, 17, 21, 24, 27, 31, 34, 38, 41, 45, 48, 51, 55, 0, 3, 7, 10, 14, 17, 21, 24, 27, 31, 34, 38, 41, 45, 48, 51, 55, 58, 62},
{0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 60, 0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 60, 63, 66, 69, 72, 75, 78, 81, 84, 87},
{0, 2, 3, 5, 6, 8, 9, 11, 12, 0, 2, 3, 5, 6, 8, 9, 11, 12, 14, 15, 17, 18, 20, 21, 23, 24, 26, 27, 29, 30, 32, 33, 35, 36, 38, 39, 41, 42, 44, 45, 47, 48, 50, 51, 53, 54, 56, 57, 59, 60, 62},
{0, 1, 3, 4, 6, 7, 9, 10, 12, 0, 1, 3, 4, 6, 7, 9, 10, 12, 13, 15, 16, 18, 19, 21, 22, 24, 25, 27, 28, 30, 31, 33, 34, 36, 37, 39, 40, 42, 43, 45, 46, 48, 49, 51, 52, 54, 55, 57, 58, 60, 61},
{0, 2, 4, 7, 9, 12, 14, 16, 19, 21, 24, 26, 28, 31, 33, 36, 38, 40, 43, 45, 48, 50, 52, 55, 57, 0, 2, 4, 7, 9, 12, 14, 16, 19, 21, 24, 26, 28, 31, 33, 36, 38, 40, 43, 45, 48, 50, 52, 55, 57, 60},
{0, 3, 5, 7, 10, 12, 15, 17, 19, 22, 24, 27, 29, 31, 34, 36, 39, 41, 43, 46, 48, 51, 53, 55, 58, 0, 3, 5, 7, 10, 12, 15, 17, 19, 22, 24, 27, 29, 31, 34, 36, 39, 41, 43, 46, 48, 51, 53, 55, 58, 60},
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, 12, 24, 36, 48, 0, 12, 24, 36, 48, 0, 12, 24, 36, 48, 0, 12, 24, 36, 48, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41}
                     };


// root note a 1 = + 41 midinotes
int rootNote = 41; //this is A1
int scaleNum = 0;

int chromatic = 0;
int ionian = 1;
int dorian = 2;
int phrygian = 3;
int lydian = 4;
int mixolydian = 5;
int aeolian = 6;
int locrian = 7;
int wholetone = 9;
int m791113 = 10;
int dim7 = 11;
int octatonic21 = 12;
int octatonic12 = 13;
int majorpentatonic = 14;
int minorpentatonic = 15;

int programChangeVal = 0;





void setup() {
    pinMode(BUTTON1, INPUT_PULLUP);
      pinMode(BUTTON2, INPUT_PULLUP);
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }

  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
 // /*    THIS IS TO DEBUG THE CHIPS
  if (!cap1.begin(0x5A)) {
    Serial.println("MPR121A not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121A found!");

    if (!cap2.begin(0x5B)) {
    Serial.println("MPR121B not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121B found!");
  // */
  /* 
    if (!cap.begin(0x5C)) {
    Serial.println("MPR121C not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121C found!");
  */
  scaleNum = aeolian;
    usbMIDI.setHandleControlChange(OnCC); // set handle for MIDI continuous controller messages
}

void loop() {
  
 // Update debouncer 
  boolean button1Changed = bouncer1.update();
   // Update debouncer 2
  boolean button2Changed = bouncer2.update();

 if ( bouncer1.fallingEdge()) {
  Serial.println("button1");
   //usbMIDI.sendControlChange(3, 127, 1);
   scaleNum = (scaleNum + 1) % 15
   programChangeVal = (programChangeVal + 1) % 15
   usbMIDI.sendProgramChange(programChangeVal, 1);
 }
  if ( bouncer2.fallingEdge()) {
    Serial.println("button2");
     usbMIDI.sendControlChange(9, 127, 1);
  }


  //   now cap stuff
  
  // Get the currently touched pads
  currtouched1 = cap1.touched();
currtouched2 = cap2.touched();
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
      Serial.print(i); Serial.println(" 1touched");
      usbMIDI.sendNoteOn((rootNote + noteValsArray[scaleNum][i]), 127, 3);
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
      Serial.print(i); Serial.println(" 1released");
      usbMIDI.sendNoteOff((rootNote + noteValsArray[scaleNum][i]), 0, 3);
    }
  }
  
      for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched2 & _BV(i)) && !(lasttouched2 & _BV(i)) ) {
      Serial.print(i); Serial.println(" 2touched");
      usbMIDI.sendNoteOn((rootNote + noteValsArray[scaleNum][i + 12]), 127, 3);
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched2 & _BV(i)) && (lasttouched2 & _BV(i)) ) {
      Serial.print(i); Serial.println(" 2released");
      usbMIDI.sendNoteOff((rootNote + noteValsArray[scaleNum][i + 12]), 0, 3);
    }
  }

  // reset our state
  lasttouched1 = currtouched1;
 lasttouched2 = currtouched2;
  // comment out this line for detailed data from the sensor!
  return;
  
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap1.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap1.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap1.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
/*
    // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap2.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap2.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap2.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  */



  
  // put a delay so it isn't overwhelming
  
  delay(10);
   usbMIDI.read();
}

void OnCC(byte channel, byte controller, byte value) {
  if(controller == 3) {
    scaleNum = (scaleNum + 1) % 15;
  }
  Serial.println("scale changed from incoming usbmidi cc # 3");
}
