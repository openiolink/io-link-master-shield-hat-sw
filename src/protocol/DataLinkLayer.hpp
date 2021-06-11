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

#include <iostream>
#include "SystemManagement.hpp"
#include "ErrorCode.hpp"

namespace openiolink
{
    class IOLMasterPort;
    class ApplicationLayer;
}

namespace openiolink
{
    class DataLinkLayer
    {
    public:
        // Message Handler Info
        // see Specification 7.2.2.6
        enum class MHInfo
        {
            COMLOST,             // lost communication
            ILLEGAL_MESSAGETYPE, // unexpected M-sequence type detected
            CHECKSUM_MISMATCH    // Checksum error detected
        };

        // qualifier status of the Process Data (PD)
        // from Specification 7.2.1.18
        enum class ControlCode
        {
            VALID,       // Input Process Data valid; see 7.2.2.5, 8.2.2.12
            INVALID,     // Input Process Data invalid
            PDOUTVALID,  // Output Process Data valid; see 7.3.7.1
            PDOUTINVALID // Output Process Data invalid or missing
        };

        // indicates whether the data link layer is in a state permitting data to be 1068 transferred to the communication partner(s).
        // see Specification 7.2.1.8
        enum class PDTransportStatus
        {
            YES, // data transmission permitted
            NO   // data transmission not permitted
        };

        // see Specification 7.2.1.13
        enum class Mode
        {
            INACTIVE,   // handler shall change to the INACTIVE state
            STARTUP,    // handler shall change to STARTUP state
            PREOPERATE, // handler shall change to PREOPERATE state
            OPERATE     // handler shall change to OPERATE state
        };

        // see Specification 7.2.1.14
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

        // see Specification 7.2.1.13
        struct OperatingParam
        {
            int mSequenceTime;
            MSequenceType mSequenceType; // TODO enum class
            int PDInputLength;
            int PDOutputLength;
            int OnReqDataLengthPerMessage;
        };

        class ODHandler
        {
        public:
            ODHandler(const DataLinkLayer &parentDL, const MessageHandler &messageHandler);
            ~ODHandler();
            void stepFSM();
            ErrorCode readParam(const unsigned int address, int &value);
            ErrorCode writeParam(const unsigned int address, const int value);
            inline ErrorCode isduTransport();
            inline ErrorCode isduAbort();
            inline void control(ControlCode &controlCode);
            inline void event() const;
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

        class PDHandler
        {
        public:
            PDHandler(const DataLinkLayer &parentDL, const MessageHandler &messageHandler);
            ~PDHandler();
            void stepFSM();
            inline ErrorCode pdOutputUpdate(const uint8_t *outputData, PDTransportStatus *transportStatus);
            inline void pdInputTransport(OctetString &inputData) const;
            inline void pdCycle() const;
            inline void handlePD_cnf();
            inline void handlePDTrig();

        private:
            DataLinkLayer *mDL;
            MessageHandler *mMessageHandler; // lower layer DL-A
            inline void pdInputTransport() const;
        };

        class MasterDLModeHandler
        {
        public:
            MasterDLModeHandler(const DataLinkLayer &parentDL);
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

        // Sollte alle M Sequence Typen unterstuetzen
        class MessageHandler
        {
        public:
            MessageHandler(const DataLinkLayer &parentDL, const IOLMasterPort &physicalLayer, const MasterDLModeHandler &modeHandler);
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

        DataLinkLayer(const IOLMasterPort &PL, const ApplicationLayer &AL);
        ~DataLinkLayer();
        void stepFSM();
        inline void mode(RealMode &realMode);
        inline ErrorCode read(const unsigned int address, int *value) const;
        inline ErrorCode write(const unsigned int address, const int value);
        inline ErrorCode setMode(const Mode mode, const OperatingParam &valueList);
        inline ErrorCode readParam(const unsigned int address, int *value) const;
        inline ErrorCode writeParam(const unsigned int address, const int value);
        ErrorCode isduTransport();
        inline ErrorCode isduAbort();
        inline void control(ControlCode &controlCode);
        inline void event() const;
        inline void eventConf() const;
        inline ErrorCode pdOutputUpdate(const uint8_t *outputData, PDTransportStatus &transportStatus);
        inline void pdInputTransport(OctetString &inputData) const;
        inline void pdCycle() const;
        inline void setPortHandler(const SystemManagement::PortHandler &portHandler);

    private:
        ApplicationLayer *mAL;
        SystemManagement::PortHandler *mPortHandler; // PortHandler (SM) is receiver of the service DL_Mode
        MasterDLModeHandler ModeHandler;
        MasterDLModeHandler MessageHandler;
        PDHandler PDHandler;
        ODHandler ODHandler;
        IOLMasterPort *mPL;
        inline void mode() const;
        inline void control() const;
        inline void event() const;
        inline void pdInputTransport() const;
    }; // class DataLinkLayer

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************

    //DL_ISDUTransport (Specification 7.2.1.6), not implemented, TODO add parameters
    inline ErrorCode DataLinkLayer::ODHandler::isduTransport()
    {
    }

    //DL_ISDUAbort (Specification 7.2.1.7), not implemented, TODO add parameters
    inline ErrorCode DataLinkLayer::ODHandler::isduAbort()
    {
    }

    //Specification 7.2.1.18, not implemented
    //The Master uses the DL_Control service to convey control information via the MasterCommand mechanism to the corresponding Device application and to get control information via the PD status flag mechanism (see A.1.5) and the PDInStatus service (see 7.2.2.5).
    inline void DataLinkLayer::ODHandler::control(DataLinkLayer::ControlCode &controlCode)
    {
    }

    //Specification 7.2.1.15, not implemented, TODO add arguments
    inline void DataLinkLayer::ODHandler::event() const
    {
    }

    //confirms the transmitted Events via the Event handler.
    //Specification 7.2.1.16, not implemented
    inline void DataLinkLayer::ODHandler::eventConf() const
    {
    }

    //end point of the service OD.cnf (from Message handler)
    inline void DataLinkLayer::ODHandler::handleOD_cnf()
    {
    }

    //end point of the service ODTrig (from Message handler)
    inline void DataLinkLayer::ODHandler::handleODTrig()
    {
    }

    //end point of the service PDInStatus (from Message handler)
    inline void DataLinkLayer::ODHandler::handlePDInStatus()
    {
    }

    //end point of the service EventFlag (from Message handler)
    inline void DataLinkLayer::ODHandler::handleEventFlag()
    {
    }

    //Initiates the Service DL_Control, when used in direction away from DL (Specification 7.2.1.18)
    inline void DataLinkLayer::ODHandler::control() const
    {
    }

    //Initiates the Service DL_Event (Specification 7.2.1.15), not implemented yet
    inline void DataLinkLayer::ODHandler::event() const
    {
    }

    //The Master's application layer uses the DL_PDOutputUpdate service to update the output data (Process Data from Master to Device) on the data link layer. (Spec. 7.2.1.8)
    inline ErrorCode DataLinkLayer::PDHandler::pdOutputUpdate(const uint8_t *outputData, TransportStatus &transportStatus)
    {
    }

    //The data link layer on the Master uses the DL_PDInputTransport service to transfer the content of input data (Process Data from Device to Master) to the application layer.
    //Specification 7.2.1.11
    inline void DataLinkLayer::PDHandler::pdInputTransport(OctetString &inputData) const
    {
    }

    //indicate the end of a Process Data cycle to the application layer (Spec. 7.2.1.12)
    inline void DataLinkLayer::PDHandler::pdCycle() const
    {
    }

    //end point of the service PD.cnf (from Message handler)
    inline void DataLinkLayer::PDHandler::handlePD_cnf()
    {
    }

    //end point of the service PDTrig (from Message handler)
    inline void DataLinkLayer::PDHandler::handlePDTrig()
    {
    }

    //Initiates the DL service PDInputTransport (to AL)
    inline void DataLinkLayer::PDHandler::pdInputTransport() const
    {
    }

    inline ErrorCode DataLinkLayer::MasterDLModeHandler::setMode(const Mode mode, const OperatingParam &valueList)
    {
        return ErrorCode();
    }

    //report to System Management that a certain operating status has been reached.
    //Specification 7.2.1.14
    //realMode[out]: where to store the current mode of the DL
    inline void DataLinkLayer::MasterDLModeHandler::mode(RealMode &realMode)
    {
    }

    //end point of the service DL_Mode
    inline void DataLinkLayer::MasterDLModeHandler::handleMHInfo()
    {
    }

    //Initiates the Service DL_Mode (Specification 7.2.1.14)
    inline void DataLinkLayer::MasterDLModeHandler::mode() const
    {
    }

    //Specification 7.2.2.7
    //dataLength[out]	available space for On-request Data (OD) per message
    inline void DataLinkLayer::MessageHandler::odTrig(int &dataLength) const
    {
    }

    //Sets "status" to the current validity state of the input Process Data.
    //PDStatus: enum VALID, INVALID
    inline void DataLinkLayer::MessageHandler::pdInStatus(PDStatus &status)
    {
    }

    //Sets "flag" to the status of the "Event flag" during cyclic communication.
    //Specification 7.2.2.4
    inline void DataLinkLayer::MessageHandler::eventFlag(bool &flag)
    {
    }

    //Specification 7.2.2.8
    //dataLength[out]	available space for Process Data (PD) per message
    inline void DataLinkLayer::MessageHandler::pdTrig(int &dataLength) const
    {
    }

    //end point of the service PL_Transfer.ind
    //TODO implementation: react on /IRQ from MAX14819, call readIOLData()
    inline void DataLinkLayer::MessageHandler::handlePLTransfer_ind()
    {
    }

    //Initiates the Service OD.cnf (Specification 7.2.2.2 OD)
    inline void DataLinkLayer::MessageHandler::od_cnf() const
    {
    }

    //Initiates the Service ODTrig (Specification 7.2.2.7)
    inline void DataLinkLayer::MessageHandler::odTrig() const
    {
    }

    //Initiates the Service PDInStatus (Specification 7.2.2.5)
    inline void DataLinkLayer::MessageHandler::pdInStatus() const
    {
    }

    //Initiates the Service EventFlag (Specification 7.2.2.4), not implemented
    inline void DataLinkLayer::MessageHandler::eventFlag() const
    {
    }

    //Initiates the Service PD.cnf (Specification 7.2.2.3 PD)
    inline void DataLinkLayer::MessageHandler::pd_cnf() const
    {
    }

    //Initiates the Service PDTrig (Specification 7.2.2.8)
    inline void DataLinkLayer::MessageHandler::pdTrig() const
    {
    }

    //report to System Management that a certain operating status has been reached.
    //Specification 7.2.1.14
    //realMode[out]: where to store the current mode of the DL
    inline void DataLinkLayer::mode(RealMode &realMode)
    {
        ModeHandler.indMode();
    }

    //!*************************************************************************
    //! \brief  Read a parameter value from the Device via the page
    //!         communication channel (used by the System Management)
    //!
    //! \param address[in]  address of the requested Device parameter {0..15}
    //!
    //! \param value[out]   the read Device parameter
    //!
    //! \return state of the operation
    //!
    //! \note   This implements the Service DL_Read (Specification 7.2.1.4).
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::read(const unsigned int address, int *value)
    {
        if (address >= 0 && address <= 15)
        {
            return ODHandler.readParam(address, value);
        }
        else
        {
            return ErrorCode::UNKNOWN_ERROR;
        }
    }

    //!*************************************************************************
    //! \brief  Write a parameter value to the Device via the page
    //!         communication channel (used by the System Management)
    //!
    //! \param address[in]  address of the requested Device parameter {0..15}
    //!
    //! \param value[in]    Device parameter value to be written
    //!
    //! \return state of the operation
    //!
    //! \note   This implements the Service DL_Write (Specification 7.2.1.5).
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::write(const unsigned int address, const int value)
    {
        if (address >= 0 && address <= 15)
        {
            return ODHandler.writeParam(address, value);
        }
        else
        {
            return ErrorCode::UNKNOWN_ERROR;
        }
    }

    //!*************************************************************************
    //! \brief  Set up the data link layer's state machines and send the
    //!         characteristic values required for operation to the data link
    //!         layer (used by System Management)
    //!
    //! \param mode[in]         requested mode of the Master's DL
    //!
    //! \param valueList[in]    struct with relevant operating parameters
    //!
    //! \return state of the operation, one of the following:
    //!         NO_ERROR, STATE_CONFLICT, PARAMETER_CONFLICT
    //!
    //! \note   This implements the Service DL_SetMode (Specification 7.2.1.13).
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::setMode(const Mode mode, const OperatingParam &valueList)
    {
        return ModeHandler.setMode(mode, valueList);
    }

    //!*************************************************************************
    //! \brief  Read a parameter value from the Device via the page
    //!         communication channel
    //!
    //! \param address[in]  address of the requested Device parameter {0..31}
    //!
    //! \param value[out]   the read Device parameter
    //!
    //! \return state of the operation
    //!
    //! \note   This implements the Service DL_ReadParam (Specification 7.2.1.2).
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::readParam(const unsigned int address, int *value)
    {
        if (address >= 0 && address <= 31)
        {
            return ODHandler.readParam(address, value);
        }
        else
        {
            return ErrorCode::UNKNOWN_ERROR;
        }
    }

    //!*************************************************************************
    //! \brief  Write a parameter value to the Device via the page
    //!         communication channel
    //!
    //! \param address[in]  address of the requested Device parameter {16..31}
    //!
    //! \param value[in]    Device parameter value to be written
    //!
    //! \return state of the operation
    //!
    //! \note   This implements the Service DL_WriteParam (Specification 7.2.1.3).
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::writeParam(const unsigned int address, const int value)
    {
        if (address >= 16 && address <= 31)
        {
            return ODHandler.writeParam(address, value);
        }
        else
        {
            return ErrorCode::UNKNOWN_ERROR;
        }
    }

    //DL_ISDUAbort (Specification 7.2.1.7), not implemented, TODO add parameters
    //TODO call mOD.isduAbort
    inline ErrorCode DataLinkLayer::isduAbort()
    {
    }

    //Specification 7.2.1.18, not implemented
    //The Master uses the DL_Control service to convey control information via the MasterCommand mechanism to the corresponding Device application and to get control information via the PD status flag mechanism (see A.1.5) and the PDInStatus service (see 7.2.2.5).
    inline void DataLinkLayer::control(ControlCode &controlCode)
    {
    }

    //Specification 7.2.1.15, not implemented, TODO add arguments
    inline void DataLinkLayer::event() const
    {
    }

    //confirms the transmitted Events via the Event handler.
    //Specification 7.2.1.16, not implemented
    inline void DataLinkLayer::eventConf() const
    {
    }

    //!*************************************************************************
    //! \brief  Update the output data (Process Data from Master to Device) on
    //!         the data link layer
    //!
    //! \param outputData[in]       new Process Data
    //!
    //! \param transportStatus[out] indicates wheter the DL permitts data to be
    //!                             transferred to the Device
    //!
    //! \return state of the operation
    //!
    //! \note   This implements the Service DL_PDOutputUpdate (Specification 7.2.1.8).
    //!
    //!*************************************************************************
    inline ErrorCode DataLinkLayer::pdOutputUpdate(const uint8_t *outputData, PDTransportStatus *transportStatus)
    {
        return PDHandler.pdOutputUpdate(outputData, transportStatus);
    }

    //The data link layer on the Master uses the DL_PDInputTransport service to transfer the content of input data (Process Data from Device to Master) to the application layer.
    inline void DataLinkLayer::pdInputTransport(OctetString &inputData) const
    {
    }

    // TODO
    //indicate the end of a Process Data cycle to the application layer (Spec. 7.2.1.12)
    inline void DataLinkLayer::pdCycle() const
    {
    }

    //!*************************************************************************
    //! \brief  Register the Port Handler object from the System Management (SM)
    //!         which belongs to this data link layer (DL).
    //!
    //! \param portHandler[in]
    //!
    //! \note   TODO called by the PortHandler when he is given the Address of the DL
    //!
    //!*************************************************************************
    inline void DataLinkLayer::setPortHandler(const SystemManagement::PortHandler &portHandler)
    {
        mPortHandler = &portHandler; // TODO OK? (Referenz zu Pointer wandeln).
    }

    //Initiates the Service DL_Mode (Specification 7.2.1.14)
    // report to System Management that a certain operating status has been reached. (Spec 7.2.1.14)
    inline void DataLinkLayer::mode() const
    {
    }

    //Initiates the Service DL_Control, when used in direction away from DL (Specification 7.2.1.18)
    inline void DataLinkLayer::control() const
    {
    }

    //Initiates the Service DL_Event (Specification 7.2.1.15), not implemented yet
    inline void DataLinkLayer::event() const
    {
    }

    //Initiates the DL service PDInputTransport (to AL)
    inline void DataLinkLayer::pdInputTransport() const
    {
    }

} // namespace openiolink
#endif
