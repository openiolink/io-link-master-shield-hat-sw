//!*****************************************************************************
//! \file   Max14819_Port.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!         based on the work of Janik Lehmann (CrazyGecko) and Pascal Frei (freip2)
//!
//! \brief  Class for one port (channel) of the maxim integrated Dual IO-Link
//!         Master Transceiver MAX14819
//!
//! \date   2021-06-02
//!
//!
//! *****************************************************************************
//!
//! \copyright
//! Copyright 2020, 2021 Bern University of Applied Sciences and Balluff AG
//! \n\n
//! Licensed under the Apache License, Version 2.0 (the "License");
//! you may not use this file except in compliance with the License.
//! You may obtain a copy of the License at
//! \n\n
//!     http://www.apache.org/licenses/LICENSE-2.0
//! \n\n
//! Unless required by applicable law or agreed to in writing, software
//! distributed under the License is distributed on an "AS IS" BASIS,
//! WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//! See the License for the specific language governing permissions and
//! limitations under the License.
//!
//!*****************************************************************************

#ifndef MAX14819_PORT_HPP_INCLUDED
#define MAX14819_PORT_HPP_INCLUDED

#include <memory>
#include "protocol/IOLMasterPort.hpp"
#include "protocol/IOLMessage.hpp"
#include "protocol/IOLinkConfig.hpp"
#include "MapperIOLPort.hpp"
#include "Max14819.hpp"

namespace openiolink
{
    //!*****************************************************************************
    //! \brief A port of the MAX14819 IO-Link transceiver
    //!
    //!        Each MAX14819 chip has two IO-Link ports. This class represents one of them.
    //!
    //!*****************************************************************************
    template <int IOLPortNr, int ChipNr = MapperIOLPort<IOLPortNr>::ChipNr>
    class Max14819_Port : public IOLMasterPort // TODO nachdem alle Klassen im namespace opeinolink sind: unnötige ns-Qualifizierer entfernen.
    {
    public:
        //!*****************************************************************************
        //! \brief Saves some information about the communication
        //!
        //!
        //!*****************************************************************************
        struct CommunicationInfo
        {
            uint8_t comSpeed;      //!< Communication speed in the register
            uint32_t comSpeedBaud; //!< Communication speed in baud
        };

        //!*****************************************************************************
        //! \brief enumerates PORTA and PORTB
        //!
        //!
        //!*****************************************************************************
        enum Port
        {
            PORTA = 0,
            PORTB = 1
        };

    private:
        typedef Max14819<ChipNr> MyChip;                               //! A Port has to call his Chip for variuos tasks.
        constexpr Port port = MapperIOLPort<IOLPortNr>::ChannelNr; //!< describes which port of the chip the object is
        CommunicationInfo communicationInfo;

    protected:
        //!*****************************************************************************
        //! \brief Sends data over IO-Link
        //!
        //!
        //! \param data pointer to the data to send
        //!
        //! \param sizeofdata length of the data to send
        //!
        //! \param sizeofanswer length of the expected answer
        //!
        //! \return uint8_t 0 if success
        //!
        //!*****************************************************************************
        uint8_t sendIOLData(uint8_t *data, uint8_t sizeofdata, uint8_t sizeofanswer) override;

        //!*****************************************************************************
        //! \brief Reads data from IO-Link
        //!
        //!
        //! \param data pointer to the destination of the data
        //!
        //! \param sizeofdata length of the expected data
        //!
        //! \return uint8_t 0 if success
        //!
        //!*****************************************************************************
        uint8_t readIOLData(uint8_t *data, uint8_t sizeofdata) override;

    public:
        //!*****************************************************************************
        //! \brief Construct a new Max14819_Port object
        //!
        //!
        //! \param port_ defines if the initialized port is either PORTA or PORTB
        //!
        //! \param chip_ pointer to the chip which contains this port
        //!
        //!*****************************************************************************
        Max14819_Port(Port port_, std::shared_ptr<Max14819> chip_) : port(port_), chip(chip_){};

        //!*****************************************************************************
        //! \brief Destroy the Max14819_Port object
        //!
        //!
        //!*****************************************************************************
        ~Max14819_Port(){};

        //!*****************************************************************************
        //! \brief Set the port to this mode
        //!
        //!
        //!*****************************************************************************
        // ca. = DL_SetMode
        void setMode(Mode);

        //!*****************************************************************************
        //! \brief Sends an WURQ over IO-Link
        //!
        //!
        //!*****************************************************************************
        void wakeUpRequest();

        // TODO enableCyclicSend
        // TODO disableCyclicSend
        // TODO enableLedControl
        // TODO disableLedControl
        // TODO writeLED
        // TODO writeDIConfig
        // TODO readDIConfig
        // TODO readCQ
        // TODO writeCQ
        // TODO writeDI

        //!*****************************************************************************
        //! \brief Get the Communication Info object
        //!
        //!
        //! \return CommunicationInfo
        //!
        //!*****************************************************************************
        // = einfache Alternative zu `DL_Mode`
        CommunicationInfo getCommunicationInfo() { return communicationInfo; };
    };
} // namespace openiolink
#endif //MAX14819_PORT_HPP_INCLUDED
