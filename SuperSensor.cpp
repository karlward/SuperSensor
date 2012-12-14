/*
 * SuperSensor - Sensor reading with moving average baked-right-in!
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
SuperSensor::SuperSensor(int pin) {
  _pin = pin;
  _values_count = 0; // no values stored yet
  _median_values_count = 0; // no values stored yet
}

int SuperSensor::read() {
  _update(analogRead(_pin)); 
  return(_values[0]); // first element of _values is always latest value
}

int SuperSensor::mean() { 
  int sum = 0;
  for (int i=0; i < _values_count; i++) { 
    sum = sum + _values[i]; 
  }
  _mean = (int) (sum / _values_count); 
  return(_mean); 
}

int SuperSensor::median() { 
  _median_values = {}; // erase old readings, we only want the freshness
  _median_values_count = 0; // reset the counter too

  // create an ordered array of the latest values 
  for (int i=0; i < _values_count; i++) { 
    _ordered_insert(_values[i]); // insert into _median_values array
  } 
  
  // median is the element in the middle of the ordered list of values
  int midpoint = (int) _values_count / 2; 
  if (_values_count % 2 == 1) { // we have an odd number of values
    _median = _median_values[midpoint]; 
  } 
  else { // we have an odd number of values, so get mean of midpoint pair
    _median = (_median_values[midpoint] + _median_values[midpoint+1]) / 2; 
  }
  return(_median); 
}


// NOTE: overloaded method
void SuperSensor::_ordered_insert(int v) { 
  _ordered_insert(v, 0); // call overloaded method specifying position arg
}
 
// NOTE: overloaded method, and recursive too
void SuperSensor::_ordered_insert(int v, int pos) { 
  for (int i=pos; i < _values_count; i++) { 
    if (_median_values_count < _values_count) { 
      if (i == _median_values_count) { 
        _median_values[i] = v; 
        _median_values_count++; 
      }
      else if (v < _median_values[i]) {
        _ordered_insert(_median_values[i], i+1); 
        _median_values[i] = v;   
        _median_values_count++; 
      } 
      else if (v >= _median_values[i]) { 
        _ordered_insert(v, i+1); 
      }
    }
  }
} 

void SuperSensor::_update(int latestValue) { 
  for (int i = (sizeof(_values) / sizeof(int)) - 1; i > 0; i--) { 
    _values[i] = _values[i-1]; // shift everything over 1 position, discarding last position
  } 
  _values[0] = latestValue; // set position 1 to current value
  if (_values_count < 10) { 
    _values_count++; 
  }
}

