#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QObject>
#include <QtNetwork/QtNetwork>
#include <QRegExp>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
class Server : public QObject
{
    Q_OBJECT
public:
    int port;
    QString srcDir;
    QString in;
    QTcpServer* tcp;
    QTcpSocket*soc;
    void set(QString,int);
    void initServer();
    Server();
    virtual ~Server();
signals:
    void sendText();
public slots:
    void done(qint64);
    void handleReq();
    void closeSocket();
    void rcv();
    void sendTo();
};

#endif // SERVER_H
