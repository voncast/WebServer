#ifndef MULSERVER_H
#define MULSERVER_H

#include <QtNetwork/QtNetwork>
#include "thread.h"
#include <QString>
class mulServer:public QTcpServer
{
    Q_OBJECT
public:
    void set(QString,int);
    void initServer();
    int port;
    QString index;
    mulServer();
    virtual ~mulServer() {}
signals:
    void sendListen(bool);
    void sendConnect(bool);
    void sendReq(QString,int);
    void sendResStatus(bool,QString,int);
protected:
    virtual void incomingConnection(qintptr id);
public slots:
    void closeClient(myThread*);
    void sendReqMessage(QString,int);
    void sendResStatusMessage(bool,QString,int);
};

#endif // MULSERVER_H
