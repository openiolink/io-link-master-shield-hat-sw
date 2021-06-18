
#include "IOLMaster.hpp"
#include "GenericIOLDevice.hpp"

namespace openiolink
{
    //
    template <template <int IOLPortNr> class IOLMasterPortImplementation>
    IOLMasterClass<IOLMasterPortImplementation>::IOLMasterClass()
        : mPort0{}, mPort1{}, mPort2{}, mPort3{}, // construct the four IO-Link ports, ...
          mAL{},                                  // the Application Layer, ...
                                                  // and the System Management, which needs various parameters:
          mSM{static_cast<IOLMasterPort &>(mPort0), static_cast<IOLMasterPort &>(mPort1),
              static_cast<IOLMasterPort &>(mPort2), static_cast<IOLMasterPort &>(mPort3),
              mAL.getDL(), mAL} //
          {
              // nothing else to do
          };

    //
    template <template <int IOLPortNr> class IOLMasterPortImplementation>
    IOLMasterClass<IOLMasterPortImplementation>::~IOLMasterClass()
    {
    }

    //
    template <template <int IOLPortNr> class IOLMasterPortImplementation>
    void IOLMasterClass<IOLMasterPortImplementation>::wakeUpPort(const int port)
    {
    }

    //
    template <template <int IOLPortNr> class IOLMasterPortImplementation>
    IOLMasterClass<IOLMasterPortImplementation>::getPage1(const int port)
    {
    }

    //
    //bind an IOL-Device to a port of the Master
    //NOTE: check the return value (false = OK, true = ERROR)
    //TODO: registerPortModeHandler(), registerALServiceHandler(), device.setAL()
    //[[nodiscard]]
    bool IOLMasterClass<IOLMasterPortImplementation>::connectDevice(const int portNr, const GenericIOLDevice &device)
    {
    }

} // namespace openiolink
