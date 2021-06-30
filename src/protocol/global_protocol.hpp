//!*****************************************************************************
//! \file   global_protocol.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  Helper module (no class) for the classes in the /protocol directory
//!
//! \date   2021-06-15
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
#ifndef GLOBAL_PROTOCOL_HPP
#define GLOBAL_PROTOCOL_HPP

#include <iostream>

namespace openiolink
{
    // --- global constants ----------------------------------------------------

    // TODO Make a configuration to enable single ports available.
    //! configuration which ports to enable
    constexpr int globalNumberOfIOLPorts = 4;

    // --- function prototypes -------------------------------------------------
    inline bool isValidIOLPortNr(const int port);

    // --- function implementations --------------------------------------------

    //!*************************************************************************
    //! \brief  Checks if the given port is configured to be used
    //!
    //! \param port[in] number of the IO-Link port
    //!
    //! \return true if "port" is valid
    //!
    //! \todo   Follow the configuration to enable single ports
    //!
    //!*************************************************************************
    inline bool isValidIOLPortNr(const int port)
    {
        return port >= 0 && port < globalNumberOfIOLPorts;
    }

} // namespace openiolink

#endif // GLOBAL_PROTOCOL_HPP
