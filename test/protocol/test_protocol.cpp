#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "protocol/IOLMasterPort.hpp"
#include "protocol/IOLMessage.hpp"

using namespace openiolink;

IOLMasterPort port;

TEST_CASE("Switch Modes", "[IOLMasterPort]")
{
    SECTION("set to IOLink")
    {
        port.setMode(IOLMasterPort::Mode::IOLink);
        REQUIRE(port.getMode() ==IOLMasterPort:: Mode::IOLink);
        REQUIRE(port.getState() == IOLMasterPort::State::IOLink_disconnected);
    }

    SECTION("set to SIO")
    {
        port.setMode(IOLMasterPort::Mode::SIO);
        REQUIRE(port.getMode() == IOLMasterPort::Mode::SIO);
        REQUIRE(port.getState() == IOLMasterPort::State::SIO);
    }

    SECTION("set to PowerDown")
    {
        port.setMode(IOLMasterPort::Mode::PowerDown);
        REQUIRE(port.getMode() == IOLMasterPort::Mode::PowerDown);
        REQUIRE(port.getState() == IOLMasterPort::State::PowerDown);
    }
}

TEST_CASE("Test the Builds of IOLinkMessages", "[IOLinkMessage]")
{
    SECTION("init Message")
    {
        IOLMessage message;
        union 
        {
            uint8_t data[config::MAX_IOL_MESSAGE_LENGTH + 2]; ///< Data to send
            struct {
                uint8_t MC_data;                            ///< M-sequence control
                uint8_t CKT_data;                           ///< Checksum / M-sequence type
                uint8_t octet_data[config::MAX_IOL_MESSAGE_LENGTH]; ///< Message Content
            };
        }message_data;

        message.setMC(IOLMessage::Read_Write::Read_access, IOLMessage::Communication_Channel::Page, 0x02); // check for MasterCycleTime
        message.setMSequenceType(IOLMessage::M_Sequence_Type::Type0);
        message.setOctets(0, 0);
        CHECK(message.getData(message_data.data) == 2); // the length of a 0 message has to be 2
        CHECK(message_data.MC_data == 0xA2);
        CHECK(message_data.CKT_data == 0x00);
        CHECK(message_data.data[0] == 0xA2 );
        CHECK(message_data.data[1] == 0x00 );

        message.setMSequenceType(IOLMessage::M_Sequence_Type::Type1);
        CHECK(message.getData(message_data.data) == 2); // the length of a 0 message has to be 2
        CHECK(message_data.CKT_data == 0x58);        
        CHECK(message_data.data[0] == 0xA2 );
        CHECK(message_data.data[1] == 0x58 );

        message.setMC(IOLMessage::Read_Write::Read_access, IOLMessage::Communication_Channel::Page, 0x05); // check for ProcessDataIn
        message.setMSequenceType(IOLMessage::M_Sequence_Type::Type0);
        CHECK(message.getData(message_data.data) == 2); // the length of a 0 message has to be 2        
        CHECK(message_data.data[0] == 0xA5 );
        CHECK(message_data.data[1] == 0x22 );

        message.setMC(IOLMessage::Read_Write::Read_access, IOLMessage::Communication_Channel::Page, 0x08); // check for VendorID
        message.setMSequenceType(IOLMessage::M_Sequence_Type::Type0);
        CHECK(message.getData(message_data.data) == 2); // the length of a 0 message has to be 2        
        CHECK(message_data.data[0] == 0xA8 );
        CHECK(message_data.data[1] == 0x03 );

        message.setMC(IOLMessage::Read_Write::Write_access, IOLMessage::Communication_Channel::Page, 0x00); // send Master Command
        message.setMSequenceType(IOLMessage::M_Sequence_Type::Type0);
        message_data.data[0] = 0x95;
        message.setOctets(message_data.data, 1);
        CHECK(message.getData(message_data.data) == 3); // the length of a 1 message has to be 3
        CHECK(message_data.data[0] == 0x20 );
        CHECK(message_data.data[1] == 0x36 );
        CHECK(message_data.data[2] == 0x95 );
    }
}