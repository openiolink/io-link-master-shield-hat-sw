//!*****************************************************************************
//!  \file Max14819.hpp
//!  
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!          based on the work of Pascal Frei (freip2)
//!  
//!  \brief Class for the maxim integrated Dual IO-Link Master Transceiver
//!         MAX14819
//!  
//!  \date 2020-11-18
//!  
//!  
//!  *****************************************************************************
//!  
//!  \copyright
//!  Copyright 2020 Bern University of Applied Sciences and Balluff AG
//!  \n\n
//!  Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!  \n\n
//!      http://www.apache.org/licenses/LICENSE-2.0
//!  \n\n
//!  Unless required by applicable law or agreed to in writing, software
//!  distributed under the License is distributed on an "AS IS" BASIS,
//!  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!  See the License for the specific language governing permissions and
//!  limitations under the License.
//!  
//!*****************************************************************************
#ifndef MAX14819_HPP_INCLUDED
#define MAX14819_HPP_INCLUDED

#include <memory>
#include "protocol/IOLMasterPort.hpp"
#include "protocol/IOLMessage.hpp"
#include "protocol/IOLinkConfig.hpp"

//!*****************************************************************************
//!  \brief Class for the maxim integrated Dual IO-Link Master Transceiver
//!         MAX14819
//!  
//!*****************************************************************************
class Max14819 : public std::enable_shared_from_this<Max14819>{
public:
    //! \name Error define
    //!\{
    static constexpr uint8_t ERROR             = 1u;    //!< return value for errors
    static constexpr uint8_t SUCCESS           = 0u;    //!< return value for success
    //!\}

    //! \name MAX14819 DI Init defines
    //!\{
    static constexpr uint8_t CURRENT_SOURCE    = 0x02u;     //!< DI Init definition current source
    static constexpr uint8_t CURRENT_SINK      = 0x01u;     //!< DI Init definition current sink
    static constexpr uint8_t CURRENT_DISABLE   = 0x00u;     //!< DI Init definition current disable
    static constexpr uint8_t THRSLD_TYPE1      = 1u;        //!< DI Init definition Different Threshold Levels, see MAX14819 Datasheet, p. 5
    static constexpr uint8_t THRSLD_TYPE2      = 0u;        //!< DI Init definition Different Threshold Levels, see MAX14819 Datasheet, p. 5
    static constexpr uint8_t FILTER_EN         = 0x08u;     //!< DI Init definition Glich filter enable
    static constexpr uint8_t FILTER_DIS        = 0x00u;     //!< DI Init definition Glich filter disable
    //!\}

    //! \name Timing constexprants for Max14819
    //!\{
    static constexpr uint32_t INIT_POWER_OFF_DELAY	= 1000u;	//!< Delay in ms for disable duration of sensor power when startup
    static constexpr uint32_t INIT_BOOTUP_DELAY    = 300u;	//!< Delay after switch-to-operational-command
    static constexpr uint32_t INIT_WURQ_TIMEOUT    = 80u;   //!< Timeout in ms for abort WURQ request (2x retry after 10ms, 3x tries a 20ms)
    //!\}

    //! \name Max14819 Register definition 
    //!\{
    static constexpr uint8_t TxRxDataA     = 0x00u; //!< register definition
    static constexpr uint8_t TxRxDataB     = 0x01u; //!< register definition

    static constexpr uint8_t Interrupt     = 0x02u; //!< register definition
    static constexpr uint8_t StatusInt     = 0x80u; //!< register definition
    static constexpr uint8_t WURQInt       = 0x40u; //!< register definition
    static constexpr uint8_t TxErrorB      = 0x20u; //!< register definition
    static constexpr uint8_t TxErrorA      = 0x10u; //!< register definition
    static constexpr uint8_t RxErrorB      = 0x08u; //!< register definition
    static constexpr uint8_t RxErrorA    	= 0x04u; //!< register definition
    static constexpr uint8_t RxDataRdyB    = 0x02u; //!< register definition
    static constexpr uint8_t RxDataRdyA   	= 0x01u; //!< register definition

    static constexpr uint8_t InterruptEn   = 0x03u; //!< register definition
    static constexpr uint8_t StatusIntEn   = 0x80u; //!< register definition
    static constexpr uint8_t WURQIntEn     = 0x40u; //!< register definition
    static constexpr uint8_t TxErrIntEnB   = 0x20u; //!< register definition
    static constexpr uint8_t TxErrIntEnA   = 0x10u; //!< register definition
    static constexpr uint8_t RxErrIntEnB   = 0x08u; //!< register definition
    static constexpr uint8_t RxErrIntEnA   = 0x04u; //!< register definition
    static constexpr uint8_t RxDaRdyIntEnB = 0x02u; //!< register definition
    static constexpr uint8_t RxDaRdyIntEnA = 0x01u; //!< register definition

    static constexpr uint8_t RxFIFOLvlA 	= 0x04u; //!< register definition
    static constexpr uint8_t RxFIFOLvlB 	= 0x05u; //!< register definition

    static constexpr uint8_t CQCtrlA       = 0x06u; //!< register definition
    static constexpr uint8_t CQCtrlB       = 0x07u; //!< register definition
    static constexpr uint8_t ComRt1        = 0x80u; //!< register definition
    static constexpr uint8_t ComRt0        = 0x40u; //!< register definition
    static constexpr uint8_t EstCom        = 0x20u; //!< register definition
    static constexpr uint8_t WuPuls        = 0x10u; //!< register definition
    static constexpr uint8_t TxFifoRst     = 0x08u; //!< register definition
    static constexpr uint8_t RxFifoRst     = 0x04u; //!< register definition
    static constexpr uint8_t CycleTmrEn    = 0x02u; //!< register definition
    static constexpr uint8_t CQSend        = 0x01u; //!< register definition

    static constexpr uint8_t CQErrA        = 0x08u; //!< register definition
    static constexpr uint8_t CQErrB        = 0x09u; //!< register definition
    static constexpr uint8_t TransmErr     = 0x80u; //!< register definition
    static constexpr uint8_t TCyclErr      = 0x40u; //!< register definition
    static constexpr uint8_t TChksmEr      = 0x20u; //!< register definition
    static constexpr uint8_t TSizeErr      = 0x10u; //!< register definition
    static constexpr uint8_t RChksmEr	    = 0x08u; //!< register definition
    static constexpr uint8_t RSizeErr      = 0x04u; //!< register definition
    static constexpr uint8_t FrameErr      = 0x02u; //!< register definition
    static constexpr uint8_t ParityErr     = 0x01u; //!< register definition

    static constexpr uint8_t MsgCtrlA      = 0x0Au; //!< register definition
    static constexpr uint8_t MsgCtrlB      = 0x0Bu; //!< register definition
    static constexpr uint8_t TxErDestroy   = 0x80u; //!< register definition
    static constexpr uint8_t SPIChks       = 0x40u; //!< register definition
    static constexpr uint8_t InsChks       = 0x20u; //!< register definition
    static constexpr uint8_t TSizeEn       = 0x10u; //!< register definition
    static constexpr uint8_t TxKeepMsg     = 0x08u; //!< register definition
    static constexpr uint8_t RChksEn       = 0x04u; //!< register definition
    static constexpr uint8_t RMessgRdyEn   = 0x02u; //!< register definition
    static constexpr uint8_t InvCQ         = 0x01u; //!< register definition

    static constexpr uint8_t ChanStatA     = 0x0Cu; //!< register definition
    static constexpr uint8_t ChanStatB     = 0x0Du; //!< register definition
    static constexpr uint8_t Rst           = 0x80u; //!< register definition
    static constexpr uint8_t FramerEn      = 0x40u; //!< register definition
    static constexpr uint8_t LCLimCOR 	    = 0x20u; //!< register definition
    static constexpr uint8_t CQFaultCOR 	= 0x10u; //!< register definition
    static constexpr uint8_t LCLim         = 0x08u; //!< register definition
    static constexpr uint8_t UVL           = 0x04u; //!< register definition
    static constexpr uint8_t CQFault       = 0x02u; //!< register definition

    static constexpr uint8_t LEDCtrl       = 0x0Eu; //!< register definition
    static constexpr uint8_t LEDEn2B       = 0x80u; //!< register definition
    static constexpr uint8_t RxErrEnB 	    = 0x40u; //!< register definition
    static constexpr uint8_t LEDEn1B       = 0x20u; //!< register definition
    static constexpr uint8_t RxRdyEnB      = 0x10u; //!< register definition
    static constexpr uint8_t LEDEn2A       = 0x08u; //!< register definition
    static constexpr uint8_t RxErrEnA      = 0x04u; //!< register definition
    static constexpr uint8_t LEDEn1A       = 0x02u; //!< register definition
    static constexpr uint8_t RxRdyEnA      = 0x01u; //!< register definition

    static constexpr uint8_t Trigger       = 0x0Fu; //!< register definition
    static constexpr uint8_t TrigInit3     = 0x08u; //!< register definition
    static constexpr uint8_t TrigInit2     = 0x04u; //!< register definition
    static constexpr uint8_t TrigInit1     = 0x02u; //!< register definition
    static constexpr uint8_t TrigInit0     = 0x01u; //!< register definition

    static constexpr uint8_t CQCfgA        = 0x10u; //!< register definition
    static constexpr uint8_t CQCfgB        = 0x11u; //!< register definition
    static constexpr uint8_t IEC3Th        = 0x80u; //!< register definition
    static constexpr uint8_t SourceSink    = 0x40u; //!< register definition
    static constexpr uint8_t SinkSel1      = 0x20u; //!< register definition
    static constexpr uint8_t SinkSel0 	    = 0x10u; //!< register definition
    static constexpr uint8_t NPN           = 0x08u; //!< register definition
    static constexpr uint8_t PushPul       = 0x04u; //!< register definition
    static constexpr uint8_t DrvDis        = 0x02u; //!< register definition
    static constexpr uint8_t CQFilterEn    = 0x01u; //!< register definition

    static constexpr uint8_t CyclTmrA 	    = 0x12u; //!< register definition
    static constexpr uint8_t CyclTmrB      = 0x12u; //!< register definition
    static constexpr uint8_t TCyclBs1      = 0x80u; //!< register definition
    static constexpr uint8_t TCyclBs0      = 0x40u; //!< register definition
    static constexpr uint8_t TCyclM5       = 0x20u; //!< register definition
    static constexpr uint8_t TCyclM4       = 0x10u; //!< register definition
    static constexpr uint8_t TCyclM3       = 0x08u; //!< register definition
    static constexpr uint8_t TCyclM2       = 0x04u; //!< register definition
    static constexpr uint8_t TCyclM1       = 0x02u; //!< register definition
    static constexpr uint8_t TCyclM0       = 0x01u; //!< register definition

    static constexpr uint8_t DeviceDlyA    = 0x14u; //!< register definition
    static constexpr uint8_t DeviceDlyB    = 0x15u; //!< register definition
    static constexpr uint8_t DelayErr      = 0x80u; //!< register definition
    static constexpr uint8_t BDelay1       = 0x40u; //!< register definition
    static constexpr uint8_t BDelay0       = 0x20u; //!< register definition
    static constexpr uint8_t DDelay3       = 0x10u; //!< register definition
    static constexpr uint8_t DDelay2       = 0x08u; //!< register definition
    static constexpr uint8_t DDelay1       = 0x04u; //!< register definition
    static constexpr uint8_t DDelay0       = 0x02u; //!< register definition
    static constexpr uint8_t RspnsTmrEn    = 0x01u; //!< register definition

    static constexpr uint8_t TrigAssgnA    = 0x16u; //!< register definition
    static constexpr uint8_t TrigAssgnB    = 0x17u; //!< register definition
    static constexpr uint8_t Trig3         = 0x80u; //!< register definition
    static constexpr uint8_t Trig2         = 0x40u; //!< register definition
    static constexpr uint8_t Trig1         = 0x20u; //!< register definition
    static constexpr uint8_t Trig0         = 0x10u; //!< register definition
    static constexpr uint8_t TrigEn        = 0x01u; //!< register definition

    static constexpr uint8_t LCnfgA        = 0x18u; //!< register definition
    static constexpr uint8_t LCnfgB        = 0x19u; //!< register definition
    static constexpr uint8_t LRT1          = 0x80u; //!< register definition
    static constexpr uint8_t LRT0          = 0x40u; //!< register definition
    static constexpr uint8_t LDynBL        = 0x20u; //!< register definition
    static constexpr uint8_t LBL1          = 0x10u; //!< register definition
    static constexpr uint8_t LBL0          = 0x08u; //!< register definition
    static constexpr uint8_t LCL2x         = 0x04u; //!< register definition
    static constexpr uint8_t LClimDis      = 0x02u; //!< register definition
    static constexpr uint8_t LEn           = 0x01u; //!< register definition

    static constexpr uint8_t IOStCfgA      = 0x1Au; //!< register definition
    static constexpr uint8_t IOStCfgB      = 0x1Bu; //!< register definition
    static constexpr uint8_t DiLevel       = 0x80u; //!< register definition
    static constexpr uint8_t CQLevel       = 0x40u; //!< register definition
    static constexpr uint8_t TxEn          = 0x20u; //!< register definition
    static constexpr uint8_t Tx            = 0x10u; //!< register definition
    static constexpr uint8_t DiFilterEn    = 0x08u; //!< register definition
    static constexpr uint8_t DiEC3Th       = 0x04u; //!< register definition
    static constexpr uint8_t DiCSource     = 0x02u; //!< register definition
    static constexpr uint8_t DiCSink       = 0x01u; //!< register definition

    static constexpr uint8_t DrvrCurrLim   = 0x1Cu; //!< register definition
    static constexpr uint8_t CL1           = 0x80u; //!< register definition
    static constexpr uint8_t CL0           = 0x40u; //!< register definition
    static constexpr uint8_t CLDis         = 0x20u; //!< register definition
    static constexpr uint8_t CLBL1         = 0x10u; //!< register definition
    static constexpr uint8_t CLBL0         = 0x08u; //!< register definition
    static constexpr uint8_t TAr1          = 0x04u; //!< register definition
    static constexpr uint8_t TAr0          = 0x02u; //!< register definition
    static constexpr uint8_t ArEn          = 0x01u; //!< register definition

    static constexpr uint8_t Clock         = 0x1Du; //!< register definition
    static constexpr uint8_t VCCWarnEn     = 0x80u; //!< register definition
    static constexpr uint8_t TXTXENDis     = 0x40u; //!< register definition
    static constexpr uint8_t ExtClkMis     = 0x20u; //!< register definition
    static constexpr uint8_t ClkOEn        = 0x10u; //!< register definition
    static constexpr uint8_t ClkDiv1       = 0x08u; //!< register definition
    static constexpr uint8_t ClkDiv0       = 0x04u; //!< register definition
    static constexpr uint8_t ExtClkEn      = 0x02u; //!< register definition
    static constexpr uint8_t XtalEn        = 0x01u; //!< register definition

    static constexpr uint8_t Status        = 0x1Eu; //!< register definition
    static constexpr uint8_t ThShdnCOR     = 0x80u; //!< register definition
    static constexpr uint8_t ThWarnCOR     = 0x40u; //!< register definition
    static constexpr uint8_t VCCUVCOR      = 0x20u; //!< register definition
    static constexpr uint8_t VCCWarnCOR    = 0x10u; //!< register definition
    static constexpr uint8_t ThShdn        = 0x08u; //!< register definition
    static constexpr uint8_t TempWarn      = 0x04u; //!< register definition
    static constexpr uint8_t VCCUV         = 0x02u; //!< register definition
    static constexpr uint8_t VCCWarn       = 0x01u; //!< register definition

    static constexpr uint8_t RevID         = 0x1Fu; //!< register definition
    static constexpr uint8_t ID3           = 0x08u; //!< register definition
    static constexpr uint8_t ID2           = 0x04u; //!< register definition
    static constexpr uint8_t ID1           = 0x02u; //!< register definition
    static constexpr uint8_t ID0           = 0x01u; //!< register definition

    static constexpr uint8_t MAX_REG       = RevID; //!< register definition
    //! \}

    static constexpr uint8_t MAX_MSG_LENGTH= 64; //!< maximal number of bytes to send (according to max14819 FIFO length)

    //!*****************************************************************************
    //!  \brief Abstract class for io pins
    //!
    //!         This is an abstract class which is needed to set pins from the
    //!         max14819 class itself.
    //!
    //!  \note  This abstract class must be implemented for the used hardware.
    //!
    //!*****************************************************************************
    class PIN
    {
    private:
        /* data */
    public:
        PIN(/* args */){};
        virtual ~PIN(){};

        //!*****************************************************************************
        //!  \brief Sets the state of an IO-Pin
        //!  
        //!  
        //!  \param state set to this
        //!  
        //!*****************************************************************************
        virtual void set(bool state){};
    };

    //!*****************************************************************************
    //!  \brief Abstract class for SPI Communication
    //!
    //!         To communicate with the MAX14819 chip a SPI interface is needed.
    //!
    //!  \note  This abstract class must be implemented for the used hardware.
    //!
    //!*****************************************************************************
    class SPI
    {
    private:
        /* data */
    public:
        SPI(/* args */){};
        virtual ~SPI(){};

        //!*****************************************************************************
        //!  \brief Reads and writes data
        //!         
        //!         Sends the data with the specified length and writes the answer to 
        //!         the source location of the data
        //!
        //!  \param data    Pointer to the data to send. It will be overwritten with
        //!                 the answer
        //!
        //!  \param length  Length of the data to send and receive.
        //!
        //!*****************************************************************************
        virtual void DataRW(uint8_t* data, uint8_t length) = 0;
    };

    //!*****************************************************************************
    //!  \brief Abstract class of an output to write strings
    //!
    //!         The MAX14819 class needs an oportunity to wait some ms.
    //!
    //!  \note This abstract class must be implemented for the used hardware.
    //!
    //!*****************************************************************************
    class DebugOut
    {
    private:
        /* data */
    public:
        DebugOut(/* args */){};
        virtual ~DebugOut(){};

        //!*****************************************************************************
        //!  \brief Printout a string
        //!  
        //!  
        //!  \param buf pointer to an string
        //!  
        //!*****************************************************************************
        virtual void print(char const * buf){};
    };
    
    //!*****************************************************************************
    //!  \brief Abstract class to wait some time
    //!  
    //!  
    //!*****************************************************************************
    class Wait
    {
    private:
        /* data */
    public:
        Wait(){};
        virtual ~Wait(){};
        
        //!*****************************************************************************
        //!  \brief Blocking function to wait the given time in ms
        //!  
        //!  
        //!  \param ms  time to wait in ms
        //!  
        //!*****************************************************************************
        virtual void ms(uint32_t ms){};
    };

    //!*****************************************************************************
    //!  \brief Class to create the two IO-Link ports on the 
    //!  
    //!         Each MAX14819 chip has two IO-Link ports. This class is used to 
    //!         create two ports with one chip.
    //!  
    //!*****************************************************************************
    class Max14819_Port : public openiolinklibrary::IOLMasterPort
    {
    public:
        //!*****************************************************************************
        //!  \brief Saves some information about the communication
        //!  
        //!  
        //!*****************************************************************************
        struct CommunicationInfo
        {
            uint8_t comSpeed;   //!< Communication speed in the register
            uint32_t comSpeedBaud;  //!< Communication speed in baud
        };

        //!*****************************************************************************
        //!  \brief enumerates PORTA and PORTB
        //!  
        //!  
        //!*****************************************************************************
        enum class PortNr {PORTA=0, PORTB=1};

    private:
        PortNr portnr;  //!< describes which port of the chip the object is
        std::shared_ptr<Max14819> chip; //!< a reference to the chip, used for SPI etc.
        CommunicationInfo communicationInfo;
    
    protected:
        //!*****************************************************************************
        //!  \brief Sends data over IO-Link
        //!  
        //!  
        //!  \param data pointer to the data to send 
        //!  
        //!  \param sizeofdata length of the data to send
        //!  
        //!  \param sizeofanswer length of the expected answer
        //!  
        //!  \return uint8_t 0 if success
        //!  
        //!*****************************************************************************
        uint8_t sendIOLData(uint8_t* data, uint8_t sizeofdata, uint8_t sizeofanswer);

        //!*****************************************************************************
        //!  \brief Reads data from IO-Link
        //!  
        //!  
        //!  \param data pointer to the destination of the data
        //!  
        //!  \param sizeofdata length of the expected data
        //!  
        //!  \return uint8_t 0 if success
        //!  
        //!*****************************************************************************
        uint8_t readIOLData(uint8_t* data, uint8_t sizeofdata);
        
    public:
        //!*****************************************************************************
        //!  \brief Construct a new Max14819_Port object
        //!  
        //!  
        //!  \param portnr_ defines if the initialized port is either PORTA or PORTB
        //!  
        //!  \param chip_ pointer to the chip which contains this port
        //!  
        //!*****************************************************************************
        Max14819_Port(PortNr portnr_, std::shared_ptr<Max14819> chip_): portnr(portnr_), chip(chip_){};

        //!*****************************************************************************
        //!  \brief Destroy the Max14819_Port object
        //!  
        //!  
        //!*****************************************************************************
        ~Max14819_Port(){};

        //!*****************************************************************************
        //!  \brief Set the port to this mode
        //!  
        //!  
        //!*****************************************************************************
        void setMode(Mode);

        //!*****************************************************************************
        //!  \brief Sends an WURQ over IO-Link
        //!  
        //!  
        //!*****************************************************************************
        void wakeUpRequest();

        // TODO enableCyclicSend
        // TODO disableCyclicSend
        // TODO enableLedControl
        // TODO disableLedControl
        // TODO writeLED
        // TODO writeDIConfig
        // TODO readDIConfig
        // TODO readCQ
        // TODO writeCQ
        // TODO writeDI

        //!*****************************************************************************
        //!  \brief Get the Communication Info object
        //!  
        //!  
        //!  \return CommunicationInfo
        //!  
        //!*****************************************************************************
        CommunicationInfo getCommunicationInfo(){return communicationInfo;};
    };
    
    
private:
    std::shared_ptr<PIN> ErrLED=nullptr;
    std::shared_ptr<PIN> StatLED=nullptr;
    std::shared_ptr<SPI> spi_interface;
    std::shared_ptr<DebugOut> debug_interface;
    std::shared_ptr<Wait> wait;

    uint8_t spi_address;

    std::shared_ptr<Max14819_Port> PORTA;
    std::shared_ptr<Max14819_Port> PORTB;



public:
    //!*****************************************************************************
    //!  \brief Construct a new Max14819 object
    //!
    //!
    //!  \param debugout_ Interface to printout text
    //!
    //!  \param spi_interface_ SPI interface where the chip is connected
    //!
    //!  \param spi_address_ The SPI address of the chip
    //!
    //!  \param wait_ Class to be able to wait some time
    //!
    //!*****************************************************************************
    Max14819(std::shared_ptr<DebugOut> debugout_, std::shared_ptr<SPI> spi_interface_, uint8_t spi_address_, std::shared_ptr<Wait> wait_);

    //!*****************************************************************************
    //!  \brief Destroy the Max14819 object
    //!
    //!
    //!*****************************************************************************
    ~Max14819();

    //!*****************************************************************************
    //!  \brief Initializes both ports of the chip
    //!  
    //!  
    //!*****************************************************************************
    void initPorts(void);

    //!*****************************************************************************
    //!  \brief Resets the whole chip
    //!  
    //!  
    //!  \return uint8_t 0 if success
    //!  
    //!*****************************************************************************
    uint8_t reset(void);

    //!*****************************************************************************
    //!  \brief Writes data into an register
    //!  
    //!  
    //!  \param reg register definition
    //!  
    //!  \param data byte to write
    //!  
    //!  \return uint8_t 0 if success
    //!  
    //!*****************************************************************************
    uint8_t writeRegister(uint8_t reg, uint8_t data);

    //!*****************************************************************************
    //!  \brief Reads data from register
    //!  
    //!  
    //!  \param reg register definition
    //!  
    //!  \return uint8_t byte read from the register
    //!  
    //!*****************************************************************************
    uint8_t readRegister(uint8_t reg);

    //!*****************************************************************************
    //!  \brief Get one of the ports
    //!  
    //!  
    //!  \param port defines the port to return, either PORTA or PORTB
    //!  
    //!  \return std::shared_ptr<Max14819_Port> pointer to the port
    //!  
    //!*****************************************************************************
    std::shared_ptr<Max14819_Port> getPort(Max14819_Port::PortNr port);
};// class max14819

#endif //MAX14819_HPP_INCLUDED
