
namespace openiolink
{
    // "declare" namespaces to be sure their names ar known below
    namespace arduino
    {
    };
    namespace raspberry
    {
    };

// Select the platform dependent code by aliasing the appropriate namespace with "platform"
#ifdef ARDUINO
    namespace platform = arduino;
    constexpr char Platform[] = "Arduino";
#else
    namespace platform = raspberry;
    constexpr char Platform[] = "Raspberry";

// FIXME do this via CMake
#include "raspberry/HardwareRaspberry.hpp"
#include "raspberry/MapperChip_Raspberry.hpp"
#include "raspberry/MapperIOLPort_Raspberry.hpp"
#include "raspberry/Pin_Raspberry.hpp"
#include "raspberry/SpiRaspberry.hpp"
#endif

} // namespace openiolink
