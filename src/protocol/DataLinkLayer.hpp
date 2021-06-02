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
#include "ErrorCode.hpp"

namespace openiolink
{
    class IOLMasterPort_thisIsPL;
    class GenericIOLDevice_thisIsAL;
}

namespace openiolink
{
    class DataLinkLayer
    {
    public:
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

        DataLinkLayer(const IOLMasterPort_thisIsPL &PL);
        ~DataLinkLayer();
        inline ErrorCode readParam(const unsigned int address, int *value);
        inline ErrorCode writeParam(const unsigned int address, const int value);
        inline ErrorCode read(const unsigned int address, int *value);
        inline ErrorCode write(const unsigned int address, const int value);
        inline ErrorCode PDOutputUpdate(const uint8_t *outputData, PDTransportStatus *transportStatus);
        inline void PDCycle();
        inline ErrorCode setMode(const Mode mode, const OperatingParam &valueList);
        inline void indMode();
        void stepFSM();
        inline void registerAL(const GenericIOLDevice_AL *ApplicationLayer);
        inline void registerPortHandler(const SystemManagement::PortHandler &NewPortHandler);

        class OD_Handler
        {
        public:
            void stepFSM();
            ErrorCode readParam(const unsigned int address, int &value);
            ErrorCode writeParam(const unsigned int address, const int value);
            void PDCycle();
        };

        class PD_Handler
        {
        public:
            void stepFSM();
            ErrorCode PDOutputUpdate(const uint8_t *outputData, PDTransportStatus *transportStatus);
            ErrorCode PDInputTransport();
        };

        class MasterDLMode_Handler
        {
        public:
            void stepFSM();
            ErrorCode setMode(const Mode mode, const OperatingParam &valueList);
            void indMode();

        private:
            //States of the Master DL-mode handler state machine
            enum class MHState
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

            MHState state;
        };

        //Sollte alle M Sequence Typen unterstuetzen
        class Message_Handler
        {
        public:
            void stepFSM();
        };

    private:
        OD_Handler ODHandler;
        PD_Handler PDHandler;
        MasterDLMode_Handler ModeHandler;
        MasterDLMode_Handler MessageHandler;
        IOLMasterPort *mPL;
        GenericIOLDevice_AL *mAL;

        inline ErrorCode PDInputTransport(int &inputData);
    }; // class DataLinkLayer

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************

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
    inline ErrorCode DataLinkLayer::PDOutputUpdate(const uint8_t *outputData, PDTransportStatus *transportStatus)
    {
        return PDHandler.PDOutputUpdate(outputData, transportStatus);
    }

    // TODO
    //indicate the end of a Process Data cycle to the application layer (Spec. 7.2.1.12)
    inline void DataLinkLayer::PDCycle()
    {
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

    //report to System Management that a certain operating status has been reached. (Spec 7.2.1.14)
    //TODO: Wie funktionieren die Aufrufe bei den Services, wo der DL Initiator ist?
    inline void DataLinkLayer::indMode()
    {
        ModeHandler.indMode();
    }

    //!*************************************************************************
    //! \brief  Register the application layer (AL) object (i.e. the IO-Link-
    //!         Device) which belongs to this data link layer (DL).
    //!
    //! \param ApplicationLayer[in] pointer to the AL (IO-Link Device)
    //!
    //!*************************************************************************
    inline void DataLinkLayer::registerAL(const GenericIOLDevice_AL *ApplicationLayer)
    {
        mAL = ApplicationLayer;
    }

    inline void DataLinkLayer::registerPortHandler(const SystemManagement::PortHandler &NewPortHandler)
    {
        mPortHandler = &NewPortHandler; // TODO OK? (Referenz zu Pointer wandeln).
    }

    //The data link layer on the Master uses the DL_PDInputTransport service to transfer the content of input data (Process Data from Device to Master) to the application layer.
    inline ErrorCode DataLinkLayer::PDInputTransport(int &inputData)
    {
    }

} // namespace openiolink
#endif
