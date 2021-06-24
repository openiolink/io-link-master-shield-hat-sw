//!*****************************************************************************
//! \file   ALServiceObserver.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  Implementation of the observer pattern to "observe" the Application
//!         Layer (AL). This module contains both the Observer and the Subject
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
#ifndef OPENIOLINK_ALSERVICEOBSERVER_HPP
#define OPENIOLINK_ALSERVICEOBSERVER_HPP

#include "global_protocol.hpp" // isValidIOLPortNr()

namespace openiolink
{
    //!*************************************************************************
    //! \brief  Abstract base class for "something" (a.k.a. the "observer") that
    //!         wants to receive the services of the application layer (AL) of
    //!         the IO-Link master.
    //!
    //! \note   The methods are "receivers" of the services with the same name
    //!         (e.g. handleALControl() "receives" the service AL_Control
    //!         according to the Table 61 in the Specification V1.1.3), where
    //!         the Master is the "initiator" of the service.
    //!
    //! \note   Each specialized "observer" must implement all the methods of
    //!         this class. (As long as there is no full support for all AL
    //!         services, some methods are not pure virtual yet, to avoid
    //!         compilation errors.)
    //!         TODO make all methods pure virtual
    //!
    //!*************************************************************************
    class ALServiceHandler
    {
        // Abstract class -> no constructor / destructor
    public:
        inline virtual void handleALControl() = 0;
        inline virtual void handleALEvent();
        inline virtual void handleALNewInput();
        inline virtual void handleALPDCycle();
    };

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************

    // This is a dummy implementation because GenericIOLDevice does not
    // implement this method yet.
    // TODO make pure virtual to force implementation
    inline void ALServiceHandler::handleALEvent() {}

    // This is a dummy implementation because GenericIOLDevice does not
    // implement this method yet.
    // TODO make pure virtual to force implementation
    inline void ALServiceHandler::handleALNewInput() {}

    // This is a dummy implementation because GenericIOLDevice does not
    // implement this method yet.
    // TODO make pure virtual to force implementation
    inline void ALServiceHandler::handleALPDCycle() {}

    //--------------------------------------------------------------------------

    //!*************************************************************************
    //! \brief  Base class for the "subject" (in terms of the observer pattern).
    //!         This would usually be a "GenericIOLDevice" object.
    //!
    //! \note   The methods are intentionally NOT virtual because the
    //!         "GenericIOLDevice" class is supposed NOT to override them (just
    //!         including them by inheriting from this class).
    //!
    //! \todo   optimization:
    //!         - Adjuste the code to adapt to the the (future) configuration
    //!           about which IO-Link ports are used.
    //!
    //!*************************************************************************
    class ALServiceSubject
    {
    public:
        inline void registerObserver(const int port, const ALServiceHandler *observer);

    protected:
        ALServiceSubject();
        ~ALServiceSubject();
        inline void notifyALControl(const int port) const;
        inline void notifyALEvent(const int port) const;
        inline void notifyALNewInput(const int port) const;
        inline void notifyALPDCycle(const int port) const;

    private:
        //! The registered "observers" (only one per IO-Link port is allowed)
        ALServiceHandler *mDevice[4]; // TODO optimization when not all ports are used
    };

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************

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
    inline void ALServiceSubject::registerObserver(const int port, const ALServiceHandler *observer)
    {
        if (isValidIOLPortNr(port))
        {
            mDevice[port] = observer; // FIXME const correctness
        }
    }

    //!*************************************************************************
    //! \brief  Notifies the observer that an AL_Control service is pending.
    //!
    //! \param port[in] number of the IO-Link port which triggered the service
    //!
    //! \note   This method is NOT intended to be overridden.
    //!
    //!*************************************************************************
    inline void ALServiceSubject::notifyALControl(const int port) const
    {
        if (isValidIOLPortNr(port))
        {
            if (mDevice[port] != nullptr)
            {
                mDevice[port]->handleALControl();
            }
        }
    }

    //!*************************************************************************
    //! \brief  Notifies the observer that an AL_Event service is pending.
    //!
    //! \param port[in] number of the IO-Link port which triggered the service
    //!
    //! \note   This method is NOT intended to be overridden.
    //!
    //!*************************************************************************
    inline void ALServiceSubject::notifyALEvent(const int port) const
    {
        if (isValidIOLPortNr(port))
        {
            if (mDevice[port] != nullptr)
            {
                mDevice[port]->handleALEvent();
            }
        }
    }

    //!*************************************************************************
    //! \brief  Notifies the observer that an AL_NewInput service is pending.
    //!
    //! \param port[in] number of the IO-Link port which triggered the service
    //!
    //! \note   This method is NOT intended to be overridden.
    //!
    //!*************************************************************************
    inline void ALServiceSubject::notifyALNewInput(const int port) const
    {
        if (isValidIOLPortNr(port))
        {
            if (mDevice[port] != nullptr)
            {
                mDevice[port]->handleALNewInput();
            }
        }
    }

    //!*************************************************************************
    //! \brief  Notifies the observer that an AL_PDCycle service is pending.
    //!
    //! \param port[in] number of the IO-Link port which triggered the service
    //!
    //! \note   This method is NOT intended to be overridden.
    //!
    //!*************************************************************************
    inline void ALServiceSubject::notifyALPDCycle(const int port) const
    {
        if (isValidIOLPortNr(port))
        {
            if (mDevice[port] != nullptr)
            {
                mDevice[port]->handleALPDCycle();
            }
        }
    }

} // namespace openiolink
#endif
