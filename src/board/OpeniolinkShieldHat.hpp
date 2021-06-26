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
#include "Max14819_Port.hpp"

namespace openiolink
{

    class OpeniolinkShieldHat
    {
        // TODO make configurable how many and which ports should be activated

    public:
        OpeniolinkShieldHat(Max14819_Port<0> *port0, Max14819_Port<1> *port1,
                            Max14819_Port<2> *port2, Max14819_Port<3> *port3);
        ~OpeniolinkShieldHat();
        void configureBothMax14819();

    private:
        Max14819<0> mChip0; //!< the first IO-Link transceiver chip on the PCB
        Max14819<1> mChip1; //!< the second IO-Link transceiver chip on the PCB
    };

} // namespace openiolink
#endif
