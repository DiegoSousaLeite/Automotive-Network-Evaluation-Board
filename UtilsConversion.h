// UtilsConversion.h
#ifndef UTILSCONVERSION_H
#define UTILSCONVERSION_H

#include <QString>

class UtilsConversion {
public:
    static uint16_t hexToShort(const QString &hexString) {
        bool ok;
        return static_cast<uint16_t>(hexString.toUShort(&ok, 16));
    }
};

#endif // UTILSCONVERSION_H
