#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "protocol/IOLMasterPort.hpp"

using namespace openiolinklibrary;

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