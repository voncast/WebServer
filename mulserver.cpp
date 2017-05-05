#include "mulserver.h"

mulServer::mulServer()
{
port=8000;
index="/Users/alice/Documents/WebServer/src";
}
void mulServer::incomingConnection(qintptr id){
    qDebug()<<"new connection";
    emit sendConnect(true);
    myThread *th=new myThread(id,index,port);
    connect(th,SIGNAL(closeThread(myThread*)),this,SLOT(closeClient(myThread*)));
    connect(th,SIGNAL(sendReq(QString,int)),this,SLOT(sendReqMessage(QString,int)));
    connect(th,SIGNAL(sendResStatus(bool,QString,int)),this,SLOT(sendResStatusMessage(bool,QString,int)));
    th->start();
}
void mulServer::closeClient(myThread*i){
    i->quit();
    i->wait();
    delete i;
    qDebug()<<"delete thread";
    emit sendConnect(false);
}

void mulServer::set(QString i, int p){
    index=i;
    port=p;
}
void mulServer::initServer(){
    if(this->listen(QHostAddress::Any,port)){
        qDebug()<<"Listen succeed!";
        emit sendListen(true);
    }else{
        qDebug()<<"Listen failed!";
        emit sendListen(true);
    }
}
void mulServer::sendReqMessage(QString str,int id){
    qDebug()<<"COMES SER";
    emit sendReq(str,id);
}
void mulServer::sendResStatusMessage(bool b, QString q,int i){
    qDebug()<<"res come server";
    emit sendResStatus(b,q,i);
}
