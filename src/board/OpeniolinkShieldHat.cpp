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
#include "PrintAndWait.hpp"

namespace openiolink
{
    //!*************************************************************************
    //! \brief  Construct a new OpeniolinkShieldHat object
    //!
    //! \note   To be compatible with the template template parameter of
    //!         IOLMasterClass, the constructor of OpeniolinkShieldHat must not
    //!         take any arguments.
    //!
    //!*************************************************************************
    OpeniolinkShieldHat::OpeniolinkShieldHat(Max14819_Port<0> *port0, Max14819_Port<1> *port1,
                                             Max14819_Port<2> *port2, Max14819_Port<3> *port3)
        : mChip0{*port0, *port1}, mChip1{*port2, *port3} // FIXME this is a manual assignment independent of the mappers!
    {
        // TODO
    }

    //!*************************************************************************
    //! \brief  Destruct the OpeniolinkShieldHat object
    //!
    //!*************************************************************************
    OpeniolinkShieldHat::~OpeniolinkShieldHat()
    {
        // TODO
    }

    //!*************************************************************************
    //! \brief  Initializes both MAX14819 IO-Link Transceiver chips
    //!
    //! \todo   Move the code to initialize a single chip to the method
    //!         ChipDef::configure().
    //!
    //! \note   This method was written by Janik Lehmann (CrazyGecko)
    //!         and refactored by Tobias Gammeter.
    //!
    //!*************************************************************************
    void OpeniolinkShieldHat::configureBothMax14819()
    {
        //!< alias to access the register definitions
        using ChipDef = Max14819_Base;

        uint8_t shadowReg = 0;
        // Enable extern crystal
        mChip0.writeRegister(ChipDef::Clock, ChipDef::TXTXENDis | ChipDef::ClkOEn | ChipDef::XtalEn); // Frequency is 14.745 MHz

        // Enable clocking from another max14819
        mChip1.writeRegister(ChipDef::Clock, ChipDef::TXTXENDis | ChipDef::ExtClkEn | ChipDef::ClkDiv0 | ChipDef::ClkDiv1); // external OSC enable, 3.686 MHz input frequency

        mChip0.reset();
        mChip1.reset();

        // Wait 1 s for turning on the powersupply for sensor
        wait_ms(ChipDef::INIT_POWER_OFF_DELAY);

        mChip0.writeRegister(ChipDef::DrvrCurrLim, ChipDef::CL1 | ChipDef::CL0 | ChipDef::CLBL1 | ChipDef::CLBL0 | ChipDef::ArEn); //CQ 500 mA currentlimit, 5 ms min error duration before interrupt
        mChip1.writeRegister(ChipDef::DrvrCurrLim, ChipDef::CL1 | ChipDef::CL0 | ChipDef::CLBL1 | ChipDef::CLBL0 | ChipDef::ArEn); //CQ 500 mA currentlimit, 5 ms min error duration before interrupt

        // Initialize the port sepcific registers
        // PortA
        shadowReg = mChip0.readRegister(ChipDef::InterruptEn);
        mChip0.writeRegister(ChipDef::InterruptEn, ChipDef::StatusIntEn | ChipDef::WURQIntEn | ChipDef::TxErrIntEnA | ChipDef::RxErrIntEnA | ChipDef::RxDaRdyIntEnA | shadowReg);

        shadowReg = mChip1.readRegister(ChipDef::InterruptEn);
        mChip1.writeRegister(ChipDef::InterruptEn, ChipDef::StatusIntEn | ChipDef::WURQIntEn | ChipDef::TxErrIntEnA | ChipDef::RxErrIntEnA | ChipDef::RxDaRdyIntEnA | shadowReg);

        // Enable LedRxRdy and RyError LED
        shadowReg = mChip0.readRegister(ChipDef::LEDCtrl);
        mChip0.writeRegister(ChipDef::LEDCtrl, ChipDef::RxRdyEnA | ChipDef::RxErrEnA | shadowReg);
        // Initialize the Port A register
        mChip0.writeRegister(ChipDef::LCnfgA, ChipDef::LRT0 | ChipDef::LBL0 | ChipDef::LBL1 | ChipDef::LClimDis | ChipDef::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
        mChip0.writeRegister(ChipDef::CQCfgA, ChipDef::SinkSel0 | ChipDef::PushPul);                                                // Int Current Sink, 5 mA, PushPull, Channel Enable

        shadowReg = mChip1.readRegister(ChipDef::LEDCtrl);
        mChip1.writeRegister(ChipDef::LEDCtrl, ChipDef::RxRdyEnA | ChipDef::RxErrEnA | shadowReg);
        // Initialize the Port A register
        mChip1.writeRegister(ChipDef::LCnfgA, ChipDef::LRT0 | ChipDef::LBL0 | ChipDef::LBL1 | ChipDef::LClimDis | ChipDef::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
        mChip1.writeRegister(ChipDef::CQCfgA, ChipDef::SinkSel0 | ChipDef::PushPul);                                                // Int Current Sink, 5 mA, PushPull, Channel Enable

        // PortB
        // Set all Interrupts
        shadowReg = mChip0.readRegister(ChipDef::InterruptEn);
        mChip0.writeRegister(ChipDef::InterruptEn, ChipDef::StatusIntEn | ChipDef::WURQIntEn | ChipDef::TxErrIntEnB | ChipDef::RxErrIntEnB | ChipDef::RxDaRdyIntEnB | shadowReg);

        shadowReg = mChip1.readRegister(ChipDef::InterruptEn);
        mChip1.writeRegister(ChipDef::InterruptEn, ChipDef::StatusIntEn | ChipDef::WURQIntEn | ChipDef::TxErrIntEnB | ChipDef::RxErrIntEnB | ChipDef::RxDaRdyIntEnB | shadowReg);

        // Enable LedRxRdy and RyError LED
        shadowReg = mChip0.readRegister(ChipDef::LEDCtrl);
        mChip0.writeRegister(ChipDef::LEDCtrl, ChipDef::RxRdyEnB | ChipDef::RxErrEnB | shadowReg);
        // Initialize the Channel A register
        mChip0.writeRegister(ChipDef::LCnfgB, ChipDef::LRT0 | ChipDef::LBL0 | ChipDef::LBL1 | ChipDef::LClimDis | ChipDef::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
        mChip0.writeRegister(ChipDef::CQCfgB, ChipDef::SinkSel0 | ChipDef::PushPul);                                                // Int Current Sink, 5 mA, PushPull, Channel Enable

        shadowReg = mChip1.readRegister(ChipDef::LEDCtrl);
        mChip1.writeRegister(ChipDef::LEDCtrl, ChipDef::RxRdyEnB | ChipDef::RxErrEnB | shadowReg);
        // Initialize the Channel A register
        mChip1.writeRegister(ChipDef::LCnfgB, ChipDef::LRT0 | ChipDef::LBL0 | ChipDef::LBL1 | ChipDef::LClimDis | ChipDef::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
        mChip1.writeRegister(ChipDef::CQCfgB, ChipDef::SinkSel0 | ChipDef::PushPul);                                                // Int Current Sink, 5 mA, PushPull, Channel Enable

        // Wait 0.2s for bootup of the device
        wait_ms(ChipDef::INIT_BOOTUP_DELAY);
    }

} // namespace openiolink
