#ifndef THREAD_H
#define THREAD_H

#include <QThread>
class thread : public QThread
{
    Q_OBJECT
public:
    thread();
    virtual ~thread() {}
};

#endif // THREAD_H
