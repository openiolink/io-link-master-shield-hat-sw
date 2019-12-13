
//!*****************************************************************************
//!  \file      BalluffBus0023.cpp
//!*****************************************************************************
//!
//!  \brief		Balluff BUS0023 distance sensor specific driver, not implemented yet
//!
//!  \author    Pascal Frei (freip2)
//!
//!  \date      2019-06-27
//!
//!*****************************************************************************
//!
//!	 Copyright 2019 Bern University of Applied Sciences and Balluff AG
//!
//!	 Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!
//!	     http://www.apache.org/licenses/LICENSE-2.0
//!
//!	 Unless required by applicable law or agreed to in writing, software
//!	 distributed under the License is distributed on an "AS IS" BASIS,
//!	 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!	 See the License for the specific language governing permissions and
//!	 limitations under the License.
//!	
//!*****************************************************************************

//!**** Header-Files ***********************************************************
#include "BalluffBus0023.h"

#ifdef ARDUINO
	#include <stdio.h>
#else
	#include <cstdio>
#endif	

//!**** Macros *****************************************************************

//!**** Data types *************************************************************

//!**** Function prototypes ****************************************************

//!**** Data *******************************************************************

//!**** Implementation *********************************************************


BalluffBus0023::BalluffBus0023():IOLGenericDevice(nullptr) {

}

BalluffBus0023::BalluffBus0023(IOLMasterPort * port) : IOLGenericDevice(port){
	
}

//!*****************************************************************************
//!  function :    begin
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::begin() {
	port->begin();

	/*uint8_t pData[3];
	uint16_t VendorID;
	uint32_t DeviceID;
	port->readDirectParameterPage(0x02, pData);

	// VendorID
	port->readDirectParameterPage(0x07, pData); //MSB
	port->readDirectParameterPage(0x08, pData + 1); //LSB
	VendorID = uint16_t((pData[0] << 8) + (pData[1]));
	// DeviceID
	port->readDirectParameterPage(0x09, pData); //MSB
	port->readDirectParameterPage(0x0A, pData + 1);
	port->readDirectParameterPage(0x0B, pData + 2); //LSB
	DeviceID = (pData[0] << 16) + (pData[1] << 8) + pData[2];
	printf("Vendor ID: %d, Device ID: %d\n", VendorID, DeviceID);*/

}

//!*****************************************************************************
//!  function :    end
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::end() {

}

//!*****************************************************************************
//!  function :    readDistance
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
uint16_t BalluffBus0023::readDistance() {
	uint8_t data[4];
	uint16_t distance = 0;
	if(port->readPD(data, 4)!= ERROR){
		distance = (uint16_t)(((data[1] << 8) | data[2]) >> 1);
	}
	return distance;
}

//!*****************************************************************************
//!  function :    readSwitchState
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::readSwitchState() {

}

//!*****************************************************************************
//!  function :    writeDetPoint1
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::writeDetPoint1() {

}

//!*****************************************************************************
//!  function :    readDetPoint1
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::readDetPoint1() {

}

//!*****************************************************************************
//!  function :    writeRetDetPoint1
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::writeRetDetPoint1() {

}

//!*****************************************************************************
//!  function :    readRetDetPoint1
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::readRetDetPoint1() {

}

//!*****************************************************************************
//!  function :    writeDetPoint2
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::writeDetPoint2() {

}

//!*****************************************************************************
//!  function :    readDetPoint2
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::readDetPoint2() {

}

//!*****************************************************************************
//!  function :    writeRetDetPoint2
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::writeRetDetPoint2() {

}

//!*****************************************************************************
//!  function :    readRetDetPoint2
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::readRetDetPoint2() {

}

//!*****************************************************************************
//!  function :    writeSwitchMode
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::writeSwitchMode() {

}

//!*****************************************************************************
//!  function :    readSwitchMode
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::readSwitchMode() {

}

//!*****************************************************************************
//!  function :    writeFilter
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::writeFilter() {

}

//!*****************************************************************************
//!  function :    readFilter
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::readFilter() {

}

//!*****************************************************************************
//!  function :    writeFilterStrength
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::writeFilterStrength() {

}

//!*****************************************************************************
//!  function :    readFilterStrength
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::readFilterStrength() {

}

//!*****************************************************************************
//!  function :    writeForgroundSuppression
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::writeForgroundSuppression() {

}

//!*****************************************************************************
//!  function :    readForegroundSuppression
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::readForegroundSuppression() {

}

//!*****************************************************************************
//!  function :    writeTeachIn
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::writeTeachIn() {

}

//!*****************************************************************************
//!  function :    readTeachIn
//!*****************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void BalluffBus0023::readTeachIn() {

}
