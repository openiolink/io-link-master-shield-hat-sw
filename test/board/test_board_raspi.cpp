#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
// #include "catch.hpp"

#include "board/HardwareRaspberry.hpp"
#include "protocol/IOLGenericDevice.hpp"

int main(int argc, char const *argv[])
{
    namespace iol = openiolinklibrary;
    using iol::IOLMessage;
    HardwareRaspberry hwraspi;
    uint8_t buffer[10];
    auto port0{hwraspi.getPort(0)};
    auto port1{hwraspi.getPort(1)};
    auto port2{hwraspi.getPort(2)};
    auto port3{hwraspi.getPort(3)};

    auto device{iol::IOLGenericDevice()};

    device.setPort(port0);

	port0->wakeUpRequest();
    

    device.readPage1Data();
    device.printPage1Data();
    return 0;
}
