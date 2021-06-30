//!*****************************************************************************
//! \file   PortModeObserver.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  Implementation of the observer pattern to "observe" the mode of an
//!         IO-Link port. This module contains both the Observer and the Subject
//!         base classes.
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
#ifndef OPENIOLINK_PORTMODEOBSERVER_HPP
#define OPENIOLINK_PORTMODEOBSERVER_HPP

#include "SystemManagement.hpp"

namespace openiolink
{
    //!*************************************************************************
    //! \brief  Abstract base class for "something" that wants to get informed
    //!         about the mode of an IO-Link port (a.k.a. the "observer").
    //!
    //! \note   Each specialized "observer" must implement the method
    //!         receiveNewPortMode().
    //!
    //!*************************************************************************
    class PortModeHandler
    {
        // Abstract class -> no constructor / destructor
    public:
        virtual void receiveNewPortMode(const int port, const SystemManagement::PortModes mode) = 0;
    };

    //--------------------------------------------------------------------------

    //!*************************************************************************
    //! \brief  Base class for the "subject" (in terms of the observer pattern).
    //!         This would be a "PortHandler" object in the "SystemManagement".
    //!
    //! \note   The methods are intentionally NOT virtual because the
    //!         "PortHandler" class is supposed NOT to override them (just
    //!         including them by inheriting from this class).
    //!
    //!*************************************************************************
    class PortModeSubject
    {
    public:
        inline void registerPortModeHandler(PortModeHandler *portModeHandler);

    protected:
        PortModeSubject();
        ~PortModeSubject();
        inline void sendPortMode(const int port, const SystemManagement::PortModes mode) const;

    private:
        //! The registered "observer" (only one is allowed)
        PortModeHandler *mHandler;
    };

    //!*************************************************************************
    //! \brief  Set portModeHandler as "observer" of this "subject". This
    //!         overwrites any previous registrations. The notifications
    //!         provided by this subject are about the mode (changes) of the
    //!         associated IO-Link port.
    //!
    //! \param portModeHandler[in]  Handler for the IO-Link port mode
    //!
    //! \note   This method is NOT intended to be overridden.
    //!
    //!*************************************************************************
    inline void PortModeSubject::registerPortModeHandler(PortModeHandler *portModeHandler)
    {
        mHandler = portModeHandler;
    }

    //!*************************************************************************
    //! \brief  Notifies the observer about the (new) mode of the IO-Link port.
    //!
    //! \param port[in] number of the IO-Link port
    //!
    //! \param mode[in] mode of the IO-Link port
    //!
    //! \note   This method is NOT intended to be overridden.
    //!
    //!*************************************************************************
    inline void PortModeSubject::sendPortMode(const int port, const SystemManagement::PortModes mode) const
    {
        mHandler->receiveNewPortMode(port, mode);
    }

} // namespace openiolink
#endif
