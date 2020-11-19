//!*****************************************************************************
//!  \file IOLinkConfig.hpp
//!  
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!  
//!  \brief configurations for the library can be done within this file
//!  
//!  \date 2020-11-05
//!  
//!  
//!  *****************************************************************************
//!  
//!  \copyright
//!  Copyright 2020 Bern University of Applied Sciences and Balluff AG
//!  \n\n
//!  Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!  \n\n
//!      http://www.apache.org/licenses/LICENSE-2.0
//!  \n\n
//!  Unless required by applicable law or agreed to in writing, software
//!  distributed under the License is distributed on an "AS IS" BASIS,
//!  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!  See the License for the specific language governing permissions and
//!  limitations under the License.
//!  
//!*****************************************************************************
#ifndef IOLINK_CONFIG_HPP_INCLUDED
#define IOLINK_CONFIG_HPP_INCLUDED

namespace openiolinklibrary
{
    namespace libraryconfig
    {
        static constexpr int MAX_IOL_MESSAGE_LENGTH = 10; //!< maximum expected length of an IO-Link message
    } // namespace libraryconfig
    
} // namespace openiolinklibrary

#endif // IOLINK_CONFIG_HPP_INCLUDED