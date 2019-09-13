
//!*****************************************************************************
//!  \file       Demonstrator_V1_0.cpp
//!*****************************************************************************
//!
//!  \brief		 Software Demonstration for the bachelor thesis.
//!
//!  \author     Pascal Frei (freip2)
//!
//! \date       27.06.2019
//!
//! \remark     Last Modification
//!				 \li freip2, 27.06.2019, Cleaned
//!              \li freip2, 14.05.2019, Created
//!
//!*****************************************************************************
//!	Copyright (C) 2019, Pascal Frei
//!
//!	This program is free software: you can redistribute it and/or modify
//!	it under the terms of the GNU General Public License as published by
//!	the Free Software Foundation, either version 3 of the License, or
//!	any later version.
//!
//!	but WITHOUT ANY WARRANTY; without even the implied warranty of
//!	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//!	GNU General Public License for more details.
//!
//!	You should have received a copy of the GNU General Public License
//!	along with this program.  If not, see <http://www.gnu.org/licenses/>.
//!
//!*****************************************************************************

//!**** Header-Files ***********************************************************
#include "Demonstrator_V1_0.h"
#include <stdio.h>

#include "Max14819.h"
#include "BallufBus0023.h"
#include "IOLMasterPort.h"
#include "IOLMasterPortMax14819.h"
#include "IOLGenericDevice.h"
#include "IOLink.h"
#include "HardwareRaspberry.h"

//!**** Macros *****************************************************************

//!**** Data types *************************************************************
IOLMasterPortMax14819 port0;
IOLMasterPortMax14819 port1;
IOLMasterPortMax14819 port2;
IOLMasterPortMax14819 port3;
BallufBus0023 BUS0023;
HardwareRaspberry hardware;
//!**** Function prototypes ****************************************************
void printDataMatlab(uint16_t level, uint32_t measureNr);
//!**** Data *******************************************************************

//!**** Implementation *********************************************************

//The setup function is called once at startup of the sketch
void Demo_setup()
{
    //testDistSensorPortLayer();
	// Create hardware setup
	hardware = HardwareRaspberry();
    // Create drivers
    max14819::Max14819 *pDriver01 = new max14819::Max14819(max14819::DRIVER01, &hardware);
    max14819::Max14819 *pDriver23 = new max14819::Max14819(max14819::DRIVER23, &hardware);

    // Create ports
	port0 = IOLMasterPortMax14819(pDriver01, max14819::PORT0PORT);
	port1 = IOLMasterPortMax14819(pDriver01, max14819::PORT1PORT);
	port2 = IOLMasterPortMax14819(pDriver23, max14819::PORT2PORT);
	port3 = IOLMasterPortMax14819(pDriver23, max14819::PORT3PORT);

	BUS0023 = BallufBus0023(&port0);

    // Start IO-Link communication
	BUS0023.begin();
    //port0.begin();
    port1.begin();
    port2.begin();
    port3.begin();

    // Variables used for distance and level conversation
    uint16_t distance = 0;
    uint16_t testVal = 0;
    uint16_t level = 0;
    uint8_t data[4];
	char buf[64];




}

// The loop function is called in an endless loop
void Demo_loop()
{
    HardwareRaspberry::Serial_Write("LOOP");
	// Variables used for distance and level conversation
	uint16_t distance = 0;
	uint16_t testVal = 0;
	uint16_t level = 0;
	uint8_t data[4];
	char buf[64];

	// Level mode for smartlight
	uint8_t dataLED[10];
	dataLED[0] = 0;
	dataLED[1] = 0;
	dataLED[2] = 0;
	dataLED[3] = 0b00000010;
	dataLED[4] = 1;
	dataLED[5] = 0;
	dataLED[6] = 0;
	dataLED[7] = 0;
	dataLED[8] = IOL::MC::PDOUT_VALID;
	dataLED[9] = 0;

	// Default levels for demonstrator
	uint16_t TANK_MAX_LVL = 210;
	uint16_t TANK_WARNING_LVL = 100;
	uint32_t measureNr = 0;
	constexpr uint16_t TANK_EMPTY_LVL = 50;
	

    while(1){
        HardwareRaspberry::wait_for(100);
        // Read process data and convert them if there is no error
		distance = BUS0023.readDistance();
		HardwareRaspberry::Serial_Write("Messung");
		sprintf(buf, "%d", distance);
		HardwareRaspberry::Serial_Write(buf);
		level = 250 - distance / 10;
        
        // When there is a valid level
        if((level < 250) && (level > 0)){
            //Serial.println(level);
            measureNr++;
            printDataMatlab(level, measureNr);

           if(level <= TANK_EMPTY_LVL){
               // Smartlight color red
               dataLED[0] = 0b00100010;				// Segment dominance 2: not (0b0), Segment color 2 : red (0b010), Segment dominance 1: not (0b0) ,Segment color 1 : red (0b010)
               dataLED[1] = 0b00000010;				// 0b0000,                                                        Segment dominance 3: not (0b0), Segment color 3 : red (0b010)
               dataLED[2] = 0;						// Buzzer state : off (0b0), 0b0, Buzzer Type: Continuous (0b00), 0b0000
               dataLED[3] = 0b00000010;				// No Sync (0b0000), Level Mode (0b0010)
               dataLED[4] = 0;						// Leveltype bottom - up (0x00)
               testVal = (uint16_t) ((float) level /(float) TANK_MAX_LVL * 65535.0);
               dataLED[5] = testVal&0xFF;			// Level Value, Lower Byte
               dataLED[6] = (testVal&0xFF00)>>8;	// Level Value, Higher Byte
               dataLED[7] = 0;						// Buzzer Volume zero
           }
           else if(level <= TANK_WARNING_LVL){
               // Smartlight color yellow
               dataLED[0] = 0b00110011;
               dataLED[1] = 0b00000011;
               dataLED[2] = 0;						// Buzzer state : off (0b0), 0b0, Buzzer Type: Continuous (0b00), 0b0000
               dataLED[3] = 0b00000010;				// No Sync (0b0000), Level Mode (0b0010)
               dataLED[4] = 0;
               testVal = (uint16_t) ((float) level / (float)TANK_MAX_LVL * 65535.0);
               dataLED[5] = testVal&0xFF;
               dataLED[6] = (testVal&0xFF00)>>8;
               dataLED[7] = 0;						// Buzzer Volume zero
           }
           else if(level <= TANK_MAX_LVL){
               // Smartlight color green
               dataLED[0] = 0b00010001;
               dataLED[1] = 0b00000001;
               dataLED[2] = 0;						// Buzzer state : off (0b0), 0b0, Buzzer Type: Continuous (0b00), 0b0000
               dataLED[3] = 0b00000010;				// No Sync (0b0000), Level Mode (0b0010)
               dataLED[4] = 0;
               testVal = (uint16_t) ((float) level / (float)TANK_MAX_LVL * 65535.0);
               dataLED[5] = testVal&0xFF;
               dataLED[6] = (testVal&0xFF00)>>8;
               dataLED[7] = 0;						// Buzzer Volume zero
           }
           else{
        	   // Smartlight starts blinking red
               dataLED[0] = 0b00001010;				// Segment dominance 2: not (0b0), Segment color 2 : off (0b000), Segment dominance 1: yes (0b1) ,Segment color 1 : red (0b010)
               dataLED[1] = 0;						// 0b0000,                                                        Segment dominance 3: not (0b0), Segment color 3 : off (0b00b540)
               dataLED[2] = 0;						// Buzzer state : off (0b0), 0b0, Buzzer Type: Continuous (0b00), 0b0000
               dataLED[3] = 0b00000001;				// No Sync (0b0000), Segment Mode (0b0010)
               dataLED[4] = 1;						// Number of Segments: 1
               dataLED[5] = 0;						// 0b00000, Blinkmode flash 50%Duty (0) for all segments
               dataLED[6] = 2;						// Blink frequency 1Hz
               dataLED[7] = 0;						// Buzzer Volume zero						
           }
            port1.writePD(10, dataLED, 2, IOL::M_TYPE_2_X);
        }
        port2.readPD(data, 3);
        //Serial.println(data[2]&0x01, DEC);
        if((data[2]&0x01)== 1){
           if(level >TANK_WARNING_LVL){
               TANK_MAX_LVL = level;
           }
        }
        port3.readPD(data, 3);
        //Serial.println(data[2]&0x01, DEC);
        if((data[2]&0x01)== 1){
            if((level > TANK_EMPTY_LVL) && (level < TANK_MAX_LVL))
                TANK_WARNING_LVL = level;
         }
    }
}

void printDataMatlab(uint16_t level, uint32_t measureNr) {
	char buf[256];
	sprintf(buf, "%d;0;0;0;0;0;0;0;0;%d", measureNr, level);
	hardware.Serial_Write(buf);
}
