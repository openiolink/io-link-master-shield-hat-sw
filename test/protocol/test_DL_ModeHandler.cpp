// test for the "Master DL mode handler" inside the Data link Layer

#include <iostream>
#include "catch.hpp"
#include "../protocol/DataLinkLayer.hpp"

TEST_CASE("Master DL mode handler")
{
    DataLinkLayer::MasterDLModeHandler modehandler;
    SECTION("")
    {
        modehandler.setMode(Mode::STARTUP);
        // wakeup request () must be called
        // max14819 does the establish communication sequence
        // TODO: COM and min cycle time should now be available
        
    }
}