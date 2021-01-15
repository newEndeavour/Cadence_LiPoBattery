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


#ifndef __CAD37LIPO_H__
#define __CAD37LIPO_H__

#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>



// DEFINES /////////////////////////////////////////////////////////////
//Main Battery = Battery 1
const uint8_t ANALOG_READ_SAMPLES         	= 10;
const double  REF_BATTERY_OUTPUT		= 5.20;  // Reference Battery Output
const double  BATTERY_FULL        		= 4.18;  // Known Battery Voltage measured with multimeter
const double  BATTERY_EMPTY       		= 3.20;
const double  BATTERY_LOW_WARNING         	= 20;    // Percentage Warning to trigger message



//
class Cadence_LiPoBattery {
public:
  
  //Constructors
  Cadence_LiPoBattery(uint8_t _vbatpin);
  Cadence_LiPoBattery(uint8_t _vbatpin, uint8_t _vccpin);

  //Methods
  bool Begin(void);
  void Read(bool constrain_percent);

  int  Get_Readings(void);
  long Get_Vbat_AnalogLvl(void);
  long Get_Vcc_AnalogLvl(void);

  double Get_VbatVoltage(void);
  double Get_VccVoltage(void);

  double Get_VbatPercent(void);
  double Get_VccPercent(void);

  double Get_REF_BATTERY_OUTPUT(void);
  double Get_BATTERY_FULL(void);
  double Get_BATTERY_EMPTY(void);


private:
	
  uint8_t	analog_Vbat_pin;			// Vbat Pin
  uint8_t	analog_Vcc_pin;			// Vcc Pin

  double 		Convert_Percent(double ,double, double, bool);
  
  int		number_readings;
  
  long 		Battery_VbatRawAnalog;
  long 		Battery_VccRawAnalog;

  double 		Battery_VbatVolts;
  double 		Battery_VccVolts;
  
  double 		Battery_VbatPerct;
  double 		Battery_VccPerct;

};

#endif
//EndofFile
