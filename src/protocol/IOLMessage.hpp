//!*****************************************************************************
//!  \file IOLMessage.hpp
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!  \brief 
//!  \version 0.1
//!  \date 05-11-2020
//!  
//!  \copyright 2019 Bern University of Applied Sciences and Balluff AG
//!  
//!  Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!  
//!      http://www.apache.org/licenses/LICENSE-2.0
//!  
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
#include <cstdlib>

namespace openiolinklibrary
{
    class IOLMessage
    {
    public:
        enum class Read_Write
        {
            Write_access = 0,
            Read_access = 1
        };
        enum class Communication_Channel
        {
            Process = 0,
            Page = 1,
            Diagnosis = 2
        };
        enum class M_Sequence_Type
        {
            Type0 = 0,
            Type1 = 1,
            Type2 = 2
        };

    private:
        union
        {
            u_int8_t data[libraryconfig::MAX_IOL_MESSAGE_LENGTH + 2]; ///< Data to send
            struct
            {
                u_int8_t MC_data;                                           ///< M-sequence control
                u_int8_t CKT_data;                                          ///< Checksum / M-sequence type
                u_int8_t octet_data[libraryconfig::MAX_IOL_MESSAGE_LENGTH]; ///< Message Content
            };
        };
        u_int8_t message_length = 2;
        u_int8_t answer_length=1;

        void calculateChecksum();
        static u_int8_t compressTo6Checksum(u_int8_t checksum8);

    public:
        IOLMessage(/* args */);
        ~IOLMessage();
        void setMC(Read_Write rw, Communication_Channel cc, u_int8_t address);
        void setMSequenceType(M_Sequence_Type type);
        u_int8_t getData(u_int8_t *data);
        void setOctets(u_int8_t *data, u_int8_t length);
        void setanswer_length(u_int8_t length);
        u_int8_t getanswer_length(void){return answer_length;};
    };

} // namespace openiolinklibrary

#endif // IOLMESSAGE_HPP_INCLUDED