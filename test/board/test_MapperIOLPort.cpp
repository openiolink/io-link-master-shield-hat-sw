// TODO file header

// \brief Test class Template MapperIOLPort
//

// manually set the "target platform"
namespace openiolink
{
#if 0
#define ARDUINO
#else
#undef ARDUINO
#define RASPI
#endif
} // namespace openiolink

#include "../../src/board/MapperIOLPort.hpp"

namespace openiolink
{
    int main()
    {
        // Check if we can instatiate this template. This won't be possible if
        // the default constructor is marked with "=delete".
        MapperIOLPort<0> mapper0;
        MapperIOLPort<1> mapper1;
        MapperIOLPort<2> mapper2;
        MapperIOLPort<3> mapper3;

        // Template parameter out of range
        MapperIOLPort<4> mapper4;

        // A few tests on instances of the mapper (although its not intended to
        // instantiate it).
        static_assert(mapper0::ChannelNr == mapper2::ChannelNr);
        static_assert(mapper1::ChipNr == mapper2::ChipNr);

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
        std::cout << "<0> DI pin number = " << MapperIOLPort<0>::DIPinNr << std::endl;
        std::cout << "<1> DI pin number = " << MapperIOLPort<1>::DIPinNr << std::endl;
        std::cout << "<2> DI pin number = " << MapperIOLPort<2>::DIPinNr << std::endl;
        std::cout << "<3> DI pin number = " << MapperIOLPort<3>::DIPinNr << std::endl;
    }
} // namespace openiolink
