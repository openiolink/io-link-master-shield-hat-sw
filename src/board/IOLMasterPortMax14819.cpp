
//!*****************************************************************************
//!  \file      IOLMasterPortMax14819.cpp
//!*****************************************************************************
//!
//!  \brief		Implementation of IOMasterPort class for the driver IC Maxim
//!             MAX14819. Extends IOMasterPort class.
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

//!***** Header-Files ************************************************************
#include "IOLMasterPortMax14819.hpp"
#include "Max14819.hpp"
#include "protocol/IOLink.hpp"

#ifdef ARDUINO
	#include <stdio.h>
#else
	#include <cstdio>
#endif	

//!***** Macros ******************************************************************

//!***** Data types **************************************************************

//!***** Function prototypes *****************************************************

//!***** Data ********************************************************************

//!***** Implementation **********************************************************

//!*******************************************************************************
//!  function :    IOLMasterPortMax14819
//!*******************************************************************************
//!  \brief        Constructor for IOLMasterPortMax14819
//!
//!  \type         local
//!
//!  \param[in]    void
//!
//!  \return       void
//!
//!*******************************************************************************
IOLMasterPortMax14819::IOLMasterPortMax14819()
:pDriver_(nullptr),
port_(max14819::PORTA),
portType_(0),
diModeSupport_(0),
portMode_(0),
portStatus_(0),
actualCycleTime_(0),
comSpeed_(0)
{

}

//!*******************************************************************************
//!  function :    IOLMasterPortMax14819
//!*******************************************************************************
//!  \brief        Constructor for IOLMasterPortMax14819
//!
//!  \type         local
//!
//!  \param[in]    void
//!
//!  \return       void
//!
//!*******************************************************************************
IOLMasterPortMax14819::IOLMasterPortMax14819(max14819::Max14819* pDriver, max14819::PortSelect port)
:pDriver_(pDriver),
 port_(port),
 portType_(0),
 diModeSupport_(0),
 portMode_(0),
 portStatus_(0),
 actualCycleTime_(0),
 comSpeed_(0)
{

}
//!*******************************************************************************
//!  function :    ~IOLMasterPort
//!*******************************************************************************
//!  \brief        Destructor for IOLMasterPort
//!
//!  \type         local
//!
//!  \param[in]    void
//!
//!  \return       void
//!
//!*******************************************************************************
IOLMasterPortMax14819::~IOLMasterPortMax14819() {
}
//!*******************************************************************************
//!  function :    begin
//!*******************************************************************************
//!  \brief        Initialize port and connect to io-link device if attached.
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       0 if success
//!
//!*******************************************************************************
uint8_t IOLMasterPortMax14819::begin() {
	char buf[256];
    uint8_t retValue = SUCCESS;

    // Initialize drivers
    if( pDriver_->begin(port_) == ERROR){
        retValue = ERROR;
        // TODO: Serial.println("Error initialize driver01 PortA");
    }
    pDriver_->Serial_Write("WakeUp");
    // Generate wakeup
    retValue = uint8_t(retValue | pDriver_->wakeUpRequest(port_, &comSpeed_ ));
   if(retValue == ERROR){
       // TODO: Serial.println("Error wakeup driver01 PortA");
   }
   else{
       sprintf(buf, "Communication established with %d bauds\n", comSpeed_);// TODO:
       pDriver_->Serial_Write(buf);
       // TODO: Serial.print("Communication established with ");
       // TODO: Serial.print(comSpeed_);
       // TODO: Serial.print(" Baud/s \n");
   }
    pDriver_->Serial_Write("Device");
   uint8_t pData[3];
   uint16_t VendorID;
   uint32_t DeviceID;
   readDirectParameterPage(0x02, pData);

   // VendorID
   readDirectParameterPage(0x07, pData); //MSB
   readDirectParameterPage(0x08, pData+1); //LSB
   VendorID = uint16_t((pData[0] << 8) + pData[1]);
   // DeviceID
   readDirectParameterPage(0x09, pData); //MSB
   readDirectParameterPage(0x0A, pData+1);
   readDirectParameterPage(0x0B, pData+2); //LSB
   DeviceID = (pData[0] << 16) + (pData[1] << 8) + pData[2];
   sprintf(buf, "Vendor ID: %d, Device ID: %d\n", VendorID, DeviceID);
   pDriver_->Serial_Write(buf);

    // Switch to operational

   uint8_t value[1] = {IOL::MC::DEV_OPERATE};
    if(pDriver_->writeData(IOL::MC::WRITE, 1, value , 1, IOL::M_TYPE_0, port_) == ERROR){
        sprintf(buf, "Error operate driver01 PortA");// TODO: 
		pDriver_->Serial_Write(buf);
    }
    return retValue;
}

//!*******************************************************************************
//!  function :    end
//!*******************************************************************************
//!  \brief        Disconnect from device an reset port.
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       0 if success
//!
//!*******************************************************************************
uint8_t IOLMasterPortMax14819::end() {
    uint8_t retValue = SUCCESS;

    // Send device fallback command
	retValue = uint8_t(retValue | pDriver_->writeData(IOL::MC::DEV_FALLBACK, 0, nullptr , 1, IOL::M_TYPE_0, port_));

    // Reset port
	retValue = uint8_t(retValue | pDriver_->reset(port_));

    return retValue;
}

//!*******************************************************************************
//!  function :    portHandler
//!*******************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*******************************************************************************
void IOLMasterPortMax14819::portHandler() {

}

//!*******************************************************************************
//!  function :    readStatus
//!*******************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*******************************************************************************
void IOLMasterPortMax14819::readStatus() {

}

//!*******************************************************************************
//!  function :    sendMCmd
//!*******************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*******************************************************************************
void IOLMasterPortMax14819::sendMCmd() {

}

//!*******************************************************************************
//!  function :    readComSpeed
//!*******************************************************************************
//!  \brief        Returns the communication speed of the port.
//!
//!  \type         local
//!
//!  \param[in]    void
//!
//!  \return       communication speed
//!
//!*******************************************************************************
uint32_t IOLMasterPortMax14819::readComSpeed() {
    return comSpeed_;
}

//!*******************************************************************************
//!  function :    readPage
//!*******************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*******************************************************************************
void IOLMasterPortMax14819::readPage() {

}

//!*******************************************************************************
//!  function :    writePage
//!*******************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*******************************************************************************
void IOLMasterPortMax14819::writePage() {

}

//!*******************************************************************************
//!  function :    readISDU
//!*******************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*******************************************************************************
void IOLMasterPortMax14819::readISDU() {

}

//!*******************************************************************************
//!  function :    writeISDU
//!*******************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*******************************************************************************
void IOLMasterPortMax14819::writeISDU() {

}

uint8_t IOLMasterPortMax14819::readDirectParameterPage(uint8_t address, uint8_t *pData) {
	uint8_t MC;

	if (address > 31) {
		pDriver_->Serial_Write("readDirectParameterPage: address to big\n");
		return 0;
	}

	MC = uint8_t((1 << 7) + (0b01 << 5) + address);

	uint8_t retValue = SUCCESS;

	// Send processdata request to device
	retValue = uint8_t(retValue | pDriver_->writeData(MC, 0, nullptr, 1, IOL::M_TYPE_0, port_));

	pDriver_->wait_for(2);

	// Receive answer
	retValue = uint8_t(retValue | pDriver_->readData(pData, 1, port_));

	return retValue;

}

//!*******************************************************************************
//!  function :    readPD
//!*******************************************************************************
//!  \brief        Sends a process data request to the device and receive the
//!                answer from the slave.
//!
//!  \type         local
//!
//!  \param[in]    *pData               pointer to data
//!  \param[in]    sizeData             size of data
//!
//!  \return       0 if success and processdata valid
//!
//!*******************************************************************************
uint8_t IOLMasterPortMax14819::readPD(uint8_t *pData, uint8_t sizeData) {
    uint8_t retValue = SUCCESS;

    // Send processdata request to device
    retValue = uint8_t(retValue | pDriver_->writeData(IOL::MC::PD_READ, 0, nullptr , sizeData, IOL::M_TYPE_2_X, port_));

	pDriver_->wait_for(10);

    // Receive answer
    retValue = uint8_t(retValue | pDriver_->readData(pData,  4,  port_));
    if((pData[3]&IOL::PD_VALID_BIT) != 0){
		retValue = ERROR;
	}
    return retValue;
}

//!*******************************************************************************
//!  function :    writePD
//!*******************************************************************************
//!  \brief        Sends process data to the device. Informations like lenght and
//!                m-sequence type must be set by user.
//!
//!  \type         local
//!
//!  \param[in]    sizeData             size in Byte of data
//!  \param[in]    *pData               pointer to data
//!  \param[in]    sizeAnswer           size in byte of answer
//!  \param[in]    mSeqType             M-seqence type
//!
//!  \return       0 if success
//!
//!*******************************************************************************
uint8_t IOLMasterPortMax14819::writePD(uint8_t sizeData, uint8_t *pData, uint8_t sizeAnswer, uint8_t mSeqType) {
    uint8_t retValue = SUCCESS;

    // Send processdata to device
    retValue = uint8_t(retValue | pDriver_->writeData(IOL::MC::WRITE, sizeData, pData, sizeAnswer, mSeqType, port_));

    return retValue;
}

//!*******************************************************************************
//!  function :    readDI
//!*******************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*******************************************************************************
void IOLMasterPortMax14819::readDI() {

}

//!*******************************************************************************
//!  function :    readCQ
//!*******************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*******************************************************************************
void IOLMasterPortMax14819::readCQ() {

}

//!*******************************************************************************
//!  function :    writeCQ
//!*******************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*******************************************************************************
void IOLMasterPortMax14819::writeCQ() {

}

//!*******************************************************************************
//!  function :    isDeviceConnected
//!*******************************************************************************
//!  \brief        Not implemented yet
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*******************************************************************************
void IOLMasterPortMax14819::isDeviceConnected() {

}
