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
    QString dir=index;
    QString sta="200 OK";
    QString type="text/html";
    QString str;
    myResponse*res=new myResponse();

    //匹配文件后缀名
    QString pat("\.([^\.]+)$");
    QRegExp reg(pat);
    reg.indexIn(in);
    QString fileType=reg.capturedTexts()[1];
    qDebug()<<"Gdgdggd:"<<reg.capturedTexts()[1];

    //确定响应报文中的content-type
    if(!in.contains(".")){
        if(!in.compare("/")){
            in+="index.html";
        }else{
            in+=".html";
        }
    }else if(in.contains("png")||in.contains("jpg")||in.contains("jpeg")||in.contains("ico")||in.contains("gif")){
        type="image/"+fileType;
    }else if(fileType.contains("css")){
        type="text/css";
    }else if(fileType.contains("js")){
        type="application/javascript";
    }

    //打开文件
    dir+=in;
    qDebug()<<"dir:"<<dir;
    QFile f(dir);
    QBuffer buf;
    QByteArray line;
    if(!f.open(QIODevice::ReadOnly))
    {
        //打不开则返回404
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
    }else{
        while(!f.atEnd()) {
            QByteArray l = f.readLine();
            line.append(l);
        }
    }
    //往响应报文中添加信息
    res->addStatus(sta);
    res->addType(type);
    //计算返回内容的长度
    QString s=QString::number(line.size(),10);
    qDebug()<<"size:"<<s;
    res->addLength(s);
    //给ui界面展示状态
    if(sta.contains("404")){
        emit sendResStatus(false,s,id);
    }else{
        emit sendResStatus(true,s,id);
    }
    this->write(res->response().toStdString().c_str());
    this->write(line);
}


