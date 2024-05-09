#ifndef TIMEOUTMONITOR_H
#define TIMEOUTMONITOR_H

#include <QObject>
#include <QTimer>
#include <type_traits>

class TimeOutListener;

class TimeOutMonitor : public QObject {
    Q_OBJECT

public:
    explicit TimeOutMonitor(QObject *parent = nullptr);
    void setTimeOut(int timeout);
    void setBoardID(int boardID);
    void setTestID(int testID);
    void start();
    void addTimeOutListener(TimeOutListener *listener);

private slots:
    void timeOutExpires();

private:
    QTimer *timer;
    int timeout;
    int boardID;
    int testID;
    QList<TimeOutListener*> listeners;
};

#endif // TIMEOUTMONITOR_H
