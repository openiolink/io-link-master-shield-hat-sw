
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
    SystemManagement::PortHandler::PortHandler(IOLMasterPort &PL,
                                               DataLinkLayer &DL,
                                               GenericIOLDevice &AL,
                                               SystemManagement &SM)
        : mPL{PL}, mDL{DL}, mAL{AL}, mSM{SM}
    {
    }

    SystemManagement::PortHandler::~PortHandler()
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

    //

    //
    SystemManagement::SystemManagement(IOLMasterPort &PL0, IOLMasterPort &PL1,
                                       IOLMasterPort &PL2, IOLMasterPort &PL3,
                                       DataLinkLayer &DL, GenericIOLDevice &AL)
        : mPortHandler[0]{PL0, DL, AL, *this},
          mPortHandler[1]{PL1, DL, AL, *this},
          mPortHandler[2]{PL2, DL, AL, *this},
          mPortHandler[3]{PL3, DL, AL, *this}
    {
    }

    SystemManagement::~SystemManagement()
    {
    }

} // namespace openiolink
