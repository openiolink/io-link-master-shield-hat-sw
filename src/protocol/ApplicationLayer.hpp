#ifndef OPENIOLINK_APPLICATIONLAYER_HPP
#define OPENIOLINK_APPLICATIONLAYER_HPP

#include "ErrorCode.hpp"
#include <iostream>
#include "ALServiceObserver.hpp"

namespace openiolink
{
    class DataLinkLayer;
}

namespace openiolink
{

    class ApplicationLayer : public ALServiceSubject
    {
    public:
        //Event at AL, from Specification 8.2.2.11
        //instance EventSource;
        //mode EventMode;
        //type EventType;
        //origin EventOrigin;
        //eventCode EventCode;
        struct Event
        {
        };

        ApplicationLayer();
        ~ApplicationLayer();

        void stepFSM();

        //read On-request Data from a Device connected to a specific port
        //Specification 8.2.2.1
        ErrorCode read(uint8_t &port, const int index, const int subindex, std::uint8_t &data);

        //write On-request Data to a Device connected to a specific port
        //Specification 8.2.2.2
        ErrorCode write(uint8_t &port, const int index, const int subindex, const uint8_t *&data);

        //abort a current AL_Read or AL_Write service on a specific port. Invocation of this service abandons the response to an AL_Read or AL_Write service in progress on the Master.
        //Specification 8.2.2.3
        void abort(const uint8_t &port);

        //The AL_Control service contains the Process Data qualifier status information transmitted to and from the Device application. This service shall be synchronized with AL_GetInput and AL_SetOutput respectively.
        //Specification 8.2.2.12
        void control(const int Port, const TODO_PDQualifier &ControlCode);

        //Specification 8.2.2.11, not implemented
        inline void event(int &port, int &eventCount, Event *&events) const;

        //reads the input data within the Process Data provided by the data 1929 link layer of a Device connected to a specific port.
        //Errors: NO_DATA (DL did not provide Process Data)
        //Specification 8.2.2.4
        inline ErrorCode getInput(int &Port, uint8_t &InputData) const;

        //service AL_NewInput (Specification 8.2.2.5)
        inline void newInput(int &port) const;

        //updates the output data within the Process Data of a Master.
        //Errors: STATE_CONFLICT (Service unavailable within current state)
        //Specifiaction 8.2.2.10
        inline ErrorCode setOutput(int &Port, const uint8_t *&OutputData);

        //service AL_PDCycle (Specification 8.2.2.7)
        inline void pdCycle(int &port) const;

        //TODO call mDL.control()
        //TODO use the results
        inline void handleDLControl();

        inline void handleDLEvent();

        inline void handleDLPDInputTransport();

        inline void handleDLPDCycle();

        inline DataLinkLayer &getDL() const;

    private:
        <DataLinkLayer> mDL;

        //initiates the service AL_Control, when used in direction away from AL
        inline void control() const;

        //initiates the service AL_Event, not implemented
        inline void event() const;

        //initiates the service AL_NewInput
        inline void newInput() const;

        //initiates the service AL_PDCycle
        inline void pdCycle() const;
    };
    //Specification 8.2.2.11, not implemented
    inline void ApplicationLayer::event(int &port, int &eventCount, Event *&events) const
    {
    }

    //reads the input data within the Process Data provided by the data 1929 link layer of a Device connected to a specific port.
    //Errors: NO_DATA (DL did not provide Process Data)
    //Specification 8.2.2.4
    inline ErrorCode ApplicationLayer::getInput(int &Port, uint8_t &InputData) const
    {
    }

    //service AL_NewInput (Specification 8.2.2.5)
    inline void ApplicationLayer::newInput(int &port) const
    {
    }

    //updates the output data within the Process Data of a Master.
    //Errors: STATE_CONFLICT (Service unavailable within current state)
    //Specifiaction 8.2.2.10
    inline ErrorCode ApplicationLayer::setOutput(int &Port, const uint8_t *&OutputData)
    {
    }

    //service AL_PDCycle (Specification 8.2.2.7)
    inline void ApplicationLayer::pdCycle(int &port) const
    {
    }

    //TODO call mDL.control()
    //TODO use the results
    inline void ApplicationLayer::handleDLControl()
    {
    }

    inline void ApplicationLayer::handleDLEvent()
    {
    }

    inline void ApplicationLayer::handleDLPDInputTransport()
    {
    }

    inline void ApplicationLayer::handleDLPDCycle()
    {
    }

    inline DataLinkLayer &ApplicationLayer::getDL() const
    {
    }

    //initiates the service AL_Control, when used in direction away from AL
    inline void ApplicationLayer::control() const
    {
    }

    //initiates the service AL_Event, not implemented
    inline void ApplicationLayer::event() const
    {
    }

    //initiates the service AL_NewInput
    inline void ApplicationLayer::newInput() const
    {
    }

    //initiates the service AL_PDCycle
    inline void ApplicationLayer::pdCycle() const
    {
    }

} // namespace openiolink
#endif
