#ifndef MENU_OPTIONS_INTERFACE_H
#define MENU_OPTIONS_INTERFACE_H

namespace MenuOptionsInterface {

constexpr char OPT_MCU_INTERFACE_TEST    = '0';
constexpr char OPT_COMMUNICATION_TEST    = '1';
constexpr char OPT_DIGITAL_INPUT_TEST    = '2';
constexpr char OPT_ANALOG_INPUT_TEST     = '3';
constexpr char OPT_ANALOG_OUTPUT_TEST    = '4';
constexpr char OPT_CAN_INIT_TEST         = '5';
constexpr char OPT_LOOPBACK_CAN_TEST     = '6';
constexpr char OPT_CAN1_NETWORK_TEST     = '7';
constexpr char OPT_CAN2_NETWORK_TEST     = '8';
constexpr char OPT_LIN_NETWORK_TEST      = '9';
constexpr char OPT_FIRMWARE_UPLOAD       = 'g';
constexpr char OPT_REPORT_TEST           = 'e';
constexpr char OPT_EXECUTE_ALL_TEST      = 'a';

constexpr char OPT_ECU1_SEL             = '1';
constexpr char OPT_ECU2_SEL             = '2';
constexpr char OPT_ECU3_SEL             = '3';
constexpr char OPT_ECU4_SEL             = '4';
constexpr char OPT_MCU1_SEL             = '5';
constexpr char OPT_ALL_SEL              = '6';

constexpr char OPT_IDENTIFY_COMM_PORT    = '1';
constexpr char OPT_SELECT_CANBUS1        = '2';
constexpr char OPT_SELECT_CANBUS2        = '3';
constexpr char OPT_SET_EXT_RST           = '4';
constexpr char OPT_RESET_EXT_RST         = '5';
constexpr char OPT_RESET_EXT_RTT         = '6';

constexpr char OPT_SERIAL_MODE           = '4';

constexpr char OPT_START_TEST            = '1';

constexpr char OPT_SERIAL_PROG           = '1';
constexpr char OPT_USB_PROG              = '2';

}

#endif // MENU_OPTIONS_INTERFACE_H
