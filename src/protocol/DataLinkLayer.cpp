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
#include "ErrorCode.hpp"

namespace openiolink
{
    //Move the state machine one step forward (i.e. make a state transition if neccessary).
    //IMPORTATNT NOTE: This function has to be called periodically!
    //TODO: call the step() function of sub-FSMs if present
    void
    DataLinkLayer::OD_Handler::stepFSM()
    {
    }

    ErrorCode DataLinkLayer::OD_Handler::readParam(const unsigned int address, int &value)
    {
        return ErrorCode::UNKNOWN_ERROR; // unimplemented
    }

    ErrorCode DataLinkLayer::OD_Handler::writeParam(const unsigned int address, const int value)
    {
        return ErrorCode::UNKNOWN_ERROR; // unimplemented
    }

    //Move the state machine one step forward (i.e. make a state transition if neccessary).
    //IMPORTATNT NOTE: This function has to be called periodically!
    //TODO: call the step() function of sub-FSMs if present
    void DataLinkLayer::PD_Handler::stepFSM()
    {
    }

    void DataLinkLayer::MasterDLMode_Handler MasterDLMode_Handler() : mRequestedMode{Mode::INACTIVE}, state{MHState::Idle_0}
    {
    }

    void DataLinkLayer::MasterDLMode_Handler ~MasterDLMode_Handler()
    {
    }
    //Move the state machine one step forward (i.e. make a state transition if neccessary).
    //IMPORTATNT NOTE: This function has to be called periodically!
    void DataLinkLayer::MasterDLMode_Handler::stepFSM()
    {
        switch (state)
        {
        case MHState::Idle_0:
            if (mRequestedMode == Mode::STARTUP)
            { // T1
                state = MHState::EstablishComm_1;
            }
            break;

        case MHState::EstablishComm_1:
            mPL.wakeupRequest();
            // TODO: when done:
            state = MHState::Startup_2; // replaces T2, T3 and T4
            // TODO: on error:
            state = MHState::Idle_0; // TOOD: T5
            break;

        case MHState::Startup_2:
            if (mRequestedMode == Mode::PREOPERATE)
            { // TODO: T6
                state = MHState::Preoperate_3;
            }
            else if (mRequestedMode == Mode::OPERATE)
            { // TODO: T11
                state = MHState::Operate_4;
            }
            break;

        case MHState::Preoperate_3:
            if (mRequestedMode == Mode::STARTUP)
            { // TODO: T7
                state = MHState::Startup_2;
            }
            else if (mRequestedMode == Mode::INACTIVE /*TODO || MHInfo_COMLOST*/)
            { // TODO: T8, TODO: T9
                state = MHState::Idle_0;
            }
            else if (mRequestedMode == Mode::OPERARTE)
            { // TODO: T10
                state = MHState::Operate_4;
            }
            break;

        case MHState::Operate_4:
            if (mRequestedMode == Mode::STARTUP)
            { // TODO: T12
                state = MHState::Startup_2;
            }
            else if (mRequestedMode == Mode::INACTIVE /*TODO || MHInfo_COMLOST*/)
            { // TODO: T13, TODO: T14
                state = MHState::Idle_0;
            }
            break;

        case MHState::WURQ_5:
        case MHState::ComRequestCOM3_6:
        case MHState::ComRequestCOM2_7:
        case MHState::ComRequestCOM1_8:
        case MHState::Retry_9:
            state = MHState::EstablishComm_1; // "Submachine 1 "WakeUp"" not implemented (not neccessary with MAX14819 transceiver)
            break;
        }
    }

    //Move the state machine one step forward (i.e. make a state transition if neccessary).
    //IMPORTATNT NOTE: This function has to be called periodically!
    //TODO: call the step() function of sub-FSMs if present
    void DataLinkLayer::Message_Handler::stepFSM()
    {
    }

    //Specification 7.2.2.6 MHInfo
    void DataLinkLayer::Message_Handler::mhInfo(MHInfo &mhInfo)
    {
    }

    //Set up the On-request Data for the next message to be sent. In 1266 turn, the confirmation of the service contains the data from the receiver.
    //\note "data" and "length" are only valid, when ErrorCode::NO_ERROR is returned!
    ErrorCode DataLinkLayer::Message_Handler::OD(const RWDirection &rwDirection, const ComChannel &comChannel, const int addressCtrl, uint8_t *data, int &length)
    {
    }

    //Setup the Process Data to be sent through the process communication channel. The confirmation of the service contains the data from the receiver.
    ErrorCode DataLinkLayer::Message_Handler::PD(const uint8_t *pdOut, const int pdOutAddress, const int pdOutLength, uint8_t *pdIn, int &pdInAddress, int &pdInLength)
    {
    }

    DataLinkLayer::DataLinkLayer(const IOLMasterPort &PL) : mPL{PL}
    {
    }

    DataLinkLayer::~DataLinkLayer()
    {
    }

    //Move the state machine one step forward (i.e. make a state transition if neccessary).
    //IMPORTATNT NOTE: This function has to be called periodically!
    //TODO: call the step() function of all handler FSMs
    void DataLinkLayer::stepFSM()
    {
        ODHandler.stepFSM();
        PDHandler.stepFSM();
        MessageHandler.stepFSM();
        ModeHandler.stepFSM();
    }

    //DL_ISDUTransport (Specification 7.2.1.6), not implemented, TODO add parameters
    //TODO call mOD_Handler.isduTransport()
    ErrorCode DataLinkLayer::isduTransport()
    {
    }

} // namespace openiolink
