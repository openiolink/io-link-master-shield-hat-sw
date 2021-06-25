//!*****************************************************************************
//! \file   IOLMaster.cpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  This class represents an IO-Link Master.
//!
//! \date   2021-06-22
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

#include "IOLMaster.hpp"
#include "GenericIOLDevice.hpp"

#include "IOLMessage.hpp"

namespace openiolink
{
    //!*************************************************************************
    //! \brief  construct a new IOLMasterClass object
    //!
    //! \note   The template template parameter 'IOLMasterPortImplementation'
    //!         takes the typename of a class template which implements (i.e.
    //!         inherits from) the class IOLMasterPort.
    //!
    //! \note   There is an alias defintion called 'IOLMaster' which the user
    //!         of the library can use to instantiate this class.
    //!
    //!*************************************************************************
    template <template <int IOLPortNr> class IOLMasterPortImplementation>
    IOLMasterClass<IOLMasterPortImplementation>::IOLMasterClass()
        : mPort0{}, mPort1{}, mPort2{}, mPort3{}, // construct the four IO-Link ports, ...
          //mAL{},                                  // the Application Layer, ...
          //                                        // the System Management, which needs various parameters:
          //mSM{static_cast<IOLMasterPort &>(mPort0), static_cast<IOLMasterPort &>(mPort1),
          //    static_cast<IOLMasterPort &>(mPort2), static_cast<IOLMasterPort &>(mPort3),
          //    mAL.getDL(), mAL},
          mPCB{} //and finally the shield/hat object.
          {
              // FIXME should there be a call to stepFSM() in this place?
          };

    //!*************************************************************************
    //! \brief  destruct the IOLMasterClass object
    //!
    //!*************************************************************************
    template <template <int IOLPortNr> class IOLMasterPortImplementation>
    IOLMasterClass<IOLMasterPortImplementation>::~IOLMasterClass()
    {
    }

    //
    template <template <int IOLPortNr> class IOLMasterPortImplementation>
    void IOLMasterClass<IOLMasterPortImplementation>::wakeUpPort(const int port)
    {
        switch (port)
        {
        case 0:
            mPort0.wakeUpRequest();
            break;

        default:
            assert(false, "not port 0");
            break;
        }
    }

    // TODO define return type (+ additional argument)
    template <template <int IOLPortNr> class IOLMasterPortImplementation>
    void IOLMasterClass<IOLMasterPortImplementation>::getPage1(const int port)
    {
        // FIXME currently ignores argument "port" and only returns Page1 of port 0!


        //!*****************************************************************************
        //!  \brief Page 1 data
        //!
        //!         IO-Link Interface and System Specification V1.1.2 Table B.1
        //!TODO: move out of this method (is already in GenericIOLDevice)
        //!*****************************************************************************
        union
        {
            uint8_t data[13];
            struct __attribute__((__packed__))
            {
                uint8_t MasterCycleTime;
                uint8_t MinCycleTime;
                uint8_t M_sequenceCapability;
                uint8_t RevisionID;
                uint8_t ProcessDataIn;
                uint8_t ProcessDataOut;
                union
                {
                    uint8_t bytes[2];
                    uint16_t value;
                } VendorID;
                union _attribute__((__packed__))   // TODO, prüfen, ob __packed__ wirklich funktioniert (1): eins schreiben, andere lesen, (2): sizeof() prüfen
                {     // damit es bei jedem Kompilieren die Grösse überprüft wird, z.B. 1/(13-sizeof(x)) sollte division /0 bzw. static_assert(). Falls dies nicht geht, Subtraktion der Addressen des letzten und ersten Elements.
                    uint8_t bytes[3];
                    uint32_t value : 24;
                } deviceID;
                union
                {
                    uint8_t bytes[2];
                    uint16_t value;
                } FunctionID;
            };
        } page1; ///< Aufbau der Page1 eines Sensors

        IOLMessage msg;
        uint8_t buffer[10];
        uint8_t page1actualread;
        msg.setMSequenceType(IOLMessage::M_Sequence_Type::Type0);

        for (uint8_t i = 0; i < 13; i++)
        {

            msg.setMC(IOLMessage::Read_Write::Read_access, IOLMessage::Communication_Channel::Page, i + 1); // 0x00 is MasterCommand
            //port->prepareForSend()    // u.a. Checksumme berechnen // andererseits gehört es fest zum Senden dazu...
            // daher in diesem Kontext in einer Funktion zusammen lassen.
            // Vorschlag besserer Name: sendMessage()
            // oder msg->prepareForSend()
            mPort0.sendIOLData(msg);

            mPort0.readIOLData(buffer, msg.getanswer_length());
            page1.data[i] = buffer[0];
        }

        std::cout << "read page1 data\n\r";
    }

    }

    //
    //bind an IOL-Device to a port of the Master
    //NOTE: check the return value (false = OK, true = ERROR)
    //TODO: registerPortModeHandler(), registerALServiceHandler(), device.setAL()
    //[[nodiscard]] to force the user to use the returned value
    bool IOLMasterClass<IOLMasterPortImplementation>::connectDevice(const int portNr, const GenericIOLDevice &device)
    {
    }

} // namespace openiolink
