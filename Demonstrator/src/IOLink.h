
//!*****************************************************************************
//!  \file      IOLink.h
//!*****************************************************************************
//!
//!  \brief		Includes all the defines and commands for the IO-Link protocoll.
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
#ifndef IOLINK_H_INCLUDED
#define IOLINK_H_INCLUDED

//!***** Header-Files ***********************************************************
#include <cstdint>

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
