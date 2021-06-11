
#include "IOLMaster.hpp"
#include "GenericIOLDevice.hpp"
#include "Max14819_Port.hpp"

namespace openiolink
{

    void IOLMaster::wakeUpPort(const int port)
    {
    }

    IOLMaster::getPage1(const int port)
    {
    }

    //bin a IOL-Device to a port of the Master
    //NOTE: check the return value (false = OK, true = ERROR)
    //TODO: registerPortModeHandler(), registerALServiceHandler(), device.setAL()
    //[[nodiscard]]
    bool IOLMaster::connectDevice(const int portNr, const GenericIOLDevice &device)
    {
    }

} // namespace openiolink
