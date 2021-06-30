// TODO file header

// \brief Test class Template MapperChip
//

// manually set the "target platform". This determines which namespace will be
// aliased "platform" by platform.hpp
namespace openiolink
{
#if 1
#define ARDUINO
#undef RASPBERRY
#else
#undef ARDUINO
#define RASPBERRY
#endif
} // namespace openiolink

#include "../../src/board/MapperChip.hpp"
#include "../../src/board/MapperIOLPort.hpp"
#include <iostream>

using namespace openiolink;

int main2(int argc, char *argv[])
{
    std::cout << "Chip 0 SPI Address: " << static_cast<int>(MapperChip<0>::SPIAddress) << std::endl;
    std::cout << "Chip 1 SPI Address: " << static_cast<int>(MapperChip<1>::SPIAddress) << std::endl;

    return 0;
}

/*
//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace openiolink;

TEST_CASE("Test MapperChip (platform independent part)")
{
    SECTION("generic SPI mapping")
    {
        REQUIRE(true);
        REQUIRE(MapperChip<0>::SPIAddress == 0x0);
        REQUIRE(MapperChip<1>::SPIAddress == 0x2);

        REQUIRE(MapperChip<0>::SPINr == 0);
        REQUIRE(MapperChip<1>::SPINr == 1);
    }
}*/
/*
// make sure that the target platform is defined
#if (!defined RASPBERRY && !defined ARDUINO)
static_assert(false, "undefined hardware platform");
#endif

#ifdef ARDUINO
TEST_CASE("Test MapperChip (Arduino specific part)")
{
    SECTION("Arduino specific SPI mapping")
    {
        // TODO check SPI type definition

        REQUIRE(MapperChip<0>::CSPinNr == 10);
        REQUIRE(MapperChip<1>::CSPinNr == 4);
    }
    SECTION("IRQ pin mapping")
    {
        REQUIRE(MapperChip<0>::IRQPinNr == 5);
        REQUIRE(MapperChip<1>::IRQPinNr == 11);
    }
}
#else // RASPBERRY
TEST_CASE("Test MapperChip (Raspberry specific part)")
{
    SECTION("Raspberry specific SPI mapping")
    {
        // TODO check SPI type definition

        REQUIRE(MapperChip<0>::CSPinNr == 31);
        REQUIRE(MapperChip<1>::CSPinNr == 31);
    }

    SECTION("IRQ pin mapping")
    {
        REQUIRE(MapperChip<0>::IRQPinNr == 0);
        REQUIRE(MapperChip<1>::IRQPinNr == 4);
    }
}
#endif

TEST_CASE("Test BackMapperChip")
{
    // The back-mapper must be consistent with the "forward" mapper
    SECTION("IO-Link port numbers")
    {
        // (1) both "calculated" channels must belong to the same chip
        REQUIRE(MapperIOLPort<BackMapperChip<0>::Ch1IOLPortNr>::ChipNr == MapperIOLPort<BackMapperChip<0>::Ch2IOLPortNr>::ChipNr);
        REQUIRE(MapperIOLPort<BackMapperChip<1>::Ch1IOLPortNr>::ChipNr == MapperIOLPort<BackMapperChip<1>::Ch2IOLPortNr>::ChipNr);

        // (2) te "calculated" channels must belong to the correct chip
        REQUIRE(MapperIOLPort<BackMapperChip<0>::Ch2IOLPortNr>::ChipNr == 0);
        REQUIRE(MapperIOLPort<BackMapperChip<1>::Ch2IOLPortNr>::ChipNr == 1);
    }
}
*/
