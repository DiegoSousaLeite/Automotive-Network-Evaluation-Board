#ifndef ATCOMMANDCONSTANTS_H
#define ATCOMMANDCONSTANTS_H

class AtCommandConstants {
public:
    // AT Commands for ECU
    static constexpr char AT_DI_CMD[] = "AT DI";
    static constexpr char AT_AI_CMD[] = "AT AI";
    static constexpr char AT_AO_CMD[] = "AT AO";
    static constexpr char AT_CS_CMD[] = "AT CS";
    static constexpr char AT_CL_CMD[] = "AT CL";
    static constexpr char AT_C1_CMD[] = "AT C1";
    static constexpr char AT_C2_CMD[] = "AT C2";
    static constexpr char AT_LN_CMD[] = "AT LN";

    // AT Commands for MCU
    static constexpr char AT_SL_CMD[] = "AT SL";
    static constexpr char AT_SU_CMD[] = "AT SU";
    static constexpr char AT_SD_CMD[] = "AT SD";
    static constexpr char AT_SV_CMD[] = "AT SV";
    static constexpr char AT_SB_CMD[] = "AT SB";
    static constexpr char AT_BV_CMD[] = "AT BV";
    static constexpr char AT_RU_CMD[] = "AT RU";
    static constexpr char AT_RD_CMD[] = "AT RD";
    static constexpr char AT_RT_CMD[] = "AT RT";

    // Common
    static constexpr char AT_BI_CMD[] = "AT BI";

    // Change to programmer mode
    static constexpr char AT_PM_CMD[] = "!";
    // Change to serial mode
    static constexpr char AT_SM_CMD[] = "@";
    // Checking programmer mode
    static constexpr char AT_CM_CMD[] = "?";

    // Status messages
    static constexpr char AT_ECU1_OK[] = "ECU1 OK";
    static constexpr char AT_ECU2_OK[] = "ECU2 OK";
    static constexpr char AT_ECU3_OK[] = "ECU3 OK";
    static constexpr char AT_ECU4_OK[] = "ECU4 OK";
    static constexpr char AT_MCU1_OK[] = "MCU1 OK";
    static constexpr char AT_PROG_OK[] = "PROG OK";
    static constexpr char AT_PROG_SM[] = "PROG SM";
    static constexpr char AT_PROG_PM[] = "PROG PM";
    static constexpr char AT_ECU1_ERR[] = "ECU1 CM E00";
    static constexpr char AT_ECU2_ERR[] = "ECU2 CM E00";
    static constexpr char AT_ECU3_ERR[] = "ECU3 CM E00";
    static constexpr char AT_ECU4_ERR[] = "ECU4 CM E00";
    static constexpr char AT_MCU1_ERR[] = "MCU1 CM E00";
    static constexpr char AT_PROG_ERR[] = "PROG CM E00";
};

#endif // ATCOMMANDCONSTANTS_H
