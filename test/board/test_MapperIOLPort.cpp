// TODO file header

// \brief Test class Template MapperIOLPort
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

#include "../../src/board/MapperIOLPort.hpp"
#include <iostream>

using namespace openiolink;

int main(int argc, char *argv[])
{
    // Check if we can instatiate this template. This won't be possible if
    // the default constructor is marked with "=delete".
    MapperIOLPort<0> mapper0;
    MapperIOLPort<1> mapper1;
    MapperIOLPort<2> mapper2;
    MapperIOLPort<3> mapper3;

    // Template parameter out of range
    MapperIOLPort<4> mapper4;
    //std::cout << mapper4.ChannelNr;          // this must cause a compiler error, because MapperIOLPort<4> has no members (we only defined 0..3)
    //std::cout << MapperIOLPort<-1>::DIPinNr; // this must cause a compiler error, because MapperIOLPort<-1> has no members (we only defined 0..3)

    // A few tests on instances of the mapper (although its not intended to
    // instantiate it).
    static_assert(mapper0.ChannelNr == mapper2.ChannelNr);
    static_assert(mapper2.ChipNr == mapper3.ChipNr);

    // Check all channel number associations
    static_assert(MapperIOLPort<0>::ChannelNr == 0);
    static_assert(MapperIOLPort<1>::ChannelNr == 1);
    static_assert(MapperIOLPort<2>::ChannelNr == 0);
    static_assert(MapperIOLPort<3>::ChannelNr == 1);

    // Check all chip number associations
    static_assert(MapperIOLPort<0>::ChipNr == 0);
    static_assert(MapperIOLPort<1>::ChipNr == 0);
    static_assert(MapperIOLPort<2>::ChipNr == 1);
    static_assert(MapperIOLPort<3>::ChipNr == 1);

    // Check all DI pin number associations. These depend on the platform.
    std::cout << "Platform: " << Platform << std::endl;
    std::cout << "<0> DI pin number = " << MapperIOLPort<0>::DIPinNr << std::endl;
    std::cout << "<1> DI pin number = " << MapperIOLPort<1>::DIPinNr << std::endl;
    std::cout << "<2> DI pin number = " << MapperIOLPort<2>::DIPinNr << std::endl;
    std::cout << "<3> DI pin number = " << MapperIOLPort<3>::DIPinNr << std::endl;

    // TODO you could also print out the other pin numbers: GreenLedPinNr, RedLedPinNr, RxErrPinNr and RxRdyPinNr
    std::cout << "You could also print out the other pin numbers: GreenLedPinNr, RedLedPinNr, RxErrPinNr and RxRdyPinNr." << std::endl;

    return 0;
}
