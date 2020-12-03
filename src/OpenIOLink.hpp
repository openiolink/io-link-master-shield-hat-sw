#ifndef OPENIOLINK_HPP_INCLUDED
#define OPENIOLINK_HPP_INCLUDED

//! \todo Reorder includes to match dependencies
#ifdef ARDUINO
#include "board/HardwareArduino.hpp"
#else
#include "board/HardwareRaspberry.hpp"
#endif
#include "protocol/IOLMasterPort.hpp"
#include "board/Max14819.hpp"

#include "protocol/IOLGenericDevice.hpp"

#endif // OPENIOLINK_HPP_INCLUDED