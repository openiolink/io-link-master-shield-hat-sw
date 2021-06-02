//!*****************************************************************************
//! \file   DataLinkLayer.hpp
//! 
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//! 
//! \brief  Implementation of the Data Link Layer according to the IO-Link
//!         Interface and System Specification V1.1.3
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

#include "DataLinkLayer.hpp"
#include "IOLMasterPort.hpp"

namespace openiolink
{
    
DataLinkLayer::DataLinkLayer(const IOLMasterPort_thisIsPL & PL){
// Bouml preserved body begin 0002B5F7
// Bouml preserved body end 0002B5F7
}

//Move the state machine one step forward (i.e. make a state transition if neccessary).
//IMPORTATNT NOTE: This function has to be called periodically!
//TODO: call the step() function of all handler FSMs
void DataLinkLayer::stepFSM() {
// Bouml preserved body begin 00023A77
// Bouml preserved body end 00023A77
}

//Move the state machine one step forward (i.e. make a state transition if neccessary).
//IMPORTATNT NOTE: This function has to be called periodically!
//TODO: call the step() function of sub-FSMs if present
void DataLinkLayer::OD_Handler::stepFSM() {
// Bouml preserved body begin 00023C77
// Bouml preserved body end 00023C77
}

BaseType DataLinkLayer::OD_Handler::readParam(const unsigned int address, int & value) {
// Bouml preserved body begin 00023677
    return static_cast<BaseType>(1);  // unimplemented
// Bouml preserved body end 00023677
}

BaseType DataLinkLayer::OD_Handler::writeParam(const unsigned int address, const int value) {
// Bouml preserved body begin 000236F7
    return static_cast<BaseType>(1);  // unimplemented
// Bouml preserved body end 000236F7
}

//Move the state machine one step forward (i.e. make a state transition if neccessary).
//IMPORTATNT NOTE: This function has to be called periodically!
//TODO: call the step() function of sub-FSMs if present
void DataLinkLayer::PD_Handler::stepFSM() {
// Bouml preserved body begin 00023AF7
// Bouml preserved body end 00023AF7
}

BaseType DataLinkLayer::PD_Handler::PDOutputUpdate() {
// Bouml preserved body begin 00023177
// Bouml preserved body end 00023177
}

BaseType DataLinkLayer::PD_Handler::PDInputTransport() {
// Bouml preserved body begin 00023377
// Bouml preserved body end 00023377
}

//Move the state machine one step forward (i.e. make a state transition if neccessary).
//IMPORTATNT NOTE: This function has to be called periodically!
//TODO: call the step() function of sub-FSMs if present
void DataLinkLayer::MasterDLMode_Handler::stepFSM() {
// Bouml preserved body begin 00023BF7
// Bouml preserved body end 00023BF7
}

//Move the state machine one step forward (i.e. make a state transition if neccessary).
//IMPORTATNT NOTE: This function has to be called periodically!
//TODO: call the step() function of sub-FSMs if present
void DataLinkLayer::Message_Handler::stepFSM() {
// Bouml preserved body begin 00023B77
// Bouml preserved body end 00023B77
}


} // namespace openiolink
