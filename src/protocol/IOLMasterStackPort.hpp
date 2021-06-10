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
    class IOLMasterStackPort //_Base
    {
    public:
        IOLMasterStackPort();
        ~IOLMasterStackPort();
        inline void stepFSM();
        inline void setDevice(const GenericIOLDevice &device);
        inline GenericIOLDevice *getAL(const int PortNumber) const;
        inline DataLinkLayer *getDL(const int PortNumber) const;
        inline IOLMasterPort *getPL(const int PortNumber) const;

    private:
        IOLMasterPort mPL;
        DataLinkLayer mDL;
        //ApplicationLayer mAL;
        ApplicationLayer* mAL;
        SystemManagement::PortHandler mPortHandler;
        GenericIOLDevice *mDevice; // provided by the user via setDevice()
    };

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************

    // TODO Doc
    inline void IOLMasterStackPort::stepFSM()
    {
        // FIXME call order
        mDL.stepFSM();
        mAL.stepFSM();
        mPortHandler.stepFSM();
    }

    // not necessary anymore, because AL is associated to -Driver, not -Port
    inline void IOLMasterStackPort::setDevice(const GenericIOLDevice &device)
    {
        mDevice = device;
        mAL.setALHandler(static_cast<ALHandler>(device));   // TODO
    }

    inline GenericIOLDevice *IOLMasterStackPort::getAL(const int PortNumber) const
    {
        return &mAL;
    }

    inline DataLinkLayer *IOLMasterStackPort::getDL(const int PortNumber) const
    {
        return &mDL;
    }

    inline IOLMasterPort *IOLMasterStackPort::getPL(const int PortNumber) const
    {
        return &mPL;
    }

} // namespace openiolink
#endif
