#ifndef MSGQUEUE_H
#define MSGQUEUE_H

#include <QThread>
#include <QMutex>

struct TMsgItem
{
    QString strUrl;
    QObject *pObj;
};

class CMsgQueue : public QThread
{
    Q_OBJECT

public:
    explicit CMsgQueue(QObject *parent = 0);
    virtual ~CMsgQueue();

public:
    static CMsgQueue *GetInstance();
    static void ExitInstance();

    bool Push(TMsgItem item);

protected:
    void run();
    void Clear();

signals:
    void SignalRecvMsg(QByteArray msg, QObject *pObj);

private:
    static CMsgQueue *m_pMsgQueue;
    QList<TMsgItem> m_listMsg;
    QMutex m_mutex;
};

#define MSGQUEUE CMsgQueue::GetInstance()

#endif // CMSGQUEUE_H
