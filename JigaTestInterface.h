#ifndef JIGATESTCONSTANTS_H
#define JIGATESTCONSTANTS_H

class JigaTestConstants {
public:
    // Board IDs
    static constexpr int ECU1_BOARD_ID = 0;
    static constexpr int ECU2_BOARD_ID = 1;
    static constexpr int ECU3_BOARD_ID = 2;
    static constexpr int ECU4_BOARD_ID = 3;
    static constexpr int MCU1_BOARD_ID = 4;
    static constexpr int PROG_BOARD_ID = 5;
    static constexpr int ALL_BOARDS_ID = 6;

    static constexpr int MAX_NUMBER_BOARDS = 5;

    static constexpr int SERIAL_PROG_ID = 6;
    static constexpr int USB_PROG_ID    = 7;

    // CAN bus identification
    static constexpr int ECU_CANBUS_1   = 0;
    static constexpr int ECU3_CANBUS1   = 1;
    static constexpr int ECU4_CANBUS1   = 2;
    static constexpr int ECU_CANBUS_2   = 3;

    // Type of test
    static constexpr int SINGLE_BOARD_TEST   = 0;
    static constexpr int MULTIPLE_BOARD_TEST = 1;

    static constexpr int COMMUNICATION_TEST    = 1;
    static constexpr int FIRMWARE_UPLOAD       = 2;
    static constexpr int DIGITAL_INPUT_TEST    = 3;
    static constexpr int ANALOG_INPUT_TEST     = 4;
    static constexpr int ANALOG_OUTPUT_TEST    = 5;
    static constexpr int CAN_INIT_TEST         = 6;
    static constexpr int LOOPBACK_CAN_TEST     = 7;
    static constexpr int CAN1_NETWORK_TEST     = 8;
    static constexpr int CAN2_NETWORK_TEST     = 9;
    static constexpr int LIN_NETWORK_TEST      = 10;
    static constexpr int MCU_INTERFACE_TEST   = 11;
    static constexpr int MCU_RST_ACT_TEST      = 12;
    static constexpr int MCU_RST_DAC_TEST      = 13;
    static constexpr int MCU_IDENT_PORT_TEST   = 14;
    static constexpr int MCU_SEL_CANBUS1_TEST  = 15;
    static constexpr int MCU_RST_ATT_TEST      = 16;
    static constexpr int MCU_SEL_CANBUS2_TEST  = 17;
    static constexpr int MCU_GET_CANBUS_TEST   = 18;
    static constexpr int MCU_TOG_ECU3BUS_TEST  = 19;
    static constexpr int MCU_TOG_ECU4BUS_TEST  = 20;

    // Programmer modes
    static constexpr int PROG_SERIAL_MODE     = 0;
    static constexpr int PROG_PROGRAMMER_MODE = 1;
    static constexpr int PROG_UNKNOWN_MODE    = -1;

    // USB-UART
    static constexpr int COMM_ECU1_ITEST = 0;
    static constexpr int COMM_ECU2_ITEST = 1;
    static constexpr int COMM_ECU3_ITEST = 2;
    static constexpr int COMM_ECU4_ITEST = 3;
    static constexpr int COMM_MCU1_ITEST = 4;
    static constexpr int COMM_PROG_ITEST = 5;

    // Digital input
    static constexpr int DIN1_INPUT_ITEST = 6;
    static constexpr int DIN2_INPUT_ITEST = 7;
    static constexpr int DIN3_INPUT_ITEST = 8;
    static constexpr int DIN4_INPUT_ITEST = 9;
    static constexpr int MSE1_INPUT_ITEST = 10;
    static constexpr int MSE2_INPUT_ITEST = 11;

    // Analog input
    static constexpr int AIN1_INPUT_ITEST = 12;
    static constexpr int AIN2_INPUT_ITEST = 13;
    static constexpr int AIN3_INPUT_ITEST = 14;
    static constexpr int AIN4_INPUT_ITEST = 15;

    // Analog output
    static constexpr int AOUT1_LDR_ITEST  = 16;
    static constexpr int AOUT2_LOOP_ITEST = 17;

    // CAN Controller initialization
    static constexpr int ICAN1_ECU1_ITEST = 18;
    static constexpr int ICAN1_ECU2_ITEST = 19;
    static constexpr int ICAN2_ECU2_ITEST = 20;
    static constexpr int ICAN1_ECU3_ITEST = 21;
    static constexpr int ICAN1_ECU4_ITEST = 22;

    // Loopback CAN
    static constexpr int LBC1_ECU1_ITEST = 23;
    static constexpr int LBC1_ECU2_ITEST = 24;
    static constexpr int LBC2_ECU2_ITEST = 25;
    static constexpr int LBC1_ECU3_ITEST = 26;
    static constexpr int LBC1_ECU4_ITEST = 27;

    // CAN1BUS Network
    static constexpr int CAN1_ECU1_ITEST = 28;
    static constexpr int CAN1_ECU2_ITEST = 29;
    static constexpr int CAN1_ECU3_ITEST = 30;
    static constexpr int CAN1_ECU4_ITEST = 31;

    // CAN2BUS Network
    static constexpr int CAN2_ECU2_ITEST = 32;
    static constexpr int CAN2_ECU3_ITEST = 33;
    static constexpr int CAN2_ECU4_ITEST = 34;

    // Lin Network
    static constexpr int LIN1_ECU3_ITEST = 35;
    static constexpr int LIN1_ECU4_ITEST = 36;

    // MCU Interface Test
    static constexpr int MCU_GET_CANBUS_ITEST  = 37;
    static constexpr int MCU_RST_ACT_ITEST     = 38;
    static constexpr int MCU_RST_DAC_ITEST     = 39;
    static constexpr int MCU_IDENT_PORT_ITEST  = 40;
    static constexpr int MCU_SEL_CANBUS1_ITEST = 41;
    static constexpr int MCU_RST_ATT_ITEST     = 42;
    static constexpr int MCU_SEL_CANBUS2_ITEST = 43;
    static constexpr int MCU_TOG_ECU3BUS_ITEST = 44;
    static constexpr int MCU_TOG_ECU4BUS_ITEST = 45;

    // Timeout durations
    static constexpr int COMMUNICATION_TEST_TIMEOUT = 5;
    static constexpr int DIGITAL_INPUT_TEST_TIMEOUT = 12;
    static constexpr int ANALOG_INPUT_TEST_TIMEOUT  = 22;
    static constexpr int ANALOG_OUTPUT_TEST_TIMEOUT = 32;
    static constexpr int CAN_INIT_TEST_TIMEOUT      = 2;
    static constexpr int CAN_NETWORK_TEST_TIMEOUT   = 12;
    static constexpr int LIN_NETWORK_TEST_TIMEOUT   = 8;
    static constexpr int MCU_CANBUS_TEST_TIMEOUT    = 2;

    // Offset values
    static constexpr int COMMUNICATION_TEST_OFFSET = 0;
    static constexpr int DIGITAL_INPUT_TEST_OFFSET = 2;
    static constexpr int ANALOG_INPUT_TEST_OFFSET  = 2;
    static constexpr int ANALOG_OUTPUT_TEST_OFFSET = 2;
    static constexpr int CAN_NETWORK_TEST_OFFSET   = 2;
    static constexpr int LIN_NETWORK_TEST_OFFSET   = 2;
    static constexpr int MCU_CANBUS_TEST_OFFSET    = 0;

    // AT command timeouts
    static constexpr int MCU_AT_COMMAND_TIMEOUT = 300;
    static constexpr int ECU_AT_COMMAND_TIMEOUT = 100;

    // Test results
    static constexpr int ERROR_TO_EXECUTE_TEST = -1;
    static constexpr int SUCCESS_EXECUTE_TEST  = 0;
};

#endif // JIGATESTCONSTANTS_H
