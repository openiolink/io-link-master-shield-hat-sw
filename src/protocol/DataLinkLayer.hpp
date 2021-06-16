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

#ifndef DATALINKLAYER_HPP
#define DATALINKLAYER_HPP

#include <iostream>
#include "SystemManagement.hpp"
#include "ErrorCode.hpp"
#include "global_typedef.hpp"   // type OctetString
#include "ApplicationLayer.hpp" // class ApplicationLayer

namespace openiolink
{
    class IOLMasterPort;
}

namespace openiolink
{
    //!*************************************************************************
    //! \brief  This class represents the data link layer (DL) of one port of
    //!         the IO-Link Master.
    //!
    //! "The data link layers of SDCI [aka IO-Link] are concerned with the
    //! delivery of messages between a Master and a Device across the physical
    //! link. It uses several M-sequence ("message sequence") types for
    //! different data categories. A set of DL-services is available to the
    //! application layer (AL) for the exchange of Process Data (PD) and
    //! On-request Data (OD). Another set of DL-services is available to System
    //! Management (SM) for the retrieval of Device identification parameters
    //! and the setting of state machines within the DL."
    //! (IO-Link Specification V1.1.3 p. 53)
    //!
    //!*************************************************************************
    class DataLinkLayer
    {
    public:
        //!*********************************************************************
        //! \brief  indicates whether the data link layer is in a state
        //!         permitting data to be transferred to the communication
        //!         partner.
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.8
        //!
        //!*********************************************************************
        enum class PDTransportStatus
        {
            YES, // data transmission permitted
            NO   // data transmission not permitted
        };

        //!*********************************************************************
        //! \brief  all M-Sequence types
        //!
        //! \note   see IO-Link Specification V1.1.3 fig. 39
        //!
        //!*********************************************************************
        enum class MSequenceType
        {
            TYPE_0,
            TYPE_1_1,
            TYPE_1_2,
            TYPE_1_V,
            TYPE_2_1,
            TYPE_2_2,
            TYPE_2_3,
            TYPE_2_4,
            TYPE_2_5,
            TYPE_2_V
        };

        //!*********************************************************************
        //! \brief  relevant operating parameters for the Master's DL (used @
        //!         DL_SetMode)
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.13
        //!
        //!*********************************************************************
        struct OperatingParam
        {
            int mSequenceTime;
            MSequenceType mSequenceType;
            int PDInputLength;
            int PDOutputLength;
            int OnReqDataLengthPerMessage;
        };

        //!*********************************************************************
        //! \brief  requestable modes of the Master's DL
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.13
        //!
        //!*********************************************************************
        enum class Mode
        {
            INACTIVE,   // handler shall change to the INACTIVE state
            STARTUP,    // handler shall change to STARTUP state
            PREOPERATE, // handler shall change to PREOPERATE state
            OPERATE     // handler shall change to OPERATE state
        };

        //!*********************************************************************
        //! \brief  status of the Master's DL
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.14
        //!
        //!*********************************************************************
        enum class RealMode
        {
            INACTIVE,   // handler changed to the INACTIVE state
            COM1,       // COM1 mode established
            COM2,       // COM2 mode established
            COM3,       // COM3 mode established
            COMLOST,    // Lost communication
            ESTABCOM,   // Handler changed to the EstablishCom state
            STARTUP,    // handler changed to STARTUP state
            PREOPERATE, // handler changed to PREOPERATE state
            OPERATE     // handler changed to OPERATE state
        };

        //!*********************************************************************
        //! \brief  qualifier status of the Process Data (PD)
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.18
        //!
        //!*********************************************************************
        enum class ControlCode
        {
            VALID,       // Input Process Data valid; see 7.2.2.5, 8.2.2.12
            INVALID,     // Input Process Data invalid
            PDOUTVALID,  // Output Process Data valid; see 7.3.7.1
            PDOUTINVALID // Output Process Data invalid or missing
        };

        //!*********************************************************************
        //! \brief  validity of input (Device -> Master) PD
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.5
        //!
        //!*********************************************************************
        enum class PDStatus
        {
            VALID,  // Input Process Data valid based on PD status flag (see A.1.5); see 7.2.1.18
            INVALID // Input Process Data invalid
        };

        //!*********************************************************************
        //! \brief  exceptions within the messge handler (Message Handler Info)
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.6
        //!
        //!*********************************************************************
        enum class MHInfo
        {
            COMLOST,             // lost communication
            ILLEGAL_MESSAGETYPE, // unexpected M-sequence type detected
            CHECKSUM_MISMATCH    // Checksum error detected
        };

        //!*********************************************************************
        //! \brief  exceptions within the messge handler (Message Handler Info)
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.6
        //!
        //!*********************************************************************
        enum class MHInfo
        {
            COMLOST,             // lost communication
            ILLEGAL_MESSAGETYPE, // unexpected M-sequence type detected
            CHECKSUM_MISMATCH    // Checksum error detected
        };

        //!*********************************************************************
        //! forward declaration of the handler-classes within the DL
        //!
        //!*********************************************************************
        class MasterDLModeHandler;
        class MessageHandler;
        class PDHandler;
        class ODHandler;
        //class ISDUHandler; // not implemented yet
        //class CommandHandler; // not implemented yet
        //class EventHandler; // not implemented yet

        //!*********************************************************************
        //! \brief  On-request Data (OD) handler
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.3.5
        //!
        //!*********************************************************************
        class ODHandler
        {
        public:
            ODHandler(DataLinkLayer &parentDL, MessageHandler &messageHandler);
            ~ODHandler();
            void stepFSM();
            ErrorCode readParam(const unsigned int address, int &value) const;
            ErrorCode writeParam(const unsigned int address, const int value);
            inline ErrorCode isduTransport();
            inline ErrorCode isduAbort();
            inline void control(ControlCode &controlCode);
            inline void event(int &argument) const;
            inline void eventConf() const;
            inline void handleOD_cnf();
            inline void handleODTrig();
            inline void handlePDInStatus();
            inline void handleEventFlag();

        private:
            DataLinkLayer *mDL;
            MessageHandler *mMessageHandler; // lower layer: DL-A
            inline void control() const;
            inline void event() const;
        };

        //!*********************************************************************
        //! \brief  Process Data (PD) handler
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.3.4
        //!
        //!*********************************************************************
        class PDHandler
        {
        public:
            PDHandler(DataLinkLayer &parentDL, MessageHandler &messageHandler);
            ~PDHandler();
            void stepFSM();
            inline ErrorCode pdOutputUpdate(const OctetString &outputData, PDTransportStatus &transportStatus);
            inline void pdInputTransport(OctetString &inputData) const;
            inline void handlePD_cnf();
            inline void handlePDTrig();

        private:
            DataLinkLayer *mDL;
            MessageHandler *mMessageHandler; // lower layer DL-A
            inline void pdInputTransport() const;
            inline void pdCycle() const;
        };

        //!*********************************************************************
        //! \brief  Master's DL mode handler
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.3.2
        //!
        //!*********************************************************************
        class MasterDLModeHandler
        {
        public:
            MasterDLModeHandler(DataLinkLayer &parentDL);
            ~MasterDLModeHandler();
            void stepFSM();
            inline ErrorCode setMode(const Mode mode, const OperatingParam &valueList);
            inline void mode(RealMode &realMode);
            inline void handleMHInfo();

        private:
            // States of the Master DL-mode handler state machine
            enum class ModeHandlerState
            {
                Idle_0,
                EstablishComm_1,
                Startup_2,
                Preoperate_3,
                Operate_4,
                WURQ_5,
                ComRequestCOM3_6,
                ComRequestCOM2_7,
                ComRequestCOM1_8,
                Retry_9
            };

            DataLinkLayer *mDL;
            Mode mRequestedMode;    // the DL is requested to go to this mode
            ModeHandlerState state; // the current state of the DL
            inline void mode() const;
        };

        //!*********************************************************************
        //! \brief  Message handler
        //!
        //! \note   see IO-Link Specification V1.1.3 par. 7.3.3
        //!
        //!*********************************************************************
        // TODO Sollte alle M Sequence Typen unterstuetzen
        class MessageHandler
        {
        public:
            MessageHandler(DataLinkLayer &parentDL, IOLMasterPort &physicalLayer, MasterDLModeHandler &modeHandler);
            ~MessageHandler();
            void stepFSM();
            void mhInfo(MHInfo &mhInfo);
            ErrorCode OD(const RWDirection &rwDirection, const ComChannel &comChannel, const int addressCtrl, uint8_t *data, int &length);
            inline void odTrig(int &dataLength) const;
            inline void pdInStatus(PDStatus &status);
            inline void eventFlag(bool &flag);
            ErrorCode PD(const uint8_t *pdOut, const int pdOutAddress, const int pdOutLength, uint8_t *pdIn, int &pdInAddress, int &pdInLength);
            inline void pdTrig(int &dataLength) const;
            inline void handlePLTransfer_ind();
            void setODHandler(ODHandler *value);
            void setPDHandler(PDHandler *value);

        private:
            IOLMasterPort *mPL;
            MasterDLModeHandler *mModeHandler; // neccessary to provide the service MHInfo
            ODHandler *mODHandler;             // upper layer: DL-B (must be known to be able to provide the services OD.cnf, ODTrig, PDInStatus and EventFlag)
            PDHandler *mPDHandler;             // upper layer DL-B (must be known in order to be able to provide the services PD.cnf and PDTrig)
            inline void od_cnf() const;
            inline void odTrig() const;
            inline void pdInStatus() const;
            inline void eventFlag() const;
            inline void pd_cnf() const;
            inline void pdTrig() const;
        };

        //**********************************************************************
        // Member declaration of class DataLinkLayer itself
        //**********************************************************************

        DataLinkLayer(IOLMasterPort &PL, ApplicationLayer &AL);
        ~DataLinkLayer();
        void stepFSM();
        inline void mode(RealMode &realMode);
        inline ErrorCode read(const unsigned int address, int *value) const;
        inline ErrorCode write(const unsigned int address, const int value);
        inline ErrorCode setMode(const Mode mode, const OperatingParam &valueList);
        inline ErrorCode readParam(const unsigned int address, int *value) const;
        inline ErrorCode writeParam(const unsigned int address, const int value);
        inline ErrorCode isduTransport();
        inline ErrorCode isduAbort();
        inline void control(ControlCode &controlCode);
        inline void event(int &argument) const;
        inline void eventConf() const;
        inline ErrorCode pdOutputUpdate(const OctetString &outputData, PDTransportStatus &transportStatus);
        inline void pdInputTransport(OctetString &inputData) const;
        inline void pdCycle() const;
        inline void setPortHandler(const SystemManagement::PortHandler &portHandler);

    private:
        /*const*/ IOLMasterPort &mPL;
        /*const*/ ApplicationLayer &mAL;             // cannot be const because access to non-const member functions is needed
        SystemManagement::PortHandler *mPortHandler; // PortHandler (SM) is receiver of the service DL_Mode
        MasterDLModeHandler mModeHandler;
        MessageHandler mMessageHandler;
        PDHandler mPDHandler;
        ODHandler mODHandler;
        inline void mode() const;
        inline void control() const;
        inline void event() const;
        inline void pdInputTransport() const;
    }; // class DataLinkLayer

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************
    //  from class ODHandler
    //**************************************************************************

    //!*************************************************************************
    //! \brief  Service DL_ISDUTransport
    //!
    //! \return always ISDU_NOT_SUPPORTED (not implemented yet)
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.6
    //!         This method is not implemented yet.
    //!
    //! \todo   add parameters and implement according to the Specification
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::ODHandler::isduTransport()
    {
        return ErrorCode::ISDU_NOT_SUPPORTED;
    }

    //!*************************************************************************
    //! \brief  Service DL_ISDUAbort
    //!
    //! \return always ISDU_NOT_SUPPORTED (not implemented yet)
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.7
    //!         This method is not implemented yet.
    //!
    //! \todo   add parameters and implement according to the Specification
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::ODHandler::isduAbort()
    {
        return ErrorCode::ISDU_NOT_SUPPORTED;
    }

    //!*************************************************************************
    //! \brief  Service DL_Control
    //!
    //! "The Master uses the DL_Control service to convey control information
    //! via the MasterCommand mechanism to the corresponding Device application
    //! and to get control information via the PD status flag mechanism (see
    //! A.1.5) and the PDInStatus service (see 7.2.2.5)."
    //!
    //! \param controlCode [in, out]    indicates the qualifier status of the PD
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.18
    //!         This method is not implemented yet.
    //!
    //! \todo   implement according to the Specification
    //!
    //!*************************************************************************
    inline void DataLinkLayer::ODHandler::control(DataLinkLayer::ControlCode &controlCode)
    {
    }

    //!*************************************************************************
    //! \brief  Service DL_Event
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.15
    //!         This method is not implemented yet.
    //!
    //! \todo   add parameters and implement according to the Specification
    //!
    //!*************************************************************************
    inline void DataLinkLayer::ODHandler::event(int &argument) const
    {
    }

    //!*************************************************************************
    //! \brief  Service DL_EventConf, confirms the transmitted Events via the
    //!         Event handler.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.16
    //!         This method is not implemented yet.
    //!
    //! \todo   add parameters and implement according to the Specification
    //!
    //!*************************************************************************
    inline void DataLinkLayer::ODHandler::eventConf() const
    {
    }

    //!*************************************************************************
    //! \brief  This method receives the On-request Data from the device (or
    //!         more formally: it is the "receiver" of confirmation of the
    //!         Service "OD" from the Message handler.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.2
    //!
    //! \todo   TODO add parameters and implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::ODHandler::handleOD_cnf()
    {
    }

    //!*************************************************************************
    //! \brief  This method is the "receiver" of the ODTrig Service from the
    //!         Message handler, which herewith requests the OD Handler to
    //!         provide the OD for the next Master message.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.7
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::ODHandler::handleODTrig()
    {
        int requestedODBytes; // TODO use this value
        mMessageHandler->odTrig(requestedODBytes);
    }

    //!*************************************************************************
    //! \brief  This method is the "receiver" of the PDInStatus Service from the
    //!         Message handler.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.5
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::ODHandler::handlePDInStatus()
    {
    }

    //!*************************************************************************
    //! \brief  This method is the "receiver" of the EventFlag Service from the
    //!         Message handler.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.5
    //!         This method is not implemented yet.
    //!
    //! \todo   implement according to the Specification
    //!
    //!*************************************************************************
    inline void DataLinkLayer::ODHandler::handleEventFlag()
    {
    }

    //!*************************************************************************
    //! \brief  Initiates the Service DL_Control in the case it is used in the
    //!         direction from the DL to the AL.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.18
    //!
    //!*************************************************************************
    inline void DataLinkLayer::ODHandler::control() const
    {
        // Because the OD handler is encapsulated inside the DL, it has to ask
        // the DL to forward this message.
        mDL->control();
    }

    //!*************************************************************************
    //! \brief  Initiates the Service DL_Event.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.15
    //!
    //! \note   This has no effect yet, because events are not implemented yet.
    //!
    //!*************************************************************************
    inline void DataLinkLayer::ODHandler::event() const
    {
        // Because the OD handler is encapsulated inside the DL, it has to ask
        // the DL to forward this message.
        mDL->event();
    }

    //**************************************************************************
    //  from class PDHandler
    //**************************************************************************

    //!*************************************************************************
    //! \brief  Service DL_PDOutputUpdate. Updates the output data (Process Data
    //!         from Master to Device) on the data link layer.
    //!
    //! \param outputData [in]          Process Data provided by the AL
    //!
    //! \param transportStatus [out]    indicates wheter DL permits data transfer
    //!
    //! \return error info, one of the following (see enum class ErrorCode):
    //!             NO_ERROR, NO_COMM, STATE_CONFLICT
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.8
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::PDHandler::pdOutputUpdate(const OctetString &outputData, PDTransportStatus &transportStatus)
    {
        // TODO implement
        transportStatus = PDTransportStatus::NO;
        return ErrorCode::UNKNOWN_ERROR;
    }

    //!*************************************************************************
    //! \brief  Service DL_PDInputTransport. Transfer the content of input data
    //!         (PD from Device to Master) to the application layer.
    //!
    //! \param inputData [out]  Process Data to be transmitted to the AL
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.11
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::PDHandler::pdInputTransport(OctetString &inputData) const
    {
    }

    //!*************************************************************************
    //! \brief  This method receives the Process Data from the device (or
    //!         more formally: it is the "receiver" of confirmation of the
    //!         Service "PD" from the Message handler.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.3
    //!
    //! \todo   TODO add parameters and implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::PDHandler::handlePD_cnf()
    {
    }

    //!*************************************************************************
    //! \brief  This method is the "receiver" of the PDTrig Service from the
    //!         Message handler, which herewith requests the PD Handler to
    //!         provide the PD for the next Master message.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.8
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::PDHandler::handlePDTrig()
    {
    }

    //!*************************************************************************
    //! \brief  Initiates the Service PDInputTransport (transport PD from DL to
    //!         AL).
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.11
    //!
    //!*************************************************************************
    inline void DataLinkLayer::PDHandler::pdInputTransport() const
    {
        // Because the PD handler is encapsulated inside the DL, it has to ask
        // the DL to forward this message.
        mDL->pdInputTransport();
    }

    //!*************************************************************************
    //! \brief  Initiates the Service DL_PDCycle which indicates the end of a
    //!         Process Data cycle to the application layer.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.12
    //!
    //! \note   Because the Service DL_PDCycle does not transport any data, the
    //!         AL will never actually call it (back).
    //!
    //!*************************************************************************
    inline void DataLinkLayer::PDHandler::pdCycle() const
    {
        // Because the PD handler is encapsulated inside the DL, it has to ask
        // the DL to forward this message.
        mDL->pdCycle();
    }

    //**************************************************************************
    //  from class MasterDLModeHandler
    //**************************************************************************

    //!*************************************************************************
    //! \brief  Service DL_SetMode. Set up the state machines of the DL
    //!
    //! \param mode [in]        requested mode
    //!
    //! \param valueList [in]   "relevant operating parameters"
    //!
    //! \return error info, one of the following (see enum class ErrorCode):
    //!             NO_ERROR, STATE_CONFLICT, PARAMETER_CONFLICT
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.13
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::MasterDLModeHandler::setMode(const Mode mode, const OperatingParam &valueList)
    {
        return ErrorCode::UNKNOWN_ERROR;
    }

    //!*************************************************************************
    //! \brief  Service DL_Mode. Report to System Management that a certain
    //!         operating status has been reached.
    //!
    //! \param realMode [out]   current status of the DL mode handler
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.14
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MasterDLModeHandler::mode(RealMode &realMode)
    {
    }

    //!*************************************************************************
    //! \brief  This method is the "receiver" of the MHInfo Service from the
    //!         Message handler, which herewith signals an exceptional operation
    //!         within the message handler.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.6
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MasterDLModeHandler::handleMHInfo()
    {
    }

    //!*************************************************************************
    //! \brief  Initiates the Service DL_Mode. (Report to System Management that
    //!         a certain operating status has been reached.)
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.14
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MasterDLModeHandler::mode() const
    {
        // Because the mode handler is encapsulated inside the DL, it has to ask
        // the DL to forward this message.
        mDL->mode();
    }

    //**************************************************************************
    //  from class MessageHandler
    //**************************************************************************

    //!*************************************************************************
    //! \brief  Service ODTrig. Trigger the OD handler to provide the OD for the
    //!         next Master Message.
    //!
    //! \param dataLength [out] available space (bytes) for OD per message
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.7
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MessageHandler::odTrig(int &dataLength) const
    {
    }

    //!*************************************************************************
    //! \brief  Service PDInStatus. Tell the OD handler wheter the PD from the
    //!         Device are valid.
    //!
    //! \param dataLength [out] PD validity indication
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.5
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MessageHandler::pdInStatus(PDStatus &status)
    {
    }

    //!*************************************************************************
    //! \brief  Service EventFlag. Tell the OD handler the status of the
    //!         "Event flag".
    //!
    //! \param flag [out]   status of the "Event flag"
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.4
    //!         This method is not implemented yet.
    //!
    //! \todo   implement according to the Specification
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MessageHandler::eventFlag(bool &flag)
    {
    }

    //!*************************************************************************
    //! \brief  Service PDTrig. Trigger the PD handler to provide the PD for the
    //!         next Master Message.
    //!
    //! \param dataLength [out] available space (bytes) for PD per message
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.8
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MessageHandler::pdTrig(int &dataLength) const
    {
    }

    //!*************************************************************************
    //! \brief  This method is the "receiver" of an IO-Link telegram. (Formally
    //!         it is the "receiver" of the indication of the Service
    //!         PL_Transfer from the Physical layer.)
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 5.2.2.3
    //!
    //! \todo   TODO implement
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MessageHandler::handlePLTransfer_ind()
    {
        //TODO implementation: react on /IRQ from MAX14819, call readIOLData()
    }

    //!*************************************************************************
    //! \brief  Initiates the Service OD.cnf which transports the received OD to
    //!         the OD handler.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.2
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MessageHandler::od_cnf() const
    {
        mODHandler->handleOD_cnf();
    }

    //!*************************************************************************
    //! \brief  Initiates the Service ODTrig: request the OD for the next
    //!         Message.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.7
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MessageHandler::odTrig() const
    {
        mODHandler->handleODTrig();
    }

    //!*************************************************************************
    //! \brief  Initiates the Service PDInStatus: tell the OD handler wheter the
    //!         PD from the Device are valid.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.5
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MessageHandler::pdInStatus() const
    {
        mODHandler->handlePDInStatus();
    }

    //!*************************************************************************
    //! \brief  Initiates the Service EventFlag. Tell the OD handler the status
    //!         of the "Event flag".
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.4
    //!         This method is not implemented yet.
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MessageHandler::eventFlag() const
    {
        mODHandler->handleEventFlag();
    }

    //!*************************************************************************
    //! \brief  Initiates the Service PD.cnf which transports the received PD to
    //!         the PD handler.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.3
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MessageHandler::pd_cnf() const
    {
        mPDHandler->handlePD_cnf();
    }

    //!*************************************************************************
    //! \brief  Initiates the Service PDTrig: request the PD for the next
    //!         Message.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.2.8
    //!
    //!*************************************************************************
    inline void DataLinkLayer::MessageHandler::pdTrig() const
    {
        mPDHandler->handlePDTrig();
    }

    //**************************************************************************
    //  from class DataLinkLayer
    //**************************************************************************

    //!*************************************************************************
    //! \brief  Service DL_Mode. Report to System Management that a certain
    //!         operating status has been reached.
    //!
    //! \param realMode [out]   current status of the DL mode handler
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.14
    //!
    //! \note   Master DL-mode handler is responsible for this service
    //!
    //!*************************************************************************
    inline void DataLinkLayer::mode(RealMode &realMode)
    {
        mModeHandler.mode(realMode);
    }

    //!*************************************************************************
    //! \brief  Service DL_Read. Read a parameter value from the Device via the
    //!         page communication channel (called from the System Management)
    //!
    //! \param address [in] address of the requested Device parameter FIXME {0..15}
    //!
    //! \param value [out]  the read Device parameter
    //!
    //! \return error info, one of the following (see enum class ErrorCode):
    //!             NO_ERROR, NO_COMM, STATE_CONFLICT,
    //!             UNKNOWN_ERROR (illegall address value)
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.4
    //!
    //! \note   On-request Data handler is responsible for this service
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::read(const unsigned int address, int *value) const
    {
        if (address >= 0 && address <= 15)
        {
            return mODHandler.readParam(address, value); // value: reference or pointer?
        }
        else
        {
            return ErrorCode::UNKNOWN_ERROR;
        }
    }

    //!*************************************************************************
    //! \brief  Service DL_Write. Write a parameter value to the Device via the
    //!         page communication channel (called from the System Management)
    //!
    //! \param address [in] address of the requested Device parameter FIXME {0..15}
    //!
    //! \param value [in]   Device parameter value to be written
    //!
    //! \return error info, one of the following (see enum class ErrorCode):
    //!             NO_ERROR, NO_COMM, STATE_CONFLICT,
    //!             UNKNOWN_ERROR (illegall address value)
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.5
    //!
    //! \note   On-request Data handler is responsible for this service
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::write(const unsigned int address, const int value)
    {
        if (address >= 0 && address <= 15)
        {
            return mODHandler.writeParam(address, value);
        }
        else
        {
            return ErrorCode::UNKNOWN_ERROR;
        }
    }

    //!*************************************************************************
    //! \brief  Service DL_SetMode. Set up the data link layer's state machines
    //!         and set the characteristic values required for operation.
    //!
    //! \param mode [in]        requested mode of the Master's DL
    //!
    //! \param valueList [in]   "relevant operating parameters"
    //!
    //! \return error info, one of the following (see enum class ErrorCode):
    //!             NO_ERROR, STATE_CONFLICT, PARAMETER_CONFLICT
    //!
    //! \note   Master DL-mode handler is responsible for this service
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::setMode(const Mode mode, const OperatingParam &valueList)
    {
        return mModeHandler.setMode(mode, valueList);
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
    //! \note   On-request Data handler is responsible for this service
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::readParam(const unsigned int address, int *value) const
    {
        if (address >= 0 && address <= 31)
        {
            return mODHandler.readParam(address, value); // value: reference or pointer?
        }
        else
        {
            return ErrorCode::UNKNOWN_ERROR;
        }
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
    //! \note   On-request Data handler is responsible for this service
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::writeParam(const unsigned int address, const int value)
    {
        if (address >= 16 && address <= 31)
        {
            return mODHandler.writeParam(address, value);
        }
        else
        {
            return ErrorCode::UNKNOWN_ERROR;
        }
    }

    //!*************************************************************************
    //! \brief  Service DL_ISDUTransport
    //!
    //! \return always ISDU_NOT_SUPPORTED (not implemented yet)
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.6
    //!         This method is not implemented yet.
    //!
    //! \note   On-request Data handler is responsible for this service
    //!
    //! \todo   add parameters and implement according to the Specification
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::isduTransport()
    {
        mODHandler.isduTransport();
    }

    //!*************************************************************************
    //! \brief  Service DL_ISDUAbort
    //!
    //! \return always ISDU_NOT_SUPPORTED (not implemented yet)
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.7
    //!         This method is not implemented yet.
    //!
    //! \note   On-request Data handler is responsible for this service
    //!
    //! \todo   add parameters and implement according to the Specification
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::isduAbort()
    {
        mODHandler.isduAbort();
    }

    //!*************************************************************************
    //! \brief  Service DL_Control
    //!
    //! "The Master uses the DL_Control service to convey control information
    //! via the MasterCommand mechanism to the corresponding Device application
    //! and to get control information via the PD status flag mechanism (see
    //! A.1.5) and the PDInStatus service (see 7.2.2.5)."
    //!
    //! \param controlCode [in, out]    indicates the qualifier status of the PD
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.18
    //!         This method is not implemented yet.
    //!
    //! \note   On-request Data handler is responsible for this service
    //!
    //! \todo   implement according to the Specification
    //!
    //!*************************************************************************
    inline void DataLinkLayer::control(ControlCode &controlCode)
    {
        mODHandler.control(controlCode);
    }

    //!*************************************************************************
    //! \brief  Service DL_Event
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.15
    //!         This method is not implemented yet.
    //!
    //! \note   On-request Data handler is responsible for this service
    //!
    //! \todo   add parameters and implement according to the Specification
    //!
    //!*************************************************************************
    inline void DataLinkLayer::event(int &argument) const
    {
        mODHandler.event(argument);
    }

    //!*************************************************************************
    //! \brief  Service DL_EventConf, confirms the transmitted Events via the
    //!         Event handler.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.16
    //!         This method is not implemented yet.
    //!
    //! \note   On-request Data handler is responsible for this service
    //!
    //! \todo   add parameters and implement according to the Specification
    //!
    //!*************************************************************************
    inline void DataLinkLayer::eventConf() const
    {
        mODHandler.eventConf();
    }

    //!*************************************************************************
    //! \brief  Service DL_PDOutputUpdate. Updates the output data (Process Data
    //!         Master -> Device) on the data link layer.
    //!
    //! \param outputData [in]          Process Data provided by the AL
    //!
    //! \param transportStatus [out]    indicates wheter DL permits data transfer to the Device
    //!
    //! \return error info, one of the following (see enum class ErrorCode):
    //!             NO_ERROR, NO_COMM, STATE_CONFLICT
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.8
    //!
    //! \note   Process Data handler is responsible for this service
    //!
    //! \note   If the PD should be queued in the DL you can make this method
    //!         write to that queue.
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::pdOutputUpdate(const OctetString &outputData, PDTransportStatus &transportStatus)
    {
        return mPDHandler.pdOutputUpdate(outputData, transportStatus);
    }

    //!*************************************************************************
    //! \brief  Service DL_PDInputTransport. Transfer the content of input data
    //!         (PD from Device to Master) to the application layer.
    //!
    //! \param inputData [out]  Process Data to be transmitted to the AL
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.11
    //!
    //! \note   Process Data handler is responsible for this service
    //!
    //!*************************************************************************
    inline void DataLinkLayer::pdInputTransport(OctetString &inputData) const
    {
        mPDHandler.pdInputTransport(inputData);
    }

    //!*************************************************************************
    //! \brief  Register the Port Handler object from the System Management (SM)
    //!         which belongs to this data link layer (DL).
    //!
    //! \param portHandler [in]
    //!
    //! \note   TODO called by the PortHandler when he is given the Address of the DL
    //!
    //!*************************************************************************
    inline void DataLinkLayer::setPortHandler(const SystemManagement::PortHandler &portHandler)
    {
        mPortHandler = &portHandler; // problem: cannot assign a const pointer to a pointer
    }

    //!*************************************************************************
    //! Initiated Services
    //!
    //! The following member functions are used to initiate a Service from the
    //! DL to the AL or SM (PortHandler). Those usually then call the overloaded
    //! function with parameters, to get the "payload" data of the Service.
    //!
    //! The following functions get called from the handler objects encapsulated
    //! in the DL without exception.
    //!
    //!*************************************************************************

    //!*************************************************************************
    //! \brief  Initiates the Service DL_Mode. (Report to System Management that
    //!         a certain operating status has been reached.)
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.14
    //!
    //!*************************************************************************
    inline void DataLinkLayer::mode() const
    {
        mPortHandler->handleDLMode();
    }

    //!*************************************************************************
    //! \brief  Initiates the Service DL_Control in the case it is used in the
    //!         direction from the DL to the AL.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.18
    //!
    //!*************************************************************************
    inline void DataLinkLayer::control() const
    {
        mAL.handleDLControl();
    }

    //!*************************************************************************
    //! \brief  Initiates the Service DL_Event.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.15
    //!
    //!*************************************************************************
    inline void DataLinkLayer::event() const
    {
        mAL.handleDLEvent();
    }

    //!*************************************************************************
    //! \brief  Initiates the Service PDInputTransport (transport PD from DL to
    //!         AL).
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.11
    //!
    //!*************************************************************************
    inline void DataLinkLayer::pdInputTransport() const
    {
        mAL.handleDLPDInputTransport();
    }

    //!*************************************************************************
    //! \brief  Initiates the Service DL_PDCycle which indicates the end of a
    //!         Process Data cycle to the application layer.
    //!
    //! \note   see IO-Link Specification V1.1.3 par. 7.2.1.12
    //!
    //! \note   Because the Service DL_PDCycle does not transport any data, the
    //!         AL will never actually call it back.
    //!
    //!*************************************************************************
    inline void DataLinkLayer::pdCycle() const
    {
        mAL.handleDLPDCycle();
    }

} // namespace openiolink
#endif
