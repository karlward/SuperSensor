/**
 * SuperSensor - Sensor reading with moving average baked-right-in!
 * 
 * SuperSensor reads digital or analog values from an Arduino pin, stores a 
 * configurable number of recent values, and provides easy access to mean, 
 * median, and standard deviation for the recent values. 
 * 
 * Copyright 2012 Karl Ward
 * See the file CREDITS for details on external code referenced/incorporated
 * See the file COPYING for details on software licensing
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Version 0.2 */ 

#include "Arduino.h"
#include "SuperSensor.h"

// Constructor
SuperSensor::SuperSensor(int pin, byte type, int sample_size) {
  _pin = pin; // Arduino pin number
  _type = type; // SUPERSENSOR_ANALOG or SUPERSENSOR_DIGITAL
  _sample_size = sample_size; // how many values to use for mean, median, etc. 
  int _values[_sample_size]; // create array of specified size
  _values_count = 0; // no values stored yet
  int _median_values[_sample_size]; // create array of specified size
  _median_values_count = 0; // no values stored yet for median calculation 
}

int SuperSensor::read() {
  // shift everything over 1 position, discarding last position
  for (int i = (sizeof(_values) / sizeof(int)) - 1; i > 0; i--) { 
    _values[i] = _values[i-1]; 
  } 

  // read the pin, setting first element of _value array to latest value
  if (_type == SUPERSENSOR_ANALOG) { 
    _values[0] = analogRead(_pin);
  else if (_type == SUPERSENSOR_DIGITAL) { 
    _values[0] = digitalRead(_pin); 
  } 

  // keep track of how many values we have in _values array
  if (_values_count < _sample_size) { 
    _values_count++; 
  }

  // return the latest value
  return(_values[0]); // first element of _values is always latest value
}

int SuperSensor::mean() { 
  long sum = 0;
  // sum all values
  // NOTE: we're doing floating point math in long rather than float
  for (int i=0; i < _values_count; i++) { 
    sum = sum + (_values[i] * 100); // multiply by 100 to do FP math
  }
  _mean = (long) (sum / _values_count); // FIXME: is long cast necessary?
  // figure out rounding, then divide by 100 to correct floating point
  if (_mean % 100 < 50) { 
    _mean = _mean / 100; // round down
  } 
  else { 
    _mean = (_mean / 100) + 1; // round up
  }
  return(_mean); // FIXME: cast to int? 
}

int SuperSensor::median() { 
  // erase old readings, we only want the freshness
  _median_values_count = 0; // reset the counter
  // NOTE: There is no simple way to delete values within an array in C++,
  //   without using a vector or a pointer. This means _median_values 
  //   can contain old/garbage data, so do not access it directly.

  // create an ordered array of the latest values 
  for (int i=0; i < _values_count; i++) { 
    _ordered_insert(_values[i]); // insert into _median_values array
  } 
  
  // median is the element in the middle of the ordered list of values
  // FIXME: should we use _median_values_count instead of _values_count ?
  int midpoint = (int) _values_count / 2; 
  if (_values_count % 2 == 1) { // we have an odd number of values
    _median = _median_values[midpoint]; 
  } 
  else { // we have an odd number of values, so get mean of midpoint pair
    _median = (_median_values[midpoint] + _median_values[midpoint+1]) / 2; 
  }
  return(_median); 
}

float SuperSensor::stdev() { 
  // make sure we have the most recent mean calculated
  mean();

  // standard deviation calculation  
  long sum = 0; 
  for (int i=0; i < _values_count; i++) { 
    sum = sum + (_values[i] - _mean)^2; 
  } 
  _stdev = sqrt(sum / (float) _values_count); 
  
  return(_stdev); 
} 

// NOTE: overloaded method
void SuperSensor::_ordered_insert(int value) { 
  _ordered_insert(value, 0); // call overloaded method with position arg
}
 
// NOTE: overloaded method, and recursive too
void SuperSensor::_ordered_insert(int value, int pos) { 
  for (int i=pos; i < _values_count; i++) { 
    if (_median_values_count < _values_count) { 
      if (i == _median_values_count) { 
        _median_values[i] = value; 
        _median_values_count++; 
      }
      else if (value < _median_values[i]) {
        _ordered_insert(_median_values[i], i+1); 
        _median_values[i] = value;   
      } 
      else if (value >= _median_values[i]) { 
        _ordered_insert(value, i+1); 
      }
    }
  }
} 

