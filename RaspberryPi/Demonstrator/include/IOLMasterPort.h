
//!******************************************************************************
//! \file      IOLMasterPort.h
//!******************************************************************************
//!
//! \brief     Abstract class layer for driver ic independent port
//!             implementation. Defines methods and variables for the
//!             IOLMasterPort<driver_ic> implementation.
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
//! Copyright (C) 2019, Pascal Frei
//!
//! This program is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 3 of the License, or
//! any later version.
//!
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with this program.  If not, see <http://www.gnu.org/licenses/>.
//!
//!******************************************************************************
#ifndef IOLMASTERPORT_H_INCLUDED
#define IOLMASTERPORT_H_INCLUDED

//!***** Header-Files ***********************************************************
#include <stdint.h>
#include "Max14819.h"

//!***** Macros *****************************************************************

//!***** Data types *************************************************************

//!***** Function prototypes ****************************************************

//!***** Data *******************************************************************

//!***** Implementation *********************************************************

class IOLMasterPort {
private:
    uint16_t portType_;
    uint16_t diModeSupport_;
    uint16_t portMode_;
    uint16_t portStatus_;
    uint16_t actualCycleTime_;
    uint16_t comSpeed_;
public:

    IOLMasterPort();

    virtual ~IOLMasterPort();

    virtual uint8_t begin() = 0;

    virtual uint8_t end() = 0;

    virtual void portHandler() = 0;

    virtual void readStatus() = 0;

    virtual void sendMCmd() = 0;

    virtual uint32_t readComSpeed() = 0;

    virtual void readPage() = 0;

    virtual void writePage() = 0;

    virtual void readISDU() = 0;

    virtual void writeISDU() = 0;

	virtual uint8_t readDirectParameterPage(uint8_t address, uint8_t *pData) = 0;

    virtual uint8_t readPD(uint8_t *pData, uint8_t sizeData) = 0;

    virtual uint8_t writePD(uint8_t sizeData, uint8_t *pData, uint8_t sizeAnswer, uint8_t mSeqType) = 0;

    virtual void readDI() = 0;

    virtual void readCQ() = 0;

    virtual void writeCQ() = 0;

    virtual void isDeviceConnected() = 0;


};

#endif //IOLMASTERPORT_H_INCLUDED
