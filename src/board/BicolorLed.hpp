//!*****************************************************************************
//! \file   BicolorLED.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  Abstraction of a bicolor LED
//!
//! \date   2021-06-18
//!
//!
//! ****************************************************************************
//!
//! \copyright
//! Copyright 2021 Bern University of Applied Sciences and Balluff AG
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
#ifndef OPENIOLINK_BICOLORLED_HPP
#define OPENIOLINK_BICOLORLED_HPP

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
#include "platform.hpp" // namespace platform
#include "MapperIOLPort.hpp"
#include "assert.h" // assert()

namespace openiolink
{
    //!*************************************************************************
    //! \brief  Abstracion of a "bicolor" LED belonging to one port of an
    //!         IO-Link Master. It may be use to visualize activity on the port
    //!         and/or the state of the port.
    //!
    //! \note   This class is meant to be used for a green-red bicolor LED. Both
    //!         color components are driven low-active via separate GPIOs.
    //!
    //! \note   This class should NOT be instantiated!
    //!
    //!*************************************************************************
    template <int IOLPortNr>
    class BicolorLed
    {
    public:
        //!*********************************************************************
        //! \brief  colors that a green-red bicolor LED can display
        //!
        //!*********************************************************************
        enum class LedColor
        {
            OFF,   // both colors off
            RED,   // only red on
            GREEN, // only green on
            ORANGE // both colors on
        };

        static inline void init();
        static inline void setColor(const LedColor Color);

    private:
        //! the GPIO for the red LED
        typedef platform::OutputPin<MapperIOLPort<IOLPortNr>::GreenLedPinNr> GreenLedPin;
        //! the GPIO for the green LED
        typedef platform::OutputPin<MapperIOLPort<IOLPortNr>::RedLedPinNr> RedLedPin;
    };

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************

    //!*************************************************************************
    //! \brief  initialize the bicolor LED and switch it off
    //!
    //!*************************************************************************
    template <int IOLPortNr>
    inline void BicolorLed<IOLPortNr>::init()
    {
        GreenLedPin::init();
        RedLedPin::init();
        setColor(LedColor::OFF);
    }

    //!*************************************************************************
    //! \brief  set the color of the "bicolor" LED
    //!
    //! \param Color [in]   the new color (enumerated value)
    //!
    //!*************************************************************************
    template <int IOLPortNr>
    inline void BicolorLed<IOLPortNr>::setColor(const LedColor Color)
    {
        switch (Color)
        {
        case LedColor::RED:
            GreenLedPin::setHigh(); // remember that the LEDs are low-active
            RedLedPin::setLow();
            break;
        case LedColor::GREEN:
            GreenLedPin::setLow();
            RedLedPin::setHigh();
            break;
        case LedColor::ORANGE:
            GreenLedPin::setLow();
            RedLedPin::setLow();
            break;
        case LedColor::OFF:
            GreenLedPin::setHigh();
            RedLedPin::setHigh();
            break;
        default:
            assert(false); // "Unsupported color for the BicolorLed requested!"
            break;
        }
    }

} // namespace openiolink
#endif
