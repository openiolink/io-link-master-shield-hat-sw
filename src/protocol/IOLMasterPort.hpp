
//!*****************************************************************************
//!  \file      IOLMasterPort.h
//!*****************************************************************************
//!
//!  \brief		Generic Hardware Layer abstraction of a physical layer
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
#ifndef IOLMASTERPORT_H_INCLUDED
#define IOLMASTERPORT_H_INCLUDED

#include "protocol/IOLMessage.hpp"
#include <cstdint>
#include <memory>
namespace openiolinklibrary
{
    class IOLMasterPort
    {
    public:
        enum class State
        {
            PowerDown,
            SIO,
            IOLink_connected,
            IOLink_disconnected
        };
        enum class Mode
        {
            PowerDown,
            SIO,
            IOLink
        };

    private:
        State state;
        Mode mode;
        // TODO: Processdata Handler
    protected:
        virtual uint8_t sendIOLData(uint8_t* data, uint8_t sizeofdata, uint8_t sizeofanswer){ return 1;};
    public:
        IOLMasterPort();
        ~IOLMasterPort();
        virtual void wakeUpRequest(){}; // todo move to private
        State getState();
        void setMode(Mode);
        Mode getMode();
        uint8_t sendIOLData(std::shared_ptr<openiolinklibrary::IOLMessage> msg);
        // virtual void readDeviceParameter();

    };
} // namespace openiolinklibrary

#endif // IOLMASTERPORT_H_INCLUDED