#ifndef OPENIOLINK_ALSERVICEOBSERVER_HPP
#define OPENIOLINK_ALSERVICEOBSERVER_HPP

namespace openiolink
{
    class PortModeHandler;
}

namespace openiolink
{

    class ALServiceHandler
    {
    public:
        inline virtual void handleALControl() = 0;

        //not implemented because not supported yet
        //TODO make abstract to force implementation
        inline virtual handleALEvent();

        //not implemented because not supported yet
        //TODO make abstract to force implementation
        inline virtual void handleALNewInput();

        inline virtual void handleALPDCycle();
    };
    //not implemented because not supported yet
    //TODO make abstract to force implementation
    inline ALServiceHandler::handleALEvent()
    {
    }

    //not implemented because not supported yet
    //TODO make abstract to force implementation
    inline void ALServiceHandler::handleALNewInput()
    {
    }

    inline void ALServiceHandler::handleALPDCycle()
    {
    }

    class ALServiceSubject
    {
    public:
        inline void registerObserver(const PortModeHandler &Observer);

    protected:
        inline void notifyALControl(const int port) const;

        inline void notifyALEvent(const int port) const;

        inline void notifyALNewInput(const int port) const;

        inline void notifyALPDCycle(const int port) const;

    private:
        //the "observers" are the device classes, one for each port
        <ALServiceHandler *> mDevice;
    };
    inline void ALServiceSubject::registerObserver(const PortModeHandler &Observer)
    {
    }

    inline void ALServiceSubject::notifyALControl(const int port) const
    {
    }

    inline void ALServiceSubject::notifyALEvent(const int port) const
    {
    }

    inline void ALServiceSubject::notifyALNewInput(const int port) const
    {
    }

    inline void ALServiceSubject::notifyALPDCycle(const int port) const
    {
    }

} // namespace openiolink
#endif
