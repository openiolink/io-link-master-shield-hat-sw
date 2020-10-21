
//!*****************************************************************************
//!  \file      HardwareDummyChip.cpp
//!*****************************************************************************
//!
//!  \brief		Simulation of an Chip Object
//!
//!  \author    Janik Lehmann (CrazyGecko)
//!
//!  \date      2020-10-11
//!
//!*****************************************************************************
//!
//!	 Copyright 2019 Bern University of Applied Sciences and Balluff AG
//!
//!	 Licensed under the Apache License, Version 2.0 (the "License")
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!
//!	     http://www.apache.org/licenses/LICENSE-2.0
//!
//!	 Unless required by applicable law or agreed to in writing, software
//!	 distributed under the License is distributed on an "AS IS" BASIS,
//!	 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!	 See the License for the specific language governing permissions and
//!	 limitations under the License.
//!
//!*****************************************************************************
#include "HardwareDummyChip.hpp"
namespace openiolinklibrary
{
    IOLinkDummyChip::IOLinkDummyChip()
    {
    }

    IOLinkDummyChip::~IOLinkDummyChip()
    {
    }

    void IOLinkDummyChip::reset()
    {
    }
    void IOLinkDummyChip::sendData()
    {
    }
    void IOLinkDummyChip::getData()
    {
    }
    void IOLinkDummyChip::powerDown()
    {
        state = State::powerDown;
    }
    void IOLinkDummyChip::powerUp()
    {
        state = State::idle;
    }
    IOLinkDummyChip::State IOLinkDummyChip::getState() { return state; }

} // namespace openiolinklibrary