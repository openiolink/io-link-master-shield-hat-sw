//!*****************************************************************************
//! \file   Pin_Arduino.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  Abstraction of input-GPIOs and output-GPIOs of an Arduino DUE
//!
//!         This module contains the following classes:
//!         PinBase, OutputPin and InputPin
//!         They are not intended to be instantiated.
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

#ifndef PIN_ARDUINO_HPP
#define PIN_ARDUINO_HPP

#include "typedefs_board.hpp" // boolean return codes
#include <Arduino.h>

namespace openiolink::arduino
{
    //!*************************************************************************
    //! \brief  Available possibilities of modes of a pin (GPIO)
    //!
    //! \note   The definitons OUTPUT, INPUT and INPUT_PULLUP are part of the
    //!         Arduino library.
    //!
    //!*************************************************************************
    enum class PinModes
    {
        out = OUTPUT,
        in = INPUT, // input without pullup resistor
        in_pullup = INPUT_PULLUP
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
    //!*************************************************************************
    inline void PinBase::init(const int gpioNr, const PinModes mode)
    {
        pinMode(gpioNr, mode); // pinMode() is part of the Arduino library.
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
        init(GpioNr, PinModes::out);
    }

    //!*************************************************************************
    //! \brief  Sets the pin to low
    //!
    //!*************************************************************************
    template <int GpioNr>
    inline void OutputPin<GpioNr>::setLow()
    {
        digitalWrite(mGpioNr, 0);
    }

    //!*************************************************************************
    //! \brief  Sets the pin to high
    //!
    //!*************************************************************************
    template <int GpioNr>
    inline void OutputPin<GpioNr>::setHigh()
    {
        digitalWrite(mGpioNr, 1);
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
        init(GpioNr, PinModes::in_pullup); // TODO: is pullup neccessary?
    }

    //!*************************************************************************
    //! \brief  Returns the current state of the pin
    //!
    //!*************************************************************************
    template <int GpioNr>
    inline bool InputPin<GpioNr>::getState()
    {
        return digitalRead(GpioNr);
    }

} // namespace openiolink::arduino

#endif
