#ifndef OPENIOLINK_IOLMASTER_HPP
#define OPENIOLINK_IOLMASTER_HPP

#include "SystemManagement.hpp"
#include "ApplicationLayer.hpp"
#include "OpeniolinkShieldHat.hpp"

#include "Max14819_Port.hpp" // TODO remove (see end of this file)

//#include "GenericIOLDevice.hpp"
namespace openiolink
{
    class GenericIOLDevice;
}

namespace openiolink
{
    //!*************************************************************************
    //! \brief  class template for class IOLMaster
    //!
    //! \note   The template template parameter 'IOLMasterPortImplementation'
    //!         takes the typename of a class template which implements (i.e.
    //!         inherits from) the class IOLMasterPort.
    //!
    //! \note   There is an alias defintion called 'IOLMaster' which the user
    //!         of the library can use to instantiate this class.
    //!
    //!*************************************************************************
    template <template <int IOLPortNr> class IOLMasterPortImplementation>
    class IOLMasterClass
    {
    public:
        IOLMasterClass();
        ~IOLMasterClass();
        inline void stepFSM();
        void wakeUpPort(const int port);
        void getPage1(const int port);
        bool connectDevice(const int portNr, const GenericIOLDevice &device); //[[nodiscard]]

    private:
        // TODO make configurable how many and which ports are used
        IOLMasterPortImplementation<0> mPort0;
        IOLMasterPortImplementation<1> mPort1;
        IOLMasterPortImplementation<2> mPort2;
        IOLMasterPortImplementation<3> mPort3;

        ApplicationLayer mAL;
        SystemManagement mSM;

        OpeniolinkShieldHat mPCB;

        // provided by user via connectDevice()
        GenericIOLDevice *mDevice[4] = {nullptr, nullptr, nullptr, nullptr};
    };

    inline IOLMasterClass<IOLMasterPortImplementation>::stepFSM()
    {
        mAL.stepFSM();
        mSM.stepFSM();
    }

    //!*************************************************************************
    //! \brief  This class represents the IO-Link Master.
    //!
    //! \note   The user application must instantiate this class once per
    //!         Master in use.
    //!
    //! \todo   Max14819_Port von config-header beziehen, nicht hardcodiert hier.
    //!
    //!*************************************************************************
    using IOLMaster = IOLMasterClass<Max14819_Port>;
    //typedef IOLMasterClass<Max14819_Port> IOLMaster; // this would say the same

} // namespace openiolink
#endif
