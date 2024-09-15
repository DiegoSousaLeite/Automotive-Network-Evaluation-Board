#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>
#include <QQuickWidget>
#include <QVBoxLayout>

class DashboardWidget : public QWidget {
    Q_OBJECT
public:
    explicit DashboardWidget(QWidget *parent = nullptr);

private:
    QQuickWidget *quickWidget;
};

#endif // DASHBOARDWIDGET_H
