
//!*****************************************************************************
//!  \file      IOLGenericDevice.h
//!*****************************************************************************
//!
//!  \brief		Generic Device Layer, not implemented yet
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
#ifndef _IOLGENERICDEVICE_H
#define _IOLGENERICDEVICE_H

//!**** Header-Files ************************************************************
#include "IOLMasterPort.h"

#include <cstdint>
//!**** Macros ******************************************************************

//!**** Data types **************************************************************

//!**** Function prototypes *****************************************************

//!**** Data ********************************************************************

//!**** Implementation **********************************************************

class IOLGenericDevice {
public: 
	IOLGenericDevice(IOLMasterPort * port);
    
	void begin();

	void end();

	void eventHandler();

	void connectIOLinkMode();

	void disconnectIOLinkMode();

	void writeCycleTme();

	void readCycleTime();

	void writeProcessData();

	void readProcessData();

	void writeCQ();

	void readCQ();

	void readDI();

	void writeSpecISDU();

	void readSpecISDU();

	void readDeviceAccessLocks();

	void readProfileCharacteristic();

	void readPDInputDescriptor();

	void readPDOutputDescriptor();

	void readVendorName();

	void readVendorText();

	void readProductName();

	void readProductID();

	void readProductText();

	void readSerialNumber();

	void readHardwareRev();

	void readFirmwareRev();

	void writeMasterCycleTime();

	void readMasterCycleTime();

	void readMinCycleTime();

	void readMSeqCapability();

	void readRevID();

	void readProcessDataIn();

	void readProcessDataOut();

	void readVendorID();

	void readDeviceID();
    
	void readFunctionID();
protected: 
    uint16_t minCyclteTime;
    uint16_t deviceType;
    uint16_t diModeSupoort;
    uint16_t portType;
	IOLMasterPort * port;
    uint16_t comSpeed;
};

#endif //_IOLGENERICDEVICE_H
