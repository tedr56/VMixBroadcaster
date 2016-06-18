#ifndef QCUSTOMTABLEWIDGET_H
#define QCUSTOMTABLEWIDGET_H

#include <QTableWidget>
#include <QSettings>

class QCustomTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    QCustomTableWidget(QWidget* parent);
    void loadConfig(QString category);
    void saveConfig(QString category);
public slots:
    void AddRow();
    void DelRow();
};

#endif // QCUSTOMTABLEWIDGET_H
