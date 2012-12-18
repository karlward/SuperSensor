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

#ifndef SuperSensor_h
#define SuperSensor_h

#include "Arduino.h"

const byte SUPERSENSOR_ANALOG = 1; 
const byte SUPERSENSOR_DIGITAL = 2; 

class SuperSensor {
  public:
    SuperSensor(int, byte, int);
    int read();
    int mean(); 
    int median(); 
    float stdev(); 
  private:
    int _pin;
    byte _type;
    int _sample_size;
    int _values[];
    int _values_count;
    long _mean;
    int _median;
    float _stdev; 
    int _median_values[]; 
    int _median_values_count;
    void _ordered_insert(int value);
    void _ordered_insert(int value, int pos);
    void _update(int); 
};

#endif

