#include "socket.h"

socket::socket(qintptr sid,QObject *parent)
{
    id=sid;
    connect(this,SIGNAL(disconnected()),this,SLOT(sendCloseMessage()));
    connect(this,SIGNAL(readyRead()),this,SLOT(sendReadMessage()));
    connect(this,SIGNAL(bytesWritten(qint64)),this,SLOT(sendByteMessage(qint64)));
//    qDebug()<<"id:"<<id;
}
void socket::sendCloseMessage(){
    qDebug()<<"here comes close";
    sendClose(id);
}
void socket::sendReadMessage(){
    qDebug()<<"here comes read";
    sendRead(id);
}
void socket::sendByteMessage(qint64 num){
    qDebug()<<"here comes byte";
    sendByte(num);
}



