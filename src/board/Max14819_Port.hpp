//!*****************************************************************************
//! \file   Max14819_Port.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!         based on the work of Janik Lehmann (CrazyGecko) and Pascal Frei (freip2)
//!
//! \brief  Class for one port (channel) of the maxim integrated Dual IO-Link
//!         Master Transceiver MAX14819
//!
//! \date   2021-06-18
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

// platform-specific headers
#ifdef ARDUINO
#include "arduino/Pin_Arduino.hpp"
#else
#ifdef RASPBERRY
#include "raspberry/Pin_Raspberry.hpp"
#else
static_assert(false, "no known platform defined");
#endif
#endif

// generic (other) headers
#include "protocol/IOLMasterPort.hpp"
#include "protocol/IOLinkConfig.hpp"
#include "MapperIOLPort.hpp"
#include "Max14819.hpp"
#include "platform.hpp" // namespace platform
#include "BicolorLed.hpp"

namespace openiolink // TODO ::PCB?
{
    //!*****************************************************************************
    //! \brief  This class is the implementation of class IOLMasterPort (the
    //!         abstraction of the Physical Layer PL) for the MAX14819 IO-Link
    //!         transceiver.
    //!
    //! \note   Each MAX14819 chip has two IO-Link ports. This class represents one
    //!         of them.
    //!
    //! \note   Objects of this class will be owned by "IOLMaster", not by "Max14819".
    //!
    //!*****************************************************************************
    template <int IOLPortNr>                   //, int ChipNr = MapperIOLPort<IOLPortNr>::ChipNr>
    class Max14819_Port : public IOLMasterPort // TODO nachdem alle Klassen im namespace opeinolink sind: unnötige ns-Qualifizierer entfernen.
    {
    public:
        //!*****************************************************************************
        //! \brief Saves some information about the communication
        //!
        //!*****************************************************************************
        struct CommunicationInfo
        {
            uint8_t comSpeed;      //!< Communication speed in the register
            uint32_t comSpeedBaud; //!< Communication speed in baud
        };

        Max14819_Port();
        virtual ~Max14819_Port();
        virtual uint8_t sendIOLData(uint8_t *data, uint8_t sizeofdata, uint8_t sizeofanswer) override; // TODO static_assert(mChip!=nullptr)
        virtual uint8_t readIOLData(uint8_t *data, uint8_t sizeofdata) override;                       // TODO static_assert(mChip!=nullptr)
        virtual void setMode(const Modes &targetMode) override;                                        // TODO static_assert(mChip!=nullptr)
        virtual void wakeUpRequest() override;                                                         // TODO static_assert(mChip!=nullptr)

        inline CommunicationInfo getCommunicationInfo();
        inline void setChip(Max14819<ChipNr> *chip);

        // TODO enableCyclicSend ??
        // TODO disableCyclicSend
        // TODO enableLedControl
        // TODO disableLedControl
        // TODO writeLED
        // TODO writeDIConfig
        // TODO readDIConfig
        // TODO readCQ
        // TODO writeCQ
        // TODO writeDI

    private:
        //!*****************************************************************************
        //! \brief alias for the channel numbers
        //!
        //!*****************************************************************************
        enum Port
        {
            PORTA = 0,
            PORTB = 1
        };

        typedef platform::InputPin<MapperIOLPort<IOLPortNr>::DIPinNr> DIPin;       //!< Digital Input
        typedef platform::InputPin<MapperIOLPort<IOLPortNr>::RxRdyPinNr> RxRdyPin; //!< Rx Ready (LED)
        typedef platform::InputPin<MapperIOLPort<IOLPortNr>::RxErrPinNr> RxErrPin; //!< Rx Error (LED)
        typedef BicolorLed<IOLPortNr> StateLED;                                    //! multicolor state LED

        static constexpr int ChipNr = MapperIOLPort<IOLPortNr>::ChipNr;
        typedef Max14819<ChipNr> Chip; //!< the chip to wich this port belongs to
        Chip *mChip = nullptr;         //!< the chip to wich this port belongs to

        //! describes which port=channel of the chip the object is
        static constexpr int channelNr = MapperIOLPort<IOLPortNr>::ChannelNr;

        CommunicationInfo detectedCOM;

        void initGPIOs();
    }; // class Max14819_Port

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************

    //!*************************************************************************
    //! \brief Get the Communication Info object
    //!TODO: change to getDetectedCOM()
    //! NOTE: to be used to detect success of estab. communic.
    //!
    //! \return CommunicationInfo
    //!
    //!*************************************************************************
    // (= einfache Alternative zu `DL_Mode`)
    template <int IOLPortNr>
    //inline Max14819_Port<IOLPortNr, ChipNr>::CommunicationInfo Max14819_Port<IOLPortNr, ChipNr>::getCommunicationInfo()
    inline Max14819_Port<IOLPortNr>::CommunicationInfo Max14819_Port<IOLPortNr, ChipNr>::getCommunicationInfo()
    {
        return detectedCOM;
    }

    //!*************************************************************************
    //! \brief  set the pointer to the chip to wich this port belongs to
    //!
    //!*************************************************************************
    template <int IOLPortNr>
    //inline void Max14819_Port<IOLPortNr, ChipNr>::setChip(Max14819<ChipNr> *chip)
    inline void Max14819_Port<IOLPortNr>::setChip(Max14819<ChipNr> *chip)
    {
        static_assert(mChip == nullptr, "Max14819_Port: chip was already set!");
        mChip = chip;
    }

} // namespace openiolink
#endif //MAX14819_PORT_HPP_INCLUDED
