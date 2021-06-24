//#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
// #include "catch.hpp"
#include <Arduino.h>
#include "OpenIOLink.hpp"

// the setup routine runs once when you press reset:
void setup()
{
    // initialize serial communication at 9600 bits per second:
    Serial.begin(115200);

    // print out hello world
    Serial.println("Hello World");

    // Setup to blink the inbuilt LED
#ifdef LED_BUILTIN
    pinMode(LED_BUILTIN, OUTPUT);
#endif
}

// the loop routine runs over and over again forever:
void loop()
{
    namespace iol = openiolink;
    //using iol::IOLMessage;
    //HardwareArduino hwarduino;
    //uint8_t buffer[10];
    //std::shared_ptr<iol::IOLMasterPort> port0 = hwarduino.getPort(0);
    //std::shared_ptr<iol::IOLMasterPort> port1 = hwarduino.getPort(1);
    //std::shared_ptr<iol::IOLMasterPort> port2 = hwarduino.getPort(2);
    //std::shared_ptr<iol::IOLMasterPort> port3 = hwarduino.getPort(3);
    //
    //iol::IOLGenericDevice device;
    //
    //device.setPort(port0);
    //
    //port0->wakeUpRequest();
    //
    //
    //device.readPage1Data();
    //device.printPage1Data();
    while (1)
    {
    }
}

// int main(int argc, char const *argv[])
// {

//     while(1);
//     return 0;
// }
