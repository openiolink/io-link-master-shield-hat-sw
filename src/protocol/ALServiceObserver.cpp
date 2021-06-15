//!*****************************************************************************
//! \file   ALServiceObserver.cpp
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

#include "ALServiceObserver.hpp"

namespace openiolink
{
    //!*************************************************************************
    //! \brief  Construct an ALServiceSubject object.
    //!
    //!*************************************************************************
    ALServiceSubject::ALServiceSubject() : mDevice{nullptr} // FIXME ist damit garantiert, dass ALLE Elemente des Arrays mit nullptr initialisiert werden?
    {
    }

    //!*************************************************************************
    //! \brief  Destruct the ALServiceSubject object.
    //!
    //!*************************************************************************
    ALServiceSubject::~ALServiceSubject()
    {
    }
} // namespace openiolink
