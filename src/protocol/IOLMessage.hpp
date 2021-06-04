//!*****************************************************************************
//!  \file IOLMessage.hpp
//!  
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!  
//!  \brief Contains the IOLMessage class which describes an IO-Link message
//!  
//!  \date 2020-11-05
//!  
//!  
//!  *****************************************************************************
//!  
//!  \copyright
//!  Copyright 2020 Bern University of Applied Sciences and Balluff AG
//!  \n\n
//!  Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!  \n\n
//!      http://www.apache.org/licenses/LICENSE-2.0
//!  \n\n
//!  Unless required by applicable law or agreed to in writing, software
//!  distributed under the License is distributed on an "AS IS" BASIS,
//!  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!  See the License for the specific language governing permissions and
//!  limitations under the License.
//!  
//!*****************************************************************************

#ifndef IOLMESSAGE_HPP_INCLUDED
#define IOLMESSAGE_HPP_INCLUDED

#include "IOLinkConfig.hpp"
#ifdef ARDUINO
	#include <stdint.h>
#else
	#include <cstdint>
#endif

namespace openiolink
{
    //!*****************************************************************************
    //!  \brief This class describes an IO-Link message
    //!  
    //!         This class is used to generate an IO-Link message. It handles the
    //!         checksum automatically.
    //!  
    //!*****************************************************************************
    class IOLMessage
    {
    public:
        //!*****************************************************************************
        //!  \brief Used for bit 7 of the M-sequence control (MC)
        //!  
        //!         IO-Link Interface and System Specification V1.1.2 Table A.2 
        //!  
        //!*****************************************************************************
        enum class Read_Write
        {
            Write_access = 0,
            Read_access = 1
        };
        
        //!*****************************************************************************
        //!  \brief Used for bit 5 to 6 of the M-sequence control (MC)
        //!  
        //!         IO-Link Interface and System Specification V1.1.2 Table A.1 
        //!  
        //!*****************************************************************************
        enum class Communication_Channel
        {
            Process = 0,
            Page = 1,
            Diagnosis = 2
        };
        
        //!*****************************************************************************
        //!  \brief Used for bit 6 to 7 of the Checksum / M-sequence type (CKT)
        //!  
        //!         IO-Link Interface and System Specification V1.1.2 Chapter A.2
        //!  
        //!*****************************************************************************
        enum class M_Sequence_Type
        {
            Type0 = 0,
            Type1 = 1,
            Type2 = 2
        };

    private:
        union
        {   // FIXME: magisches 2 ersetzen durch constextpr... oder config
            uint8_t data[config::MAX_IOL_MESSAGE_LENGTH + 2]; ///< Data to send
            struct
            {
                uint8_t MC_data;                                           ///< M-sequence control
                mutable uint8_t CKT_data;                                          ///< Checksum / M-sequence type  // mutable: darf man auch ändern, wenn es eigentlich const ist.
                uint8_t octet_data[config::MAX_IOL_MESSAGE_LENGTH]; ///< Message Content
            };
        };
        uint8_t message_length = 2;    ///< Length of the IO-Link message   // FIXME Name, Längen-Speicherung vereinheitlichen // seit C++14
        // TODO set answer length automaticly with the M-sequence type
        uint8_t answer_length=1;       ///< expected answer length

        //!*****************************************************************************
        //!  \brief calculates the checksum of the CKT
        //!  
        //!         IO-Link Interface and System Specification V1.1.2 Chapter A.1.6
        //!  
        //!*****************************************************************************
        void calculateChecksum() const;
        
        //!*****************************************************************************
        //!  \brief Compresses 8-bit checksum to an 6 bit checksum
        //!  
        //!         IO-Link Interface and System Specification V1.1.2 Chapter A.1.6
        //!  
        //!*****************************************************************************
        static uint8_t compressTo6Checksum(uint8_t checksum8);

    public:
        //!*****************************************************************************
        //!  \brief Construct a new IOLMessage object
        //!  
        //!  
        //!*****************************************************************************
        IOLMessage();

        //!*****************************************************************************
        //!  \brief Destroy the IOLMessage object
        //!  
        //!  
        //!*****************************************************************************
        ~IOLMessage();

        //!*****************************************************************************
        //!  \brief Sets the M-sequence control (MC)
        //!  
        //!         IO-Link Interface and System Specification V1.1.2 Chapter A.1.6
        //!  
        //!  \param rw  R/W (Bit 7)
        //!  
        //!  \param cc  Communication channel (Bit 5 to 6)
        //!  
        //!  \param address Address (Bit 0 to 4)
        //!  
        //!*****************************************************************************
        void setMC(Read_Write rw, Communication_Channel cc, uint8_t address);

        //!*****************************************************************************
        //!  \brief Sets the M-sequence control (MC) manually
        //!  
        //!  
        //!  \param data MC as an uint8_t
        //!  
        //!*****************************************************************************
        void setMC(uint8_t data);

        //!*****************************************************************************
        //!  \brief Sets the M-sequence type (Bit 6 to 7 of CKT)
        //!  
        //!         IO-Link Interface and System Specification V1.1.2 Chapter A.2
        //!  
        //!  \param type M-sequence type
        //!  
        //!*****************************************************************************
        void setMSequenceType(M_Sequence_Type type);

        //!*****************************************************************************
        //!  \brief Get the raw data of the IO-Link message
        //!  
        //!         It calculates the checksum automatically before returning the data.
        //!  
        //!  \param data pointer to the location, where the data should be written
        //!  
        //!  \return length of the message data
        //!  
        //!*****************************************************************************
//        uint8_t getData(const uint8_t **data) const;
        uint8_t getData(uint8_t *data) const;

        //!*****************************************************************************
        //!  \brief Sets the payload of the message
        //!  
        //!  
        //!  \param data pointer to the payload
        //!  
        //!  \param length of the payload
        //!  
        //!*****************************************************************************
        void setOctets(uint8_t *data, uint8_t length);

        //!*****************************************************************************
        //!  \brief Set the expected answer length
        //!  
        //!  
        //!  \param length of the expected answer
        //!  
        //!*****************************************************************************
        void setanswer_length(uint8_t length);

        //!*****************************************************************************
        //!  \brief Get the answer length
        //!  
        //!  
        //!  \return expected length of the answer
        //!  
        //!*****************************************************************************
        uint8_t getanswer_length(void) const {return answer_length;};
    };

} // namespace openiolink

#endif // IOLMESSAGE_HPP_INCLUDED