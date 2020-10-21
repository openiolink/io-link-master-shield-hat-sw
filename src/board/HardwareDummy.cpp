#include "HardwareDummy.hpp"
#include <ostream>
#include <unistd.h>

namespace openiolinklibrary
{

    HardwareDummy::HardwareDummy(/* args */)
    {
        std::cout << "Init HardwareDummy\n";
        PIN_Dummy testpin = PIN_Dummy("testpin", "output");
        testpin.off();
        testpin.on();
    }

    HardwareDummy::~HardwareDummy()
    {
        std::cout << "Deinit HardwareDummy\n";
    }

    void HardwareDummy::IO_PinMode(std::string name, std::string mode)
    {
        std::cout << "Pinmode: " << name << "=" << mode << "\n";
    }

    void HardwareDummy::IO_Write(std::string name, std::string output)
    {
        std::cout << "Pin set: " << name << "=" << output << "\n";
    }

    void HardwareDummy::wait_for(uint32_t delay_ms)
    {
        //printf("Sleep_in\n");
        usleep(delay_ms * 1000);
        //printf("Sleep_out\n");
    }

    HardwareDummy::PIN_Dummy::PIN_Dummy(std::string name, std::string mode) : pinname(name)
    {
        dummyref->IO_PinMode(name, mode);
    }

    HardwareDummy::PIN_Dummy::~PIN_Dummy()
    {
        dummyref->IO_PinMode(pinname, "in");
    }

    void HardwareDummy::PIN_Dummy::on()
    {
        dummyref->IO_Write(pinname, LOW);
    }

    void HardwareDummy::PIN_Dummy::off()
    {
        dummyref->IO_Write(pinname, HIGH);
    }

} // namespace openiolinklibrary