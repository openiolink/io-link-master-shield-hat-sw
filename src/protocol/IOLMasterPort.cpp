//!*****************************************************************************
//!  \file IOLMasterPort.cpp
//!
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!          based on the work of Pascal Frei (freip2)
//!
//!  \brief Generic Hardware Layer abstraction of a physical layer
//!
//!  \date 2020-10-08
//!
//!
//!  *****************************************************************************
//!
//!  \copyright
//!  Copyright 2020 Bern University of Applied Sciences and Balluff AG
//!  \n\n
//!  Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!  \n\n
//!      http://www.apache.org/licenses/LICENSE-2.0
//!  \n\n
//!  Unless required by applicable law or agreed to in writing, software
//!  distributed under the License is distributed on an "AS IS" BASIS,
//!  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!  See the License for the specific language governing permissions and
//!  limitations under the License.
//!
//!*****************************************************************************
#include "IOLMasterPort.hpp"
namespace openiolink
{

    //!*****************************************************************************
    //!  \brief Construct a new IOLMasterPort object
    //!
    //!*****************************************************************************
    IOLMasterPort::IOLMasterPort() : state(State::PowerDown), mode(Mode::PowerDown) {}

    //!*****************************************************************************
    //!  \brief Destroy the IOLMasterPort object
    //!
    //!*****************************************************************************
    IOLMasterPort::~IOLMasterPort() {}

    //!*****************************************************************************
    //!  \brief Get the state of the port
    //!
    //!  \return actual state of the port
    //!
    //!*****************************************************************************
    IOLMasterPort::State IOLMasterPort::getState() { return state; }

    //!*****************************************************************************
    //!  \brief Set the port to mode
    //!
    //!
    //!  \param mode to be set
    //!
    //! \note: Specification 5.2.2.1 (PL_SetMode)
    //!
    //!*****************************************************************************
    void IOLMasterPort::setMode(Mode targetMode)
    {
        this->mode = targetMode;
        switch (targetMode)
        {
        case Mode::SIO:
            // TODO: set to SIO Mode
            state = State::SIO;
            break;

        case Mode::PowerDown:
            // TODO: Powerdown device
            state = State::PowerDown;
            break;

        case Mode::IOLink:
            // TODO: Set Device to IOLink Mode and start with wakeUp requests
            state = State::IOLink_disconnected;
            break;

        default:
            break;
        }
    }

    //!*****************************************************************************
    //!  \brief Get the actually set mode
    //!
    //!
    //!  \return Mode actually set
    //!
    //!*****************************************************************************
    IOLMasterPort::Mode IOLMasterPort::getMode() { return mode; }

    //!*****************************************************************************
    //!  \brief sends an IO-Link Message over IO-Link
    //!
    //!
    //!  \param msg Message to be sent
    //!
    //!  \return uint8_t 0 if success
    //!
    //!*****************************************************************************
    uint8_t IOLMasterPort::sendIOLData(const openiolink::IOLMessage &msg)
    {
        uint8_t buffer[openiolink::config::MAX_IOL_MESSAGE_LENGTH];
        uint8_t msglength = msg.getData(buffer);
        return sendIOLData(buffer, msglength, msg.getanswer_length());
        //        const/**/ uint8_t *datapointer; // FIXME sollte eigentlich nur mit const vornedran funtkionieren ohne Fehlermeldung
        //        uint8_t msglength = msg.getData(&datapointer);
        //        return sendIOLData(datapointer, msglength, msg.getanswer_length());
    }

    //!*****************************************************************************
    //!  \brief reads an IO-Link answer
    //!
    //!
    //!  \param msg destination, where the answer will be written
    //!
    //!  \return uint8_t 0 if success
    //!
    //!*****************************************************************************
    uint8_t IOLMasterPort::readIOLData(std::shared_ptr<openiolink::IOLMessage> msg)
    {
        // TODO function not working at the time
        uint8_t buffer[openiolink::config::MAX_IOL_MESSAGE_LENGTH];
        readIOLData(buffer, msg->getanswer_length());
        for (uint8_t i = 0; i < msg->getanswer_length(); i++)
        {
            switch (i)
            {
            case 0:
                break;

            default:
                // msg->setOctets()
                break;
            }
        }

        return 0; // TODO check checksum
    }

} // namespace openiolink