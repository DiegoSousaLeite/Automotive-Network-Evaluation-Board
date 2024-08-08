#ifndef MENU_OPTIONS_INTERFACE_H
#define MENU_OPTIONS_INTERFACE_H

class MenuOptionsInterface {
public:
    static constexpr char OPT_MCU_INTERFACE_TEST = '0';
    static constexpr char OPT_COMMUNICATION_TEST = '1';
    static constexpr char OPT_DIGITAL_INPUT_TEST = '2';
    static constexpr char OPT_ANALOG_INPUT_TEST = '3';
    static constexpr char OPT_ANALOG_OUTPUT_TEST = '4';
    static constexpr char OPT_CAN_INIT_TEST = '5';
    static constexpr char OPT_LOOPBACK_CAN_TEST = '6';
    static constexpr char OPT_CAN1_NETWORK_TEST = '7';
    static constexpr char OPT_CAN2_NETWORK_TEST = '8';
    static constexpr char OPT_LIN_NETWORK_TEST = '9';
    static constexpr char OPT_FIRMWARE_UPLOAD = 'g';
    static constexpr char OPT_REPORT_TEST = 'e';
    static constexpr char OPT_REPORT_ALL_TEST = 'f';
    static constexpr char OPT_EXECUTE_ALL_TEST = 'a';
    static constexpr char OPT_LOAD_SERIAL_PORT_TEST = 's';

    static constexpr char OPT_ECU1_SEL = '1';
    static constexpr char OPT_ECU2_SEL = '2';
    static constexpr char OPT_ECU3_SEL = '3';
    static constexpr char OPT_ECU4_SEL = '4';
    static constexpr char OPT_MCU1_SEL = '5';
    static constexpr char OPT_ALL_SEL = '6';

    static constexpr char OPT_ATMEGA328P_OLD = '1';
    static constexpr char OPT_ATMEGA328P = '2';

    static constexpr char OPT_IDENTIFY_COMM_PORT = '1';
    static constexpr char OPT_SELECT_CANBUS1 = '2';
    static constexpr char OPT_SELECT_CANBUS2 = '3';
    static constexpr char OPT_SET_EXT_RST = '4';
    static constexpr char OPT_RESET_EXT_RST = '5';
    static constexpr char OPT_RESET_EXT_RTT = '6';

    static constexpr char OPT_CAN1_NETWORK_ECU12_TEST = '0';
    static constexpr char OPT_CAN1_NETWORK_ECU13_TEST = '1';
    static constexpr char OPT_CAN1_NETWORK_ECU14_TEST = '2';
    static constexpr char OPT_CAN1_NETWORK_ECU23_TEST = '3';
    static constexpr char OPT_CAN1_NETWORK_ECU24_TEST = '4';
    static constexpr char OPT_CAN1_NETWORK_ECU34_TEST = '5';

    static constexpr char OPT_CAN2_NETWORK_ECU23_TEST = '1';
    static constexpr char OPT_CAN2_NETWORK_ECU24_TEST = '2';
    static constexpr char OPT_CAN2_NETWORK_ECU34_TEST = '3';

    static constexpr char OPT_SERIAL_MODE = '4';
    static constexpr char OPT_START_TEST = '1';

    static constexpr char OPT_SERIAL_PROG = '1';
    static constexpr char OPT_USB_PROG = '2';
};


#endif // MENU_OPTIONS_INTERFACE_H
