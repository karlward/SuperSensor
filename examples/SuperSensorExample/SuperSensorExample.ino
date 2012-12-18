/* 
 * SuperSensor example code
 * 
 * Simple example demonstrating the "SuperSensor" Arduino library
 * 
 * This code reads two sensors (one analog, one digital) and outputs the 
 * current, mean, and median values to the Arduino hardware serial port.  
 *
 * Author: Karl Ward
 * License: this example code is released into the public domain
 * (note that the SuperSensor library itself is not public domain)
 */


#include "SuperSensor.h"

// we're going to do analogRead on pin A0, storing 100 values for analysis
SuperSensor analogSensor(A0, SUPERSENSOR_ANALOG, 100); 

// we're going to do digitalRead on pin 2, storing 10 values for analysis
SuperSensor digitalSensor(2, SUPERSENSOR_DIGITAL, 10); 

void setup() { 
  Serial.begin(9600); // open serial port for debugging output
} 

void loop() { 
  int analogValue = analogSensor.read();
  int analogMean = analogSensor.mean(); 
  int analogMedian = analogSensor.median(); 
  Serial.print("analog sensor value is "); 
  Serial.print(analogValue); 
  Serial.print(", mean is "); 
  Serial.print(analogMean); 
  Serial.print(", median is "); 
  Serial.println(analogMedian);

  int digitalValue = digitalSensor.read();
  int digitalMean = digitalSensor.mean(); 
  int digitalMedian = digitalSensor.median(); 
  Serial.print("digital sensor value is "); 
  Serial.print(digitalValue); 
  Serial.print(", mean is "); 
  Serial.print(digitalMean); 
  Serial.print(", median is "); 
  Serial.println(digitalMedian);  
  
  delay(250); // short delay so we don't flood the serial monitor
}
