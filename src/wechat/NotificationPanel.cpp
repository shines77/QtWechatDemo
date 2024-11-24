#include "NotificationPanel.h"

#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QPropertyAnimation>
#include <QDateTime>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QApplication>

#include "PushButtonEx.h"
#include "IconHelper.h"

NotificationPanel::NotificationPanel(QWidget *parent) : QWidget(parent)
{
    m_pTimerHide = NULL;
    m_btnClose = NULL;
    m_nIndex = 0;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setWindowFlags(windowFlags() | Qt::ToolTip | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setProperty("form", "IconfontPanel");
    setAttribute(Qt::WA_TranslucentBackground, true);

    m_pTimerHide = new QTimer(this);
    connect(m_pTimerHide, SIGNAL(timeout()), this, SLOT(OnTimerHideTimeOut()));

    m_btnClose = new CPushButtonEx(this);
    m_btnClose->setFixedSize(40, 40);
    m_btnClose->setProperty("white_bk", "true");

    IconHelper::SetIcon(m_btnClose, QChar(0xe64f));
    connect(m_btnClose, SIGNAL(clicked()), this, SLOT(OnTimerHideTimeOut()));

    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->addStretch();
    layoutTop->addWidget(m_btnClose);
    layoutTop->setSpacing(0);
    layoutTop->setContentsMargins(0, 10, 20, 0);

    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addLayout(layoutTop);
    layoutMain->addStretch();
    layoutMain->setSpacing(0);
    layoutMain->setMargin(0);
    setLayout(layoutMain);

    setFixedSize(400, 150);
}

void NotificationPanel::Start(int msec)
{
    m_pTimerHide->stop();

    if (m_tMsgInfo.bAutoClose)
    {
        m_pTimerHide->setInterval(msec);
        m_pTimerHide->start();
    }

    update();
}

void NotificationPanel::Notice(NotificationPanel::TMsgInfo tMsgInfo)
{
    m_tMsgInfo = tMsgInfo;
}

void NotificationPanel::enterEvent(QEvent *event)
{
    m_pTimerHide->stop();
}

void NotificationPanel::leaveEvent(QEvent *event)
{
    m_pTimerHide->start();
}

void NotificationPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);         // 创建画家对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width() - 20, this->height() - 20);

    painter.fillPath(path, QBrush(Qt::white));

    QColor color(92, 93, 95, 50);
    int arr[10] = { 150, 120, 80, 50, 40, 30, 20, 10, 5, 5};
    for (int i = 0; i < 10; i++)
    {
         QPainterPath path;
         path.setFillRule(Qt::WindingFill);
         if(i == 5)
             path.addRect(10-i-1, 10-i-1, this->width()-(10-i)*2, this->height()-(10-i)*2);
         else
            path.addRoundedRect(10-i-1, 10-i-1, this->width()-(10-i)*2, this->height()-(10-i)*2,2,2);

         color.setAlpha(arr[i]);
         painter.setPen(color);
         painter.drawPath(path);
    }

    QFont ft = painter.font();

    QRect rcClient = rect();

    painter.save();
    QRect rcTitle(rcClient);
    rcTitle.setTop(rcClient.top() + 17);
    rcTitle.setLeft(rcClient.left() + 25);
    rcTitle.setBottom(rcTitle.top() + 27);
    rcTitle.setRight(rcClient.right() - 25);

    QFont ftTemp = ft;
    ftTemp.setPointSize(12);
    ftTemp.setBold(false);
    painter.setFont(ftTemp);

    painter.setPen(QColor("#262626"));
    painter.drawText(rcTitle, Qt::AlignLeft | Qt::AlignVCenter, m_tMsgInfo.strTitle);
    painter.setFont(ft);
    painter.restore();

    painter.save();
    QRect rcContent(rcClient);
    rcContent.setTop(rcTitle.bottom() + 17);
    rcContent.setLeft(rcClient.left() + 25);
    rcContent.setBottom(rcClient.bottom() - 17);
    rcContent.setRight(rcClient.right() - 25);

    ftTemp.setPointSize(10);
    ftTemp.setBold(false);
    painter.setFont(ftTemp);

    painter.setPen(QColor("#262626"));
    painter.drawText(rcContent, Qt::AlignLeft | Qt::TextWordWrap, m_tMsgInfo.strContent);
    painter.setFont(ft);
    painter.restore();
}

void NotificationPanel::OnTimerHideTimeOut()
{
    m_pTimerHide->stop();
    hide();
    emit SignalHide(m_nIndex);
}

////////////////////////////////////////////////////////////////////

NotificationMgr* NotificationMgr::m_pNotificationMgr = NULL;

NotificationMgr::NotificationMgr(QWidget *parent)
{
    m_bSingleMode = true;

    m_listNotification.clear();

    // 默认创建10个
    for (int i = 0; i < MAX_NOTICE; i++)
    {
        NotificationPanel *pNotice = new NotificationPanel(parent);
        pNotice->hide();
        pNotice->SetId(i);

        connect(pNotice, SIGNAL(SignalHide(int)), this, SLOT(OnItemHide(int)));

        TNoteItem tItem;
        tItem.pNotificationPanel = pNotice;
        m_listNotification << tItem;
    }
}

void NotificationMgr::Init(QWidget *parent)
{
    if (NULL == m_pNotificationMgr)
    {
        m_pNotificationMgr = new NotificationMgr(parent);
    }
}

NotificationMgr *NotificationMgr::GetInstance()
{
    return m_pNotificationMgr;
}

void NotificationMgr::ExitInstance()
{
    if (m_pNotificationMgr != NULL)
    {
        delete m_pNotificationMgr;
        m_pNotificationMgr = NULL;
    }
}

bool NotificationMgr::CompareData(const TNoteItem &tItem1, const TNoteItem &tItem2)
{
    if (tItem1.currentTime < tItem2.currentTime)
    {
        return true;
    }

    return false;
}

void NotificationMgr::Notice(QString strContent, QString strTitle, bool bAutoClose, uint dwFlag)
{
    int nPos = 10;
    int nStartHeight = 10;

    for (int i = 0; i < m_listNotification.size(); i++)
    {
        if (m_bSingleMode)
        {
            m_listNotification[0].bShow = true;
            m_listNotification[0].bNew = true;
            m_listNotification[0].pNotificationPanel->hide();
            m_listNotification[0].dwFlag = dwFlag;

            NotificationPanel::TMsgInfo tMsgInfo;
            tMsgInfo.bAutoClose = bAutoClose;
            tMsgInfo.strContent = strContent;
            tMsgInfo.strTitle = strTitle;
            m_listNotification[0].pNotificationPanel->Notice(tMsgInfo);
            break;
        }
        else
        {
            TNoteItem tItem = m_listNotification.at(i);
            NotificationPanel *pNotice = tItem.pNotificationPanel;

            if (!tItem.bShow)
            {
                m_listNotification[i].bShow = true;
                m_listNotification[i].bNew = true;
                m_listNotification[i].currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_listNotification[i].dwFlag = dwFlag;

                NotificationPanel::TMsgInfo tMsgInfo;
                tMsgInfo.bAutoClose = bAutoClose;
                tMsgInfo.strContent = strContent;
                tMsgInfo.strTitle = strTitle;
                pNotice->Notice(tMsgInfo);

                break;
            }
            else
            {
                QSize size = pNotice->size();
                nStartHeight += size.height();
                nStartHeight += nPos;
            }
        }
    }

    ShowAll();
}

void NotificationMgr::ShowAll()
{
    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->availableGeometry();

    int dWidth = screenRect.width();
    int dHeight = screenRect.height();

    int nPos = 10;
    int nStartHeight = 10;
    for (int i = 0; i < m_listNotification.size(); i++)
    {
        TNoteItem tItem = m_listNotification.at(i);
        NotificationPanel *pNotice = tItem.pNotificationPanel;
        if (tItem.bShow)
        {
           pNotice->show();

           const int nSpace = 10;
           QSize size = pNotice->size();
           QRect rcStart, rcEnd;
           QPoint ptStart, ptEnd;
           if (tItem.dwFlag & AlignLeft)
           {
               ptStart.setX(-size.width());
               ptEnd.setX(nSpace);
           }
           if (tItem.dwFlag & AlignTop)
           {
               ptStart.setY(nStartHeight);
               ptEnd.setY(nStartHeight);
           }
           if (tItem.dwFlag & AlignRight)
           {
               ptStart.setX(dWidth);
               ptEnd.setX(dWidth - size.width() - nSpace);
           }
           if (tItem.dwFlag & AlignBottom)
           {
               ptStart.setY(dHeight - size.height() - nStartHeight);
               ptEnd.setY(dHeight - size.height() - nStartHeight);
           }

           rcStart = QRect(ptStart.x(), ptStart.y(), size.width(), size.height());
           rcEnd = QRect(ptEnd.x(), ptEnd.y(), size.width(), size.height());

           if (tItem.bNew)
           {
               QPropertyAnimation *animation = new QPropertyAnimation(pNotice, "geometry");
               animation->setDuration(200);
               animation->setStartValue(rcStart);
               animation->setEndValue(rcEnd);
               animation->start();

               pNotice->Start(tItem.nInterval);
               m_listNotification[i].bNew = false;
           }
           else
           {
               QSize size = pNotice->size();
               pNotice->move(dWidth - size.width() - nSpace, nStartHeight);
           }

           nStartHeight += size.height();
           nStartHeight += nPos;

           if (m_bSingleMode)
           {
               break;
           }
        }
    }
}

void NotificationMgr::OnItemHide(int nIndex)
{
    m_listNotification[nIndex].bShow = false;
    ShowAll();
}
