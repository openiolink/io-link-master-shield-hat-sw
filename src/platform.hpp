// TODO Dateiheader

#ifndef PLATFORM_HPP
#define PLATFORM_HPP

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
#endif

} // namespace openiolink

#endif