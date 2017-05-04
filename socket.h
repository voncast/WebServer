#ifndef SOCKET_H
#define SOCKET_H

#include <QtNetwork>
class socket : public QTcpSocket
{
    Q_OBJECT
public:
    int port;
    QString srcDir;
    QString in;
    explicit socket(qintptr sid,QObject *parent = 0);
    virtual ~socket() {}
signals:
    void sendClose(qintptr);
    void sendRead(qintptr);
    void sendByte(qint64);
public slots:
    void sendCloseMessage();
    void sendReadMessage();
    void sendByteMessage(qint64);
private:
    qintptr id;
};

#endif // SOCKET_H
