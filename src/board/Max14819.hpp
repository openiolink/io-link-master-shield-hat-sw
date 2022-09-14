
//!*****************************************************************************
//!  \file      Max14819.h
//!*****************************************************************************
//!
//!  \brief		max14819 driver specific layer
//!
//!  \author    Pascal Frei (freip2)
//!
//!  \date      2019-06-27
//!
//!*****************************************************************************
//!
//!	 Copyright 2019 Bern University of Applied Sciences and Balluff AG
//!
//!	 Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!
//!	     http://www.apache.org/licenses/LICENSE-2.0
//!
//!	 Unless required by applicable law or agreed to in writing, software
//!	 distributed under the License is distributed on an "AS IS" BASIS,
//!	 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!	 See the License for the specific language governing permissions and
//!	 limitations under the License.
//!	
//!*****************************************************************************
#ifndef MAX14819_HPP_INCLUDED
#define MAX14819_HPP_INCLUDED



//!**** Header-Files **********************************************************
#include "protocol/HardwareBase.hpp"
//!**** Macros ****************************************************************
// Error define
constexpr uint8_t ERROR             = 1u;
constexpr uint8_t SUCCESS           = 0u;


namespace max14819 {
	// MAX14819 driver enum
    enum DriverSelect{
        DRIVER01,
        DRIVER23
    };
    // MAX14819 port enum
    enum PortSelect{
        PORTA,
        PORTB
    };

    // Port allocation for max14819
    constexpr PortSelect PORT0PORT      = PORTA;
    constexpr PortSelect PORT1PORT      = PORTB;
    constexpr PortSelect PORT2PORT      = PORTA;
    constexpr PortSelect PORT3PORT      = PORTB;

	// LED state defines, low active
	constexpr uint8_t LED_ON            = 0u;
	constexpr uint8_t LED_OFF           = 1u;

	// MAX14819 DI Init defines
	constexpr uint8_t CURRENT_SOURCE    = 0x02u;
	constexpr uint8_t CURRENT_SINK      = 0x01u;
	constexpr uint8_t CURRENT_DISABLE   = 0x00u;
	constexpr uint8_t THRSLD_TYPE1      = 1u;        // Different Threshold Levels, see MAX14819 Datasheet, p. 5
	constexpr uint8_t THRSLD_TYPE2      = 0u;        // Different Threshold Levels, see MAX14819 Datasheet, p. 5
	constexpr uint8_t FILTER_EN         = 0x08u;     // Glich filter enable
	constexpr uint8_t FILTER_DIS        = 0x00u;     // Glich filter disable

	// Timing constexprants for Max14819
	constexpr uint32_t INIT_POWER_OFF_DELAY	= 1000u;	// Delay in ms for disable duration of sensor power when startup
	constexpr uint32_t INIT_BOOTUP_DELAY    = 300u;	// Delay after switch-to-operational-command
	constexpr uint32_t INIT_WURQ_TIMEOUT    = 80u;   // Timeout in ms for abort WURQ request (2x retry after 10ms, 3x tries a 20ms)

	// IO-Link Master Shield Max14819 Address
	constexpr uint8_t port01Address  = 0;
	constexpr uint8_t port23Address  = 2;

	// Max14819 Register defines
	constexpr uint8_t TxRxDataA     = 0x00u;
	constexpr uint8_t TxRxDataB     = 0x01u;

	constexpr uint8_t Interrupt     = 0x02u;
	constexpr uint8_t StatusInt     = 0x80u;
	constexpr uint8_t WURQInt       = 0x40u;
	constexpr uint8_t TxErrorB      = 0x20u;
	constexpr uint8_t TxErrorA      = 0x10u;
	constexpr uint8_t RxErrorB      = 0x08u;
	constexpr uint8_t RxErrorA    	= 0x04u;
	constexpr uint8_t RxDataRdyB    = 0x02u;
	constexpr uint8_t RxDataRdyA   	= 0x01u;

	constexpr uint8_t InterruptEn   = 0x03u;
	constexpr uint8_t StatusIntEn   = 0x80u;
	constexpr uint8_t WURQIntEn     = 0x40u;
	constexpr uint8_t TxErrIntEnB   = 0x20u;
	constexpr uint8_t TxErrIntEnA   = 0x10u;
	constexpr uint8_t RxErrIntEnB   = 0x08u;
	constexpr uint8_t RxErrIntEnA   = 0x04u;
	constexpr uint8_t RxDaRdyIntEnB = 0x02u;
	constexpr uint8_t RxDaRdyIntEnA = 0x01u;

	constexpr uint8_t RxFIFOLvlA 	= 0x04u;
	constexpr uint8_t RxFIFOLvlB 	= 0x05u;

	constexpr uint8_t CQCtrlA       = 0x06u;
	constexpr uint8_t CQCtrlB       = 0x07u;
	constexpr uint8_t ComRt1        = 0x80u;
	constexpr uint8_t ComRt0        = 0x40u;
	constexpr uint8_t EstCom        = 0x20u;
	constexpr uint8_t WuPuls        = 0x10u;
	constexpr uint8_t TxFifoRst     = 0x08u;
	constexpr uint8_t RxFifoRst     = 0x04u;
	constexpr uint8_t CycleTmrEn    = 0x02u;
	constexpr uint8_t CQSend        = 0x01u;

	constexpr uint8_t CQErrA        = 0x08u;
	constexpr uint8_t CQErrB        = 0x09u;
	constexpr uint8_t TransmErr     = 0x80u;
	constexpr uint8_t TCyclErr      = 0x40u;
	constexpr uint8_t TChksmEr      = 0x20u;
	constexpr uint8_t TSizeErr      = 0x10u;
	constexpr uint8_t RChksmEr	    = 0x08u;
	constexpr uint8_t RSizeErr      = 0x04u;
	constexpr uint8_t FrameErr      = 0x02u;
	constexpr uint8_t ParityErr     = 0x01u;

	constexpr uint8_t MsgCtrlA      = 0x0Au;
	constexpr uint8_t MsgCtrlB      = 0x0Bu;
	constexpr uint8_t TxErDestroy   = 0x80u;
	constexpr uint8_t SPIChks       = 0x40u;
	constexpr uint8_t InsChks       = 0x20u;
	constexpr uint8_t TSizeEn       = 0x10u;
	constexpr uint8_t TxKeepMsg     = 0x08u;
	constexpr uint8_t RChksEn       = 0x04u;
	constexpr uint8_t RMessgRdyEn   = 0x02u;
	constexpr uint8_t InvCQ         = 0x01u;

	constexpr uint8_t ChanStatA     = 0x0Cu;
	constexpr uint8_t ChanStatB     = 0x0Du;
	constexpr uint8_t Rst           = 0x80u;
	constexpr uint8_t FramerEn      = 0x40u;
	constexpr uint8_t LCLimCOR 	    = 0x20u;
	constexpr uint8_t CQFaultCOR 	= 0x10u;
	constexpr uint8_t LCLim         = 0x08u;
	constexpr uint8_t UVL           = 0x04u;
	constexpr uint8_t CQFault       = 0x02u;

	constexpr uint8_t LEDCtrl       = 0x0Eu;
	constexpr uint8_t LEDEn2B       = 0x80u;
	constexpr uint8_t RxErrEnB 	    = 0x40u;
	constexpr uint8_t LEDEn1B       = 0x20u;
	constexpr uint8_t RxRdyEnB      = 0x10u;
	constexpr uint8_t LEDEn2A       = 0x08u;
	constexpr uint8_t RxErrEnA      = 0x04u;
	constexpr uint8_t LEDEn1A       = 0x02u;
	constexpr uint8_t RxRdyEnA      = 0x01u;

	constexpr uint8_t Trigger       = 0x0Fu;
	constexpr uint8_t TrigInit3     = 0x08u;
	constexpr uint8_t TrigInit2     = 0x04u;
	constexpr uint8_t TrigInit1     = 0x02u;
	constexpr uint8_t TrigInit0     = 0x01u;

	constexpr uint8_t CQCfgA        = 0x10u;
	constexpr uint8_t CQCfgB        = 0x11u;
	constexpr uint8_t IEC3Th        = 0x80u;
	constexpr uint8_t SourceSink    = 0x40u;
	constexpr uint8_t SinkSel1      = 0x20u;
	constexpr uint8_t SinkSel0 	    = 0x10u;
	constexpr uint8_t NPN           = 0x08u;
	constexpr uint8_t PushPul       = 0x04u;
	constexpr uint8_t DrvDis        = 0x02u;
	constexpr uint8_t CQFilterEn    = 0x01u;

	constexpr uint8_t CyclTmrA 	    = 0x12u;
	constexpr uint8_t CyclTmrB      = 0x12u;
	constexpr uint8_t TCyclBs1      = 0x80u;
	constexpr uint8_t TCyclBs0      = 0x40u;
	constexpr uint8_t TCyclM5       = 0x20u;
	constexpr uint8_t TCyclM4       = 0x10u;
	constexpr uint8_t TCyclM3       = 0x08u;
	constexpr uint8_t TCyclM2       = 0x04u;
	constexpr uint8_t TCyclM1       = 0x02u;
	constexpr uint8_t TCyclM0       = 0x01u;

	constexpr uint8_t DeviceDlyA    = 0x14u;
	constexpr uint8_t DeviceDlyB    = 0x15u;
	constexpr uint8_t DelayErr      = 0x80u;
	constexpr uint8_t BDelay1       = 0x40u;
	constexpr uint8_t BDelay0       = 0x20u;
	constexpr uint8_t DDelay3       = 0x10u;
	constexpr uint8_t DDelay2       = 0x08u;
	constexpr uint8_t DDelay1       = 0x04u;
	constexpr uint8_t DDelay0       = 0x02u;
	constexpr uint8_t RspnsTmrEn    = 0x01u;

	constexpr uint8_t TrigAssgnA    = 0x16u;
	constexpr uint8_t TrigAssgnB    = 0x17u;
	constexpr uint8_t Trig3         = 0x80u;
	constexpr uint8_t Trig2         = 0x40u;
	constexpr uint8_t Trig1         = 0x20u;
	constexpr uint8_t Trig0         = 0x10u;
	constexpr uint8_t TrigEn        = 0x01u;

	constexpr uint8_t LCnfgA        = 0x18u;
	constexpr uint8_t LCnfgB        = 0x19u;
	constexpr uint8_t LRT1          = 0x80u;
	constexpr uint8_t LRT0          = 0x40u;
	constexpr uint8_t LDynBL        = 0x20u;
	constexpr uint8_t LBL1          = 0x10u;
	constexpr uint8_t LBL0          = 0x08u;
	constexpr uint8_t LCL2x         = 0x04u;
	constexpr uint8_t LClimDis      = 0x02u;
	constexpr uint8_t LEn           = 0x01u;

	constexpr uint8_t IOStCfgA      = 0x1Au;
	constexpr uint8_t IOStCfgB      = 0x1Bu;
	constexpr uint8_t DiLevel       = 0x80u;
	constexpr uint8_t CQLevel       = 0x40u;
	constexpr uint8_t TxEn          = 0x20u;
	constexpr uint8_t Tx            = 0x10u;
	constexpr uint8_t DiFilterEn    = 0x08u;
	constexpr uint8_t DiEC3Th       = 0x04u;
	constexpr uint8_t DiCSource     = 0x02u;
	constexpr uint8_t DiCSink       = 0x01u;

	constexpr uint8_t DrvrCurrLim   = 0x1Cu;
	constexpr uint8_t CL1           = 0x80u;
	constexpr uint8_t CL0           = 0x40u;
	constexpr uint8_t CLDis         = 0x20u;
	constexpr uint8_t CLBL1         = 0x10u;
	constexpr uint8_t CLBL0         = 0x08u;
	constexpr uint8_t TAr1          = 0x04u;
	constexpr uint8_t TAr0          = 0x02u;
	constexpr uint8_t ArEn          = 0x01u;

	constexpr uint8_t Clock         = 0x1Du;
	constexpr uint8_t VCCWarnEn     = 0x80u;
	constexpr uint8_t TXTXENDis     = 0x40u;
	constexpr uint8_t ExtClkMis     = 0x20u;
	constexpr uint8_t ClkOEn        = 0x10u;
	constexpr uint8_t ClkDiv1       = 0x08u;
	constexpr uint8_t ClkDiv0       = 0x04u;
	constexpr uint8_t ExtClkEn      = 0x02u;
	constexpr uint8_t XtalEn        = 0x01u;

	constexpr uint8_t Status        = 0x1Eu;
	constexpr uint8_t ThShdnCOR     = 0x80u;
	constexpr uint8_t ThWarnCOR     = 0x40u;
	constexpr uint8_t VCCUVCOR      = 0x20u;
	constexpr uint8_t VCCWarnCOR    = 0x10u;
	constexpr uint8_t ThShdn        = 0x08u;
	constexpr uint8_t TempWarn      = 0x04u;
	constexpr uint8_t VCCUV         = 0x02u;
	constexpr uint8_t VCCWarn       = 0x01u;

	constexpr uint8_t RevID         = 0x1Fu;
	constexpr uint8_t ID3           = 0x08u;
	constexpr uint8_t ID2           = 0x04u;
	constexpr uint8_t ID1           = 0x02u;
	constexpr uint8_t ID0           = 0x01u;

	constexpr uint8_t MAX_REG       = RevID;

	// maximal number of bytes to send (according to max14819 FIFO length)
	constexpr uint8_t MAX_MSG_LENGTH= 64;

//!**** Data types ************************************************************

//!**** Function prototypes ***************************************************

//!**** Data ******************************************************************

//!**** Implementation ********************************************************
    class Max14819 {
    private:
		DriverSelect driver_;
        uint8_t isInitPortA_;
        uint8_t isInitPortB_;
        uint8_t isLedCtrlPortAEn_;
        uint8_t isLedCtrlPortBEn_;
		HardwareBase* Hardware;

    public:
        uint8_t comSpeedRegA;
        uint8_t comSpeedRegB;
        Max14819();
        Max14819(DriverSelect driver, HardwareBase* Hardware);
        ~Max14819();
        uint8_t begin (PortSelect port);
        uint8_t end(PortSelect port);

        uint8_t reset(void);
        uint8_t reset(PortSelect port);

        uint8_t readStatus(PortSelect port);

        uint8_t wakeUpRequest(PortSelect port, uint32_t * comSpeed_ret);

        uint8_t readRegister(uint8_t reg);

        uint8_t writeRegister(uint8_t reg, uint8_t data);

        uint8_t writeData(uint8_t mc, uint8_t data, uint8_t sizeAnswer, uint8_t mSeqType, PortSelect port);

        uint8_t writeData(uint8_t mc, uint8_t sizeData, uint8_t *pData, uint8_t sizeAnswer, uint8_t mSeqType, PortSelect port);

        uint8_t readData(uint8_t *pData, uint8_t sizeData, PortSelect port);

        uint8_t enableCyclicSend(uint8_t mc, uint8_t sizeData, uint8_t *pData, uint8_t sizeAnswer, uint8_t mSeqType, uint16_t cycleTime, PortSelect port);

        uint8_t disableCyclicSend(PortSelect port);

        uint8_t enableLedControl(PortSelect port);

        uint8_t disableLedControl(PortSelect port);

        uint8_t writeLed(HardwareBase::PinNames led, uint8_t state);

        uint8_t writeDIConfig(PortSelect port, uint8_t currentType, uint8_t threshold, uint8_t filter);

        uint8_t readDIConfig(PortSelect port);

        uint8_t writeCQ(PortSelect port, uint8_t value);

        uint8_t readCQ(PortSelect port);

        uint8_t readDI(PortSelect port);

		void Serial_Write(char const * buf);
		void wait_for(uint32_t delay_ms);
    };// class max14819
} // namespace max14819

#endif //MAX14819_HPP_INCLUDED
