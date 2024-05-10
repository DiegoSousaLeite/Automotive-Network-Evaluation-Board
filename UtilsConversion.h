#include <QString>
#include <QDir>

class UtilsConversion {
public:
    static short hexToShort(const QString &hexStr) {
        bool ok;
        return static_cast<short>(hexStr.toInt(&ok, 16));
    }

    static QVector<int> parseBinary(int num) {
        QVector<int> binary(4, 0);
        int index = 0;
        while (num > 0 && index < binary.size()) {
            binary[index++] = num % 2;
            num /= 2;
        }
        return binary;
    }

    static bool isPathValid(const QString &path) {
        QDir dir(path);
        return dir.exists();
    }
};
