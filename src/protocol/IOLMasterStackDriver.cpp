
#include "IOLMasterStackDriver.hpp"
#include "GenericIOLDevice.hpp"

namespace openiolink
{

    IOLMasterStackDriver::IOLMasterStackDriver()
    {
    }

    IOLMasterStackDriver::~IOLMasterStackDriver()
    {
    }

    IOLMasterStackDriver::setDevice(const int portNr, const GenericIOLDevice &device)
    {
        // TODO tell new Device (ALHandler) to AL
        // TODO tell Device who AL is (Pointer)
    }

} // namespace openiolink
