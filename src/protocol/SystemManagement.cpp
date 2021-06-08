
#include "SystemManagement.hpp"
#include "IOLMasterPort.hpp"
#include "DataLinkLayer.hpp"
#include "ProxyClasses.hpp"
#include "ApplicationLayer.hpp"

namespace openiolink
{

    //constructor
    SystemManagement::PortHandler::PortHandler(const IOLMasterPort_thisIsPL &PL, const DataLinkLayer &DL, const GenericIOLDevice_thisIsAL &AL)
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
