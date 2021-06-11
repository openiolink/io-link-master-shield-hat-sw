#ifndef OPENIOLINK_PORTMODEOBSERVER_HPP
#define OPENIOLINK_PORTMODEOBSERVER_HPP

#include "SM_typedefs.hpp"

namespace openiolink
{

    class PortModeHandler
    {
    public:
        virtual void receiveNewPortMode(const int Port, PortModes Mode) = 0;
    };
    class PortModeSubject
    {
    public:
        //"registerObserver()"
        inline void registerPortModeHandler(const PortModeHandler &portModeHandler);

    protected:
        //"notify()"
        inline void sendPortMode(const int Port, PortModes NewMode) const;

    private:
        //only one handler ("observer") allowed
        PortModeHandler *mHandler;
    };
    //"registerObserver()"
    inline void PortModeSubject::registerPortModeHandler(const PortModeHandler &portModeHandler)
    {
    }

    //"notify()"
    inline void PortModeSubject::sendPortMode(const int Port, PortModes NewMode) const
    {
    }

} // namespace openiolink
#endif
