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
}

namespace openiolink
{

    //owns all objects of the Master Stack for one IO-Link-Port
    class IOLMasterStackPort
    {
    public:
        inline void stepFSM();
        inline setDevice(const GenericIOLDevice &device);
        inline GenericIOLDevice *getAL(const int PortNumber) const;
        inline DataLinkLayer *getDL(const int PortNumber) const;
        inline IOLMasterPort_thisIsPL *getPL(const int PortNumber) const;

    private:
        PCB::OpeniolinkShieldHat mBoard; // the shield/hat
        IOLMasterPort_thisIsPL mPL;
        DataLinkLayer mDL;
        ApplicationLayer mAL;
        SystemManagement::PortHandler mPortHandler;
        GenericIOLDevice *mDevice; // provided by the user via setDevice()
    };

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************

    inline void IOLMasterStackPort::stepFSM()
    {
    }

    inline IOLMasterStackPort::setDevice(const GenericIOLDevice &device)
    {
    }

    inline GenericIOLDevice *IOLMasterStackPort::getAL(const int PortNumber) const
    {
    }

    inline DataLinkLayer *IOLMasterStackPort::getDL(const int PortNumber) const
    {
    }

    inline IOLMasterPort_thisIsPL *IOLMasterStackPort::getPL(const int PortNumber) const
    {
    }

} // namespace openiolink
#endif
