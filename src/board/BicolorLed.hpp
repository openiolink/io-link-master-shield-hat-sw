#ifndef OPENIOLINK_BICOLORLED_HPP
#define OPENIOLINK_BICOLORLED_HPP

// DRAFT file witch class BicolorLed

#include "Pin_Arduino.hpp"
#include "Pin_Raspberry.hpp"
#include "../platform.hpp"
#include "MapperIOLPort.hpp"

namespace openiolink
{

    // e.g. for port activity and/or port state
    // to be used as type (no object)
    template <int IOLPortNr>
    class BicolorLed
    {
    public:
        //
        enum class LedColor
        {
            OFF,
            RED,
            GREEN,
            ORANGE
        };

        static inline void setColor(const LedColor Color);

    private:
        typedef HW::OutputPin<MapperIOLPort<IOLPortNr>::GreenLedPinNr> GreenLedPin;
        typedef HW::OutputPin<MapperIOLPort<IOLPortNr>::RedLedPinNr> RedLedPin;
    };

    template <int IOLPortNr>
    inline void BicolorLed<IOLPortNr>::setColor(const LedColor Color)
    {
        switch (Color)
        {
        case BicolorLed<IOLPortNr>::LedColor::RED:
            GreenLedPin::setLow();
            RedLedPin::setHigh();
            break;
        case LedColor::GREEN:
            GreenLedPin::setHign();
            RedLedPin::setLow();
            break;
        case LedColor::ORANGE:
            GreenLedPin::setHigh();
            RedLedPin::setHigh();
            break;
        case LedColor::OFF:
            //[[falltrough]]
        default:
            GreenLedPin::setLow();
            RedLedPin::setLow();
            break;
        }
    }

} // namespace openiolink
#endif
