#ifndef ARDUINO


	//!*****************************************************************************
	//!  \file       Demonstrator.ino
	//!*****************************************************************************
	//!
	//!  \brief	Software Demonstration for the bachelor thesis.
	//!
	//!  \author    Pascal Frei (freip2)
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
	//!*****************************************************************************

	//!**** Header-Files ***********************************************************
	#include "../include/Demonstrator_V1_0.h"

	#include "../include/HardwareRaspberry.h"

	//!**** Macros *****************************************************************

	//!**** Data types *************************************************************

	//!**** Function prototypes ****************************************************

	//!**** Data *******************************************************************

	//!**** Implementation *********************************************************

	int main(){
		HardwareRaspberry hardware;
		Demo_setup(&hardware);
		while(1){
			Demo_loop();
		}
		return 0;
	}

#endif