#ifndef SYSTEMPROPERTIES_H
#define SYSTEMPROPERTIES_H

#include <QSettings>
#include <QDir>
#include <QStandardPaths>
#include "JigaTestInterface.h"

class SystemProperties {
public:
    static constexpr auto TEST_RESULT_PROPERTY      = "test.result";
    static constexpr auto TEST_STATE_PROPERTY       = "test.state";
    static constexpr auto TEST_MESSAGE_PROPERTY     = "test.message";
    static constexpr auto USER_DIRECTORY            = "user.dir";
    static constexpr auto MCU_DIRECTORY             = "mcu.dir";
    static constexpr auto MCU_APPLICATION           = "mcu.app";
    static constexpr auto MCU_BOOTLOADER            = "mcu.boot";
    static constexpr auto AVRDUDE_PROGRAM           = "avrdude.exe";
    static constexpr auto AVRDUDE_CONFIG            = "avrdude.conf";
    static constexpr auto MCU_OPT_PROG              = "mcu.opt.prog";
    static constexpr auto ECU_OPT_PROG              = "ecu.opt.prog";
    static constexpr auto MCU_OPT_FUSE              = "mcu.opt.fuse";
    static constexpr auto MCU_OPT_BOOT1             = "mcu.opt.boot1";
    static constexpr auto MCU_OPT_BOOT2             = "mcu.opt.boot2";
    static constexpr auto MCU_PROG_BAUDRATE         = "mcu.prog.baudrate";
    static constexpr auto ECU_PROG_BAUDRATE         = "ecu.prog.baudrate";
    static constexpr auto ECU_APP_BAUDRATE          = "ecu.app.baudrate";
    static constexpr auto MCU_APP_BAUDRATE          = "mcu.app.baudrate";
    static constexpr auto MCU_PROG_USB              = "mcu.prog.usb";
    static constexpr auto MCU_PROG_VID              = "mcu.prog.vid";
    static constexpr auto MCU_PROG_PID              = "mcu.prog.pid";
    static constexpr auto MCU_PROG_SERIAL           = "mcu.prog.serial";
    static constexpr auto ECU_PORT_DESCRIPTION      = "ecu.port.desc";
    static constexpr auto ECU_DESC_PORT_NAME        = "ecu.desc.port";
    static constexpr auto MCU_PORT_DESCRIPTION      = "mcu.port.desc";
    static constexpr auto MCU_DESC_PORT_NAME        = "mcu.desc.port";
    static constexpr auto ECU_APPLICATION           = "ecu.app";
    static constexpr auto ECU_DIRECTORY             = "ecu.dir";

    static constexpr auto SYSTEM_APP_NAME           = "app.name";

    static QString getPortDescription(int boardId) {
        QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
        QString configFile = QDir(configPath).filePath("settings.ini");
        QSettings settings(configFile, QSettings::IniFormat);

        if(boardId == JigaTestConstants::MCU1_BOARD_ID ){
            return settings.value(QString("mcu.port.desc")).toString();
        }else{
            return settings.value(QString("ecu.port.desc")).toString();
        }
    }
};

#endif // SYSTEMPROPERTIES_H
