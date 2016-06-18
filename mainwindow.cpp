#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <QSslConfiguration>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("VMix Broadcaster");

    //Disable SSL
    QSslConfiguration sslConf = QSslConfiguration::defaultConfiguration();
    sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
    QSslConfiguration::setDefaultConfiguration(sslConf);

    //Set Command Table Header
    QStringList CommandHeader = QStringList();
    CommandHeader.append("Name");
    CommandHeader.append("Command");
    ui->Commands->setHorizontalHeaderLabels(CommandHeader);

    QStringList IpHeader = QStringList();
    IpHeader.append("Name");
    IpHeader.append("Ip");
    ui->Ip1->setHorizontalHeaderLabels(IpHeader);
    ui->Ip2->setHorizontalHeaderLabels(IpHeader);
    ui->Ip3->setHorizontalHeaderLabels(IpHeader);


    //Connect Add/Remove Rows buttons to Tables
    connect(ui->AddCommand, SIGNAL(clicked()), ui->Commands, SLOT(AddRow()));
    connect(ui->RemoveCommand, SIGNAL(clicked()), ui->Commands, SLOT(DelRow()));

    connect(ui->AddIp1, SIGNAL(clicked()), ui->Ip1, SLOT(AddRow()));
    connect(ui->RemoveIp1, SIGNAL(clicked()), ui->Ip1, SLOT(DelRow()));

    connect(ui->AddIp2, SIGNAL(clicked()), ui->Ip2, SLOT(AddRow()));
    connect(ui->RemoveIp2, SIGNAL(clicked()), ui->Ip2, SLOT(DelRow()));

    connect(ui->AddIp3, SIGNAL(clicked()), ui->Ip3, SLOT(AddRow()));
    connect(ui->RemoveIp3, SIGNAL(clicked()), ui->Ip3, SLOT(DelRow()));

    //Connect CommandTable SelectionChange to IpTable Command
    connect(ui->Commands, SIGNAL(cellClicked(int,int)), ui->Ip1, SLOT(setCommand(int,int)));
    connect(ui->Commands, SIGNAL(cellClicked(int,int)), ui->Ip2, SLOT(setCommand(int,int)));
    connect(ui->Commands, SIGNAL(cellClicked(int,int)), ui->Ip3, SLOT(setCommand(int,int)));

    //Connect CommandTable CellEdited to IptTable Command
    connect(ui->Commands, SIGNAL(cellChanged(int,int)), ui->Ip1, SLOT(setCommand(int,int)));
    connect(ui->Commands, SIGNAL(cellChanged(int,int)), ui->Ip2, SLOT(setCommand(int,int)));
    connect(ui->Commands, SIGNAL(cellChanged(int,int)), ui->Ip3, SLOT(setCommand(int,int)));

    //Setup Network
    m_net_manager = new QNetworkAccessManager();
    ui->Ip1->setNetworkManager(m_net_manager);
    ui->Ip2->setNetworkManager(m_net_manager);
    ui->Ip3->setNetworkManager(m_net_manager);

    //Connect Send Button to IpTables
    connect(ui->Send1, SIGNAL(clicked()), ui->Ip1, SLOT(sendCommand()));
    connect(ui->Send2, SIGNAL(clicked()), ui->Ip2, SLOT(sendCommand()));
    connect(ui->Send3, SIGNAL(clicked()), ui->Ip3, SLOT(sendCommand()));

    connect(ui->SendAll, SIGNAL(clicked()), ui->Ip1, SLOT(sendCommand()));
    connect(ui->SendAll, SIGNAL(clicked()), ui->Ip2, SLOT(sendCommand()));
    connect(ui->SendAll, SIGNAL(clicked()), ui->Ip3, SLOT(sendCommand()));

    //Setup Settings
    QCoreApplication::setOrganizationName("ARocherVj");
    QCoreApplication::setOrganizationDomain("arochervj.fr.to");
    QCoreApplication::setApplicationName("VMixBroadcaster");

    ui->Commands->loadConfig("commands");
    ui->Ip1->loadConfig("ip1");
    ui->Ip2->loadConfig("ip2");
    ui->Ip3->loadConfig("ip3");

    //Setup Shortcuts
    QShortcut* sendAllShortcut = new QShortcut(QKeySequence(Qt::Key_Space), ui->SendAll);
    connect(sendAllShortcut, SIGNAL(activated()), ui->SendAll, SLOT(click()));

    QShortcut* send1Shortcut = new QShortcut(QKeySequence(Qt::Key_1), ui->Send1);
    connect(send1Shortcut, SIGNAL(activated()), ui->Send1, SLOT(click()));

    QShortcut* send2Shortcut = new QShortcut(QKeySequence(Qt::Key_2), ui->Send2);
    connect(send2Shortcut, SIGNAL(activated()), ui->Send2, SLOT(click()));

    QShortcut* send3Shortcut = new QShortcut(QKeySequence(Qt::Key_3), ui->Send3);
    connect(send3Shortcut, SIGNAL(activated()), ui->Send3, SLOT(click()));

}

MainWindow::~MainWindow()
{
    ui->Commands->saveConfig("commands");
    ui->Ip1->saveConfig("ip1");
    ui->Ip2->saveConfig("ip2");
    ui->Ip3->saveConfig("ip3");
    delete ui;
}
