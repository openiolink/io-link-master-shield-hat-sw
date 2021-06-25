//!*****************************************************************************
//! \file   Pin_Raspberry.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  Abstraction of input-GPIOs and output-GPIOs of an Raspberry Pi 3
//!
//!         This module contains the following classes:
//!             - class PinBase
//!             - class OutputPin
//!             - class InputPin
//!         They are NOT intended to be instantiated!
//!
//! \date   2021-06-02
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
#ifndef PIN_RASPBERRY_HPP
#define PIN_RASPBERRY_HPP

#include <wiringPi.h>

namespace openiolink
{
    namespace raspberry
    {
        //!*************************************************************************
        //! \brief  Available possibilities of modes of a pin (GPIO)
        //!
        //! \note   OUTPUT and INPUT are part of the WiringPi library.
        //!
        //!*************************************************************************
        enum class PinModes
        {
            out = OUTPUT,
            in = INPUT,
            in_pullup,
            in_pulldown
        };

        ////////////////////////////////////////////////////////////////////////////
        //!*************************************************************************
        //! \brief  Base class for pin classes to avoid multiple generation of the
        //!         init() method (because pin classes are templates).
        //!
        //! \note   This class is not intended to be instantiated.
        //!
        //!*************************************************************************
        class PinBase
        {
        protected:
            static inline void init(const int gpioNr, const PinModes mode);
        };

        //!*************************************************************************
        //! \brief  Initializes the pin
        //!
        //! \param name the enumerated pinname
        //!
        //! \param mode mode of the pin
        //!
        //! \note   refer to http://wiringpi.com/reference/core-functions/
        //!
        //!*************************************************************************
        inline void PinBase::init(const int gpioNr, const PinModes mode) // TODO make non-inline?
        {
            if (mode == PinModes::out)
            {
                pinMode(gpioNr, static_cast<int>(PinModes::out));
            }
            else
            {
                pinMode(gpioNr, static_cast<int>(PinModes::in));
                if (mode == PinModes::in_pullup)
                {
                    pullUpDnControl(gpioNr, PUD_UP);
                }
                else if (mode == PinModes::in_pulldown)
                {
                    pullUpDnControl(gpioNr, PUD_DOWN);
                }
                else
                {
                    pullUpDnControl(gpioNr, PUD_OFF);
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////////
        //!*************************************************************************
        //! \brief  This class can be used to access an output GPIO.
        //!
        //! \note   This class is not intended to be instantiated.
        //!
        //!*************************************************************************
        template <int GpioNr>
        class OutputPin : public PinBase
        {
        public:
            static inline void init();
            static inline void setLow();
            static inline void setHigh();

        private:
            //static constexpr int mGpioNr = GpioNr;
        };

        //!*************************************************************************
        //! \brief  Initializes the pin as output
        //!
        //!*************************************************************************
        template <int GpioNr>
        inline void OutputPin<GpioNr>::init()
        {
            PinBase::init(GpioNr, PinModes::out);
        }

        //!*************************************************************************
        //! \brief  Sets the pin to low
        //!
        //!*************************************************************************
        template <int GpioNr>
        inline void OutputPin<GpioNr>::setLow()
        {
            digitalWrite(GpioNr, 0);
        }

        //!*************************************************************************
        //! \brief  Sets the pin to high
        //!
        //!*************************************************************************
        template <int GpioNr>
        inline void OutputPin<GpioNr>::setHigh()
        {
            digitalWrite(GpioNr, 1);
        }

        ////////////////////////////////////////////////////////////////////////////
        //!*************************************************************************
        //! \brief  This class can be used to access an input GPIO.
        //!
        //! \note   This class is not intended to be instantiated.
        //!
        //!*************************************************************************
        template <int GpioNr>
        class InputPin : public PinBase
        {
        public:
            static inline void init();
            static inline bool getState();

        private:
            //static constexpr int mGpioNr = GpioNr;
        };

        //!*************************************************************************
        //! \brief  Initializes the pin as input
        //!
        //!*************************************************************************
        template <int GpioNr>
        inline void InputPin<GpioNr>::init()
        {
            PinBase::init(GpioNr, PinModes::in_pullup); // TODO: is pullup neccessary?
        }

        //!*************************************************************************
        //! \brief  Returns the current state of the pin
        //!
        //!*************************************************************************
        template <int GpioNr>
        inline bool InputPin<GpioNr>::getState()
        {
            return static_cast<bool>(digitalRead(GpioNr));
        }

    } // namespace raspberry
} // namespace openiolink

#endif
