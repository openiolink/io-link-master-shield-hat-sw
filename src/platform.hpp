
namespace openiolink
{
#ifdef ARDUINO
    namespace platform = arduino;
#else
    namespace platform = raspberry;
#endif

} // namespace openiolink
