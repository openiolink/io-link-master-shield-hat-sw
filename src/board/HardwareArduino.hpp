
//!*****************************************************************************
//!  \file      HardwareArduino.h
//!*****************************************************************************
//!
//!  \brief		Generic Hardware Layer abstraction of a physical layer
//!
//!  \author    Markus Gafner (gnm7)
//!
//!  \date      2019-09-13
//!
//!*****************************************************************************
//!
//!	 Copyright 2019 Bern University of Applied Sciences and Balluff AG
//!
//!	 Licensed under the Apache License, Version 2.0 (the "License");
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
#ifndef HARDWARARDUINO_HPP_INCLUDED
#define HARDWARARDUINO_HPP_INCLUDED

//!**** Header-Files ************************************************************
#include "protocol/HardwareBase.hpp"
//!**** Macros ******************************************************************

//!**** Data types **************************************************************

//!**** Function prototypes *****************************************************

//!**** Data ********************************************************************

//!**** Implementation **********************************************************

class HardwareArduino :
	public HardwareBase
{
	

public:
	HardwareArduino();
	~HardwareArduino();

	virtual void begin();

	virtual void IO_Write(PinNames pinname, uint8_t state);
	virtual void IO_PinMode(PinNames pinname, PinMode mode); //pinMode

	virtual void Serial_Write(char const * buf);
	virtual void Serial_Write(int number);

	virtual void SPI_Write(uint8_t channel, uint8_t * data, uint8_t length);

	virtual void wait_for(uint32_t delay_ms);

private:
	uint8_t get_pinnumber(PinNames pinname);
};

#endif //HARDWARARDUINO_HPP_INCLUDED