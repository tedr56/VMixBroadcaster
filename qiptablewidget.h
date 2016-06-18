#ifndef QIPTABLEWIDGET_H
#define QIPTABLEWIDGET_H

#include "qcustomtablewidget.h"
#include <QNetworkAccessManager>
#include <QSettings>

class QIpTableWidget : public QCustomTableWidget
{
    Q_OBJECT

public:
    QIpTableWidget(QWidget* parent);
    void setNetworkManager(QNetworkAccessManager* netManager);

public slots:
    void updateIps();
    bool sendCommand();
    int  returnCommand();
    bool setCommand(int row, int column);

private:
    QString m_command;
    QNetworkAccessManager* m_net_manager;
};

#endif // QIPTABLEWIDGET_H
