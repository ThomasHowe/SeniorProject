
//Thomas Howe, Alan Kwok
//11/16/2016

//Modified from https://www.ccsinfo.com/forum/viewtopic.php?t=54957 for use on STM32L053

#DEFINE 
packet txbuffer[100]
packet rxbuffer[100]
recievelength=0;

// Strobe commands 
#define SRES 0x30 // Reset chip. 
#define SFSTXON 0x31 // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL = 1). 
// If in RX / TX: Go to a wait state where only the synthesizer is 
// Running (for quick RX / TX turnaround). 
#define SXOFF 0x32 // Turn off crystal oscillator. 
#define SCAL 0x33 // Calibrate frequency synthesizer and turn it off 
// (Enables quick start). 
#define SRX 0x34 // Enable RX. Perform calibration first if coming from IDLE and 
// MCSM0.FS_AUTOCAL = 1. 
#define STX 0x35 // In IDLE state: Enable TX. Perform calibration first if 
// MCSM0.FS_AUTOCAL = 1. If in RX state and CCA is enabled: 
// Only go to TX if channel is clear. 
#define SIDLE 0x36 // Exit RX / TX, turn off frequency synthesizer and exit 
// Wake-On-Radio mode if applicable. 
#define SAFC 0x37 // Perform AFC adjustment of the frequency synthesizer 
#define SWOR 0x38 // Start automatic RX polling sequence (Wake-on-Radio) 
#define SPWD 0x39 // Enter power down mode when CSn goes high. 
#define SFRX 0x3A // Flush the RX FIFO buffer. 
#define SFTX 0x3B // Flush the TX FIFO buffer. 
#define SWORRST 0x3C // Reset real time clock. 
#define SNOP 0x3D // No operation. May be used to pad strobe commands to two 
// int8s for simpler software. 
#define PARTNUM 0x30 
#define VERSION 0x31 
#define FREQEST 0x32 
#define LQI 0x33 
#define RSSI 0x34 
#define MARCSTATE 0x35 
#define WORTIME1 0x36 
#define WORTIME0 0x37 
#define PKTSTATUS 0x38 
#define VCO_VC_DAC 0x39 
#define TXBYTES 0x3A 
#define RXBYTES 0x3B 
#define PATABLE 0x3E 
#define TXFIFO 0x3F 
#define RXFIFO 0x3F 

//Imported from SmartRF Studio
// RF settings for CC1101

typedef struct {
    uint8 iocfg0;     // GDO0 Output Pin Configuration
    uint8 fifothr;    // RX FIFO and TX FIFO Thresholds
    uint8 pktctrl0;   // Packet Automation Control
    uint8 fsctrl1;    // Frequency Synthesizer Control
    uint8 freq2;      // Frequency Control Word, High Byte
    uint8 freq1;      // Frequency Control Word, Middle Byte
    uint8 freq0;      // Frequency Control Word, Low Byte
    uint8 mdmcfg4;    // Modem Configuration
    uint8 mdmcfg3;    // Modem Configuration
    uint8 mdmcfg2;    // Modem Configuration
    uint8 deviatn;    // Modem Deviation Setting
    uint8 mcsm0;      // Main Radio Control State Machine Configuration
    uint8 foccfg;     // Frequency Offset Compensation Configuration
    uint8 worctrl;    // Wake On Radio Control
    uint8 frend0;     // Front End TX Configuration
    uint8 fscal3;     // Frequency Synthesizer Calibration
    uint8 fscal2;     // Frequency Synthesizer Calibration
    uint8 fscal1;     // Frequency Synthesizer Calibration
    uint8 fscal0;     // Frequency Synthesizer Calibration
    uint8 test2;      // Various Test Settings
    uint8 test1;      // Various Test Settings
    uint8 test0;      // Various Test Settings
} RF_SETTINGS;

//Imported from SmartRF Studio
// Rf settings for CC1101
RF_SETTINGS code rfSettings = {
    0x06,  // IOCFG0        GDO0 Output Pin Configuration
    0x47,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
    0x05,  // PKTCTRL0      Packet Automation Control
    0x06,  // FSCTRL1       Frequency Synthesizer Control
    0x21,  // FREQ2         Frequency Control Word, High Byte
    0x62,  // FREQ1         Frequency Control Word, Middle Byte
    0x76,  // FREQ0         Frequency Control Word, Low Byte
    0xF5,  // MDMCFG4       Modem Configuration
    0x83,  // MDMCFG3       Modem Configuration
    0x33,  // MDMCFG2       Modem Configuration
    0x15,  // DEVIATN       Modem Deviation Setting
    0x18,  // MCSM0         Main Radio Control State Machine Configuration
    0x16,  // FOCCFG        Frequency Offset Compensation Configuration
    0xFB,  // WORCTRL       Wake On Radio Control
    0x11,  // FREND0        Front End TX Configuration
    0xE9,  // FSCAL3        Frequency Synthesizer Calibration
    0x2A,  // FSCAL2        Frequency Synthesizer Calibration
    0x00,  // FSCAL1        Frequency Synthesizer Calibration
    0x1F,  // FSCAL0        Frequency Synthesizer Calibration
    0x81,  // TEST2         Various Test Settings
    0x35,  // TEST1         Various Test Settings
    0x09,  // TEST0         Various Test Settings
};

int8_t spibyte (int8_t data) {
    int8_t i = 0;
    int8_t temp = 0;
    //SCK low output
    for (i = 0; i < 8; i++) {
        if (data & 0x80) ;//output high MOSI
        else ;//output low MOSI
        
        data <<= 1;
        delay(whatever amount);
        //output high SCK
        temp <<= 1;
        if (/**/) {
            temp++;    
        }
        delay(whatever amount);
        //output low SCK
    }
    return temp;
}

int8_t spireadreg (int8_t address) {
    int8_t temp = 0;
    int8_t value = 0;
    temp = address | 0x80; // read register command 
    output_low(CS); 
    while (input(MISO)); 
    spibyte (temp); 
    value = spibyte (0); 
    output_high(CS); 
    return value;     
}

void halRFWriteReg (int8 addr, int8 value) {
    //CS Out Low
    while ();           //input MISO
    spibyte (addr);     //Address
    spibyte (value);    //Configuration
    //CS out high
}

void burstwrite(packet address, packet count) {
    int8_t i = 0;
    
    //low CS output
    while (/*input MISO*/);
    spibyte(address | 0x80) {
        delay(whatever value);
        for(i = 0; i < count; i++) {
            spibyte(txbuffer[i]);
            delay(whatever value);
        }           
    }
    //CS output high
}

void halSpiStrobe(packet strobe) { 
   output_low(CS); 
   while (input(MISO)); 
   spibyte (strobe); // write address 
   output_high(CS); 
}

packet halSPIreadstat(packet address) {
   int8_t val; 

   output_low(CS); 
   while (input(MISO)); 
   spibyte (address|0x80); 
   // SPI_WAIT 
   val=spibyte (0); 
   // SPI_WAIT 
   output_high(CS); 
   return val;         
}

packet halSPIreadburst(packet address, packet count) {
    int8_t i = 0;
    packet values;
    
    output_low(CS);
    while (input(MISO));
    spibyte (address|0xC0);
    values = spibyte(0);
    output_high(CS);
    return values;
}

void halSPIreadburstreg(packet address, packet count) { 
    int8_t i; 
    packet x; 

   output_low(CS); 
   while (input(MISO)); 
   spibyte (address|0xC0); 
//    SPI_WAIT();  
   if(count>(100-5)) count=100-5; 
    for (i = 0; i < count; i++) { 
       x=spibyte (0); 
        //SPI_WAIT(); 
        rxbuffer[i] = x; 
    } 
   output_high(CS); 
} 

//
// Rf settings for CC1101
// Imported from SmartRF Studio
void halRFSettings (void) {
halRfWriteReg(IOCFG0,0x06);  //GDO0 Output Pin Configuration
halRfWriteReg(FIFOTHR,0x47); //RX FIFO and TX FIFO Thresholds
halRfWriteReg(PKTCTRL0,0x05);//Packet Automation Control
halRfWriteReg(FSCTRL1,0x06); //Frequency Synthesizer Control
halRfWriteReg(FREQ2,0x21);   //Frequency Control Word, High Byte
halRfWriteReg(FREQ1,0x62);   //Frequency Control Word, Middle Byte
halRfWriteReg(FREQ0,0x76);   //Frequency Control Word, Low Byte
halRfWriteReg(MDMCFG4,0xF5); //Modem Configuration
halRfWriteReg(MDMCFG3,0x83); //Modem Configuration
halRfWriteReg(MDMCFG2,0x33); //Modem Configuration
halRfWriteReg(DEVIATN,0x15); //Modem Deviation Setting
halRfWriteReg(MCSM0,0x18);   //Main Radio Control State Machine Configuration
halRfWriteReg(FOCCFG,0x16);  //Frequency Offset Compensation Configuration
halRfWriteReg(WORCTRL,0xFB); //Wake On Radio Control
halRfWriteReg(FREND0,0x11);  //Front End TX Configuration
halRfWriteReg(FSCAL3,0xE9);  //Frequency Synthesizer Calibration
halRfWriteReg(FSCAL2,0x2A);  //Frequency Synthesizer Calibration
halRfWriteReg(FSCAL1,0x00);  //Frequency Synthesizer Calibration
halRfWriteReg(FSCAL0,0x1F);  //Frequency Synthesizer Calibration
halRfWriteReg(TEST2,0x81);   //Various Test Settings
halRfWriteReg(TEST1,0x35);   //Various Test Settings
halRfWriteReg(TEST0,0x09);   //Various Test Settings
}

void sendpacket(int8_t size) {
    halRFWriteReg(TXFIFO, size);
    burstwrite(TXFIFO,size);
    halSpiStrobe(STX);
    
    while(!input(GDO));    
    while(input(GDO));
    halSpiStrobe(SFTX);
}
