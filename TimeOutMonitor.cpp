#include "TimeOutMonitor.h"
#include "TimeOutListener.h"

TimeOutMonitor::TimeOutMonitor(QObject *parent)
    : QObject(parent) {
    timer = new QTimer(this);
    timer->setSingleShot(true);  // Configura o timer para disparar uma única vez
    connect(timer, &QTimer::timeout, this, &TimeOutMonitor::timeOutExpires);
}

void TimeOutMonitor::setTimeOut(int timeout) {
    this->timeout = timeout;
}

void TimeOutMonitor::setBoardID(int boardID) {
    this->boardID = boardID;
}

void TimeOutMonitor::setTestID(int testID) {
    this->testID = testID;
}

void TimeOutMonitor::start() {
    timer->start(timeout * 1000);  // Convert seconds to milliseconds
}

void TimeOutMonitor::addTimeOutListener(TimeOutListener *listener) {
    listeners.append(listener);
}

void TimeOutMonitor::timeOutExpires() {
    timer->stop();
    for (TimeOutListener *listener : std::as_const(listeners)) {
        listener->getTestResult(testID, boardID);
    }
}
