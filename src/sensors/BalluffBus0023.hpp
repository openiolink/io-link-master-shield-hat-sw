
//!*****************************************************************************
//!  \file      BalluffBus0023.h
//!*****************************************************************************
//!
//!  \brief		Balluff BUS0023 distance sensor specific driver, not implemented yet
//!
//!  \author    Pascal Frei (freip2)
//!
//!  \date      2019-06-27
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
#ifndef BALLUFFBUS0023_H_INCLUDED
#define BALLUFFBUS0023_H_INCLUDED

//!**** Header-Files ***********************************************************
#include "protocol/IOLGenericDevice.hpp"

//!**** Macros *****************************************************************

//!**** Data types *************************************************************

//!**** Function prototypes ****************************************************

//!**** Data *******************************************************************

//!**** Implementation *********************************************************

class BalluffBus0023: public IOLGenericDevice {
public:
	BalluffBus0023();
	BalluffBus0023(IOLMasterPort * port);
    
	void begin();

	void end();

	uint16_t readDistance();

	void readSwitchState();

	void writeDetPoint1();

	void readDetPoint1();

	void writeRetDetPoint1();

	void readRetDetPoint1();

	void writeDetPoint2();

	void readDetPoint2();

	void writeRetDetPoint2();

	void readRetDetPoint2();

	void writeSwitchMode();

	void readSwitchMode();

	void writeFilter();

	void readFilter();

	void writeFilterStrength();

	void readFilterStrength();

	void writeForgroundSuppression();

	void readForegroundSuppression();

	void writeTeachIn();

	void readTeachIn();
};

#endif //BALLUFFBUS0023_H_INCLUDED
