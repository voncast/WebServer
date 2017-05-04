#include "server.h"

Server::Server()
{
tcp=new QTcpServer();

}
Server::~Server(){
    delete soc;
    delete tcp;
}

void Server::set(QString i, int p){
    srcDir=i;
    port=p;
}
void Server::initServer(){
    if(tcp->listen(QHostAddress::Any,port)){
        qDebug()<<"Listen succeed!";
        connect(tcp,SIGNAL(newConnection()),this,SLOT(handleReq()));
    }else{
        qDebug()<<"Listen failed!";
    }
}

void Server::handleReq(){
    Server::soc=tcp->nextPendingConnection();
    connect(Server::soc,SIGNAL(readyRead()),this,SLOT(rcv()));
    connect(Server::soc,SIGNAL(disconnected()),this,SLOT(closeSocket()));
    connect(soc,SIGNAL(bytesWritten(qint64)),this,SLOT(done(qint64)));
    connect(this,SIGNAL(sendText()),this,SLOT(sendTo()));
}
void Server::done(qint64 i){
    qDebug()<<"done:"<<i;
}

void Server::rcv(){
    QByteArray rcvMessage=static_cast<QTcpSocket*>(sender())->readAll();
    qDebug()<<"read:"<<rcvMessage.data();
    QString str;
    str.prepend(rcvMessage);
    QString pattern("GET\\s(.*)\\sHTTP");
    QRegExp reg(pattern);
    reg.indexIn(str);
    in=reg.capturedTexts()[1];
    qDebug()<<reg.capturedTexts()[1];
    sendText();
}
void Server::sendTo(){
    qDebug()<<"send";
    QString dir=QCoreApplication::applicationDirPath();
//    dir+="/src";
    dir+=srcDir;
    QDateTime date=QDateTime::currentDateTime();
    QString d=date.toString("ddd, dd MMM yyyy hh:mm:ss ");
    d+="GMT";
    QString sendMessage="HTTP/1.1 200 OK\r\nDate:"+d+"\r\n";
    sendMessage+="Content-type:text/html;charset=utf-8\r\n";
    QString str;

    if(in.contains("/")||in.contains("/index")){
        dir+="/index.html";
        qDebug()<<"dir:"<<dir;
        QFile f(dir);
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Open failed." << endl;
            return;
        }
        QTextStream input(&f);
        while(!input.atEnd()){
            str+=input.readLine();
        }
        QString size=QString::number(str.length(),10);
        sendMessage+="Content-length:"+size+"\r\n\r\n";
        sendMessage+=str;
    }
    qDebug()<<"sent-length:"<<sendMessage.length();
    soc->connectToHost(QHostAddress("127.0.0.1"), 8000);
    soc->write(sendMessage.toStdString().c_str());
}

void Server::closeSocket(){
    qDebug()<<"closed";
    tcp->close();
}
