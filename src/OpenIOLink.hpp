#ifndef OPENIOLINK_HPP_INCLUDED
#define OPENIOLINK_HPP_INCLUDED

//! \todo Reorder includes to match dependencies
#ifdef ARDUINO
#include "board/HardwareArduino.hpp"
#else
#include "board/HardwareRaspberry.hpp"
#endif
#include "board/IOLMasterPortMax14819.hpp"
#include "board/Max14819.hpp"

#include "protocol/HardwareBase.hpp"
#include "protocol/IOLGenericDevice.hpp"
#include "protocol/IOLink.hpp"
#include "protocol/IOLMasterPort_old.hpp"

#include "sensors/BalluffBni0088.hpp"
#include "sensors/BalluffBus0023.hpp"

#endif // OPENIOLINK_HPP_INCLUDED