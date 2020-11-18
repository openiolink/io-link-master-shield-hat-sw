//!*****************************************************************************
//!  \file IOLGenericDevice.hpp
//!
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!
//!  \brief
//!
//!  \date 2020-11-15
//!
//!
//!  *****************************************************************************
//!
//!  \copyright
//!  Copyright 2020 Bern University of Applied Sciences and Balluff AG
//!
//!  Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!
//!      http://www.apache.org/licenses/LICENSE-2.0
//!
//!  Unless required by applicable law or agreed to in writing, software
//!  distributed under the License is distributed on an "AS IS" BASIS,
//!  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!  See the License for the specific language governing permissions and
//!  limitations under the License.
//!
//!*****************************************************************************

#ifndef IOLGENERICDEVICE_HPP_INCLUDED
#define IOLGENERICDEVICE_HPP_INCLUDED

#include "IOLMasterPort.hpp"
#include <memory>

namespace openiolinklibrary
{

    class IOLGenericDevice
    {
    private:
        std::shared_ptr<IOLMasterPort> port;

        union
        {
            uint8_t data[13];
            struct __attribute__((__packed__))
            {
                uint8_t MasterCycleTime;
                uint8_t MinCycleTime;
                uint8_t M_sequenceCapability;
                uint8_t RevisionID;
                uint8_t ProcessDataIn;
                uint8_t ProcessDataOut;
                union
                {
                    uint8_t bytes[2];
                    uint16_t value;
                } VendorID;
                union __attribute__((__packed__))
                {
                    uint8_t bytes[3];
                    uint32_t value : 24;
                } deviceID;
                union
                {
                    uint8_t bytes[2];
                    uint16_t value;
                } FunctionID;
            };
        } page1; ///< Aufbau der Page1 eines Sensors

    public:
        IOLGenericDevice(/* args */){};
        ~IOLGenericDevice(){};
        void setPort(std::shared_ptr<IOLMasterPort> port_);
        void readPage1Data();
        void printPage1Data();
    };

} // namespace openiolinklibrary

#endif // IOLGENERICDEVICE_HPP_INCLUDED