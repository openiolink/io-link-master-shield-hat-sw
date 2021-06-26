//!** TODO DOC
//! 
#ifndef PLATFORM_HPP
#define PLATFORM_HPP

namespace openiolink
{
    // "declare" namespaces to be sure their names are known below
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
#ifdef RASPBERRY
    namespace platform = raspberry;
    constexpr char Platform[] = "Raspberry";
#else
    static_assert(false, "no known platform defined");
#endif
#endif

} // namespace openiolink

#endif // PLATFORM_HPP
