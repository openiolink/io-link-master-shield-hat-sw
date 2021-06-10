
#include "IOLMasterStackPort.hpp"

namespace openiolink
{

    IOLMasterStackPort::IOLMasterStackPort(ApplicationLayer& AL) : mPL(), mDL(mPL), mAL(&AL), mPortHandler(), mDevice(nullptr)
    {
    }

    IOLMasterStackPort::~IOLMasterStackPort()
    {
    }

} // namespace openiolink
