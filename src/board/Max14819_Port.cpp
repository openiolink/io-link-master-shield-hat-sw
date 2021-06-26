//!*****************************************************************************
//! \file   Max14819_Port.cpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!         based on the work of Janik Lehmann (CrazyGecko) and Pascal Frei (freip2)
//!
//! \brief  Class for one port (channel) of the maxim integrated Dual IO-Link
//!         Master Transceiver MAX14819
//!
//! \date   2021-06-18
//!
//!
//! *****************************************************************************
//!
//! \copyright
//! Copyright 2020, 2021 Bern University of Applied Sciences and Balluff AG
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

// This .cpp file is included by the same-named .hpp file. For explanations see
// the end of the .hpp file.
// #include "Max14819_Port.hpp"

#include "Max14819.hpp"
#include "protocol/IOLMasterPort.hpp"
#include "board/PrintAndWait.hpp"

#ifdef ARDUINO
#include <stdint.h>
#include <stdio.h>
#else
#include <cstdint>
#include <cstdio>
#endif

namespace openiolink // TODO ::PCB?
{
    //!*****************************************************************************
    //! \brief  Construct a new Max14819_Port object
    //!
    //! \note   To be compatible with the template template parameter of
    //!         IOLMasterClass, the constructor of Max14819_Port must not take any
    //!         arguments.
    //!
    //!*****************************************************************************
    template <int IOLPortNr>
    Max14819_Port<IOLPortNr>::Max14819_Port() : detectedCOM{0U, 0U}
    {
        initGPIOs();
    }

    //!*****************************************************************************
    //! \brief Destroy the Max14819_Port object
    //!
    //!*****************************************************************************
    template <int IOLPortNr>
    Max14819_Port<IOLPortNr>::~Max14819_Port()
    {
    }

    //!*****************************************************************************
    //! \brief Sends data over IO-Link
    //!
    //!
    //! \param data pointer to the data to send
    //!
    //! \param sizeofdata length of the data to send
    //!
    //! \param sizeofanswer length of the expected answer
    //!
    //! \return uint8_t 0 if success
    //!
    //!*****************************************************************************
    template <int IOLPortNr>
    uint8_t Max14819_Port<IOLPortNr>::sendIOLData(const /*FIXME OK?*/ uint8_t *data,
                                                  uint8_t sizeofdata,
                                                  uint8_t sizeofanswer)
    {
        uint8_t retValue = SUCCESS;
        uint8_t offset = 0;
        // Todo remove offset and replace with enum
        if (channelNr == Port::PORTB)
        {
            offset = 1; // PORTB Registers are 1 address higher than PORTA Register
        }

        retValue = uint8_t(retValue | mChip->writeRegister(ChipDef::TxRxDataA + offset, sizeofanswer)); // number of bytes for answer
        retValue = uint8_t(retValue | mChip->writeRegister(ChipDef::TxRxDataA + offset, sizeofdata));   // number of bytes for answer
        // send data
        for (uint8_t i = 0; i < sizeofdata; i++)
        {
            retValue = uint8_t(retValue | mChip->writeRegister(ChipDef::TxRxDataA + offset, data[i]));
        }
        retValue = uint8_t(retValue | mChip->writeRegister(ChipDef::CQCtrlA + offset, ChipDef::CQSend | detectedCOM.comSpeed));
        return retValue;
    }

    //!*****************************************************************************
    //! \brief Reads data from IO-Link
    //!
    //!
    //! \param data pointer to the destination of the data
    //!
    //! \param sizeofdata length of the expected data
    //!
    //! \return uint8_t 0 if success
    //!
    //!*****************************************************************************
    template <int IOLPortNr>
    uint8_t Max14819_Port<IOLPortNr>::readIOLData(uint8_t *data, uint8_t sizeofdata)
    {
        uint8_t bufferRegister;
        uint8_t retValue = SUCCESS;
        // Use corresponding transmit FIFO address
        uint8_t offset = 0;
        // Todo remove offset and replace with enum
        if (channelNr == Port::PORTB)
        {
            offset = 1; // PORTB Registers are 1 address higher than PORTA Register
        }

        wait_ms(10); // TODO another solution to wait for an iol answer should be implemented

        // Controll if the aswer has the expected length (first byte in the FIFO is the messagelength)
        if (sizeofdata != mChip->readRegister(bufferRegister))
        {
            // TODO Error Handling if Buffer is corrupted
            retValue = ERROR;
        }

        // Read data from FIFO
        for (uint8_t i = 0; i < sizeofdata; i++)
        {
            *data++ = mChip->readRegister(bufferRegister);
        }
        // Return Error state
        return retValue;
    }

    //!*****************************************************************************
    //! \brief Set the port to this mode
    //!
    //!
    //!*****************************************************************************
    template <int IOLPortNr>
    void Max14819_Port<IOLPortNr>::setMode(const Mode &targetMode)
    {
        // TODO set mode
    }

    //!*****************************************************************************
    //! \brief Sends an WURQ over IO-Link
    //!
    //! \note   Specification 5.2.2.2 (PL_WakeUp.req)
    //! TODO: rename to establishCom()
    //!*****************************************************************************
    template <int IOLPortNr>
    void Max14819_Port<IOLPortNr>::wakeUpRequest()
    {
        uint8_t retValue = 0;
        uint8_t comReqRunning = 0;
        uint8_t timeOutCounter = 0;
        uint16_t length = 0;
        uint8_t offset = 0;

        if (channelNr == Port::PORTB)
        {
            offset = 1; // PORTB Registers are 1 address higher than PORTA Register
        }

        // Start wakeup and communcation
        retValue = uint8_t(retValue | mChip->writeRegister(ChipDef::IOStCfgA + offset, 0));                  // Disable tx needed for wake up
        retValue = uint8_t(retValue | mChip->writeRegister(ChipDef::ChanStatA + offset, ChipDef::FramerEn)); // Enable ChanA Framer
        retValue = uint8_t(retValue | mChip->writeRegister(ChipDef::MsgCtrlA + offset, 0));                  // Dont use InsChks when transmit OD Data, max14819 doesnt calculate it right
        retValue = uint8_t(retValue | mChip->writeRegister(ChipDef::CQCtrlA + offset, ChipDef::EstCom));     // Start communication

        // Wait till establish communication sequence is over or timeout is reached
        do
        {
            comReqRunning = mChip->readRegister(ChipDef::CQCtrlA + offset);
            comReqRunning &= ChipDef::EstCom;
            timeOutCounter++;
            wait_ms(1);
        } while (comReqRunning || (timeOutCounter < ChipDef::INIT_WURQ_TIMEOUT));

        wait_ms(10);
        // Clear buffer
        length = mChip->readRegister(ChipDef::RxFIFOLvlA + offset);
        for (uint8_t i = 0; i < length; i++)
        {
            mChip->readRegister(ChipDef::TxRxDataA + offset);
        }

        // read communication speed
        detectedCOM.comSpeed = mChip->readRegister(ChipDef::CQCtrlA + offset) & (ChipDef::ComRt0 | ChipDef::ComRt1);

        // Set correct communication speed in kBaud/s
        switch (detectedCOM.comSpeed)
        {
        case ChipDef::ComRt0:
            // Communication established at 4.8 kBaud/s
            detectedCOM.comSpeedBaud = 4800;
            break;
        case ChipDef::ComRt1:
            // Communication established at 38.4 kBaud/s
            detectedCOM.comSpeedBaud = 38400;
            break;
        case (ChipDef::ComRt0 | ChipDef::ComRt1):
            // Communication established at 230.4 kBaud/s
            detectedCOM.comSpeedBaud = 230400;
            break;
        default:
            // No communication established or other error occured
            detectedCOM.comSpeedBaud = 0;
            break;
        }
        print("wurq done");
        // return SUCCESS;
    }

    //!*****************************************************************************
    //! \brief  Initializes the GPIOs that are associated to the port.
    //!
    //!*****************************************************************************
    template <int IOLPortNr>
    void Max14819_Port<IOLPortNr>::initGPIOs()
    {
        DIPin::init();
        RxRdyPin::init();
        RxErrPin::init();
        StateLED::init();
    }

} // namespace openiolink
