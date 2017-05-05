#ifndef MYREQUEST_H
#define MYREQUEST_H

#include <QString>
#include <QObject>
#include <QtNetwork/QtNetwork>
#include <QRegExp>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
class myResponse : public QObject
{
    Q_OBJECT
public:
    QString res;
    void addStatus(QString);
    void addType(QString);
    void addLength(QString);
    void addContent(QString);
    QString response();
    myResponse();
    virtual ~myResponse() {}

};
#endif // MYREQUEST_H
