#include "qcustomtablewidget.h"
#include <QDebug>

QCustomTableWidget::QCustomTableWidget(QWidget* parent) : QTableWidget(parent)
{
}

void QCustomTableWidget::AddRow()
{
    //QTableWidgetItem* newItem = new QTableWidgetItem();
    this->setRowCount(this->rowCount() + 1);
}

void QCustomTableWidget::DelRow()
{
    QItemSelectionModel *select = this->selectionModel();

    if (select->hasSelection()) { //check if has selection
        this->removeRow(select->selectedRows().at(0).row());
    }
}

void QCustomTableWidget::loadConfig(QString category)
{
    QSettings settings;
    int size = settings.beginReadArray(category);
    for (int i = 0; i < size; i ++) {
        AddRow();
        settings.setArrayIndex(i);
        QVariant savedName = settings.value("name", "");
        QTableWidgetItem* savedNameItem = new QTableWidgetItem(savedName.toString());
        this->setItem(i, 0, savedNameItem);
        QVariant savedQuery = settings.value("query", "");
        QTableWidgetItem* savedQueryItem = new QTableWidgetItem(savedQuery.toString());
        this->setItem(i, 1, savedQueryItem);
    }
    settings.endArray();
}

void QCustomTableWidget::saveConfig(QString category)
{
    QSettings settings;
    settings.beginWriteArray(category);
    for (int i = 0; i < rowCount(); i++) {
        settings.setArrayIndex(i);
        QTableWidgetItem* nameItem = this->item(i, 0);
        QString name = QString("");
        if (nameItem) {
            name = nameItem->text();
        }
        settings.setValue("name", name);

        QTableWidgetItem* queryItem = item(i, 1);
        QString query = QString("");
        if (queryItem) {
            query = queryItem->text();
        }
        settings.setValue("query", query);
    }
    settings.endArray();
}
