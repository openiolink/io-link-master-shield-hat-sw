//!*****************************************************************************
//!  \file HardwareDummy.hpp
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
#ifndef HARDWAREDUMMY_HPP_INCLUDED
#define HARDWAREDUMMY_HPP_INCLUDED

#include "board/HardwareDummyChip.hpp"
#include <iostream>
namespace openiolink
{
    //!*****************************************************************************
    //!  \brief This class simulates hardware
    //!  
    //!  
    //!*****************************************************************************
    class HardwareDummy
    {
    private:
        /* data */
    public:
        //!*****************************************************************************
        //!  \brief Construct a new Hardware Dummy object
        //!  
        //!  
        //!*****************************************************************************
        HardwareDummy();

        //!*****************************************************************************
        //!  \brief Destroy the Hardware Dummy object
        //!  
        //!  
        //!*****************************************************************************
        ~HardwareDummy();

        //!*****************************************************************************
        //!  \brief Waits for the given time in ms
        //!  
        //!  
        //!  \param delay_ms time to wait in ms
        //!  
        //!*****************************************************************************
        void wait_for(uint32_t delay_ms);

        //!*****************************************************************************
        //!  \brief Implementation of the abstract class used for the IOLinkDummyChip
        //!  
        //!  
        //!*****************************************************************************
        class PIN_Dummy : public IOLinkDummyChip::PIN
        {
        private:
            std::string pinname = "undef";
            std::string LOW = "LOW";
            std::string HIGH = "HIGH";
            void IO_PinMode(std::string mode);
            void IO_Write(std::string output);

        public:
            //!*****************************************************************************
            //!  \brief Construct a new pin dummy object
            //!  
            //!  
            //!*****************************************************************************
            PIN_Dummy(){};

            //!*****************************************************************************
            //!  \brief Construct a new pin dummy object
            //!  
            //!  
            //!  \param name of the pin
            //!  
            //!  \param mode like Pull up etc
            //!  
            //!*****************************************************************************
            PIN_Dummy(std::string name, std::string mode);

            //!*****************************************************************************
            //!  \brief Destroy the pin dummy object
            //!  
            //!  
            //!*****************************************************************************
            ~PIN_Dummy();

            //!*****************************************************************************
            //!  \brief Set the pin to the state
            //!  
            //!  
            //!  \param setto this state
            //!  
            //!*****************************************************************************
            void set(bool setto);
        };

        PIN_Dummy testpin = PIN_Dummy("testpin", "output"); //!< a test pin
    };

} // namespace openiolink

#endif // HARDWAREDUMMY_HPP_INCLUDED