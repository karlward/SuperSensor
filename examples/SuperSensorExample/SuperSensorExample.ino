/* 
 * SuperSensor example code
 * 
 * Simple example demonstrating the "SuperSensor" Arduino library
 * 
 * This code reads an analog sensor and outputs the current and mean 
 * values to the Arduino hardware serial port.  
 *
 * Remember that this is a simple example.  You can use more than one 
 * SuperSensor in your own code. 
 * 
 * Author: Karl Ward
 * License: this example code is released into the public domain
 * (note that the SuperSensor library itself is not public domain)
 */


#include "SuperSensor.h"

SuperSensor sensor(A0); // we're going to do analogRead on pin A0

void setup() { 
  Serial.begin(9600); // open serial port for debugging output
} 

void loop() { 
  int currentValue = sensor.read();
  int meanValue = sensor.mean(); 
  Serial.print("current value is "); 
  Serial.print(currentValue); 
  Serial.print(", mean value is "); 
  Serial.println(meanValue); 
  delay(250); // short delay so we don't flood the serial monitor
}
