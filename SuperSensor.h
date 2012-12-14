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

class SuperSensor {
  public:
    SuperSensor(int pin);
    int read();
    int mean(); 
    int median(); 
  private:
    int _pin;
    int _values_count;
    int _values[10]; 
    void _update(); 
};

#endif

