#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <linkbot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connect();
    void setID();

private:
    Ui::MainWindow *ui;
    CLinkbot *linkbot_;
};

#endif // MAINWINDOW_H
