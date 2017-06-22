#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mulserver.h"
#include <QHash>
#include <QTableWidget>
#include <QHeaderView>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    mulServer *ser;
    QHash<qintptr,int>rowMap;
private slots:
    void on_on_clicked();

    void on_off_clicked();

    void statusChanged();

    void listenStatus(bool);

    void connectStatus(bool);

    void reqInfo(QString,int);

    void resStatus(bool,QString,int);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
