#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
// #include "catch.hpp"
#include "board/HardwareArduino.hpp"
#include "protocol/IOLGenericDevice.hpp"


int main(int argc, char const *argv[])
{
    namespace iol = openiolinklibrary;
    using iol::IOLMessage;
    HardwareArduino hwarduino;
    uint8_t buffer[10];
    return 0;
}
