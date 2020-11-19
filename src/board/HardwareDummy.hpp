#ifndef HARDWAREDUMMY_HPP_INCLUDED
#define HARDWAREDUMMY_HPP_INCLUDED

#include "protocol/HardwareBase.hpp"
#include "board/HardwareDummyChip.hpp"
#include <iostream>
namespace openiolinklibrary
{

    class HardwareDummy
    {
    private:
        /* data */
    public:
        HardwareDummy(/* args */);
        ~HardwareDummy();

        void wait_for(uint32_t delay_ms);

        class PIN_Dummy : public IOLinkDummyChip::PIN
        {
        private:
            std::string pinname = "undef";
            std::string LOW = "LOW";
            std::string HIGH = "HIGH";

        public:
            PIN_Dummy(){};
            PIN_Dummy(std::string name, std::string mode);
            ~PIN_Dummy();
            void on();
            void off();
            void IO_PinMode(std::string mode);
            void IO_Write(std::string output);
        };

        PIN_Dummy testpin = PIN_Dummy("testpin", "output");
    };

} // namespace openiolinklibrary

#endif // HARDWAREDUMMY_HPP_INCLUDED