//!*****************************************************************************
//! \file   Max14819.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!         based on the work of Janik Lehmann (CrazyGecko) and Pascal Frei (freip2)
//!
//! \brief  Class for the maxim integrated Dual IO-Link Master Transceiver
//!         MAX14819
//!
//! \date   2021-06-18
//!
//!
//! *****************************************************************************
//!
//! \copyright
//! Copyright 2020 Bern University of Applied Sciences and Balluff AG
//! \n\n
//! Licensed under the Apache License, Version 2.0 (the "License");
//! you may not use this file except in compliance with the License.
//! You may obtain a copy of the License at
//! \n\n
//!     http://www.apache.org/licenses/LICENSE-2.0
//! \n\n
//! Unless required by applicable law or agreed to in writing, software
//! distributed under the License is distributed on an "AS IS" BASIS,
//! WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//! See the License for the specific language governing permissions and
//! limitations under the License.
//!
//!*****************************************************************************
#ifndef MAX14819_HPP_INCLUDED
#define MAX14819_HPP_INCLUDED

#include "protocol/IOLMasterPort.hpp"
#include "protocol/IOLMessage.hpp"
#include "protocol/IOLinkConfig.hpp"
#include "MapperChip.hpp"
#include "Max14819_Port.hpp"
#include "typedefs_board.hpp" // BoolSuccess and BoolError

namespace openiolink // TODO ::PCB?
{
    //!*****************************************************************************
    //! \brief  Class for the maxim integrated Dual IO-Link Master Transceiver
    //!         MAX14819
    //!
    //! \note   When referencing this class you MUST give the first template
    //!         parameter (ChipNr) only!
    //!
    //!*****************************************************************************
    template <int ChipNr> //,
                          //class SPI = typename MapperChip<ChipNr>::SPI,
                          //int ChAPortNr = BackMapperChip<ChipNr>::Ch1IOLPortNr,
                          //int ChBPortNr = BackMapperChip<ChipNr>::Ch2IOLPortNr>
    class Max14819
    {
    public:
        // NOTE: Because the following definitions are static they should not
        //       take any memory. And thus it is no problem that the compiler
        //       rewrites the code for this class for each template parameter
        //       value.

        //! \name Error define
        //!\{
        static constexpr uint8_t ERROR = static_cast<uint8_t>(BoolError);     //!< return value for errors
        static constexpr uint8_t SUCCESS = static_cast<uint8_t>(BoolSuccess); //!< return value for success
        //!\}

        //! \name MAX14819 DI Init defines
        //!\{
        static constexpr uint8_t CURRENT_SOURCE = 0x02u;  //!< DI Init definition current source
        static constexpr uint8_t CURRENT_SINK = 0x01u;    //!< DI Init definition current sink
        static constexpr uint8_t CURRENT_DISABLE = 0x00u; //!< DI Init definition current disable
        static constexpr uint8_t THRSLD_TYPE1 = 1u;       //!< DI Init definition Different Threshold Levels, see MAX14819 Datasheet, p. 5
        static constexpr uint8_t THRSLD_TYPE2 = 0u;       //!< DI Init definition Different Threshold Levels, see MAX14819 Datasheet, p. 5
        static constexpr uint8_t FILTER_EN = 0x08u;       //!< DI Init definition Glich filter enable
        static constexpr uint8_t FILTER_DIS = 0x00u;      //!< DI Init definition Glich filter disable
        //!\}

        //! \name Timing constexprants for Max14819
        //!\{
        static constexpr uint32_t INIT_POWER_OFF_DELAY = 1000u; //!< Delay in ms for disable duration of sensor power when startup
        static constexpr uint32_t INIT_BOOTUP_DELAY = 300u;     //!< Delay after switch-to-operational-command
        static constexpr uint32_t INIT_WURQ_TIMEOUT = 80u;      //!< Timeout in ms for abort WURQ request (2x retry after 10ms, 3x tries a 20ms)
        //!\}

        //! \name Max14819 Register definition
        //!\{
        static constexpr uint8_t TxRxDataA = 0x00u; //!< register definition
        static constexpr uint8_t TxRxDataB = 0x01u; //!< register definition

        static constexpr uint8_t Interrupt = 0x02u;  //!< register definition
        static constexpr uint8_t StatusInt = 0x80u;  //!< register definition
        static constexpr uint8_t WURQInt = 0x40u;    //!< register definition
        static constexpr uint8_t TxErrorB = 0x20u;   //!< register definition
        static constexpr uint8_t TxErrorA = 0x10u;   //!< register definition
        static constexpr uint8_t RxErrorB = 0x08u;   //!< register definition
        static constexpr uint8_t RxErrorA = 0x04u;   //!< register definition
        static constexpr uint8_t RxDataRdyB = 0x02u; //!< register definition
        static constexpr uint8_t RxDataRdyA = 0x01u; //!< register definition

        static constexpr uint8_t InterruptEn = 0x03u;   //!< register definition
        static constexpr uint8_t StatusIntEn = 0x80u;   //!< register definition
        static constexpr uint8_t WURQIntEn = 0x40u;     //!< register definition
        static constexpr uint8_t TxErrIntEnB = 0x20u;   //!< register definition
        static constexpr uint8_t TxErrIntEnA = 0x10u;   //!< register definition
        static constexpr uint8_t RxErrIntEnB = 0x08u;   //!< register definition
        static constexpr uint8_t RxErrIntEnA = 0x04u;   //!< register definition
        static constexpr uint8_t RxDaRdyIntEnB = 0x02u; //!< register definition
        static constexpr uint8_t RxDaRdyIntEnA = 0x01u; //!< register definition

        static constexpr uint8_t RxFIFOLvlA = 0x04u; //!< register definition
        static constexpr uint8_t RxFIFOLvlB = 0x05u; //!< register definition

        static constexpr uint8_t CQCtrlA = 0x06u;    //!< register definition
        static constexpr uint8_t CQCtrlB = 0x07u;    //!< register definition
        static constexpr uint8_t ComRt1 = 0x80u;     //!< register definition
        static constexpr uint8_t ComRt0 = 0x40u;     //!< register definition
        static constexpr uint8_t EstCom = 0x20u;     //!< register definition
        static constexpr uint8_t WuPuls = 0x10u;     //!< register definition
        static constexpr uint8_t TxFifoRst = 0x08u;  //!< register definition
        static constexpr uint8_t RxFifoRst = 0x04u;  //!< register definition
        static constexpr uint8_t CycleTmrEn = 0x02u; //!< register definition
        static constexpr uint8_t CQSend = 0x01u;     //!< register definition

        static constexpr uint8_t CQErrA = 0x08u;    //!< register definition
        static constexpr uint8_t CQErrB = 0x09u;    //!< register definition
        static constexpr uint8_t TransmErr = 0x80u; //!< register definition
        static constexpr uint8_t TCyclErr = 0x40u;  //!< register definition
        static constexpr uint8_t TChksmEr = 0x20u;  //!< register definition
        static constexpr uint8_t TSizeErr = 0x10u;  //!< register definition
        static constexpr uint8_t RChksmEr = 0x08u;  //!< register definition
        static constexpr uint8_t RSizeErr = 0x04u;  //!< register definition
        static constexpr uint8_t FrameErr = 0x02u;  //!< register definition
        static constexpr uint8_t ParityErr = 0x01u; //!< register definition

        static constexpr uint8_t MsgCtrlA = 0x0Au;    //!< register definition
        static constexpr uint8_t MsgCtrlB = 0x0Bu;    //!< register definition
        static constexpr uint8_t TxErDestroy = 0x80u; //!< register definition
        static constexpr uint8_t SPIChks = 0x40u;     //!< register definition
        static constexpr uint8_t InsChks = 0x20u;     //!< register definition
        static constexpr uint8_t TSizeEn = 0x10u;     //!< register definition
        static constexpr uint8_t TxKeepMsg = 0x08u;   //!< register definition
        static constexpr uint8_t RChksEn = 0x04u;     //!< register definition
        static constexpr uint8_t RMessgRdyEn = 0x02u; //!< register definition
        static constexpr uint8_t InvCQ = 0x01u;       //!< register definition

        static constexpr uint8_t ChanStatA = 0x0Cu;  //!< register definition
        static constexpr uint8_t ChanStatB = 0x0Du;  //!< register definition
        static constexpr uint8_t Rst = 0x80u;        //!< register definition
        static constexpr uint8_t FramerEn = 0x40u;   //!< register definition
        static constexpr uint8_t LCLimCOR = 0x20u;   //!< register definition
        static constexpr uint8_t CQFaultCOR = 0x10u; //!< register definition
        static constexpr uint8_t LCLim = 0x08u;      //!< register definition
        static constexpr uint8_t UVL = 0x04u;        //!< register definition
        static constexpr uint8_t CQFault = 0x02u;    //!< register definition

        static constexpr uint8_t LEDCtrl = 0x0Eu;  //!< register definition
        static constexpr uint8_t LEDEn2B = 0x80u;  //!< register definition
        static constexpr uint8_t RxErrEnB = 0x40u; //!< register definition
        static constexpr uint8_t LEDEn1B = 0x20u;  //!< register definition
        static constexpr uint8_t RxRdyEnB = 0x10u; //!< register definition
        static constexpr uint8_t LEDEn2A = 0x08u;  //!< register definition
        static constexpr uint8_t RxErrEnA = 0x04u; //!< register definition
        static constexpr uint8_t LEDEn1A = 0x02u;  //!< register definition
        static constexpr uint8_t RxRdyEnA = 0x01u; //!< register definition

        static constexpr uint8_t Trigger = 0x0Fu;   //!< register definition
        static constexpr uint8_t TrigInit3 = 0x08u; //!< register definition
        static constexpr uint8_t TrigInit2 = 0x04u; //!< register definition
        static constexpr uint8_t TrigInit1 = 0x02u; //!< register definition
        static constexpr uint8_t TrigInit0 = 0x01u; //!< register definition

        static constexpr uint8_t CQCfgA = 0x10u;     //!< register definition
        static constexpr uint8_t CQCfgB = 0x11u;     //!< register definition
        static constexpr uint8_t IEC3Th = 0x80u;     //!< register definition
        static constexpr uint8_t SourceSink = 0x40u; //!< register definition
        static constexpr uint8_t SinkSel1 = 0x20u;   //!< register definition
        static constexpr uint8_t SinkSel0 = 0x10u;   //!< register definition
        static constexpr uint8_t NPN = 0x08u;        //!< register definition
        static constexpr uint8_t PushPul = 0x04u;    //!< register definition
        static constexpr uint8_t DrvDis = 0x02u;     //!< register definition
        static constexpr uint8_t CQFilterEn = 0x01u; //!< register definition

        static constexpr uint8_t CyclTmrA = 0x12u; //!< register definition
        static constexpr uint8_t CyclTmrB = 0x12u; //!< register definition
        static constexpr uint8_t TCyclBs1 = 0x80u; //!< register definition
        static constexpr uint8_t TCyclBs0 = 0x40u; //!< register definition
        static constexpr uint8_t TCyclM5 = 0x20u;  //!< register definition
        static constexpr uint8_t TCyclM4 = 0x10u;  //!< register definition
        static constexpr uint8_t TCyclM3 = 0x08u;  //!< register definition
        static constexpr uint8_t TCyclM2 = 0x04u;  //!< register definition
        static constexpr uint8_t TCyclM1 = 0x02u;  //!< register definition
        static constexpr uint8_t TCyclM0 = 0x01u;  //!< register definition

        static constexpr uint8_t DeviceDlyA = 0x14u; //!< register definition
        static constexpr uint8_t DeviceDlyB = 0x15u; //!< register definition
        static constexpr uint8_t DelayErr = 0x80u;   //!< register definition
        static constexpr uint8_t BDelay1 = 0x40u;    //!< register definition
        static constexpr uint8_t BDelay0 = 0x20u;    //!< register definition
        static constexpr uint8_t DDelay3 = 0x10u;    //!< register definition
        static constexpr uint8_t DDelay2 = 0x08u;    //!< register definition
        static constexpr uint8_t DDelay1 = 0x04u;    //!< register definition
        static constexpr uint8_t DDelay0 = 0x02u;    //!< register definition
        static constexpr uint8_t RspnsTmrEn = 0x01u; //!< register definition

        static constexpr uint8_t TrigAssgnA = 0x16u; //!< register definition
        static constexpr uint8_t TrigAssgnB = 0x17u; //!< register definition
        static constexpr uint8_t Trig3 = 0x80u;      //!< register definition
        static constexpr uint8_t Trig2 = 0x40u;      //!< register definition
        static constexpr uint8_t Trig1 = 0x20u;      //!< register definition
        static constexpr uint8_t Trig0 = 0x10u;      //!< register definition
        static constexpr uint8_t TrigEn = 0x01u;     //!< register definition

        static constexpr uint8_t LCnfgA = 0x18u;   //!< register definition
        static constexpr uint8_t LCnfgB = 0x19u;   //!< register definition
        static constexpr uint8_t LRT1 = 0x80u;     //!< register definition
        static constexpr uint8_t LRT0 = 0x40u;     //!< register definition
        static constexpr uint8_t LDynBL = 0x20u;   //!< register definition
        static constexpr uint8_t LBL1 = 0x10u;     //!< register definition
        static constexpr uint8_t LBL0 = 0x08u;     //!< register definition
        static constexpr uint8_t LCL2x = 0x04u;    //!< register definition
        static constexpr uint8_t LClimDis = 0x02u; //!< register definition
        static constexpr uint8_t LEn = 0x01u;      //!< register definition

        static constexpr uint8_t IOStCfgA = 0x1Au;   //!< register definition
        static constexpr uint8_t IOStCfgB = 0x1Bu;   //!< register definition
        static constexpr uint8_t DiLevel = 0x80u;    //!< register definition
        static constexpr uint8_t CQLevel = 0x40u;    //!< register definition
        static constexpr uint8_t TxEn = 0x20u;       //!< register definition
        static constexpr uint8_t Tx = 0x10u;         //!< register definition
        static constexpr uint8_t DiFilterEn = 0x08u; //!< register definition
        static constexpr uint8_t DiEC3Th = 0x04u;    //!< register definition
        static constexpr uint8_t DiCSource = 0x02u;  //!< register definition
        static constexpr uint8_t DiCSink = 0x01u;    //!< register definition

        static constexpr uint8_t DrvrCurrLim = 0x1Cu; //!< register definition
        static constexpr uint8_t CL1 = 0x80u;         //!< register definition
        static constexpr uint8_t CL0 = 0x40u;         //!< register definition
        static constexpr uint8_t CLDis = 0x20u;       //!< register definition
        static constexpr uint8_t CLBL1 = 0x10u;       //!< register definition
        static constexpr uint8_t CLBL0 = 0x08u;       //!< register definition
        static constexpr uint8_t TAr1 = 0x04u;        //!< register definition
        static constexpr uint8_t TAr0 = 0x02u;        //!< register definition
        static constexpr uint8_t ArEn = 0x01u;        //!< register definition

        static constexpr uint8_t Clock = 0x1Du;     //!< register definition
        static constexpr uint8_t VCCWarnEn = 0x80u; //!< register definition
        static constexpr uint8_t TXTXENDis = 0x40u; //!< register definition
        static constexpr uint8_t ExtClkMis = 0x20u; //!< register definition
        static constexpr uint8_t ClkOEn = 0x10u;    //!< register definition
        static constexpr uint8_t ClkDiv1 = 0x08u;   //!< register definition
        static constexpr uint8_t ClkDiv0 = 0x04u;   //!< register definition
        static constexpr uint8_t ExtClkEn = 0x02u;  //!< register definition
        static constexpr uint8_t XtalEn = 0x01u;    //!< register definition

        static constexpr uint8_t Status = 0x1Eu;     //!< register definition
        static constexpr uint8_t ThShdnCOR = 0x80u;  //!< register definition
        static constexpr uint8_t ThWarnCOR = 0x40u;  //!< register definition
        static constexpr uint8_t VCCUVCOR = 0x20u;   //!< register definition
        static constexpr uint8_t VCCWarnCOR = 0x10u; //!< register definition
        static constexpr uint8_t ThShdn = 0x08u;     //!< register definition
        static constexpr uint8_t TempWarn = 0x04u;   //!< register definition
        static constexpr uint8_t VCCUV = 0x02u;      //!< register definition
        static constexpr uint8_t VCCWarn = 0x01u;    //!< register definition

        static constexpr uint8_t RevID = 0x1Fu; //!< register definition
        static constexpr uint8_t ID3 = 0x08u;   //!< register definition
        static constexpr uint8_t ID2 = 0x04u;   //!< register definition
        static constexpr uint8_t ID1 = 0x02u;   //!< register definition
        static constexpr uint8_t ID0 = 0x01u;   //!< register definition

        static constexpr uint8_t MAX_REG = RevID; //!< register definition
        //! \}

        static constexpr uint8_t MAX_MSG_LENGTH = 64; //!< maximal number of bytes to send (according to max14819 FIFO length)

        // class member functions
        // the class signature is (just to remind):
        //// template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr> class Max14819
        // template <int ChipNr> class Max14819
    private:
        static constexpr int ChAPortNr = BackMapperChip<ChipNr>::Ch1IOLPortNr; // was defaulted template parameter
        static constexpr int ChBPortNr = BackMapperChip<ChipNr>::Ch2IOLPortNr; // was defaulted template parameter

    public:
        Max14819(Max14819_Port<ChAPortNr> &portA, Max14819_Port<ChBPortNr> &portB);
        ~Max14819();
        uint8_t readRegister(uint8_t reg);
        uint8_t writeRegister(uint8_t reg, uint8_t data);
        //auto &getPort(Max14819_Port::PortNr port);-> Max14819_Port<port>
        // would be complicated because parametrized. If getPort() is necessary,
        // (A) split it to seperate methods for each port/channel or (B) return a IOLMasterPort reference.

    private:
        using SPI = typename MapperChip<ChipNr>::SPI; // was defaulted template parameter
        static constexpr uint8_t spi_address = MapperChip<ChipNr>::SPIAddress;

        typedef platform::InputPin<MapperChip<ChipNr>::IRQPinNr> IRQPin; //!< Interrupt
        typedef platform::OutputPin<MapperChip<ChipNr>::CSPinNr> CSPin;  //!< ChipSelect

        Max14819_Port<ChAPortNr> &mPortA;
        Max14819_Port<ChBPortNr> &mPortB;

        void initGPIOs();
        void configure();
        uint8_t reset();

    }; // class Max14819

    ////!*****************************************************************************
    ////! \brief  Class for the maxim integrated Dual IO-Link Master Transceiver
    ////!         MAX14819 (alias)
    ////!
    ////!*****************************************************************************
    //template <int ChipNr>
    //using Max14819Alias = Max14819<ChipNr,
    //                               class SPI = typename MapperChip<ChipNr>::SPI,
    //                               int ChAPortNr = BackMapperChip<ChipNr>::Ch1IOLPortNr,
    //                               int ChBPortNr = BackMapperChip<ChipNr>::Ch2IOLPortNr>

} // namespace openiolink // TODO ::PCB?

// We need to include "our" .cpp file here. Explanation:
// Part of the methods of the class template declared in this .hpp file may be
// defined in the same-named .cpp file. Since these are template methods the
// compiler won't do anything when compiling the .cpp file, because he does not
// know the actual template parameter(s) (value or type) that will be given when
// the template is instatiated.
// Wherever this class template will be used (i.e. instantiated), the compiler
// will only have this .hpp at hand (assuming it was included), but lacks the
// implementation details (the definitions). Those are located in the .cpp and
// tis is why we include the .cpp file here.
// (There may be other solutions to this problem, see e.g.
// https://www.codeproject.com/Articles/48575/How-to-Define-a-Template-Class-in-a-h-File-and-Imp)
#include "Max14819.cpp"
#endif //MAX14819_HPP_INCLUDED
