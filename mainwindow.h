#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "multhreadserver.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    mulThreadServer *ser;
private slots:
    void on_on_clicked();

    void on_off_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
