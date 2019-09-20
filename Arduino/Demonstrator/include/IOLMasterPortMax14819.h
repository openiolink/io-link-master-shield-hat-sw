
//!******************************************************************************
//! \file      IOLMasterPortMax14819.h
//!******************************************************************************
//!
//! \brief      Implementation of IOMasterPort class for the driver IC Maxim
//!             MAX14819. Extends IOMasterPort class.
//!
//! \author     Pascal Frei (freip2)
//!
//! \date       27.06.2019
//!
//! \remark     Last Modification
//!				 \li freip2, 27.06.2019, Cleaned
//!              \li freip2, 14.05.2019, Created
//!
//!******************************************************************************
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
#ifndef IOLMASTERPORTMAX14819_H_INCLUDED
#define IOLMASTERPORTMAX14819_H_INCLUDED

//!***** Header-Files ***********************************************************
#include <stdint.h>
#include "IOLMasterPort.h"
#include "Max14819.h"
#include "stdio.h"

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
