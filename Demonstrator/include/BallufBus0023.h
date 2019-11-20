
//!*****************************************************************************
//!  \file       BallufBus0023.h
//!*****************************************************************************
//!
//!  \brief		Balluf BUS0023 distance sensor specific driver, not implemented yet
//!
//!  \author     Pascal Frei (freip2)
//!
//!  \date       2019-06-27
//!
//!*****************************************************************************
//!	Copyright (C) 2019, Pascal Frei
//!
//!	This program is free software: you can redistribute it and/or modify
//!	it under the terms of the GNU General Public License as published by
//!	the Free Software Foundation, either version 3 of the License, or
//!	any later version.
//!
//!	but WITHOUT ANY WARRANTY; without even the implied warranty of
//!	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//!	GNU General Public License for more details.
//!
//!	You should have received a copy of the GNU General Public License
//!	along with this program.  If not, see <http://www.gnu.org/licenses/>.
//!
//!******************************************************************************
#ifndef BALLUFBUS0023_H_INCLUDED
#define BALLUFBUS0023_H_INCLUDED

//!**** Header-Files ***********************************************************
#include "IOLGenericDevice.h"

//!**** Macros *****************************************************************

//!**** Data types *************************************************************

//!**** Function prototypes ****************************************************

//!**** Data *******************************************************************

//!**** Implementation *********************************************************

class BallufBus0023: public IOLGenericDevice {
public:
	BallufBus0023();
	BallufBus0023(IOLMasterPort * port);
    
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

#endif //BALLUFBUS0023_H_INCLUDED
