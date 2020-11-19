//!*****************************************************************************
//!  \file HardwareDummyChip.hpp
//!  
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!  
//!  \brief Simulation of an Chip Object
//!
//!  \date 2020-10-11
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
#ifndef HARDWAREDUMMYCHIP_HPP_INCLUDED
#define HARDWAREDUMMYCHIP_HPP_INCLUDED

namespace openiolinklibrary
{
    //!*****************************************************************************
    //!  \brief This class simulates an chip
    //!  
    //!  
    //!*****************************************************************************
    class IOLinkDummyChip
    {
    public:
        //!*****************************************************************************
        //!  \brief Abstract class for io pins
        //!
        //!         This is an abstract class which is needed to set pins from the
        //!         max14819 class itself.
        //!
        //!  \note  This abstract class must be implemented for the used hardware.
        //!
        //!*****************************************************************************
        class PIN
        {
        private:
            /* data */
        public:
            PIN(){};
            virtual ~PIN(){};
            //!*****************************************************************************
            //!  \brief Sets the state of an IO-Pin
            //!  
            //!  
            //!  \param state set to this
            //!  
            //!*****************************************************************************
            virtual void set(bool state) = 0;
        };
        
        //!*****************************************************************************
        //!  \brief available states of the chip
        //!  
        //!  
        //!*****************************************************************************
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
        State state;    //!< actual state

    public:
        //!*****************************************************************************
        //!  \brief Construct a new IOLinkDummyChip object
        //!  
        //!  
        //!*****************************************************************************
        IOLinkDummyChip();

        //!*****************************************************************************
        //!  \brief Destroy the IOLinkDummyChip object
        //!  
        //!  
        //!*****************************************************************************
        ~IOLinkDummyChip();

        //!*****************************************************************************
        //!  \brief Resets the dummy chip
        //!  
        //!  
        //!*****************************************************************************
        void reset();

        //!*****************************************************************************
        //!  \brief Sends data
        //!  
        //!  
        //!*****************************************************************************
        void sendData();

        //!*****************************************************************************
        //!  \brief Receives data
        //!  
        //!  
        //!*****************************************************************************
        void getData();

        //!*****************************************************************************
        //!  \brief Shutdown the chip
        //!  
        //!  
        //!*****************************************************************************
        void powerDown();

        //!*****************************************************************************
        //!  \brief Starts the chip
        //!  
        //!  
        //!*****************************************************************************
        void powerUp();

        //!*****************************************************************************
        //!  \brief Get the State object
        //!  
        //!  
        //!  \return State
        //!  
        //!*****************************************************************************
        State getState();
    };
} // namespace openiolinklibrary

#endif // HARDWAREDUMMYCHIP_HPP_INCLUDED