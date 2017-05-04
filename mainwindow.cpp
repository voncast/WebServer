#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ser=new mulThreadServer();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_on_clicked()
{
    QString in=ui->index->text();
    int p=ui->port->text().toInt();
    ser->set(in,p);
    ser->initServer();

}

void MainWindow::on_off_clicked()
{
    delete ser;
    qDebug()<<"server down!";
}
