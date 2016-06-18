#include "qiptablewidget.h"
#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>

QIpTableWidget::QIpTableWidget(QWidget* parent) : QCustomTableWidget(parent)
{
}

void QIpTableWidget::setNetworkManager(QNetworkAccessManager *netManager)
{
    m_net_manager = netManager;
}

void QIpTableWidget::updateIps()
{

}

bool QIpTableWidget::sendCommand()
{
    for (int i = 0; i < this->rowCount(); i++) {
        QTableWidgetItem* item = this->item(i, 1);
        if (item) {
            QUrl itemUrl = QUrl();
            itemUrl.setScheme("http");
            itemUrl.setHost(item->text());
            itemUrl.setPort(8088);
            itemUrl.setPath("/api/");
            itemUrl.setQuery(m_command, QUrl::TolerantMode);
            m_net_manager->get(QNetworkRequest(itemUrl));
        }
    }
    return true;
}

int QIpTableWidget::returnCommand()
{
    return 0;
}

bool QIpTableWidget::setCommand(int row, int column)
{
    Q_UNUSED(column)

    QCustomTableWidget* commandTable = qobject_cast<QCustomTableWidget*>(sender());
    QTableWidgetItem* item = commandTable->item(row, 1);
    if (item) {
        m_command = item->text();
    return true;
    } else {
        qDebug() << "Exception " << "Empty Command";
        return false;
    }
}
