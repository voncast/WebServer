#include "socket.h"

socket::socket(qintptr sid,QString in,int p,QObject *parent)
{
    this->setSocketDescriptor(sid);
    id=sid;
    index=in;
    port=p;
    connect(this,SIGNAL(readyRead()),this,SLOT(rcv()));
//    connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()));
    connect(this,SIGNAL(disconnected()),this,SLOT(sendCloseSocket()));

}
void socket::sendCloseSocket(){
    qDebug()<<"sendCloseSocket";
    emit closeSocket();
    deleteLater();
}
void socket::rcv(){
    QByteArray rcvMessage=static_cast<QTcpSocket*>(sender())->readAll();
//    qDebug()<<"read:"<<rcvMessage.data();
    QString str;
    str.prepend(rcvMessage);
    QString pattern("GET\\s(.*)\\sHTTP");
    QString pat("Host:(.*)Connection");
    QRegExp regg(pat);
    regg.indexIn(str);
    QString reqHost=regg.capturedTexts()[1];
    QString pat1("(.*)HTTP");
    QRegExp reg1(pat1);
    reg1.indexIn(str);
    QString reqHead=reg1.capturedTexts()[1];
    QString reqSent=reqHost+"   "+reqHead;
    int i=id;
    emit sendReq(reqSent,i);
    QRegExp reg(pattern);
    reg.indexIn(str);
    in=reg.capturedTexts()[1];
    qDebug()<<reg.capturedTexts()[1];
    sendTo();
}
void socket::sendTo(){
    qDebug()<<"send";
    QString dir,sta="200 OK";
    dir=index;
    QString type,str;
    myResponse*res=new myResponse();
    type="text/html";
    QString pat("\.([^\.]+)$");
    QRegExp reg(pat);
    reg.indexIn(in);
    QString fileType=reg.capturedTexts()[1];
    qDebug()<<"Gdgdggd:"<<reg.capturedTexts()[1];
    if(!in.contains(".")){
        if(!in.compare("/")){
            in+="index.html";
        }else{
            in+=".html";
        }
    }else if(in.contains("png")||in.contains("jpg")||in.contains("jpeg")||in.contains("ico")||in.contains("gif")){
        type="image/"+fileType;
//        type+="image/";
//        type+=in.contains("png")?"png":"jpg";
    }else if(fileType.contains("css")){
        type="text/css";
    }else if(fileType.contains("js")){
        type="application/javascript";
    }
    dir+=in;
    qDebug()<<"dir:"<<dir;
    QFile f(dir);
    QBuffer buf;
    QByteArray line;
    if(type.contains("image")){
//        sta="200 OK";
//        res->addStatus(sta);
//        res->addType(type);
        QPixmap pix(dir);
        buf.open(QIODevice::ReadWrite);
        QString t=type.contains("png")?"png":"jpg";
        QByteArray ba = t.toLatin1();
        char *mm = ba.data();
        pix.save(&buf,mm);
        line.append(buf.data());
        if(line.size()==0){
            sta="404 Not Found";
        }
    }else if(type.contains("text")||type.contains("javascript")){
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       qDebug() << "Open failed." << endl;
       QString rdir=QCoreApplication::applicationDirPath();
       rdir+="/src/404.html";
       qDebug()<<rdir;
       QFile fr(rdir);
       fr.open(QIODevice::ReadOnly | QIODevice::Text);
       while(!fr.atEnd()) {
           QByteArray li = fr.readLine();
           line.append(li);
       }
        sta="404 Not Found";
//        res->addStatus(sta);
    }else{
//        res->addStatus(sta);
//        res->addType(type);
        while(!f.atEnd()) {
            QByteArray l = f.readLine();
            line.append(l);
        }
    }
    }
//    QString qs(line);
    res->addStatus(sta);
    res->addType(type);
    QString s=QString::number(line.size(),10);
    qDebug()<<"size:"<<s;
    res->addLength(s);
    if(sta.contains("404")){
        emit sendResStatus(false,s,id);
    }else{
        emit sendResStatus(true,s,id);
    }
    this->write(res->response().toStdString().c_str());
    this->write(line);
//    QString size=QString::number(line.size(),10);
//    res->addLength(size);
//    qDebug()<<res->response();
//    this->write(res->response().toStdString().c_str());
//    this->write(line);
}

//void socket::sendTo(){
//    qDebug()<<"send";
//    QString dir=QCoreApplication::applicationDirPath();
//    dir+="/src";
//    dir=index;
//    QDateTime date=QDateTime::currentDateTime();
//    QString d=date.toString("ddd, dd MMM yyyy hh:mm:ss ");
//    d+="GMT";
//    QString sendMessage="HTTP/1.1 200 OK\r\nDate:"+d+"\r\n";
//    QString str,type;
//    QBuffer buf;
//    QByteArray data;
//    bool fimg=false;
//    if(!in.compare("/")||!in.compare("/index")){
//        dir+="/index.html";
//    }else if(!in.compare("/page")){
//        dir+="/page.html";
//    }
//    else if(in.contains("png")||in.contains("jpg")){
//        dir+=in;
//        QPixmap pix(dir);
//        buf.open(QIODevice::ReadWrite);
//        type=in.contains("png")?"png":"jpg";
//        QByteArray ba = type.toLatin1();
//        char *mm = ba.data();
//        pix.save(&buf,mm);
//        fimg=true;
//    }
//    if(!fimg){
//        sendMessage+="Content-type:text/html\r\n";
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
//        qDebug()<<"sent-length:"<<sendMessage.length();
//    //    soc->connectToHost(QHostAddress("127.0.0.1"), port);
//        this->write(sendMessage.toStdString().c_str());
//    }else{
//        sendMessage+="Accept-Ranges:bytes\r\n";
//        sendMessage+="Content-type:image/"+type+"\r\n";
//        data.append(buf.data());
//        QString qs(data);
//        QString s=QString::number(data.length(),10);
//        qDebug()<<"size:"<<s;
//        sendMessage+="Content-length:"+s+"\r\n\r\n";
//        this->write(sendMessage.toStdString().c_str());
//        this->write(data);
//    }


//}

