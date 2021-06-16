//!*****************************************************************************
//! \file   DataLinkLayer.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  Implementation of the Data Link Layer according to the IO-Link
//!         Interface and System Specification V1.1.3 chapter 7
//!
//! \date   2021-06-15
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
#include "global_typedef.hpp" // type OctetString

namespace openiolink
{
    /** OD Handler */
    DataLinkLayer::ODHandler::ODHandler(const DataLinkLayer &parentDL, const DataLinkLayer::MessageHandler &messageHandler)
    {
    }

    DataLinkLayer::ODHandler::~ODHandler()
    {
    }

    //Move the state machine one step forward (i.e. make a state transition if neccessary).
    //IMPORTATNT NOTE: This function has to be called periodically!
    //TODO: call the step() function of sub-FSMs if present
    void
    DataLinkLayer::ODHandler::stepFSM()
    {
    }

    ErrorCode DataLinkLayer::ODHandler::readParam(const unsigned int address, int &value) const
    {
        return ErrorCode::UNKNOWN_ERROR; // unimplemented
    }

    ErrorCode DataLinkLayer::ODHandler::writeParam(const unsigned int address, const int value)
    {
        return ErrorCode::UNKNOWN_ERROR; // unimplemented
    }

    /** PD Handler */
    DataLinkLayer::PDHandler::PDHandler(const DataLinkLayer &parentDL, const DataLinkLayer::MessageHandler &messageHandler)
    {
    }

    DataLinkLayer::PDHandler::~PDHandler()
    {
    }

    //Move the state machine one step forward (i.e. make a state transition if neccessary).
    //IMPORTATNT NOTE: This function has to be called periodically!
    //TODO: call the step() function of sub-FSMs if present
    void DataLinkLayer::PDHandler::stepFSM()
    {
    }

    /** Master DL Mode Handler */
    DataLinkLayer::MasterDLModeHandler::MasterDLModeHandler(const DataLinkLayer &parentDL) : mRequestedMode{Mode::INACTIVE}, state{ModeHandlerState::Idle_0}
    // TODO complete and sort initializer list
    {
    }

    DataLinkLayer::MasterDLModeHandler::~MasterDLModeHandler()
    {
    }
    //Move the state machine one step forward (i.e. make a state transition if neccessary).
    //IMPORTATNT NOTE: This function has to be called periodically!
    void DataLinkLayer::MasterDLModeHandler::stepFSM()
    {
        switch (state)
        {
        case ModeHandlerState::Idle_0:
            if (mRequestedMode == Mode::STARTUP)
            { // T1
                state = ModeHandlerState::EstablishComm_1;
            }
            break;

        case ModeHandlerState::EstablishComm_1:
            // FIXME ERROR "a nonstatic member reference must be relative to a specific object"
            mPL.wakeupRequest();
            // TODO: when done:
            state = ModeHandlerState::Startup_2; // replaces T2, T3 and T4
            // TODO: on error:
            state = ModeHandlerState::Idle_0; // TOOD: T5
            break;

        case ModeHandlerState::Startup_2:
            if (mRequestedMode == Mode::PREOPERATE)
            { // TODO: T6
                state = ModeHandlerState::Preoperate_3;
            }
            else if (mRequestedMode == Mode::OPERATE)
            { // TODO: T11
                state = ModeHandlerState::Operate_4;
            }
            break;

        case ModeHandlerState::Preoperate_3:
            if (mRequestedMode == Mode::STARTUP)
            { // TODO: T7
                state = ModeHandlerState::Startup_2;
            }
            else if (mRequestedMode == Mode::INACTIVE /*TODO || MHInfo_COMLOST*/)
            { // TODO: T8, TODO: T9
                state = ModeHandlerState::Idle_0;
            }
            else if (mRequestedMode == Mode::OPERATE)
            { // TODO: T10
                state = ModeHandlerState::Operate_4;
            }
            break;

        case ModeHandlerState::Operate_4:
            if (mRequestedMode == Mode::STARTUP)
            { // TODO: T12
                state = ModeHandlerState::Startup_2;
            }
            else if (mRequestedMode == Mode::INACTIVE /*TODO || MHInfo_COMLOST*/)
            { // TODO: T13, TODO: T14
                state = ModeHandlerState::Idle_0;
            }
            break;

        case ModeHandlerState::WURQ_5:
        case ModeHandlerState::ComRequestCOM3_6:
        case ModeHandlerState::ComRequestCOM2_7:
        case ModeHandlerState::ComRequestCOM1_8:
        case ModeHandlerState::Retry_9:
            state = ModeHandlerState::EstablishComm_1; // "Submachine 1 "WakeUp"" not implemented (not neccessary with MAX14819 transceiver)
            break;
        }
    }

    /** Message Handler */
    DataLinkLayer::MessageHandler::MessageHandler(const DataLinkLayer &parentDL, const IOLMasterPort &physicalLayer, const DataLinkLayer::MasterDLModeHandler &modeHandler)
    {
    }

    DataLinkLayer::MessageHandler::~MessageHandler()
    {
    }

    //Move the state machine one step forward (i.e. make a state transition if neccessary).
    //IMPORTATNT NOTE: This function has to be called periodically!
    //TODO: call the step() function of sub-FSMs if present
    void DataLinkLayer::MessageHandler::stepFSM()
    {
    }

    //Specification 7.2.2.6 MHInfo
    void DataLinkLayer::MessageHandler::mhInfo(MHInfo &mhInfo)
    {
    }

    //Set up the On-request Data for the next message to be sent. In 1266 turn, the confirmation of the service contains the data from the receiver.
    //\note "data" and "length" are only valid, when ErrorCode::NO_ERROR is returned!
    ErrorCode DataLinkLayer::MessageHandler::OD(const RWDirection &rwDirection, const ComChannel &comChannel, const int addressCtrl, uint8_t *data, int &length)
    {
    }

    //Setup the Process Data to be sent through the process communication channel. The confirmation of the service contains the data from the receiver.
    ErrorCode DataLinkLayer::MessageHandler::PD(const uint8_t *pdOut, const int pdOutAddress, const int pdOutLength, uint8_t *pdIn, int &pdInAddress, int &pdInLength)
    {
    }

    void DataLinkLayer::MessageHandler::setODHandler(DataLinkLayer::ODHandler *value)
    {
        mODHandler = value;
    }

    void DataLinkLayer::MessageHandler::setPDHandler(DataLinkLayer::PDHandler *value)
    {
        mPDHandler = value;
    }

    /** Data link Layer */
    DataLinkLayer::DataLinkLayer(const IOLMasterPort &PL, const ApplicationLayer &AL) : mPL{PL}, mAL{AL}
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
        mODHandler.stepFSM();
        mPDHandler.stepFSM();
        mMessageHandler.stepFSM();
        mModeHandler.stepFSM();
    }

} // namespace openiolink
