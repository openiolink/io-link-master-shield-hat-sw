
//!*****************************************************************************
//!  \file      IOLMasterPort.cpp
//!*****************************************************************************
//!
//!  \brief		Abstract class layer for driver ic independent Port
//!             implementation. Defines methods and variables for the
//!             IOLMasterPort<driver_ic> implementation.
//!
//!  \author    Pascal Frei (freip2)
//!             Janik Lehmann (CrazyGecko)
//!
//!  \date      2020-10-08
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
#include "IOLMasterPort.hpp"
namespace openiolinklibrary
{

    IOLMasterPort::IOLMasterPort() : state(State::PowerDown), mode(Mode::PowerDown) {}

    IOLMasterPort::~IOLMasterPort() {}

    IOLMasterPort::State IOLMasterPort::getState() { return state; }

    void IOLMasterPort::setMode(Mode mode)
    {
        this->mode = mode;
        switch (mode)
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

    IOLMasterPort::Mode IOLMasterPort::getMode() { return mode; }
    
} // namespace openiolinklibrary