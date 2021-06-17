//!*****************************************************************************
//!  \file IOLMasterPort.hpp
//!
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!          based on the work of Pascal Frei (freip2)
//!
//!  \brief Generic Hardware Layer abstraction of a physical layer
//!
//!  \date 2020-10-08
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
#ifndef IOLMASTERPORT_HPP_INCLUDED
#define IOLMASTERPORT_HPP_INCLUDED

#include "protocol/IOLMessage.hpp"
#include <memory>
#ifdef ARDUINO
#include <stdint.h>
#else
#include <cstdint>
#endif
namespace openiolink
{
    //!*****************************************************************************
    //!  \brief Abstract port class
    //!
    //!         Abstract class of an port without hardware layer
    //!
    //!*****************************************************************************
    class IOLMasterPort
    {
    public:
        //!*****************************************************************************
        //!  \brief States, in which the port can be
        //!
        //!*****************************************************************************
        enum class State
        {
            PowerDown,
            SIO,
            IOLink_connected,
            IOLink_disconnected
        };

        //!*****************************************************************************
        //!  \brief Modes in which the port could be set
        //!
        //! \note: Specification 5.2.2.1 (PL_SetMode)
        //!
        //!*****************************************************************************
        enum class Mode
        {
            INACTIVE, // PowerDown
            DI,       // SIO
            DO,       // SIO
            COM1,     // IOLink
            COM2,     // IOLink
            COM3      // IOLink
        };

        IOLMasterPort();
        ~IOLMasterPort();

        //!*****************************************************************************
        //!  \brief Abstract function to create an WURQ
        //!
        //!  \note This abstract function must be implemented for the used hardware
        //!
        //!*****************************************************************************
        virtual void wakeUpRequest(){}; // todo move to private // TODO pure virtual // TODO rename to establishCommunication() (also in class Max14819_Port)

        virtual void setMode(const Mode &targetMode);                             // TODO pure virtual
        virtual uint8_t sendIOLData(const openiolink::IOLMessage &msg);           // TODO pure virtual
        virtual uint8_t readIOLData(std::shared_ptr<openiolink::IOLMessage> msg); // TODO pure virtual
        State getState();
        Mode getMode();

        //!*****************************************************************************
        //!  \brief Abstract function te read data from IO-Link
        //!
        //!  \note This abstract function must be implemented for the used hardware
        //!
        //!
        //!  \param data pointer to the data destination
        //!
        //!  \param sizeofdata size of the data to read
        //!
        //!  \return uint8_t 1 for error because the function is not implemented
        //!
        //!*****************************************************************************
        virtual uint8_t readIOLData(uint8_t *data, uint8_t sizeofdata) { return 1; }; // todo move to protected

    protected:
        //!*****************************************************************************
        //!  \brief Abstract function to send data over IO-Link
        //!
        //!  \note This abstract function must be implemented for the used hardware
        //!
        //!
        //!  \param data pointer to the data to send
        //!
        //!  \param sizeofdata length of the data to send
        //!
        //!  \param sizeofanswer length of the expected answer
        //!
        //!  \return uint8_t 1 for error because the function is not implemented
        // TODO: Muss diese Methode hier überhaupt noch implementiert werden, oder könnte man sie auch rein virtuell machen mit "= 0;" ?
        //!
        //!*****************************************************************************
        virtual uint8_t sendIOLData(const /*FIXME OK?*/ uint8_t *data, uint8_t sizeofdata, uint8_t sizeofanswer) { return 1; };

    private: // TODO protected
        State state;
        Mode mode;
        // TODO comSpeed
    };
} // namespace openiolink

#endif // IOLMASTERPORT_HPP_INCLUDED