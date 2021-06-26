//!*****************************************************************************
//! \file   IOLinkConfig.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!         based on the work of Janik Lehmann (xxthegeckoxx@gmail.com)
//!
//! \brief  configurations for the library can be done within this file
//!
//! \date   2021-06-26
//!
//!
//! ****************************************************************************
//!
//! \copyright
//! Copyright 2020 Bern University of Applied Sciences and Balluff AG
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
#ifndef IOLINK_CONFIG_HPP_INCLUDED
#define IOLINK_CONFIG_HPP_INCLUDED

namespace openiolink
{
    //! CONFIG 1:
    //! The class that implements the IO-Link port
    //! capability of the IO-Link transceiver chip that you are using.
    //! note: This class must inherit from IOLMasterPort.
    //! note: This class must take one integer template parameter.
    //! (forward declaration to avoid inclusion of the defining header)
    template <int PortNr>
    class Max14819_Port;

    //! CONFIG 2:
    //! The class that describes your IO-Link-Master PCB
    //! (forward declaration to avoid inclusion of the defining header)
    //! NOTE: Don't forget to #include the appropriate header in protocol/IOLMaster.cpp
    class OpeniolinkShieldHat;

    //! Library configruations are done in this namespace
    namespace config
    {
        //! CONFIG 1-b: class that implements the IO-Link port
        //! --> Put the class from CONFIG 1 here.
        template <int PortNr>
        using IOLMasterPortImplementation = Max14819_Port<PortNr>;

        //! CONFIG 2-b: class that describes your IO-Link-Master PCB
        //! --> Put the class from CONFIG 2 here.
        using IOLMasterPCB = OpeniolinkShieldHat;

        //! CONFIG 3:
        //! maximum expected length of an IO-Link message
        static constexpr int MAX_IOL_MESSAGE_LENGTH = 10;

        //! CONFIG 4:
        // TODO how many and which IO-Link ports on the Master should be used

    } // namespace config

} // namespace openiolink

#endif // IOLINK_CONFIG_HPP_INCLUDED