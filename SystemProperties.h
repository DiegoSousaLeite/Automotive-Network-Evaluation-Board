#ifndef SYSTEMPROPERTIES_H
#define SYSTEMPROPERTIES_H

#include <QSettings>
#include <QDir>
#include <QStandardPaths>
#include "JigaTestInterface.h"

class SystemProperties {
public:
    static constexpr auto TEST_RESULT_PROPERTY     = "test.result";
    static constexpr auto TEST_STATE_PROPERTY      = "test.state";
    static constexpr auto TEST_MESSAGE_PROPERTY    = "test.message";
    static constexpr auto USER_DIRECTORY           = "user.dir";
    static constexpr auto MCU_DIRECTORY            = "mcu.dir";
    static constexpr auto MCU_APPLICATION          = "mcu.app";
    static constexpr auto MCU_BOOTLOADER           = "mcu.boot";
    static constexpr auto AVRDUDE_PROGRAM          = "avrdude.exe";
    static constexpr auto AVRDUDE_CONFIG           = "avrdude.conf";
    static constexpr auto MCU_OPT_PROG             = "mcu.opt.prog";
    static constexpr auto ECU_OPT_PROG             = "ecu.opt.prog";
    static constexpr auto MCU_OPT_FUSE             = "mcu.opt.fuse";
    static constexpr auto MCU_OPT_BOOT1            = "mcu.opt.boot1";
    static constexpr auto MCU_OPT_BOOT2            = "mcu.opt.boot2";
    static constexpr auto MCU_PROG_BAUDRATE        = "mcu.prog.baudrate";
    static constexpr auto ECU_OLD_PROG_BAUDRATE    = "ecu.old.baudrate";
    static constexpr auto ECU_NEW_PROG_BAUDRATE    = "ecu.new.baudrate";
    static constexpr auto ECU_APP_BAUDRATE         = "ecu.app.baudrate";
    static constexpr auto MCU_APP_BAUDRATE         = "mcu.app.baudrate";
    static constexpr auto MCU_PROG_USB             = "mcu.prog.usb";
    static constexpr auto MCU_APP_VID              = "mcu.app.vid";
    static constexpr auto MCU_APP_PID              = "mcu.app.pid";
    static constexpr auto MCU_PROG_VID             = "mcu.prog.vid";
    static constexpr auto MCU_PROG_PID             = "mcu.prog.pid";
    static constexpr auto MCU_PROG_SERIAL          = "mcu.prog.serial";
    static constexpr auto MCU_PORT_DESCRIPTION     = "mcu.port.desc";
    static constexpr auto MCU_DESC_PORT_NAME       = "mcu.desc.port";
    static constexpr auto ECU_PORT_DESCRIPTION     = "ecu.port.desc";
    static constexpr auto ECU_DESC_PORT_NAME       = "ecu.desc.port";
    static constexpr auto ECU_VID                  = "ecu.vid";
    static constexpr auto ECU_PID                  = "ecu.pid";
    static constexpr auto ECU_APPLICATION          = "ecu.app";
    static constexpr auto ECU_DIRECTORY            = "ecu.dir";
    static constexpr auto SYSTEM_APP_NAME          = "app.name";

    // Report test error
    static constexpr auto REP_COMMT_ECU1_ERR        = "com.ecu1.err";
    static constexpr auto REP_COMMT_ECU2_ERR        = "com.ecu2.err";
    static constexpr auto REP_COMMT_ECU3_ERR        = "com.ecu3.err";
    static constexpr auto REP_COMMT_ECU4_ERR        = "com.ecu4.err";
    static constexpr auto REP_COMMT_MCU1_ERR        = "com.mcu1.err";
    static constexpr auto REP_COMMT_PROG_ERR        = "com.prog.err";

    static constexpr auto REP_DIN1T_ECU1_ERR        = "di1.ecu1.err";
    static constexpr auto REP_DIN1T_ECU2_ERR        = "di1.ecu2.err";
    static constexpr auto REP_DIN1T_ECU3_ERR        = "di1.ecu3.err";
    static constexpr auto REP_DIN1T_ECU4_ERR        = "di1.ecu4.err";

    static constexpr auto REP_DIN2T_ECU1_ERR        = "di2.ecu1.err";
    static constexpr auto REP_DIN2T_ECU2_ERR        = "di2.ecu2.err";
    static constexpr auto REP_DIN2T_ECU3_ERR        = "di2.ecu3.err";
    static constexpr auto REP_DIN2T_ECU4_ERR        = "di2.ecu4.err";

    static constexpr auto REP_DIN3T_ECU1_ERR        = "di3.ecu1.err";
    static constexpr auto REP_DIN3T_ECU2_ERR        = "di3.ecu2.err";
    static constexpr auto REP_DIN3T_ECU3_ERR        = "di3.ecu3.err";
    static constexpr auto REP_DIN3T_ECU4_ERR        = "di3.ecu4.err";

    static constexpr auto REP_DIN4T_ECU1_ERR        = "di4.ecu1.err";
    static constexpr auto REP_DIN4T_ECU2_ERR        = "di4.ecu2.err";
    static constexpr auto REP_DIN4T_ECU3_ERR        = "di4.ecu3.err";
    static constexpr auto REP_DIN4T_ECU4_ERR        = "di4.ecu4.err";

    static constexpr auto REP_AIN1T_ECU1_ERR        = "ai1.ecu1.err";
    static constexpr auto REP_AIN1T_ECU2_ERR        = "ai1.ecu2.err";
    static constexpr auto REP_AIN1T_ECU3_ERR        = "ai1.ecu3.err";
    static constexpr auto REP_AIN1T_ECU4_ERR        = "ai1.ecu4.err";

    static constexpr auto REP_AIN2T_ECU1_ERR        = "ai2.ecu1.err";
    static constexpr auto REP_AIN2T_ECU2_ERR        = "ai2.ecu2.err";
    static constexpr auto REP_AIN2T_ECU3_ERR        = "ai2.ecu3.err";
    static constexpr auto REP_AIN2T_ECU4_ERR        = "ai2.ecu4.err";

    static constexpr auto REP_AIN3T_ECU1_ERR        = "ai3.ecu1.err";
    static constexpr auto REP_AIN3T_ECU2_ERR        = "ai3.ecu2.err";
    static constexpr auto REP_AIN3T_ECU3_ERR        = "ai3.ecu3.err";
    static constexpr auto REP_AIN3T_ECU4_ERR        = "ai3.ecu4.err";

    static constexpr auto REP_AIN4T_ECU1_ERR        = "ai4.ecu1.err";
    static constexpr auto REP_AIN4T_ECU2_ERR        = "ai4.ecu2.err";
    static constexpr auto REP_AIN4T_ECU3_ERR        = "ai4.ecu3.err";
    static constexpr auto REP_AIN4T_ECU4_ERR        = "ai4.ecu4.err";

    static constexpr auto REP_ANOUT_ECU1_ERR        = "io1.ecu1.err";
    static constexpr auto REP_ANOUT_ECU2_ERR        = "io2.ecu2.err";

    // CAN initialization
    static constexpr auto REP_CANIT_ECU1_ERR        = "ci1.ecu1.err";
    static constexpr auto REP_CANIT_ECU2C1_ERR      = "ci1.ecu2.err";
    static constexpr auto REP_CANIT_ECU2C2_ERR      = "ci2.ecu2.err";
    static constexpr auto REP_CANIT_ECU3_ERR        = "ci1.ecu3.err";
    static constexpr auto REP_CANIT_ECU4_ERR        = "ci1.ecu4.err";

    // CAN loopback
    static constexpr auto REP_CAN1L_ECU1_ERR        = "cl1.ecu1.err";
    static constexpr auto REP_CAN1L_ECU2_ERR        = "cl1.ecu2.err";
    static constexpr auto REP_CAN2L_ECU2_ERR        = "cl2.ecu2.err";
    static constexpr auto REP_CAN1L_ECU3_ERR        = "cl1.ecu3.err";
    static constexpr auto REP_CAN1L_ECU4_ERR        = "cl1.ecu4.err";

    // CAN1 Communication
    static constexpr auto REP_CAN1T_EC12_ERR        = "ca1.ec12.err";
    static constexpr auto REP_CAN1T_EC13_ERR        = "ca1.ec13.err";
    static constexpr auto REP_CAN1T_EC14_ERR        = "ca1.ec14.err";

    static constexpr auto REP_CAN1T_EC21_ERR        = "ca1.ec21.err";
    static constexpr auto REP_CAN1T_EC23_ERR        = "ca1.ec23.err";
    static constexpr auto REP_CAN1T_EC24_ERR        = "ca1.ec24.err";

    static constexpr auto REP_CAN1T_EC31_ERR        = "ca1.ec31.err";
    static constexpr auto REP_CAN1T_EC32_ERR        = "ca1.ec32.err";
    static constexpr auto REP_CAN1T_EC34_ERR        = "ca1.ec34.err";

    static constexpr auto REP_CAN1T_EC41_ERR        = "ca1.ec41.err";
    static constexpr auto REP_CAN1T_EC42_ERR        = "ca1.ec42.err";
    static constexpr auto REP_CAN1T_EC43_ERR        = "ca1.ec43.err";

    // CAN2 Communication
    static constexpr auto REP_CAN2T_EC23_ERR        = "ca2.ec23.err";
    static constexpr auto REP_CAN2T_EC24_ERR        = "ca2.ec24.err";

    static constexpr auto REP_CAN2T_EC32_ERR        = "ca2.ec32.err";
    static constexpr auto REP_CAN2T_EC34_ERR        = "ca2.ec34.err";

    static constexpr auto REP_CAN2T_EC42_ERR        = "ca2.ec42.err";
    static constexpr auto REP_CAN2T_EC43_ERR        = "ca2.ec43.err";

    // LIN Communication
    static constexpr auto REP_LINNT_EC34_ERR        = "lin.ec34.err";
    static constexpr auto REP_LINNT_EC43_ERR        = "lin.ec43.err";

    static QString getProperty(const char* key) {
        QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
        QString configFile = QDir(configPath).filePath("settings.ini");
        QSettings settings(configFile, QSettings::IniFormat);
        return settings.value(QString(key)).toString();
    }

    static QString getPortDescription(int boardId) {
        QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
        QString configFile = QDir(configPath).filePath("settings.ini");
        QSettings settings(configFile, QSettings::IniFormat);

        if(boardId == JigaTestInterface::MCU1_BOARD_ID ){
            return settings.value(QString("mcu.port.desc")).toString();
        }else{
            return settings.value(QString("ecu.port.desc")).toString();
        }
    }


};

#endif // SYSTEMPROPERTIES_H
