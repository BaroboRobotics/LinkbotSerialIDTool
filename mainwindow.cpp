#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <linkbot.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton_connect, SIGNAL(clicked()),
                     this, SLOT(connect()));
    QObject::connect(ui->pushButton_disconnect, SIGNAL(clicked()),
                     this, SLOT(disconnect()));
    QObject::connect(ui->pushButton_setID, SIGNAL(clicked()),
                     this, SLOT(setID()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect()
{
    char buf[32];
    if(-1 == Mobot_dongleGetTTY(buf, sizeof(buf))) {
        QMessageBox msg;
        msg.setText("Could not detect connected Linkbot. Please make sure the Linkbot is connected and powered on.");
        msg.exec();
        return;
    }
    linkbot_ = new CLinkbot();
    if(linkbot_->connectWithTTY(buf)) {
        QMessageBox msg;
        msg.setText("Could not connect to robot. If the robot firmware is corrupted, you may need to reflash or rescue the firmware first.");
        msg.exec();
        return;
    }
    ui->lineEdit->setText(linkbot_->getID());
}

void MainWindow::disconnect()
{
    if(linkbot_) {
        linkbot_->disconnect();
        delete linkbot_;
        linkbot_ = NULL;
    }
    ui->lineEdit->clear();
}

void MainWindow::setID()
{
    QString text = ui->lineEdit->text();
    QRegExp rx("[A-Za-z0-9]{4}");
    if(!rx.exactMatch(text)) {
        QMessageBox msg;
        msg.setText("Serial ID incorrect. The serial ID must be 4 alpha-numeric characters.");
        msg.exec();
        return;
    }
    if(Mobot_setID(linkbot_->getMobotObject(), text.toLatin1().data())) {
        QMessageBox msg;
        msg.setText("Error setting Serial ID.");
        msg.exec();
        return;
    } else {
        QMessageBox msg;
        msg.setText("New serial ID programmed.");
        msg.exec();
        return;
    }
}
