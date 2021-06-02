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

#ifndef DATALINKLAYER_HPP
#define DATALINKLAYER_HPP


#include "SystemManagement.hpp"

namespace openiolink { class IOLMasterPort_thisIsPL; } 
namespace openiolink { class GenericIOLDevice_thisIsAL; } 

namespace openiolink {

class DataLinkLayer {
    public:
    DataLinkLayer(const IOLMasterPort_thisIsPL & PL);
    ~DataLinkLayer();

    //read a parameter value from the Device via the page communication channel
    inline BaseType readParam(const unsigned int address, int & value);

    //write a parameter value to the Device via the page communication channel
    inline BaseType writeParam(const unsigned int address, const int value);

    //used by System Management to read a Device parameter value via the page communication channel.
    inline BaseType read(const unsigned int address, int & value);

    //used by System Management to write a Device parameter value to the Device via the page communication channel
    inline BaseType write(const unsigned int address, const int value);

    //The Master's application layer uses the DL_PDOutputUpdate service to update the output data (Process Data from Master to Device) on the data link layer. (Spec. 7.2.1.8)
    inline BaseType PDOutputUpdate(const int outputData);

    //indicate the end of a Process Data cycle to the application layer (Spec. 7.2.1.12)
    inline void PDCycle();

    //The DL_SetMode service is used by System Management to set up the data link layer's state machines and to send the characteristic values required for operation to the data link layer. (Spec. 7.2.1.13) // TODO Datentyp von Mode und valueList
    inline BaseType setMode(const int mode, const int valueList);

    //report to System Management that a certain operating status has been reached. (Spec 7.2.1.14)
    //TODO: Wie funktionieren die Aufrufe bei den Services, wo der DL Initiator ist?
    inline void indMode();

    //Move the state machine one step forward (i.e. make a state transition if neccessary).
    //IMPORTATNT NOTE: This function has to be called periodically!
    //TODO: call the step() function of all handler FSMs
    void stepFSM();

    inline void registerAL(const GenericIOLDevice_thisIsAL & ApplicationLayer);

    inline void registerPortHandler(const SystemManagement::PortHandler & NewPortHandler);

    class OD_Handler {
        public:
        //Move the state machine one step forward (i.e. make a state transition if neccessary).
        //IMPORTATNT NOTE: This function has to be called periodically!
        //TODO: call the step() function of sub-FSMs if present
        void stepFSM();

        BaseType readParam(const unsigned int address, int & value);

        BaseType writeParam(const unsigned int address, const int value);

        void PDCycle();

    };
    
    class PD_Handler {
        public:
        //Move the state machine one step forward (i.e. make a state transition if neccessary).
        //IMPORTATNT NOTE: This function has to be called periodically!
        //TODO: call the step() function of sub-FSMs if present
        void stepFSM();

        BaseType PDOutputUpdate();

        BaseType PDInputTransport();

    };
    
    class MasterDLMode_Handler {
        public:
        //Move the state machine one step forward (i.e. make a state transition if neccessary).
        //IMPORTATNT NOTE: This function has to be called periodically!
        //TODO: call the step() function of sub-FSMs if present
        void stepFSM();

        BaseType setMode(const int mode, const int valueList);

        void indMode();


        private:
        //States of the Master DL-mode handler state machine
        //members: Idle_0, EstablishComm_1, Startup_2, Preoperate_3, Operate_4, ([SM:] WURQ_5, ComRequestCOM3_6, ComRequestCOM2_7, ComRequestCOM1_8, Retry_9)
        //        
        enum class MHState {
        };

        MHState state;

    };
    
    //Sollte alle M Sequence Typen unterstuetzen
    class Message_Handler {
        public:
        //Move the state machine one step forward (i.e. make a state transition if neccessary).
        //IMPORTATNT NOTE: This function has to be called periodically!
        //TODO: call the step() function of sub-FSMs if present
        void stepFSM();

    };
    

    private:
    OD_Handler ODHandler;

    PD_Handler PDHandler;

    MasterDLMode_Handler ModeHandler;

    MasterDLMode_Handler MessageHandler;

    IOLMasterPort_thisIsPL * mPL;

    //The data link layer on the Master uses the DL_PDInputTransport service to transfer the content of input data (Process Data from Device to Master) to the application layer.
    inline BaseType PDInputTransport(int & inputData);

};
//read a parameter value from the Device via the page communication channel
inline BaseType DataLinkLayer::readParam(const unsigned int address, int & value) {
// Bouml preserved body begin 000234F7
  return ODHandler.readParam(address, value);
// Bouml preserved body end 000234F7
}

//write a parameter value to the Device via the page communication channel
inline BaseType DataLinkLayer::writeParam(const unsigned int address, const int value) {
// Bouml preserved body begin 00023577
// Bouml preserved body end 00023577
}

//used by System Management to read a Device parameter value via the page communication channel.
inline BaseType DataLinkLayer::read(const unsigned int address, int & value) {
// Bouml preserved body begin 000231F7
  return ODHandler.readParam(address, value);
// Bouml preserved body end 000231F7
}

//used by System Management to write a Device parameter value to the Device via the page communication channel
inline BaseType DataLinkLayer::write(const unsigned int address, const int value) {
// Bouml preserved body begin 00023277
// Bouml preserved body end 00023277
}

//The Master's application layer uses the DL_PDOutputUpdate service to update the output data (Process Data from Master to Device) on the data link layer. (Spec. 7.2.1.8)
inline BaseType DataLinkLayer::PDOutputUpdate(const int outputData) {
// Bouml preserved body begin 000233F7
  return PDHandler.PDOutputUpdate();
// Bouml preserved body end 000233F7
}

//indicate the end of a Process Data cycle to the application layer (Spec. 7.2.1.12)
inline void DataLinkLayer::PDCycle() {
// Bouml preserved body begin 000235F7
// Bouml preserved body end 000235F7
}

//The DL_SetMode service is used by System Management to set up the data link layer's state machines and to send the characteristic values required for operation to the data link layer. (Spec. 7.2.1.13) // TODO Datentyp von Mode und valueList
inline BaseType DataLinkLayer::setMode(const int mode, const int valueList) {
// Bouml preserved body begin 000232F7
    return ModeHandler.setMode(mode, valueList);
// Bouml preserved body end 000232F7
}

//report to System Management that a certain operating status has been reached. (Spec 7.2.1.14)
//TODO: Wie funktionieren die Aufrufe bei den Services, wo der DL Initiator ist?
inline void DataLinkLayer::indMode() {
// Bouml preserved body begin 00023777
    ModeHandler.indMode();
// Bouml preserved body end 00023777
}

inline void DataLinkLayer::registerAL(const GenericIOLDevice_thisIsAL & ApplicationLayer) {
// Bouml preserved body begin 00027677
// Bouml preserved body end 00027677
}

inline void DataLinkLayer::registerPortHandler(const SystemManagement::PortHandler & NewPortHandler) {
// Bouml preserved body begin 0002B577
// Bouml preserved body end 0002B577
}

//The data link layer on the Master uses the DL_PDInputTransport service to transfer the content of input data (Process Data from Device to Master) to the application layer.
inline BaseType DataLinkLayer::PDInputTransport(int & inputData) {
// Bouml preserved body begin 000230F7
// Bouml preserved body end 000230F7
}


} // namespace openiolink
#endif
