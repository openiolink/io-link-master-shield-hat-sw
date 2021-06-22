//!*****************************************************************************
//! \file   IOLMaster.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  This class represents an IO-Link Master.
//!
//! \date   2021-06-22
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

#ifndef OPENIOLINK_IOLMASTER_HPP
#define OPENIOLINK_IOLMASTER_HPP

//#include "SystemManagement.hpp"
//#include "ApplicationLayer.hpp"
#include "OpeniolinkShieldHat.hpp"

//#include "IOLinkConfig.hpp"
#include "Max14819_Port.hpp" // TODO remove (see end of this file)

//#include "GenericIOLDevice.hpp"
namespace openiolink
{
    class GenericIOLDevice;
}

namespace openiolink
{
    //!*************************************************************************
    //! \brief  class template for class IOLMaster
    //!
    //! \note   The template template parameter 'IOLMasterPortImplementation'
    //!         takes the typename of a class template which implements (i.e.
    //!         inherits from) the class IOLMasterPort.
    //!
    //! \note   There is an alias defintion called 'IOLMaster' which the user
    //!         of the library should use to instantiate this class.
    //!
    //!*************************************************************************
    template <template <int IOLPortNr> class IOLMasterPortImplementation>
    class IOLMasterClass
    {
    public:
        IOLMasterClass();
        ~IOLMasterClass();
        inline void stepFSM();
        void wakeUpPort(const int port);
        void getPage1(const int port);
        bool connectDevice(const int portNr, const GenericIOLDevice &device);

    private:
        // TODO make configurable how many and which ports are used
        IOLMasterPortImplementation<0> mPort0; //!< IO-Link PORT0
        IOLMasterPortImplementation<1> mPort1; //!< IO-Link PORT1
        IOLMasterPortImplementation<2> mPort2; //!< IO-Link PORT2
        IOLMasterPortImplementation<3> mPort3; //!< IO-Link PORT3

        //ApplicationLayer mAL; //!< the "application layer" (part of the IO-Link stack)
        //SystemManagement mSM; //!< the "system management" (part of the IO-Link stack)

        OpeniolinkShieldHat mPCB; //!< the shield or hat

        //! \brief  currently connected IO-Link Devices
        //! \note   provided by user via connectDevice()
        GenericIOLDevice *mDevice[4] = {nullptr, nullptr, nullptr, nullptr};
    };

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************

    //!*************************************************************************
    //! \brief  keep the library runnung
    //!
    //! The IO-Link Master stack that is implemented in this library relies on
    //! multiple state machines (FSMs). If these do not run there will also be
    //! no IO-Link communication.
    //!
    //! \note   IMPORTANT: This function has to be called periodically!
    //!                    Please consult the documentation for details.
    //!
    //!*************************************************************************
    inline void IOLMasterClass<IOLMasterPortImplementation>::stepFSM()
    {
        //mAL.stepFSM();
        //mSM.stepFSM();
    }

    //**************************************************************************
    // class alias definition for the convenience of the user
    //**************************************************************************

    //!*************************************************************************
    //! \brief  This class represents the IO-Link Master.
    //!
    //! \note   The user application must instantiate this class once per
    //!         Master in use.
    //!
    //! \todo   Max14819_Port von config-header beziehen, nicht hardcodiert hier.
    //!
    //!*************************************************************************
    using IOLMaster = IOLMasterClass<Max14819_Port>;
    //typedef IOLMasterClass<Max14819_Port> IOLMaster; // this would say the same

} // namespace openiolink
#endif
