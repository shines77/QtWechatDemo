#include "ChatTopToolbar.h"
#include "IconHelper.h"
#include "PushButtonEx.h"
#include "public.h"
#include "UserDetailDlg.h"

CChatTopToolbar::CChatTopToolbar(QWidget *parent) : QWidget(parent)
{
    m_lblUserName = NULL;
    m_lblState = NULL;
    m_lblEmail = NULL;
    m_lblEmailValue = NULL;

    m_lblSeparatorLine = NULL;

    m_lblPart = NULL;
    m_lblPartValue = NULL;
    m_btnAddUser = NULL;

    m_lblSign = NULL;
    m_lblSignValue = NULL;

    m_pUserDetail = NULL;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "TopToolbar");

    CreateAllCtrls();
    InitCtrls();
    Relayout();
}

void CChatTopToolbar::OnFriendChanged(TUserInfo tUserInfo)
{
    m_tUserInfo = tUserInfo;
    m_lblUserName->setText(tUserInfo.strName);
    m_lblPartValue->setText(tUserInfo.strPart);
    m_lblEmailValue->setText(tUserInfo.strEmail);

    QStringList strListSign;
    strListSign << "会议轰炸中" << "疯狂打码中" << "5F-16L-04" << "疯狂打BUG" << "╰╮45°仰朢天空，眼涙就不會畱下來╭╯" << "哪天版本？" <<
                   "说重点" << "有事烧香" << "我不复杂，但也不简单。" << "可能不舍的不是你而是昨天。" << "一样的眼睛，不一样的看法。"
                << "人穷志不穷，心要野，志要大!" << "嫉妒的别放弃，羡慕的请继续。" << "你玩你的自定义我玩我的格式化。" << "你我之间还有什么比沉默更难堪。"
                << "我的容忍也许会过界，请你理智。" << "有间旺铺要出租" << "招聘一个心上人。" << "我的世界黑与白，五彩世界请滚开。" << "有些事不要逞强，有些人不必勉强。";

    qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
    int nIndex = qrand() % strListSign.length();
    m_lblSignValue->setText(strListSign.at(nIndex));
}

bool CChatTopToolbar::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_lblUserName)   // 指定某个 QLabel
    {
        if (event->type() == QEvent::MouseButtonPress)  // mouse button pressed
        {
            m_pUserDetail->SetUserInfo(m_lblUserName->text(), m_tUserInfo.strAvatar);
            m_pUserDetail->show();

            QPoint ptBtn = m_lblUserName->mapToGlobal(m_lblUserName->pos());
            QPoint point(ptBtn);
            point.setX(ptBtn.x() - m_lblUserName->pos().x());
            point.setY(ptBtn.y() - m_lblUserName->pos().y() + m_lblUserName->height() + 2);
            m_pUserDetail->move(point);
        }
    }

    return QWidget::eventFilter(obj, event);
}

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

void CChatTopToolbar::CreateAllCtrls()
{
    NEW_OBJECT(m_lblUserName, QLabel);
    NEW_OBJECT(m_lblState, QLabel);
    NEW_OBJECT(m_lblEmail, QLabel);
    NEW_OBJECT(m_lblEmailValue, QLabel);
    NEW_OBJECT(m_lblSeparatorLine, QLabel);
    NEW_OBJECT(m_lblPart, QLabel);
    NEW_OBJECT(m_lblPartValue, QLabel);
    NEW_OBJECT(m_btnAddUser, CPushButtonEx);
    NEW_OBJECT(m_lblSign, QLabel);
    NEW_OBJECT(m_lblSignValue, QLabel);
    NEW_OBJECT(m_pUserDetail, CUserDetailDlg);
}

void CChatTopToolbar::InitCtrls()
{
    setFixedHeight(60);

    m_lblUserName->setText(tr("顾一城"));
    m_lblUserName->setStyleSheet("font: 16px; font-weight: bold; color:#000000;");

    m_lblEmailValue->setText(tr("wokss@163.com"));
    m_lblEmailValue->setStyleSheet("color:#ACACAC;");
    m_lblPartValue->setText(tr("开发应用组"));
    m_lblPartValue->setStyleSheet("color:#ACACAC;");

    m_lblSignValue->setText(tr("你有你坚持，我有我自由。"));
    m_lblSignValue->setStyleSheet("color:#ACACAC;");

    m_lblSeparatorLine->setFixedSize(1, 14);
    m_lblSeparatorLine->setStyleSheet("background-color:#E5E5E5");

    IconHelper::SetIcon(m_lblState, QChar(0xe655), 20);
    m_lblState->setStyleSheet("color:#5FB8F1;");

    IconHelper::SetIcon(m_lblEmail, QChar(0xe652), 20);
    m_lblEmail->setStyleSheet("color:#ACACAC;");

    IconHelper::SetIcon(m_lblPart, QChar(0xe654), 20);
    m_lblPart->setStyleSheet("color:#ACACAC;");

    IconHelper::SetIcon(m_btnAddUser, QChar(0xe656), 24);
    m_btnAddUser->setProperty("white_bk", "true");

    IconHelper::SetIcon(m_lblSign, QChar(0xe645), 20);
    m_lblSign->setStyleSheet("color:#ACACAC;");

    m_lblUserName->installEventFilter(this);    // 安装事件过滤器
    m_pUserDetail->hide();
}

void CChatTopToolbar::Relayout()
{
    QHBoxLayout *layoutUser = new QHBoxLayout();
    layoutUser->addWidget(m_lblUserName);
    layoutUser->addWidget(m_lblState);
    layoutUser->setContentsMargins(0, 0, 10, 0);

    QHBoxLayout *layoutInfo = new QHBoxLayout();
    layoutInfo->addLayout(layoutUser);
    layoutInfo->addWidget(m_lblEmail);
    layoutInfo->addWidget(m_lblEmailValue);
    layoutInfo->addWidget(m_lblSeparatorLine);
    layoutInfo->addWidget(m_lblPart);
    layoutInfo->addWidget(m_lblPartValue);
    layoutInfo->addStretch();
    layoutInfo->addWidget(m_btnAddUser);

    layoutInfo->setSpacing(6);
    layoutInfo->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *layoutSign = new QHBoxLayout();
    layoutSign->addWidget(m_lblSign);
    layoutSign->addWidget(m_lblSignValue);
    layoutSign->addStretch();
    layoutSign->setSpacing(6);
    layoutSign->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addLayout(layoutInfo);
    layoutMain->addLayout(layoutSign);
    layoutMain->setSpacing(0);
    layoutMain->setContentsMargins(20, 6, 10, 6);

    setLayout(layoutMain);
}
