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
        DataLinkLayer(const IOLMasterPort_thisIsPL &PL);
        ~DataLinkLayer();
        inline BaseType readParam(const unsigned int address, int &value);
        inline BaseType writeParam(const unsigned int address, const int value);
        inline BaseType read(const unsigned int address, int &value);
        inline BaseType write(const unsigned int address, const int value);
        inline BaseType PDOutputUpdate(const int outputData);
        inline void PDCycle();
        inline BaseType setMode(const int mode, const int valueList);
        inline void indMode();
        void stepFSM();
        inline void registerAL(const GenericIOLDevice_thisIsAL &ApplicationLayer);
        inline void registerPortHandler(const SystemManagement::PortHandler &NewPortHandler);

        class OD_Handler
        {
        public:
            void stepFSM();
            BaseType readParam(const unsigned int address, int &value);
            BaseType writeParam(const unsigned int address, const int value);
            void PDCycle();
        };

        class PD_Handler
        {
        public:
            void stepFSM();
            BaseType PDOutputUpdate();
            BaseType PDInputTransport();
        };

        class MasterDLMode_Handler
        {
        public:
            void stepFSM();
            BaseType setMode(const int mode, const int valueList);
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
        IOLMasterPort_thisIsPL *mPL;

        inline BaseType PDInputTransport(int &inputData);
    };  // class DataLinkLayer

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************
    //read a parameter value from the Device via the page communication channel
    inline BaseType DataLinkLayer::readParam(const unsigned int address, int &value)
    {
        return ODHandler.readParam(address, value);
    }

    //write a parameter value to the Device via the page communication channel
    inline BaseType DataLinkLayer::writeParam(const unsigned int address, const int value)
    {
    }

    //used by System Management to read a Device parameter value via the page communication channel.
    inline BaseType DataLinkLayer::read(const unsigned int address, int &value)
    {
        return ODHandler.readParam(address, value);
    }

    //used by System Management to write a Device parameter value to the Device via the page communication channel
    inline BaseType DataLinkLayer::write(const unsigned int address, const int value)
    {
    }

    //The Master's application layer uses the DL_PDOutputUpdate service to update the output data (Process Data from Master to Device) on the data link layer. (Spec. 7.2.1.8)
    inline BaseType DataLinkLayer::PDOutputUpdate(const int outputData)
    {
        return PDHandler.PDOutputUpdate();
    }

    //indicate the end of a Process Data cycle to the application layer (Spec. 7.2.1.12)
    inline void DataLinkLayer::PDCycle()
    {
    }

    //The DL_SetMode service is used by System Management to set up the data link layer's state machines and to send the characteristic values required for operation to the data link layer. (Spec. 7.2.1.13) // TODO Datentyp von Mode und valueList
    inline BaseType DataLinkLayer::setMode(const int mode, const int valueList)
    {
        return ModeHandler.setMode(mode, valueList);
    }

    //report to System Management that a certain operating status has been reached. (Spec 7.2.1.14)
    //TODO: Wie funktionieren die Aufrufe bei den Services, wo der DL Initiator ist?
    inline void DataLinkLayer::indMode()
    {
        ModeHandler.indMode();
    }

    inline void DataLinkLayer::registerAL(const GenericIOLDevice_thisIsAL &ApplicationLayer)
    {
    }

    inline void DataLinkLayer::registerPortHandler(const SystemManagement::PortHandler &NewPortHandler)
    {
    }

    //The data link layer on the Master uses the DL_PDInputTransport service to transfer the content of input data (Process Data from Device to Master) to the application layer.
    inline BaseType DataLinkLayer::PDInputTransport(int &inputData)
    {
    }

} // namespace openiolink
#endif
