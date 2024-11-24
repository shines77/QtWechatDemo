#include "MsgQueue.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

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

void CMsgQueue::run()
{
    while (!isInterruptionRequested()/* TRUE */)
    {
        bool hasMsg = false;
        {
            QMutexLocker locker(&m_mutex);

            if (!m_listMsg.isEmpty())
            {
                hasMsg = true;

                QNetworkAccessManager *m_pHttpMgr = new QNetworkAccessManager();
                QNetworkRequest requestInfo;
                requestInfo.setUrl(QUrl(m_listMsg.at(0).strUrl));

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
                emit SignalRecvMsg(responseByte, m_listMsg.at(0).pObj);
                m_listMsg.removeFirst();
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
