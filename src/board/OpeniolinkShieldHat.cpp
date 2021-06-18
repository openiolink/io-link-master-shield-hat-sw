//!*****************************************************************************
//! \file   OpeniolinkShieldHat.cpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  The class for the IO-Link-Master-Shield/Hat from openiolink
//!
//! \date   2021-06-18
//!
//!
//! ****************************************************************************
//!
//! \copyright
//! Copyright 2021 Bern University of Applied Sciences and Balluff AG
//! \n\n
//! Licensed under the Apache License, Version 2.0 (the "License");
//! you may not use this file except in compliance with the License.
//! You may obtain a copy of the License at
//! \n\n
//!     http://www.apache.org/licenses/LICENSE-2.0
//! \n\n
//! Unless required by applicable law or agreed to in writing, software
//! distributed under the License is distributed on an "AS IS" BASIS,
//! WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//! See the License for the specific language governing permissions and
//! limitations under the License.
//!
//!*****************************************************************************

#include "OpeniolinkShieldHat.hpp"
#include "Max14819.hpp"

namespace openiolink
{

    //!*************************************************************************
    //! \brief  Initializes both MAX14819 IO-Link Transceiver chips
    //!
    //! \todo   Move the code to initialize a single chip to the method
    //!         Max14819::init().
    //!
    //!*************************************************************************
    void OpeniolinkShieldHat::configureBothMax14819()
    {
        uint8_t shadowReg = 0;
        // Enable extern crystal
        mChip0->writeRegister(Max14819::Clock, Max14819::TXTXENDis | Max14819::ClkOEn | Max14819::XtalEn); // Frequency is 14.745 MHz

        // Enable clocking from another max14819
        mChip1->writeRegister(Max14819::Clock, Max14819::TXTXENDis | Max14819::ExtClkEn | Max14819::ClkDiv0 | Max14819::ClkDiv1); // external OSC enable, 3.686 MHz input frequency

        mChip0->reset();
        mChip1->reset();

        // Wait 1 s for turning on the powersupply for sensor
        wait_for(Max14819::INIT_POWER_OFF_DELAY);

        mChip0->writeRegister(Max14819::DrvrCurrLim, Max14819::CL1 | Max14819::CL0 | Max14819::CLBL1 | Max14819::CLBL0 | Max14819::ArEn); //CQ 500 mA currentlimit, 5 ms min error duration before interrupt
        mChip1->writeRegister(Max14819::DrvrCurrLim, Max14819::CL1 | Max14819::CL0 | Max14819::CLBL1 | Max14819::CLBL0 | Max14819::ArEn); //CQ 500 mA currentlimit, 5 ms min error duration before interrupt

        // Initialize the port sepcific registers
        // PortA
        shadowReg = mChip0->readRegister(Max14819::InterruptEn);
        mChip0->writeRegister(Max14819::InterruptEn, Max14819::StatusIntEn | Max14819::WURQIntEn | Max14819::TxErrIntEnA | Max14819::RxErrIntEnA | Max14819::RxDaRdyIntEnA | shadowReg);

        shadowReg = mChip1->readRegister(Max14819::InterruptEn);
        mChip1->writeRegister(Max14819::InterruptEn, Max14819::StatusIntEn | Max14819::WURQIntEn | Max14819::TxErrIntEnA | Max14819::RxErrIntEnA | Max14819::RxDaRdyIntEnA | shadowReg);

        // Enable LedRxRdy and RyError LED
        shadowReg = mChip0->readRegister(Max14819::LEDCtrl);
        mChip0->writeRegister(Max14819::LEDCtrl, Max14819::RxRdyEnA | Max14819::RxErrEnA | shadowReg);
        // Initialize the Port A register
        mChip0->writeRegister(Max14819::LCnfgA, Max14819::LRT0 | Max14819::LBL0 | Max14819::LBL1 | Max14819::LClimDis | Max14819::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
        mChip0->writeRegister(Max14819::CQCfgA, Max14819::SinkSel0 | Max14819::PushPul);                                                // Int Current Sink, 5 mA, PushPull, Channel Enable

        shadowReg = mChip1->readRegister(Max14819::LEDCtrl);
        mChip1->writeRegister(Max14819::LEDCtrl, Max14819::RxRdyEnA | Max14819::RxErrEnA | shadowReg);
        // Initialize the Port A register
        mChip1->writeRegister(Max14819::LCnfgA, Max14819::LRT0 | Max14819::LBL0 | Max14819::LBL1 | Max14819::LClimDis | Max14819::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
        mChip1->writeRegister(Max14819::CQCfgA, Max14819::SinkSel0 | Max14819::PushPul);                                                // Int Current Sink, 5 mA, PushPull, Channel Enable

        // PortB
        // Set all Interrupts
        shadowReg = mChip0->readRegister(Max14819::InterruptEn);
        mChip0->writeRegister(Max14819::InterruptEn, Max14819::StatusIntEn | Max14819::WURQIntEn | Max14819::TxErrIntEnB | Max14819::RxErrIntEnB | Max14819::RxDaRdyIntEnB | shadowReg);

        shadowReg = mChip1->readRegister(Max14819::InterruptEn);
        mChip1->writeRegister(Max14819::InterruptEn, Max14819::StatusIntEn | Max14819::WURQIntEn | Max14819::TxErrIntEnB | Max14819::RxErrIntEnB | Max14819::RxDaRdyIntEnB | shadowReg);

        // Enable LedRxRdy and RyError LED
        shadowReg = mChip0->readRegister(Max14819::LEDCtrl);
        mChip0->writeRegister(Max14819::LEDCtrl, Max14819::RxRdyEnB | Max14819::RxErrEnB | shadowReg);
        // Initialize the Channel A register
        mChip0->writeRegister(Max14819::LCnfgB, Max14819::LRT0 | Max14819::LBL0 | Max14819::LBL1 | Max14819::LClimDis | Max14819::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
        mChip0->writeRegister(Max14819::CQCfgB, Max14819::SinkSel0 | Max14819::PushPul);                                                // Int Current Sink, 5 mA, PushPull, Channel Enable

        shadowReg = mChip1->readRegister(Max14819::LEDCtrl);
        mChip1->writeRegister(Max14819::LEDCtrl, Max14819::RxRdyEnB | Max14819::RxErrEnB | shadowReg);
        // Initialize the Channel A register
        mChip1->writeRegister(Max14819::LCnfgB, Max14819::LRT0 | Max14819::LBL0 | Max14819::LBL1 | Max14819::LClimDis | Max14819::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
        mChip1->writeRegister(Max14819::CQCfgB, Max14819::SinkSel0 | Max14819::PushPul);                                                // Int Current Sink, 5 mA, PushPull, Channel Enable

        // Wait 0.2s for bootup of the device
        wait_for(Max14819::INIT_BOOTUP_DELAY);
    }

} // namespace openiolink
