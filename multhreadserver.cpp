//#include "multhreadserver.h"
//void mulThreadServer::incomingConnection(qintptr id){
//    socket *newSoc=new socket(id);
//    QThread*thread=new QThread(newSoc);
//    connect(newSoc,SIGNAL(sendRead(qintptr)),this,SLOT(rcv(qintptr)));
//    connect(newSoc,SIGNAL(sendClose(qintptr)),this,SLOT(closeSocket(qintptr)));
//    connect(newSoc,SIGNAL(sendByte(qint64)),this,SLOT(done(qint64)));
//    connect(this,SIGNAL(sendText(qintptr)),this,SLOT(sendTo(qintptr)));
//    connect(newSoc,SIGNAL(sendClose(qintptr)),this,SLOT(closeSocket(qintptr)));
//    newSoc->moveToThread(thread);
//    thread->start();
//    clients.insert(id,newSoc);
//    qDebug()<<"num:"<<clients.count();
//    qDebug()<<id;
//}
//void mulThreadServer::closeSocket(qintptr id){
//    socket*s=new socket(id);
//    clients.remove(id);
//    delete s;
//    qDebug()<<"closed";
//}

//void mulThreadServer::set(QString i, int p){
//    srcDir=i;
//    port=p;
//}
//void mulThreadServer::initServer(){
//    if(this->listen(QHostAddress::Any,port)){
//        qDebug()<<"Listen succeed!";
////        connect(tcp,SIGNAL(newConnection()),this,SLOT(handleReq()));
//    }else{
//        qDebug()<<"Listen failed!";
//    }
//}
//void mulThreadServer::rcv(qintptr id){
//    qDebug()<<"read:";
//    QByteArray rcvMessage=static_cast<QTcpSocket*>(sender())->readAll();
//    qDebug()<<rcvMessage.data();
//    QString str;
//    str.prepend(rcvMessage);
//    QString pattern("GET\\s(.*)\\sHTTP");
//    QRegExp reg(pattern);
//    reg.indexIn(str);
//    in=reg.capturedTexts()[1];
//    qDebug()<<reg.capturedTexts()[1];
//    sendText(id);
//}
//void mulThreadServer::sendTo(qintptr id){
//    qDebug()<<"send";
//    socket *soc=new socket(id);
//    QString dir=QCoreApplication::applicationDirPath();
////    dir+="/src";
//    dir+=srcDir;
//    QDateTime date=QDateTime::currentDateTime();
//    QString d=date.toString("ddd, dd MMM yyyy hh:mm:ss ");
//    d+="GMT";
//    QString sendMessage="HTTP/1.1 200 OK\r\nDate:"+d+"\r\n";
//    sendMessage+="Content-type:text/html;charset=utf-8\r\n";
//    QString str;

//    if(in.contains("/")||in.contains("/index")){
//        dir+="/index.html";
//        qDebug()<<"dir:"<<dir;
//        QFile f(dir);
//        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
//        {
//            qDebug() << "Open failed." << endl;
//            return;
//        }
//        QTextStream input(&f);
//        while(!input.atEnd()){
//            str+=input.readLine();
//        }
//        QString size=QString::number(str.length(),10);
//        sendMessage+="Content-length:"+size+"\r\n\r\n";
//        sendMessage+=str;
//    }
//    qDebug()<<"sent-length:"<<sendMessage.length();
//    soc->connectToHost(QHostAddress("127.0.0.1"), port);
//    soc->write(sendMessage.toStdString().c_str());
//}
//void mulThreadServer::done(qint64 i){
//    qDebug()<<"done:"<<i;
//}
