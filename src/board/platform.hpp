
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
    namespace platform = raspberry;
    constexpr char Platform[] = "Raspberry";

#endif

} // namespace openiolink
