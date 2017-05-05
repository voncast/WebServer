#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include "socket.h"
class myThread : public QThread
{
    Q_OBJECT
public:
    QString index;
    int port;
    myThread(qintptr,QString,int);
    virtual ~myThread() {}
signals:
    void closeThread(myThread*);
    void sendReq(QString,int);
    void sendResStatus(bool,QString,int);
public slots:
    void sendCloseThread();
    void sendReqMessage(QString,int);
    void sendResStatusMessage(bool,QString,int);
private:
    qintptr id;
protected:
    virtual void run();
};

#endif // THREAD_H
