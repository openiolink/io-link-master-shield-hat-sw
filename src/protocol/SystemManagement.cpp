
#include "SystemManagement.hpp"
#include "IOLMasterPort.hpp"
#include "DataLinkLayer.hpp"
#include "GenericIOLDevice.hpp"
#include "ApplicationLayer.hpp"

namespace openiolink
{

    //constructor
    //TODO call mDL = mAL->getDL();
    //TODO call mDL.setPortHandler(this);
    SystemManagement::PortHandler::PortHandler(const IOLMasterPort &PL, const DataLinkLayer &DL, const GenericIOLDevice &AL)
    {
    }

    void SystemManagement::PortHandler::stepFSM()
    {
    }

    //TODO Interface wie bei äusserer Klasse
    SystemManagement::PortHandler::setPortConfig()
    {
    }

    //TODO Interface wie bei äusserer Klasse
    SystemManagement::PortHandler::getPortConfig()
    {
    }

    //The SM_Operate service prompts System Management to calculate the MasterCycleTime for the ports if the service is acknowledged positively with Result (+). This service is effective at the indicated port.
    //Spec. 9.2.2.5
    ErrorCode SystemManagement::PortHandler::operate(int &PortNumber)
    {
    }

} // namespace openiolink
