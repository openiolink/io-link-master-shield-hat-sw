
//!*****************************************************************************
//!  \file       IOLGenericDevice.h
//!*****************************************************************************
//!
//!  \brief		Generic Device Layer, not implemented yet
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
//!******************************************************************************
#ifndef _IOLGENERICDEVICE_H
#define _IOLGENERICDEVICE_H

//!**** Header-Files ************************************************************
#include <stdint.h>
#include "IOLMasterPort.h"
#include "stdio.h"
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
