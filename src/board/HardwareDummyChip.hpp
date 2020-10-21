
//!*****************************************************************************
//!  \file      Max14819.h
//!*****************************************************************************
//!
//!  \brief		Simulation of an Chip Object
//!
//!  \author    Janik Lehmann (CrazyGecko)
//!
//!  \date      2020-10-11
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
#ifndef HARDWAREDUMMYCHIP_HPP_INCLUDED
#define HARDWAREDUMMYCHIP_HPP_INCLUDED

namespace openiolinklibrary
{
    class IOLinkDummyChip
    {
    public:
        class PIN
        {
        private:
            /* data */
        public:
            PIN(/* args */){};
            virtual ~PIN(){};
            virtual void on(){};
            virtual void off(){};
        };
        
        enum class State
        {
            powerDown,
            idle,
            sendingData,
            receivingData,
            DataReceived,
            waitingForProcessData,
            SIO
        };

    private:
        State state;

    public:
        IOLinkDummyChip();
        ~IOLinkDummyChip();
        void reset();
        void sendData();
        void getData();
        void powerDown();
        void powerUp();
        State getState();
    };
} // namespace openiolinklibrary

#endif // HARDWAREDUMMYCHIP_HPP_INCLUDED