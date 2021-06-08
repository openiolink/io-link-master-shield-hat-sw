
#include "ApplicationLayer.hpp"
#include "DataLinkLayer.hpp"

namespace openiolink
{

    ApplicationLayer::ApplicationLayer()
    {
    }

    //read On-request Data from a Device connected to a specific port
    //Specification 8.2.2.1
    ErrorCode ApplicationLayer::read(uint8_t &port, const int index, const int subindex, std::uint8_t &data)
    {
    }

    //write On-request Data to a Device connected to a specific port
    //Specification 8.2.2.2
    ErrorCode ApplicationLayer::write(uint8_t &port, const int index, const int subindex, const uint8_t *data)
    {
    }

    //abort a current AL_Read or AL_Write service on a specific port. Invocation of this service abandons the response to an AL_Read or AL_Write service in progress on the Master.
    //Specification 8.2.2.3
    void ApplicationLayer::abort(const uint8_t &port)
    {
    }

    //The AL_Control service contains the Process Data qualifier status information transmitted to and from the Device application. This service shall be synchronized with AL_GetInput and AL_SetOutput respectively.
    //Specification 8.2.2.12
    void ApplicationLayer::control(const int Port, const TODO_PDQualifier &ControlCode)
    {
    }

} // namespace openiolink
