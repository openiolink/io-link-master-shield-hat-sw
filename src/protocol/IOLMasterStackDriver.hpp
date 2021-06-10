#ifndef OPENIOLINK_IOLMASTERSTACKDRIVER_HPP
#define OPENIOLINK_IOLMASTERSTACKDRIVER_HPP

#include "DataLinkLayer.hpp"
#include "IOLMasterPort.hpp"
#include "OpeniolinkShieldHat.hpp"
#include "ApplicationLayer.hpp"
#include "SystemManagement.hpp"

namespace openiolink
{
    class GenericIOLDevice;
    class PortModeHandler;
}

namespace openiolink
{

    class IOLMasterStackDriver
    {
    public:
        IOLMasterStackDriver();
        ~IOLMasterStackDriver();
        inline stepFSM();
        inline void registerPortEventHandler(const int Port, const PortModeHandler &Handler);
        setDevice(const int portNr, const GenericIOLDevice &device);

    private:
        SystemManagement mSM;
        <IOLMasterStackPort> mPort;
    };

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************

    inline IOLMasterStackDriver::stepFSM()
    {
    }

    //call mSM.registerObserver(..)
    inline void IOLMasterStackDriver::registerPortEventHandler(const int Port, const PortModeHandler &Handler)
    {
    }

} // namespace openiolink
#endif
