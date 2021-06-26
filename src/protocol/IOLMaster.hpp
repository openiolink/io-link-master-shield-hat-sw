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

//! Include the header file with the class describing the IO-Link Master PCB here!
#include "board/OpeniolinkShieldHat.hpp"

#include "IOLinkConfig.hpp"

//#include "SystemManagement.hpp"
//#include "ApplicationLayer.hpp"

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

        config::IOLMasterPCB mPCB; //!< the shield or hat

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
    template <template <int IOLPortNr> class IOLMasterPortImplementation>
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
    //!         IO-Link-Master in use.
    //!
    //!*************************************************************************
    using IOLMaster = IOLMasterClass<config::IOLMasterPortImplementation>;

} // namespace openiolink

// We need to include "our" .cpp file here. Explanation:
// Part of the methods of the class template declared in this .hpp file are
// defined in the same-named .cpp file. Since these are template methods the
// compiler won't do anything when compiling the .cpp file, because he does not
// know the actual template parameter(s) (value or type) that will be given when
// the template is instatiated.
// Wherever this class template will be used (i.e. instantiated), the compiler
// will only have this .hpp at hand (assuming it was included), but lacks the
// implementation details (the definitions). Those are located in the .cpp and
// tis is why we include the .cpp file here.
// (There may be other solutions to this problem, see e.g.
// https://www.codeproject.com/Articles/48575/How-to-Define-a-Template-Class-in-a-h-File-and-Imp)
//#ifndef EDITING
#include "IOLMaster.cpp"
//#endif
#endif
