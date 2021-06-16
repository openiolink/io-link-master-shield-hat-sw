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
    //**************************************************************************
    // OD Handler
    //**************************************************************************

    //!*************************************************************************
    //! \brief  Construct a new ODHandler object
    //!
    //! \param parentDL [in]        the DL object encapsulating this ODHandler
    //!
    //! \param messageHandler [in]  the associated Message Handler
    //!
    //!*************************************************************************
    DataLinkLayer::ODHandler::ODHandler(DataLinkLayer &parentDL,
                                        DataLinkLayer::MessageHandler &messageHandler)
        : mDL{parentDL}, mMessageHandler{messageHandler} // references
    {
    }

    //!*************************************************************************
    //! \brief  Destruct the ODHandler object
    //!
    //!*************************************************************************
    DataLinkLayer::ODHandler::~ODHandler()
    {
    }

    //!*************************************************************************
    //! \brief  Move the state machine one step forward (i.e. make a state
    //!         transition if neccessary).
    //!
    //! \note   IMPORTATNT: This function has to be called periodically!
    //!
    //!*************************************************************************
    void DataLinkLayer::ODHandler::stepFSM()
    {
        //TODO: call the step() function of sub-FSMs if present
    }

    //!*************************************************************************
    //! \brief  Service DL_ReadParam. Read a parameter value from the Device via
    //!         the page communication channel
    //!
    //! \param address [in] address of the requested Device parameter FIXME {0..31}
    //!
    //! \param value [out]  the read Device parameter
    //!
    //! \return error info, one of the following (see enum class ErrorCode):
    //!             NO_ERROR, NO_COMM, STATE_CONFLICT,
    //!             UNKNOWN_ERROR (illegall address value)
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.2
    //!
    //!*************************************************************************
    ErrorCode DataLinkLayer::ODHandler::readParam(const unsigned int address, int &value) const
    {
        return ErrorCode::UNKNOWN_ERROR; // unimplemented
    }

    //!*************************************************************************
    //! \brief  Service DL_WriteParam. Write a parameter value to the Device via
    //!         the page communication channel
    //!
    //! \param address [in] address of the requested Device parameter {16..31}
    //!
    //! \param value [in]   Device parameter value to be written
    //!
    //! \return error info, one of the following (see enum class ErrorCode):
    //!             NO_ERROR, NO_COMM, STATE_CONFLICT,
    //!             UNKNOWN_ERROR (illegall address value)
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.3
    //!
    //!*************************************************************************
    ErrorCode DataLinkLayer::ODHandler::writeParam(const unsigned int address, const int value)
    {
        return ErrorCode::UNKNOWN_ERROR; // unimplemented
    }

    //**************************************************************************
    // PD Handler
    //**************************************************************************

    //!*************************************************************************
    //! \brief  Construct a new PDHandler object
    //!
    //! \param parentDL [in]        the DL object encapsulating this ODHandler
    //!
    //! \param messageHandler [in]  the associated Message Handler
    //!
    //!*************************************************************************
    DataLinkLayer::PDHandler::PDHandler(DataLinkLayer &parentDL,
                                        DataLinkLayer::MessageHandler &messageHandler)
        : mDL{parentDL}, mMessageHandler{messageHandler} // references
    {
    }

    //!*************************************************************************
    //! \brief  Destruct the PDHandler object
    //!
    //!*************************************************************************
    DataLinkLayer::PDHandler::~PDHandler()
    {
    }

    //!*************************************************************************
    //! \brief  Move the state machine one step forward (i.e. make a state
    //!         transition if neccessary).
    //!
    //! \note   IMPORTATNT: This function has to be called periodically!
    //!
    //!*************************************************************************
    void DataLinkLayer::PDHandler::stepFSM()
    {
        //TODO: call the step() function of sub-FSMs if present
    }

    //**************************************************************************
    // Master DL Mode Handler
    //**************************************************************************

    //!*************************************************************************
    //! \brief  Construct a new MasterDLModeHandler object
    //!
    //! \param parentDL [in]    the DL object encapsulating this ODHandler
    //!
    //!*************************************************************************
    DataLinkLayer::MasterDLModeHandler::MasterDLModeHandler(DataLinkLayer &parentDL)
        : mDL{parentDL},                                                  // reference
          mMessageHandler{nullptr},                                       // pointer
          mRequestedMode{Mode::INACTIVE}, state{ModeHandlerState::Idle_0} // attributes
    {
        // NOTE: mMessageHandler must be initialized later with
    }

    //!*************************************************************************
    //! \brief  Destruct the MasterDLModeHandler object
    //!
    //!*************************************************************************
    DataLinkLayer::MasterDLModeHandler::~MasterDLModeHandler()
    {
    }

    //!*************************************************************************
    //! \brief  Move the state machine one step forward (i.e. make a state
    //!         transition if neccessary).
    //!
    //! \note   IMPORTATNT: This function has to be called periodically!
    //!
    //!*************************************************************************
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

    //**************************************************************************
    // Message Handler
    //**************************************************************************

    //!*************************************************************************
    //! \brief  Construct a new MessageHandler object
    //!
    //! \param physicalLayer [in]   the PL (IO-Link-Master port) below the encapsulating DL object
    //!
    //! \param modeHandler [in]     the associated Master DL-mode Handler
    //!
    //!*************************************************************************
    DataLinkLayer::MessageHandler::MessageHandler(IOLMasterPort &physicalLayer,
                                                  DataLinkLayer::MasterDLModeHandler &modeHandler)
        : mPL{physicalLayer}, mModeHandler{modeHandler}, // references
          mODHandler{nullptr}, mPDHandler{nullptr}       // pointers
    {
        // NOTE: mODHandler and mPDHandler must be initialized later via setXDHandler()
    }

    //!*************************************************************************
    //! \brief  Destruct the MessageHandler object
    //!
    //!*************************************************************************
    DataLinkLayer::MessageHandler::~MessageHandler()
    {
    }

    //!*************************************************************************
    //! \brief  Move the state machine one step forward (i.e. make a state
    //!         transition if neccessary).
    //!
    //! \note   IMPORTATNT: This function has to be called periodically!
    //!
    //!*************************************************************************
    void DataLinkLayer::MessageHandler::stepFSM()
    {
        //TODO: call the step() function of sub-FSMs if present
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

    //**************************************************************************
    // Data link Layer
    //**************************************************************************

    //!*************************************************************************
    //! \brief  Construct a new MessageHandler object
    //!
    //! \param PL [in]  the associated Physical Layer (IO-Link-Master port)
    //!
    //! \param AL [in]  the associated Aplication Layer
    //!
    //!*************************************************************************
    DataLinkLayer::DataLinkLayer(IOLMasterPort &PL, ApplicationLayer &AL)
        : mPL{PL}, mAL{AL},                                                      // references
          mPortHandler{nullptr},                                                 // pointer
          mModeHandler{*this}, mMessageHandler{PL, mModeHandler},                // attributes
          mPDHandler{*this, mMessageHandler}, mODHandler{*this, mMessageHandler} // attributes
    {
        // NOTE: mPortHandler must be initialized later with setPortHandler()

        // additional initialization of mModeHandler
        mModeHandler.setMessageHandler(&mMessageHandler);

        // additional initialization of mMessageHandler
        mMessageHandler.setODHandler(&mODHandler);
        mMessageHandler.setPDHandler(&mPDHandler);

        // mODHandler does not need additional initialization
        // mPDHandler does not need additional initialization
    }

    //!*************************************************************************
    //! \brief  Destruct the DataLinkLayer object
    //!
    //!*************************************************************************
    DataLinkLayer::~DataLinkLayer()
    {
        // revert the additional initialization (see constructor)
        mMessageHandler.setPDHandler(nullptr);
        mMessageHandler.setODHandler(nullptr);
        mModeHandler.setMessageHandler(nullptr);
    }

    //!*************************************************************************
    //! \brief  Move the state machine one step forward (i.e. make a state
    //!         transition if neccessary).
    //!
    //! \note   IMPORTATNT: This function has to be called periodically!
    //!
    //!*************************************************************************
    void DataLinkLayer::stepFSM()
    {
        // FIXME call order
        mODHandler.stepFSM();
        mPDHandler.stepFSM();
        mMessageHandler.stepFSM();
        mModeHandler.stepFSM();
    }

} // namespace openiolink
