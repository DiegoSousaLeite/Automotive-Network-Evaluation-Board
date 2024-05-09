#include "RepBusinessController.h"
#include <QDebug>
#include <QThread>

RepBusinessController::RepBusinessController(QObject *parent)
    : BusinessController(parent) {
    psController = PersistenceController::getInstance();
}

void RepBusinessController::startTestResultMonitor(int testId, int boardId) {
    // Placeholder for starting the test monitoring based on Qt's capabilities (QTimer, QThread, etc.)
    Q_UNUSED(testId);
    Q_UNUSED(boardId);
    // Logic to start and monitor test with timeout
}
