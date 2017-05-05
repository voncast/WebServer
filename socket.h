#ifndef SOCKET_H
#define SOCKET_H

//#include "request.h"
#include <QtNetwork/QtNetwork>
#include <QPixmap>
#include <QBuffer>
#include "myresponse.h"
class socket : public QTcpSocket
{
    Q_OBJECT
public:
    int port;
    QString srcDir;
    QString index;
    QString in;
    void sendTo();
    explicit socket(qintptr sid,QString,int,QObject *parent = 0);
    virtual ~socket() {}
signals:
    void closeSocket();
    void sendReq(QString,int);
    void sendResStatus(bool,QString,int);
public slots:
    void sendCloseSocket();
    void rcv();
private:
    qintptr id;
};

#endif // SOCKET_H
