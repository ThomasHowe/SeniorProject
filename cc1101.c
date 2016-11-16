
//Thomas Howe, Alan Kwok
//11/16/2016

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

//
// Rf settings for CC1101
// Imported from SmartRF Studio

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
