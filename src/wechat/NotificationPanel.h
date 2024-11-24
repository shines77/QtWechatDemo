#ifndef NOTIFICATIONPANEL_H
#define NOTIFICATIONPANEL_H

#include <QWidget>
#include <QTimer>
#include <QMutex>

const uint MAX_NOTICE = 10;

class CPushButtonEx;

class NotificationPanel : public QWidget
{
    Q_OBJECT
public:
    explicit NotificationPanel(QWidget *parent = 0);

    struct TMsgInfo
    {
        bool bAutoClose;
        QString strContent;
        QString strTitle;

        TMsgInfo()
        {
            bAutoClose = true;
        }
    };

public:
    void SetId(int nIndex) { m_nIndex = nIndex; }
    int GetId() { return m_nIndex; }
    void Start(int msec);
    void Notice(TMsgInfo tMsgInfo);

private:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);

signals:
    void SignalHide(int nIndex);

public slots:
    void OnTimerHideTimeOut();

private:
    QTimer *m_pTimerHide;
    CPushButtonEx *m_btnClose;
    int m_nIndex;
    TMsgInfo m_tMsgInfo;
};

class NotificationMgr : public QObject
{
    Q_OBJECT
public:
    explicit NotificationMgr(QWidget *parent = 0);

    enum EAlignment
    {
        AlignLeft = 0x01,
        AlignRight = 0x02,
        AlignTop = 0x04,
        AlignBottom = 0x08,
    };

    struct TNoteItem
    {
        NotificationPanel *pNotificationPanel;
        bool bShow;
        int nInterval;
        bool bNew;
        qint64 currentTime;
        uint dwFlag;

        TNoteItem()
        {
            pNotificationPanel = NULL;
            bShow = false;
            nInterval = 4500;
            bNew = true;
            currentTime = 0;
            dwFlag = AlignTop | AlignRight;
        }
    };

public:
    static void Init(QWidget *parent = 0);
    static NotificationMgr *GetInstance();
    static void ExitInstance();

    void SetSingleMode(bool bSingleMode) { m_bSingleMode = bSingleMode; }
    void Notice(QString strContent, QString strTitle = tr("通知"), bool bAutoClose = true, uint dwFlag = AlignTop | AlignRight);

private:
    void ShowAll();

    static bool CompareData(const TNoteItem &tItem1, const TNoteItem &tItem2);

public slots:
    void OnItemHide(int nIndex);

private:
    static NotificationMgr *m_pNotificationMgr;
    QList<TNoteItem> m_listNotification;
    QMutex m_mutex;
    bool m_bSingleMode;
};

#endif // NOTIFICATIONPANEL_H
