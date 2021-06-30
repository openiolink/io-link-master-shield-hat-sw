//!*****************************************************************************
//! \file   ErrorCode.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  This file defines all error status codes which can occur in the
//!         data link layer, application layer and system management.
//!
//! \date   2021-06-02
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
#ifndef ERRORCODE_HPP
#define ERRORCODE_HPP

namespace openiolink
{
    //!*************************************************************************
    //! \brief  All error status codes which can occur in the
    //!         data link layer, application layer and system management.
    //!
    //! \note   This is a collection from the whole IO-Link Specification
    //!
    //!*************************************************************************
    enum class ErrorCode
    {
        // success
        NO_ERROR = 0,

        // from DL services
        NO_COMM,            // no communication available
        STATE_CONFLICT,     // service unavailable within current state
        PARAMETER_CONFLICT, // consistency of parameter set violated
        ISDU_TIMEOUT,       // ISDU acknowledgment time elapsed, see Table 102
        ISDU_NOT_SUPPORTED, // ISDU not implemented
        VALUE_OUT_OF_RANGE, // Service parameter value violates range definitions

        // general/unknown error (NOT according to the IO-Link Specification)
        UNKNOWN_ERROR
    };

} // namespace openiolink

#endif // ERRORCODE_HPP
