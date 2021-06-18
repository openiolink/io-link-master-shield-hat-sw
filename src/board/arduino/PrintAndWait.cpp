//!*****************************************************************************
//! \file   PrintAndWait.cpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  Function to
//!             - print a message to the console
//!             - wait some time in ms
//!
//! \note   This is the implementation of PrintAndWait.hpp for Arduino.
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

#include "PrintAndWait.hpp"
#include <Arduino.h>
#include <stdio.h>

//!*************************************************************************
//! \brief  Prints a string to the default serial interface.
//!
//! \param buf [in] the string to print
//!
//!*************************************************************************
inline void print(char const *buf)
{
    printf("%s\n\r", buf);
}

//!*************************************************************************
//! \brief  Prints a number to the default serial interface.
//!
//! \param number [in]  the number to print
//!
//!*************************************************************************
inline void print(const int number)
{
    printf("%d\n\r", number);
}

//!*************************************************************************
//! \brief  Blocking delay
//!
//! \param ms [in]  time to wait in milliseconds
//!
//!*************************************************************************
inline void wait(uint32_t ms)
{
    delay(ms);
}
