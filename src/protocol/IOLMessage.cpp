#include "IOLMessage.hpp"

namespace openiolinklibrary
{
    IOLMessage::IOLMessage()
    {
    }

    IOLMessage::~IOLMessage()
    {
    }

    void IOLMessage::setMC(Read_Write rw, Communication_Channel cc, u_int8_t address)
    {
        MC_data = ((static_cast<u_int8_t>(rw) << 7) | (static_cast<u_int8_t>(cc) << 5) | address);
    }

    u_int8_t IOLMessage::getData(u_int8_t *data)
    {
        this->calculateChecksum();
        for (u_int8_t i = 0; i < openiolinklibrary::libraryconfig::MAX_IOL_MESSAGE_LENGTH + 2; i++)
        {
            data[i] = this->data[i];
        }

        return this->message_length;
    }

    void IOLMessage::setOctets(u_int8_t *data, u_int8_t length)
    {
        for (size_t i = 0; i < length; i++)
        {
            this->octet_data[i] = data[i];
        }
        this->message_length = length + 2;
    }

    void IOLMessage::calculateChecksum()
    {
        u_int8_t checksum = 0x52;
        this->CKT_data &= 0xC0;
        for (u_int8_t i = 0; i < (message_length); i++)
        { // Berechnung inkl MC und CKT
            checksum ^= this->data[i];
        }
        this->CKT_data |= compressTo6Checksum(checksum);
    }

    u_int8_t IOLMessage::compressTo6Checksum(u_int8_t checksum8)
    {
        u_int8_t checksum = 0;
        for (u_int8_t i = 0; i < 4; i++)
        {
            checksum = checksum | ((((checksum8 >> (i * 2)) % 2) ^ (((checksum8 >> (i * 2 + 1)) % 2))) << i);
        }
        checksum = checksum | ((((checksum8 >> 7) % 2) ^ ((checksum8 >> 5) % 2) ^ ((checksum8 >> 3) % 2) ^ ((checksum8 >> 1) % 2)) << 5);
        checksum = checksum | ((((checksum8 >> 6) % 2) ^ ((checksum8 >> 4) % 2) ^ ((checksum8 >> 2) % 2) ^ ((checksum8 >> 0) % 2)) << 4);

        return checksum;
    }

    void IOLMessage::setMSequenceType(M_Sequence_Type type)
    {
        this->CKT_data = static_cast<u_int8_t>(type) << 6;
    }

    void IOLMessage::setanswer_length(u_int8_t length)
    {
        // todo check if length is too big
        this->answer_length = length + 1; // CKS uses size 1
    }

    u_int8_t IOLMessage::setCKS(u_int8_t data)
    {
        this->CKT_data = data;
        this->calculateChecksum();
        if (data == this->CKT_data) // checksum is correct
        {
            return 0;
        }
        else // checksum is not correct
        {
            this->CKT_data = data;
            return 1;
        }
        
        
    }
} // namespace openiolinklibrary
