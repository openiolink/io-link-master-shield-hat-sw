//!*****************************************************************************
//!  \file IOLGenericDevice.cpp
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

#include "IOLGenericDevice.hpp"
#include <iostream>

namespace openiolinklibrary
{
    void IOLGenericDevice::setPort(std::shared_ptr<IOLMasterPort> port_)
    {
        port = port_;
    }

    void IOLGenericDevice::readPage1Data()
    {
        IOLMessage msg;
        uint8_t buffer[10];
        uint8_t page1actualread;
        msg.setMSequenceType(IOLMessage::M_Sequence_Type::Type0);

        for (uint8_t i = 0; i < 13; i++)
        {
            
            msg.setMC(IOLMessage::Read_Write::Read_access, IOLMessage::Communication_Channel::Page, i+1); // 0x00 is MasterCommand
            port->sendIOLData(std::make_shared<IOLMessage>(msg));

            port->readIOLData(buffer, msg.getanswer_length());
            page1.data[i] = buffer[0];

        }



        std::cout << "read data\n\r";
    }

    void IOLGenericDevice::printPage1Data(void)
    {
        std::ios_base::fmtflags f(std::cout.flags()); // save flags state
        std::cout << std::showbase << std::hex;
        std::cout << "MasterCycleTime:    " << static_cast<int>(page1.MasterCycleTime) << "\n\r";
        std::cout << "MinCycleTime:    " << static_cast<int>(page1.MinCycleTime) << "\n\r";
        std::cout << "M_sequenceCapability:    " << static_cast<int>(page1.M_sequenceCapability) << "\n\r";
        std::cout << "RevisionID:    " << static_cast<int>(page1.RevisionID) << "\n\r";
        std::cout << "ProcessDataIn:    " << static_cast<int>(page1.ProcessDataIn) << "\n\r";
        std::cout << "ProcessDataOut:    " << static_cast<int>(page1.ProcessDataOut) << "\n\r";
        std::cout << "VendorID:    " << static_cast<int>(page1.VendorID.value) << "\n\r";
        std::cout << "deviceID:    " << static_cast<int>(page1.deviceID.value) << "\n\r";
        std::cout << "FunctionID:    " << static_cast<int>(page1.FunctionID.value) << "\n\r";
        std::cout << "\n\r";
        std::cout.flags(f); // restore flags state
    }
} // namespace openiolinklibrary
