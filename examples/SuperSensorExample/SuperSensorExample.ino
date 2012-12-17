/* 
 * SuperSensor example code
 * 
 * Simple example demonstrating the "SuperSensor" Arduino library
 * 
 * This code reads an analog sensor and outputs the current, mean,  
 * and median values to the Arduino hardware serial port.  
 *
 * Remember that this is a simple example.  You can use more than one 
 * SuperSensor in your own code. 
 * 
 * Author: Karl Ward
 * License: this example code is released into the public domain
 * (note that the SuperSensor library itself is not public domain)
 */


#include "SuperSensor.h"

// we're going to do analogRead on pin A0, storing 10 values for analysis
SuperSensor sensor(A0, SUPERSENSOR_DIGITAL, 10); 

void setup() { 
  Serial.begin(9600); // open serial port for debugging output
} 

void loop() { 
  int currentValue = sensor.read();
  int meanValue = sensor.mean(); 
  int medianValue = sensor.median(); 
  Serial.print("current value is "); 
  Serial.print(currentValue); 
  Serial.print(", mean is "); 
  Serial.print(meanValue); 
  Serial.print(", median is "); 
  Serial.println(medianValue); 
  delay(250); // short delay so we don't flood the serial monitor
}
