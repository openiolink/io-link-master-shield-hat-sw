#ifndef OPENIOLINK_SYSTEMMANAGEMENT_HPP
#define OPENIOLINK_SYSTEMMANAGEMENT_HPP

#include "PortModeObserver.hpp"
#include "ErrorCode.hpp"
#include "SM_typedefs.hpp"

namespace openiolink
{
    class IOLMasterPort;
    class DataLinkLayer;
    class GenericIOLDevice;
    class ApplicationLayer;
    struct SMRequestedConfig;
    struct SMRealConfig;
    class PortModeHandler;
}

namespace openiolink
{

    class SystemManagement
    {
    public:
        //see Spec. Table 81
        enum class TargetModes
        {
            INACTIVE,
            DI,
            DO,
            CFGCOM,
            AUTOCOM
        };

        //two-digit version number of the SDCI protocol currently used.
        //  Bits 0 to 3: MinorRev
        //  Bits 4 to 7: MajorRev
        enum class RevisionIDs
        {
            V1_1 = 0x11,
            V1_0 = 0x10
        };

        //IL
        //Spec. Table 80
        enum class InspectionLevels
        {
            NO_CHECK,
            TYPE_COMP /*, IDENTICAL*/
        };

        //
        enum class Baudrates
        {
            COM1,
            COM2,
            COM3
        };

        //Data type for SM.setPortConfig()
        //This Record contains the configured port and Device parameters of a Master port. (Spec. 9.2.2.2)
        ///* ConfiguredSerialNumber (CSN) not implemented yet */
        struct SMRequestedConfig
        {
            //This parameter contains the port number
            uint8_t PortNumber;

            //This parameter contains the requested cycle time for the OPERATE mode.
            //Permitted values:
            //	0 (FreeRunning)
            //	Time (see Table B.3)
            uint8_t ConfiguredCycleTime;

            //This parameter indicates the requested operational mode of the port.
            TargetModes TargetMode;

            //CRID
            //Data length: 1 octet for the protocol version (see B.1.5)
            RevisionIDs ConfiguredRevisionID;

            InspectionLevels InspectionLevel;

            //"CVID"
            //Data length: 2 octets
            uint16_t ConfiguredVendorID;

            //"CDID"
            //Data length: 3 octets
            uint24_t ConfiguredDeviceID;

            //"CFID"
            //Data length: 2 octets
            uint16_t ConfiguredFunctionID;
        };

        //Data type for SM.getPortConfig()
        //This Record contains the configured port and Device parameters of a Master port. (Spec. 9.2.2.3)
        ///* RealSerialNumber (RSN) not implemented yet */
        struct SMRealConfig
        {
            uint8_t PortNumber;

            //This parameter indicates the operational mode.
            TargetModes TargetMode;

            //This parameter indicates the actual transmission rate.
            Baudrates RealBaudrate;

            //This parameter contains the real (actual) cycle time.
            uint8_t RealCycleTime;

            //"RRID"
            //Data length: 1 octet for the protocol version (see B.1.5)
            RevisionIDs RealRevisionID;

            //"RVID"
            //Data length: 2 octets
            uint16_t RealVendorID;

            //"RDID"
            //Data length: 3 octets
            uint24_t RealDeviceID;

            //Data length: 2 octets
            uint16_t RealFunctionID;
        };

        //(Spec 9.2.2.4)
        enum class PortModes
        {
            INACTIVE,       // Communication disabled, no DI, no DO
            DI,             // Port in digital input mode (SIO)
            DO,             // Port in digital output mode (SIO)
            COMREADY,       // Communication established and inspection successful
            SM_OPERATE,     // Port is ready to exchange Process Data
            COMLOST,        // Communication failed, new wake-up procedure required
            REVISION_FAULT, // Incompatible protocol revision
            COMP_FAULT,     // Incompatible Device or Legacy-Device according to the Inspection Level
            SERNUM_FAULT,   // Mismatching SerialNumber according to the InspectionLevel
            CYCTIME_FAULT   // Device does not support the configured cycle time
        };

    protected:
        class PortHandler : public PortModeSubject
        {
        public:
            //constructor
            //TODO call mDL = mAL->getDL();
            //TODO call mDL.setPortHandler(this);
            PortHandler(const IOLMasterPort &PL, const DataLinkLayer &DL, const GenericIOLDevice &AL);
            void stepFSM();
            setPortConfig(); // TODO Interface wie bei äusserer Klasse
            getPortConfig(); // TODO Interface wie bei äusserer Klasse
            ErrorCode operate(int &PortNumber);
            inline void portMode(int &PortNumber, PortModes &Mode);
            inline void handleDLMode();

        private:
            SystemManagement *mSM;
            ApplicationLayer *mAL;       // PortHandler (SM) uses the service Read of the Application Layer (AL)
            DataLinkLayer *mDL;          // PortHandler (SM) needs some services of the DL
            IOLMasterPort *mPL; // PortHandler (SM) uses the service SetMode of the Physical Layer (PL)
            inline void portMode() const;
        };

    public:
        inline void stepFSM();
        inline ErrorCode setPortConfig(int &PortNumber, const SMRequestedConfig &ParameterList);
        inline ErrorCode getPortConfig(const int PortNumber, SMRealConfig &ParameterList);
        inline ErrorCode operate(int &PortNumber);
        inline void registerObserver(const int Port, const PortModeHandler &Observer);

    private:
        PortHandler mPortHandler[4];
    };

    //**************************************************************************
    // Implementation of the inline Methods
    //**************************************************************************

    //The SM_PortMode service is used to indicate changes or faults of the local communication mode. These shall be reported to the Master application.
    //Spec. 9.2.2.4
    inline void SystemManagement::PortHandler::portMode(int &PortNumber, PortModes &Mode)
    {
    }

    inline void SystemManagement::PortHandler::handleDLMode()
    {
    }

    //TODO call notifyObserver()
    inline void SystemManagement::PortHandler::portMode() const
    {
    }

    //TODO call stepFSM() of all PortHandlers
    inline void SystemManagement::stepFSM()
    {
    }

    //The SM_SetPortConfig service is used to set up the requested Device configuration.
    //Spec. 9.2.2.2
    inline ErrorCode SystemManagement::setPortConfig(int &PortNumber, const SMRequestedConfig &ParameterList)
    {
    }

    //The SM_GetPortConfig service is used to acquire the real (actual) Device configuration.
    inline ErrorCode SystemManagement::getPortConfig(const int PortNumber, SMRealConfig &ParameterList)
    {
    }

    //The SM_Operate service prompts System Management to calculate the MasterCycleTime for the ports if the service is acknowledged positively with Result (+). This service is effective at the indicated port.
    //Spec. 9.2.2.5
    inline ErrorCode SystemManagement::operate(int &PortNumber)
    {
    }

    inline void SystemManagement::registerObserver(const int Port, const PortModeHandler &Observer)
    {
    }

} // namespace openiolink
#endif
