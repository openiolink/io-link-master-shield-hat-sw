//!*****************************************************************************
//! \file   PrintAndWait.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  Function declarations to 
//!             - print a message to the console
//!             - wait some time in ms
//!
//! \note   There shall be an implementation (PrintAndWait.cpp) for each 
//!         platform in the corresponding subdirectory.
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

#ifndef PRINTANDWAIT_HPP
#define PRINTANDWAIT_HPP

#include <iostream>

namespace openiolink
{

    void print(char const *buf);
    void print(const int number);
    void wait(uint32_t ms);

} // namespace openiolink

#endif
