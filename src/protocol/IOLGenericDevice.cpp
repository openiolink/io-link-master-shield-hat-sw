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
        u_int8_t buffer[10];
        uint8_t page1actualread;
        msg.setMSequenceType(IOLMessage::M_Sequence_Type::Type0);

        for (u_int8_t i = 0; i < 13; i++)
        {
            
            msg.setMC(IOLMessage::Read_Write::Read_access, IOLMessage::Communication_Channel::Page, i+1); // 0x00 is MasterCommand
            port->sendIOLData(std::make_shared<IOLMessage>(msg));

            port->readIOLData(buffer, msg.getanswer_length());
            page1.data[i] = buffer[0];

        }



        std::cout << "read data" << std::endl;
    }

    void IOLGenericDevice::printPage1Data(void)
    {
        std::ios_base::fmtflags f(std::cout.flags()); // save flags state
        std::cout << std::showbase << std::hex;
        std::cout << "MasterCycleTime:    " << static_cast<int>(page1.MasterCycleTime) << std::endl;
        std::cout << "MinCycleTime:    " << static_cast<int>(page1.MinCycleTime) << std::endl;
        std::cout << "M_sequenceCapability:    " << static_cast<int>(page1.M_sequenceCapability) << std::endl;
        std::cout << "RevisionID:    " << static_cast<int>(page1.RevisionID) << std::endl;
        std::cout << "ProcessDataIn:    " << static_cast<int>(page1.ProcessDataIn) << std::endl;
        std::cout << "ProcessDataOut:    " << static_cast<int>(page1.ProcessDataOut) << std::endl;
        std::cout << "VendorID:    " << static_cast<int>(page1.VendorID.value) << std::endl;
        std::cout << "deviceID:    " << static_cast<int>(page1.deviceID.value) << std::endl;
        std::cout << "FunctionID:    " << static_cast<int>(page1.FunctionID.value) << std::endl;
        std::cout.flags(f); // restore flags state
    }
} // namespace openiolinklibrary
