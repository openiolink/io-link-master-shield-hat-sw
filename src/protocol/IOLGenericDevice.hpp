//!*****************************************************************************
//!  \file IOLGenericDevice.hpp
//!  
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!  
//!  \brief Contains a class of an IO-Link device
//!
//!  \date 2020-11-15
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

#ifndef IOLGENERICDEVICE_HPP_INCLUDED
#define IOLGENERICDEVICE_HPP_INCLUDED

#include "IOLMasterPort.hpp"
#include <memory>

namespace openiolinklibrary
{
    //!*****************************************************************************
    //!  \brief Class of an IO-Link device
    //!  
    //!         This class describes an device connected to an IO-Link port
    //!  
    //!*****************************************************************************
    class IOLGenericDevice
    {
    private:
        std::shared_ptr<IOLMasterPort> port;    //!< Port, where the device is connected

        //!*****************************************************************************
        //!  \brief Page 1 data
        //!  
        //!         IO-Link Interface and System Specification V1.1.2 Table B.1
        //!  
        //!*****************************************************************************
        union
        {
            uint8_t data[13];
            struct //__attribute__((__packed__))
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
                union //__attribute__((__packed__))
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
        //!*****************************************************************************
        //!  \brief Construct a new IOLGenericDevice object
        //!  
        //!  
        //!*****************************************************************************
        IOLGenericDevice(){};

        //!*****************************************************************************
        //!  \brief Destroy the IOLGenericDevice object
        //!  
        //!  
        //!*****************************************************************************
        ~IOLGenericDevice(){};

        //!*****************************************************************************
        //!  \brief Set the port, where the device is connected
        //!  
        //!  
        //!  \param port_
        //!  
        //!*****************************************************************************
        void setPort(std::shared_ptr<IOLMasterPort> port_);

        //!*****************************************************************************
        //!  \brief Reads the page 1 data from the device
        //!  
        //!  \note  Do not use this function. It will be moved to private. It is public
        //!         for debug only.
        //!  
        //!*****************************************************************************
        void readPage1Data();

        //!*****************************************************************************
        //!  \brief Prints the data contained in page1 to the ostream object
        //!  
        //!  \note  Do not use this function. It is for debug only. There will be
        //!         functions to read the page1 data
        //!  
        //!*****************************************************************************
        void printPage1Data();
    };

} // namespace openiolinklibrary

#endif // IOLGENERICDEVICE_HPP_INCLUDED