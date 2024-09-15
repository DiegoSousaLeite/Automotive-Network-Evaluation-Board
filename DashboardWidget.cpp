#include "DashboardWidget.h"

DashboardWidget::DashboardWidget(QWidget *parent)
    : QWidget(parent)
{
    quickWidget = new QQuickWidget(this);
    quickWidget->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(quickWidget);
    setLayout(layout);
}

