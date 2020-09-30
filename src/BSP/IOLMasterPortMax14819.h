
//!*****************************************************************************
//!  \file      IOLMasterPortMax14819.h
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
#ifndef IOLMASTERPORTMAX14819_H_INCLUDED
#define IOLMASTERPORTMAX14819_H_INCLUDED

//!***** Header-Files ***********************************************************
#include "../protocol/IOLMasterPort.h"
#include "Max14819.h"

#include <stdint.h>
//!***** Macros *****************************************************************

//!***** Data types *************************************************************

//!***** Function prototypes ****************************************************

//!***** Data *******************************************************************

//!***** Implementation *********************************************************

class IOLMasterPortMax14819: public IOLMasterPort{
private:
    max14819::Max14819* pDriver_;
    max14819::PortSelect port_;
    uint16_t portType_;
    uint16_t diModeSupport_;
    uint16_t portMode_;
    uint16_t portStatus_;
    uint16_t actualCycleTime_;
    uint32_t comSpeed_;
public: 
    IOLMasterPortMax14819();

    IOLMasterPortMax14819(max14819::Max14819* pDriver, max14819::PortSelect port);

    ~IOLMasterPortMax14819();
    
    uint8_t begin();

    uint8_t end();

	void portHandler();

	void readStatus();

	void sendMCmd();

	uint32_t readComSpeed();

	void readPage();

	void writePage();

	void readISDU();

	void writeISDU();

	uint8_t readDirectParameterPage(uint8_t address, uint8_t *pData);

	uint8_t readPD(uint8_t *pData, uint8_t sizeData);

	uint8_t writePD(uint8_t sizeData, uint8_t *pData, uint8_t sizeAnswer, uint8_t mSeqType);

	void readDI();

	void readCQ();

	void writeCQ();

	void isDeviceConnected();
};

#endif //IOLMASTERPORTMAX14819_H_INCLUDED
