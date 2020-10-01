#ifndef ARDUINO

	//!*****************************************************************************
	//!  \file      main.cpp
	//!*****************************************************************************
	//!
	//!  \brief		Software Demonstration for the bachelor thesis.
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

	//!**** Header-Files ***********************************************************
	#include "Demonstrator_V1_0.hpp"

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