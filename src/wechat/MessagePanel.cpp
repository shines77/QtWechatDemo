#include "MessagePanel.h"
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QKeyEvent>
#include <QWebEngineSettings>

#include "FriendList.h"
#include "MsgQueue.h"
#include "ChatTopToolbar.h"
#include "PushButtonEx.h"

CMessagePanel::CMessagePanel(QWidget *parent) : QWidget(parent)
{
    m_pFriendList = NULL;
    m_pTopToolbar = NULL;
    m_pViewChat = NULL;

    m_txtEdit = NULL;
    m_btnSend = NULL;
    m_lblSeparatorLine = NULL;

    CreateAllCtrls();
    InitCtrls();
    InitSlots();
    Relayout();
}

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

void CMessagePanel::CreateAllCtrls()
{
    NEW_OBJECT(m_pFriendList, CFriendList);
    NEW_OBJECT(m_pTopToolbar, CChatTopToolbar);
    NEW_OBJECT(m_pViewChat, QWebEngineView);
    NEW_OBJECT(m_txtEdit, QTextEdit);
    NEW_OBJECT(m_btnSend, CPushButtonEx);
    NEW_OBJECT(m_lblSeparatorLine, QLabel);
}

void CMessagePanel::InitCtrls()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "MessagePanel");

    m_pFriendList->setFixedWidth(250);

    m_pViewChat->setContextMenuPolicy(Qt::NoContextMenu);
    m_pViewChat->load(QUrl("qrc:/html/html/index.html"));
    m_pViewChat->show();

    //m_pViewChat->setMaximumSize(1920, 1000);
    m_pViewChat->setMinimumSize(200, 250);

    //m_txtEdit->setFixedHeight(110);
    m_txtEdit->resize(300, 110);
    m_txtEdit->setStyleSheet("font: 14px; color: #000000;");

    m_btnSend->setFixedSize(80, 40);
    m_btnSend->setText(tr("发送(S)"));
    m_btnSend->setProperty("btnSend", "true");

    m_lblSeparatorLine->setFixedHeight(1);
    m_lblSeparatorLine->setStyleSheet("background-color: #4A7ABA;");
    m_lblSeparatorLine->hide();

    m_txtEdit->installEventFilter(this);
    //m_txtEdit->setFixedHeight(130);
    //
    // See: https://forum.qt.io/topic/53919/qsplitter-size-solved
    //
    //m_txtEdit->setMaximumSize(1920, 600);
    m_txtEdit->setMinimumSize(200, 60);
    m_txtEdit->resize(300, 130);
}

void CMessagePanel::InitSlots()
{
    connect(m_pFriendList, SIGNAL(SignalFriendChanged(TUserInfo)), m_pTopToolbar, SLOT(OnFriendChanged(TUserInfo)));
    connect(m_pFriendList, SIGNAL(SignalFriendChanged(TUserInfo)), this, SLOT(OnFriendChanged(TUserInfo)));
    connect(m_btnSend, SIGNAL(clicked()), this, SLOT(OnBtnSendClicked()));

    connect(CMsgQueue::GetInstance(), SIGNAL(SignalRecvMsg(QByteArray, QObject *)), this, SLOT(OnRecvMsg(QByteArray, QObject *)));
}

void CMessagePanel::Relayout()
{
    QHBoxLayout *layoutSend = new QHBoxLayout();
    layoutSend->addStretch();
    layoutSend->addWidget(m_btnSend);

    QVBoxLayout *layoutRMain = new QVBoxLayout();
    layoutRMain->addWidget(m_pTopToolbar);

    //
    // See: https://blog.51cto.com/u_15907770/5925998
    //
    QSplitter *splitterMiddle = new QSplitter(Qt::Vertical, layoutRMain->widget());
    splitterMiddle->addWidget(m_pViewChat);
    splitterMiddle->addWidget(m_txtEdit);

    ///*
    QWidget *widget = splitterMiddle->widget(0);
    QSizePolicy policy0 = widget->sizePolicy();
    policy0.setHorizontalStretch(1);
    policy0.setVerticalStretch(1);
    widget->setSizePolicy(policy0);

    splitterMiddle->widget(1);
    QSizePolicy policy1 = widget->sizePolicy();
    policy1.setHorizontalStretch(1);
    policy1.setVerticalStretch(0);
    widget->setSizePolicy(policy1);
    //*/

    //splitterMiddle->setStretchFactor(0, 1);
    splitterMiddle->setOpaqueResize(true);
    //
    // The children wdiget of splitter can not be collapse.
    // See: https://blog.csdn.net/kongcheng253/article/details/128769777
    //
    splitterMiddle->setChildrenCollapsible(false);

    //
    // See: https://forum.qt.io/topic/53919/qsplitter-size-solved
    //
    QList<int> listSizes;
    listSizes << 400 << 130;
    splitterMiddle->setSizes(listSizes);

    layoutRMain->addWidget(splitterMiddle);
    layoutRMain->addLayout(layoutSend);

    /*
    layoutRMain->addWidget(m_pViewChat);
    layoutRMain->addWidget(m_lblSeparatorLine);
    layoutRMain->addWidget(m_txtEdit);
    layoutRMain->addLayout(layoutSend);
    //*/

    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_pFriendList);
    layoutMain->addLayout(layoutRMain);
    layoutMain->setSpacing(0);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}

bool CMessagePanel::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_txtEdit)   // 指定某个QLabel
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
            {
                OnBtnSendClicked(); // 发送消息的槽
                return true;
            }
        }
    }

    return QWidget::eventFilter(obj, event);
}

void CMessagePanel::OnBtnSendClicked()
{
    TMsgItem item;
    item.strUrl = QString("http://api.qingyunke.com/api.php?key=free&appid=0&msg=%1").arg(m_txtEdit->toPlainText());
    item.pObj = this;
    CMsgQueue::GetInstance()->Push(item);

    QString jsStr = QString(QString("addMsg(\"%1\")").arg(m_txtEdit->toPlainText()));
    m_pViewChat->page()->runJavaScript(jsStr);
    m_txtEdit->clear();
}

void CMessagePanel::OnRecvMsg(QByteArray strMsg, QObject *obj)
{
    if (obj != this)
        return;

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(strMsg, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("content"))
            {
                QJsonValue value = object.value("content");
                if (value.isString())
                {
                    QString strName = value.toString();

                    QString jsStr = QString(QString("addRecvMsg(\"%1\")").arg(strName));
                    m_pViewChat->page()->runJavaScript(jsStr);
                }
            }
        }
    }
}

void CMessagePanel::OnFriendChanged(TUserInfo tUserInfo)
{
    QString jsStr = QString(QString("clear()"));
    m_pViewChat->page()->runJavaScript(jsStr);
}
