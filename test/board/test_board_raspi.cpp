#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
// #include "catch.hpp"

#include "board/HardwareRaspberry.hpp"
int main(int argc, char const *argv[])
{
    HardwareRaspberry hwraspi;
    std::shared_ptr<openiolinklibrary::IOLMasterPort> port0;
    std::shared_ptr<openiolinklibrary::IOLMasterPort> port1;
    std::shared_ptr<openiolinklibrary::IOLMasterPort> port2;
    std::shared_ptr<openiolinklibrary::IOLMasterPort> port3;
    
    port0 = hwraspi.getPort(0);
    port1 = hwraspi.getPort(1);
    port2 = hwraspi.getPort(2);
    port3 = hwraspi.getPort(3);

	port0->wakeUpRequest();
	openiolinklibrary::IOLMessage msg;
	msg.setMC(openiolinklibrary::IOLMessage::Read_Write::Read_access, openiolinklibrary::IOLMessage::Communication_Channel::Page, 0x08);
	msg.setMSequenceType(openiolinklibrary::IOLMessage::M_Sequence_Type::Type0);
	port0->sendIOLData(std::make_shared<openiolinklibrary::IOLMessage>(msg));
    return 0;
}
