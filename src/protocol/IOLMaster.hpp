#ifndef OPENIOLINK_IOLMASTER_HPP
#define OPENIOLINK_IOLMASTER_HPP

#include "SystemManagement.hpp"
#include "ApplicationLayer.hpp"

namespace openiolink
{
    class GenericIOLDevice;
}
namespace PCB
{
    template <int IOLPortNr, int ChipNr>
    class Max14819_Port;
}

namespace openiolink
{

    class IOLMaster
    {
    public:
        inline stepFSM();

        void wakeUpPort(const int port);

        getPage1(const int port);

        //bin a IOL-Device to a port of the Master
        //NOTE: check the return value (false = OK, true = ERROR)
        //TODO: registerPortModeHandler(), registerALServiceHandler(), device.setAL()
        //[[nodiscard]]
        bool connectDevice(const int portNr, const GenericIOLDevice &device);

    private:
        SystemManagement mSM;

        ApplicationLayer mAL;

        <PCB::Max14819_Port<IOLPortNr, ChipNr>> mPL;

        //provided by user via connectDevice()
        <GenericIOLDevice *> mDevice;
    };
    inline IOLMaster::stepFSM()
    {
    }

} // namespace openiolink
#endif
