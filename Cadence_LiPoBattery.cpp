/*
  File:         Cadence_LiPoBattery.h
  Version:      1.0.0
  Date:         8-Jan-2021
  Revision:     8-Jan-2021
  Author:       Jerome Drouin
  
  https://github.com/newEndeavour/Cadence_LiPoBattery
  library for the 3.7v Rechargeable LiPo Battery

  Credits: 

  Copyright (c) 2018-2021 Jerome Drouin  All rights reserved.  

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Versions:
  1.0.0		: Initial version

*/


#include "Cadence_LiPoBattery.h"
#include "Arduino.h"
#include <Wire.h>

 
// constructor using analog pin for Vbat
Cadence_LiPoBattery::Cadence_LiPoBattery(uint8_t _vbatpin) {

  // initialize this instance's variables	
  analog_Vbat_pin = _vbatpin;
  analog_Vcc_pin = -1;

  number_readings = 0;

}

// constructor using analog pin
Cadence_LiPoBattery::Cadence_LiPoBattery(uint8_t _vbatpin, uint8_t _vccpin) {

  // initialize this instance's variables	
  analog_Vbat_pin = _vbatpin;
  analog_Vcc_pin = _vccpin;

  number_readings = 0;

}


//  Initialises the object.
bool Cadence_LiPoBattery::Begin(void) {

	//if ((analog_Vbat_pin>-1) && (analog_Vcc_pin>-1))
	if (analog_Vbat_pin>-1)
  		return true;
  	else
    		return false;
}


// Reads the battery analog level and converts to voltage
void Cadence_LiPoBattery::Read(bool constrain_percent) {
long VbatSum = 0;
long VccSum  = 0;

  //increment readings ID
  number_readings++;

  //Voltage Divider factor as a function of R1 and R2: Df = R2 / (R1 + R2)
  //Div1_DF = Div1_R2 / (Div1_R1+Div1_R2);

  //Survey Batteries
  for (int i=0; i<ANALOG_READ_SAMPLES; i++) {
    VbatSum += analogRead(analog_Vbat_pin);
    VccSum += analogRead(analog_Vcc_pin);
    
    //Short delays between reads
    delay(50);    
  }
  
  Battery_VbatRawAnalog   = VbatSum / ANALOG_READ_SAMPLES;
  Battery_VccRawAnalog   = VccSum / ANALOG_READ_SAMPLES;
    
  //Voltage
  Battery_VbatVolts = ((float)Battery_VbatRawAnalog / (float)1023) * (float)REF_BATTERY_OUTPUT;
  Battery_VccVolts = ((float)Battery_VccRawAnalog / (float)1023) * (float)REF_BATTERY_OUTPUT;

  //Percent
  Battery_VbatPerct = Convert_Percent(Battery_VbatVolts, BATTERY_FULL, BATTERY_EMPTY, constrain_percent);
  Battery_VccPerct = Convert_Percent(Battery_VccVolts, BATTERY_FULL, BATTERY_EMPTY, constrain_percent);    
}




// Convert Volts to percentage
float Cadence_LiPoBattery::Convert_Percent(float inputVolts,float range_max, float range_min, bool clip) {
float perc;

  // Convert Volts to percentage
  perc = 100.0 * (inputVolts - range_min) / (range_max - range_min);

  // Clip to [0..100]% range, when requested.
  if (clip)
    perc = constrain(perc, 0.0, 100.0);
  return perc;
}


// Returns the current reading ID
int Cadence_LiPoBattery::Get_Readings(void) {
  return number_readings;
}


// Returns the current level of Battery_VbatRawAnalog
long Cadence_LiPoBattery::Get_Vbat_AnalogLvl(void) {
  return Battery_VbatRawAnalog;
}


// Returns the current level of Battery_VccRawAnalog
long Cadence_LiPoBattery::Get_Vcc_AnalogLvl(void) {
  return Battery_VccRawAnalog;
}


// Returns the current level of Battery_VbatVolts
float Cadence_LiPoBattery::Get_VbatVoltage(void) {
  return Battery_VbatVolts;
}


// Returns the current level of Battery_VccVolts
float Cadence_LiPoBattery::Get_VccVoltage(void) {
  return Battery_VccVolts;
}


// Returns the current level of Battery_VbatPerct
float Cadence_LiPoBattery::Get_VbatPercent(void) {
  return Battery_VbatPerct;
}


// Returns the current level of Battery_VccPerct
float Cadence_LiPoBattery::Get_VccPercent(void) {
  return Battery_VccPerct;
}


// Returns the PARAMETER level of REF_BATTERY_OUTPUT
float Cadence_LiPoBattery::Get_REF_BATTERY_OUTPUT(void) {
  return REF_BATTERY_OUTPUT;
}


// Returns the PARAMETER level of REF_BATTERY_FULL
float Cadence_LiPoBattery::Get_BATTERY_FULL(void) {
  return BATTERY_FULL;
}


// Returns the PARAMETER level of REF_BATTERY_EMPTY
float Cadence_LiPoBattery::Get_BATTERY_EMPTY(void) {
  return BATTERY_EMPTY;
}


//EndofFile



