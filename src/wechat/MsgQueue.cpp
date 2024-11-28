#include "MsgQueue.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>

CMsgQueue* CMsgQueue::m_pMsgQueue = NULL;

CMsgQueue::CMsgQueue(QObject *parent) : QThread(parent)
{
    //
}

CMsgQueue::~CMsgQueue()
{
    Clear();
}

CMsgQueue *CMsgQueue::GetInstance()
{
    if (NULL == m_pMsgQueue)
    {
        m_pMsgQueue = new CMsgQueue();
        m_pMsgQueue->start();
    }

    return m_pMsgQueue;
}

void CMsgQueue::ExitInstance()
{
    if (m_pMsgQueue != NULL)
    {
        m_pMsgQueue->requestInterruption();
        m_pMsgQueue->wait();

        delete m_pMsgQueue;
        m_pMsgQueue = NULL;
    }
}

bool CMsgQueue::Push(TMsgItem item)
{
    QMutexLocker locker(&m_mutex);
    m_listMsg.append(item);
    return true;
}

inline int StringDeepCopy(QString &str, const QString &src)
{
    str.resize(src.size());
    int i = 0;
    foreach (const QString::value_type & ch, src)
    {
        str[i] = ch;
        i++;
    }
    Q_ASSERT(i == str.size());
    return str.size();
}

void CMsgQueue::run()
{
    QString strUrl;
    TMsgItem current;

    while (!isInterruptionRequested()/* TRUE */)
    {
        volatile bool hasMsg = false;
        {
            current.pObj = NULL;
            {
                // 把对 m_listMsg 的读写操作集中在这里, 并且保证字符串的生命周期, 减少队列的阻塞时间。
                // 我们不需要在等到网络数据发送出去再解锁队列, 而是在取得数据之后就可以解锁了。
                QMutexLocker locker(&m_mutex);

                if (!m_listMsg.isEmpty())
                {
                    // 深度拷贝字符串, 防止 current.strUrl 失效
                    StringDeepCopy(strUrl, m_listMsg.at(0).strUrl);
                    current.strUrl = strUrl;
                    current.pObj = m_listMsg.at(0).pObj;
                    hasMsg = true;

                    m_listMsg.removeFirst();
                }
            }

            if (hasMsg && (current.pObj != NULL)) {
                QNetworkAccessManager *m_pHttpMgr = new QNetworkAccessManager();
                QNetworkRequest requestInfo;
                requestInfo.setUrl(QUrl(current.strUrl));

                QEventLoop eventLoop;
                QNetworkReply *reply = m_pHttpMgr->get(requestInfo);
                connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
                eventLoop.exec();       // block until finish

                if (reply->error() == QNetworkReply::NoError)
                {
                    qDebug() << "request protobufHttp NoError";
                }
                else
                {
                    qDebug() << "request protobufHttp handle errors here";
                    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

                    // statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
                    qDebug("request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
                    qDebug(qPrintable(reply->errorString()));
                }

                // 请求返回的结果
                QByteArray responseByte = reply->readAll();
                emit SignalRecvMsg(responseByte, current.pObj);
            }
        }

        if (!hasMsg)
        {
            msleep(200);
        }
    }
}

void CMsgQueue::Clear()
{
    QMutexLocker locker(&m_mutex);

    if (!m_listMsg.isEmpty())
    {
        m_listMsg.clear();
    }
}
