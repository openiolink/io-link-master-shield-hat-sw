//!*****************************************************************************
//! \file   OpeniolinkShieldHat.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  The class for the IO-Link-Master-Shield/Hat from openiolink
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

#ifndef OPENIOLINK_OPENIOLINKSHIELDHAT_HPP
#define OPENIOLINK_OPENIOLINKSHIELDHAT_HPP

#include "Max14819.hpp"

namespace openiolink
{

    class OpeniolinkShieldHat
    {
    public:
        // note: members not in initializer list: default initialization: https://en.cppreference.com/w/cpp/language/default_initialization
        OpeniolinkShieldHat();
        ~OpeniolinkShieldHat();
        void configureBothMax14819();

    protected:
        typedef Max14819<0> Chip0;
        typedef Max14819<1> Chip1;

    private:
        Chip0 mChip0; //!< the first IO-Link chip on the PCB
        Chip1 mChip1; //!< the second IO-Link chip on the PCB

        // TODO make configurable how many and which ports should be activated
        //static constexpr int mMaxPortCount = 4;
    };

} // namespace openiolink
#endif
