
//!*****************************************************************************
//!  \file       BallufBus0023.cpp
//!*****************************************************************************
//!
//!  \brief		Balluf BUS0023 distance sensor specific driver, not implemented yet
//!
//!  \author     Pascal Frei (freip2)
//!
//!  \date       2019-06-27
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
#include "../include/BallufBus0023.h"

#include <cstdio>

//!**** Macros *****************************************************************

//!**** Data types *************************************************************

//!**** Function prototypes ****************************************************

//!**** Data *******************************************************************

//!**** Implementation *********************************************************


BallufBus0023::BallufBus0023():IOLGenericDevice(nullptr) {

}

BallufBus0023::BallufBus0023(IOLMasterPort * port) : IOLGenericDevice(port){
	
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
void BallufBus0023::begin() {
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
void BallufBus0023::end() {

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
uint16_t BallufBus0023::readDistance() {
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
void BallufBus0023::readSwitchState() {

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
void BallufBus0023::writeDetPoint1() {

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
void BallufBus0023::readDetPoint1() {

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
void BallufBus0023::writeRetDetPoint1() {

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
void BallufBus0023::readRetDetPoint1() {

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
void BallufBus0023::writeDetPoint2() {

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
void BallufBus0023::readDetPoint2() {

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
void BallufBus0023::writeRetDetPoint2() {

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
void BallufBus0023::readRetDetPoint2() {

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
void BallufBus0023::writeSwitchMode() {

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
void BallufBus0023::readSwitchMode() {

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
void BallufBus0023::writeFilter() {

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
void BallufBus0023::readFilter() {

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
void BallufBus0023::writeFilterStrength() {

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
void BallufBus0023::readFilterStrength() {

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
void BallufBus0023::writeForgroundSuppression() {

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
void BallufBus0023::readForegroundSuppression() {

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
void BallufBus0023::writeTeachIn() {

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
void BallufBus0023::readTeachIn() {

}
