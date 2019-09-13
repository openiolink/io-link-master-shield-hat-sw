
//!******************************************************************************
//! \file      IOLink.h
//!******************************************************************************
//!
//! \brief      Includes all the defines and commands for the IO-Link protocoll.
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
#ifndef IOLINK_H_INCLUDED
#define IOLINK_H_INCLUDED

//!***** Header-Files ***********************************************************
#include <stdint.h>

namespace IOL{
    // IO-Link M-Sequence Types
    constexpr uint8_t M_TYPE_0          = 0u;
    constexpr uint8_t M_TYPE_1_X        = 1u;
    constexpr uint8_t M_TYPE_2_X        = 2u;

    constexpr uint8_t PD_VALID_BIT      = 0x40u;
    namespace MC{
        constexpr uint8_t PD_READ       = 0xF1u;
        constexpr uint8_t WRITE         = 0x20u;

        constexpr uint8_t DEV_FALLBACK  = 0x5Au;
        constexpr uint8_t MAS_IDENT     = 0x95u;
        constexpr uint8_t DEV_IDENT     = 0x96u;
        constexpr uint8_t DEV_STARTUP   = 0x97u;
        constexpr uint8_t PDOUT_VALID   = 0x98u;
        constexpr uint8_t DEV_OPERATE   = 0x99u;
        constexpr uint8_t DEV_PREOPERATE= 0x9Au;
    }
    namespace PAGE{
        constexpr uint8_t MAS_COMMAND   = 0x00u;
        constexpr uint8_t MAS_CYCLE_TIME= 0x01u;
        constexpr uint8_t MIN_CYCLE_TIME= 0x02u;
        constexpr uint8_t M_SEQ_CAP     = 0x03u;
        constexpr uint8_t REVISION_ID   = 0x04u;
        constexpr uint8_t PD_IN         = 0x05u;
        constexpr uint8_t PD_OUT        = 0x06u;
        constexpr uint8_t VENDOR_ID1    = 0x07u;
        constexpr uint8_t VENDOR_ID2    = 0x08u;
        constexpr uint8_t DEVICE_ID1    = 0x09u;
        constexpr uint8_t DEVICE_ID2    = 0x0Au;
        constexpr uint8_t DEVICE_ID3    = 0x0Bu;
        constexpr uint8_t FUNCTION_ID1  = 0x0Cu;
        constexpr uint8_t FUNCTION_ID2  = 0x0Du;
        constexpr uint8_t SYSTEM_CMD    = 0x0Fu;
    }

}

#endif //IOLINK_H_INCLUDED
