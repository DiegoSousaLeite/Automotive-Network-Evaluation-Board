#ifndef SERIALCOMMPORT_H
#define SERIALCOMMPORT_H

#include <QString>
#include <QObject>

class SerialCommPort : public QObject
{
    Q_OBJECT

public:
    explicit SerialCommPort(QObject *parent = nullptr);
    SerialCommPort(int portId, const QString &portDescription, QObject *parent = nullptr);

    int getCommPortId() const;
    void setCommPortId(int portId);

    QString getPortDescription() const;
    void setPortDescription(const QString &portDescription);

    QString getDescriptivePortName() const;
    void setDescriptivePortName(const QString &descPortName);

    QString getSystemPortName() const;
    void setSystemPortName(const QString &systemPortName);

    void printSerialCommPortInfo() const;
    QString toString() const;

private:
    int commPortID;
    QString portDescription;
    QString descPortName;
    QString systemPortName;
};

#endif // SERIALCOMMPORT_H
