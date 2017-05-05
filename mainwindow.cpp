#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ser=new mulServer();
    connect(ser,SIGNAL(sendListen(bool)),this,SLOT(listenStatus(bool)));
    connect(ser,SIGNAL(sendConnect(bool)),this,SLOT(connectStatus(bool)));
    connect(ser,SIGNAL(sendReq(QString,int)),this,SLOT(reqInfo(QString,int)));
    connect(ser,SIGNAL(sendResStatus(bool,QString,int)),this,SLOT(resStatus(bool,QString,int)));
    ui->setupUi(this);
    QStringList h;
    h<<""<<"time"<<"Ip / Port / HTTP-headers"<<"Resonse / Content-byte";
    ui->clientTable->setHorizontalHeaderLabels(h);
    ui->clientTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->clientTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->clientTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->clientTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->clientTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
//    ui->clientTable->horizontalHeader()->setStretchLastSection(true);
//    ui->toggle->setCheckable(true);
    connect(ui->toggle,SIGNAL(toggled(bool)),this,SLOT(statusChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::statusChanged(){
    if(ui->toggle->text().contains("Start")){
        ui->toggle->setText("Stop Server");
        QString in=ui->index->text();
        int p=ui->port->text().toInt();
        if(in.length()>0){
            ser->set(in,p);
        }
        ser->initServer();
    }else{
        ui->toggle->setText("Start Server");
        ser->close();
        ui->status->setText("Server is out of service!");
        qDebug()<<"server down!";
    }
}
void MainWindow::listenStatus(bool sta){
    if(sta){
        ui->status->setText("Waiting for connections...");
    }else{
        ui->status->setText("Listen Failed!");
    }
}
void MainWindow::connectStatus(bool sta){
    if(sta){
        ui->status->setText("Request comes...");
    }else{
        ui->status->setText("Response completed...");
    }
}
void MainWindow::reqInfo(QString str,int id){
    qDebug()<<"COMES req";
    int rowIndex = ui->clientTable->rowCount();
    ui->clientTable->setRowCount(rowIndex + 1);
    rowMap.insert(id,rowIndex);
    QTableWidgetItem *r = new QTableWidgetItem("");
    ui->clientTable->setVerticalHeaderItem(rowIndex, r);
    QTableWidgetItem *t, *reqMes,*cur;
    cur=new QTableWidgetItem;
    t=new QTableWidgetItem;
    reqMes=new QTableWidgetItem;
    cur->setText("❓");
    t->setText(QTime::currentTime().toString("hh:mm:ss"));
    reqMes->setText(str);
    ui->clientTable->setItem(rowIndex, 0, cur);
    ui->clientTable->setItem(rowIndex, 1, t);
    ui->clientTable->setItem(rowIndex, 2, reqMes);
}
void MainWindow::resStatus(bool b, QString q,int id){
    qDebug()<<"res come main";
    QTableWidgetItem *resMes,*cur;
    cur=new QTableWidgetItem;
    resMes=new QTableWidgetItem;
    QString re;
    if(b==true){
        cur->setText("☑️");
        re="200 OK/";
    }else{
        cur->setText("✖️");
        re="404 Not Found/";
    }
    int row=rowMap[id];
    re+=q;
    qDebug()<<"RRRRRRRow:"<<QString::number(row, 10);
    resMes->setText(re);
    ui->clientTable->setItem(row, 0, cur);
    ui->clientTable->setItem(row, 3, resMes);
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
    ser->close();
    qDebug()<<"server down!";
}
