#include "thread.h"

myThread::myThread(qintptr i,QString in,int p)
{
    id=i;
    port=p;
    index=in;
}

void myThread::run(){
    socket*soc=new socket(id,index,port);
    connect(soc,SIGNAL(closeSocket()),this,SLOT(sendCloseThread()));
    connect(soc,SIGNAL(sendReq(QString,int)),this,SLOT(sendReqMessage(QString,int)));
    connect(soc,SIGNAL(sendResStatus(bool,QString,int)),this,SLOT(sendResStatusMessage(bool,QString,int)));
    qDebug()<<id;
    exec();
    return;
}
void myThread::sendCloseThread(){
    qDebug()<<"sendCloseThread";
    emit closeThread(this);
}
void myThread::sendReqMessage(QString str,int id){
    qDebug()<<"COMES THREAD";
    emit sendReq(str,id);
}
void myThread::sendResStatusMessage(bool b,QString q,int i){
    qDebug()<<"res come thread";
    emit sendResStatus(b,q,i);
}
