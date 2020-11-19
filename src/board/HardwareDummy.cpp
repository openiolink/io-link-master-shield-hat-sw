//!*****************************************************************************
//!  \file HardwareDummy.cpp
//!  
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!  
//!  \brief Simulates some Hardware
//!  
//!  \date 2020-10-22
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
#include "HardwareDummy.hpp"
#include <ostream>
#include <unistd.h>

namespace openiolinklibrary
{

    HardwareDummy::HardwareDummy(/* args */)
    {
        std::cout << "Init HardwareDummy\n";
        testpin.set(false);
        testpin.set(true);
    }

    HardwareDummy::~HardwareDummy()
    {
        std::cout << "Deinit HardwareDummy\n";
    }

    void HardwareDummy::wait_for(uint32_t delay_ms)
    {
        usleep(delay_ms * 1000);
    }

    HardwareDummy::PIN_Dummy::PIN_Dummy(std::string name, std::string mode) : pinname(name)
    {
        IO_PinMode(mode);
    }

    HardwareDummy::PIN_Dummy::~PIN_Dummy()
    {
        IO_PinMode("in");
    }

    void HardwareDummy::PIN_Dummy::set(bool setto)
    {
        if (setto)
        {
            IO_Write(HIGH);
        }
        else
        {
            IO_Write(LOW);
        }
    }

    void HardwareDummy::PIN_Dummy::IO_PinMode(std::string mode)
    {
        std::cout << "Pinmode: " << pinname << "=" << mode << "\n";
    }

    void HardwareDummy::PIN_Dummy::IO_Write(std::string output)
    {
        std::cout << "Pin set: " << pinname << "=" << output << "\n";
    }

} // namespace openiolinklibrary