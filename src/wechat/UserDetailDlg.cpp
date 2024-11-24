#include "UserDetailDlg.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDesktopServices>
#include <QUrl>

#include "PushButtonEx.h"
#include "IconHelper.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

CUserDetailDlg::CUserDetailDlg(QWidget *parent) : QWidget(parent)
{
    m_widgetTop = NULL;
    m_btnUserAvatar = NULL;
    m_lblUserName = NULL;
    m_lblSex = NULL;

    m_lblSeparatorLine = NULL;

    m_lblTel = NULL;
    m_lblTelValue = NULL;
    m_lblMail = NULL;
    m_lblMailValue = NULL;
    m_lblDepartment = NULL;
    m_lblDepartmentValue = NULL;

    m_btnSendMsg = NULL;

    m_pAvatar = NULL;
    m_lblAvatar = NULL;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "UserDetail");

    CreateAllCtrls();
    InitCtrls();
    Relayout();

    connect(m_btnUserAvatar, SIGNAL(clicked()), this, SLOT(OnBtnUserAvatarClicked()));
}

CUserDetailDlg::~CUserDetailDlg()
{
    //
}

void CUserDetailDlg::SetUserInfo(QString strName, QString ico)
{
    m_lblUserName->setText(strName);
    m_btnUserAvatar->setIcon(QIcon(ico));
    m_btnUserAvatar->setIconSize(m_btnUserAvatar->size());

    m_lblAvatar->setStyleSheet(QString("border-image: url(%1);").arg(ico));
}

void CUserDetailDlg::CreateAllCtrls()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_widgetTop, QWidget);
    NEW_OBJECT(m_btnUserAvatar, CPushButtonEx);
    NEW_OBJECT(m_lblUserName, QLabel);
    NEW_OBJECT(m_lblSex, QLabel);
    NEW_OBJECT(m_lblSeparatorLine, QLabel);
    NEW_OBJECT(m_lblTel, QLabel);
    NEW_OBJECT(m_lblTelValue, QLabel);
    NEW_OBJECT(m_lblMail, QLabel);
    NEW_OBJECT(m_lblMailValue, QLabel);
    NEW_OBJECT(m_lblDepartment, QLabel);
    NEW_OBJECT(m_lblDepartmentValue, QLabel);
    NEW_OBJECT(m_btnSendMsg, CPushButtonEx);

    NEW_OBJECT(m_pAvatar, QWidget);

    if (NULL == m_lblAvatar)
        m_lblAvatar = new QLabel(m_pAvatar);
}

void CUserDetailDlg::InitCtrls()
{
    setFixedSize(280, 270);
    setWindowFlags(Qt::Popup);

    m_pAvatar->hide();
    m_lblAvatar->setStyleSheet("border-image: url(:/avatar/avatar/user-avatar.jpeg);");
    m_pAvatar->setFixedSize(230, 230);
    m_pAvatar->setWindowFlags(Qt::Popup);
    m_pAvatar->setProperty("form", "UserDetail");

    m_btnUserAvatar->setFixedSize(70, 70);
    m_btnUserAvatar->setIcon(QIcon(":/avatar/avatar/user-avatar.jpeg"));
    m_btnUserAvatar->setIconSize(m_btnUserAvatar->size());

    m_lblSeparatorLine->setFixedHeight(1);
    m_lblSeparatorLine->setStyleSheet("background-color: #E5E5E5;");

    m_lblTel->setProperty("title", "true");
    m_lblMail->setProperty("title", "true");
    m_lblDepartment->setProperty("title", "true");
    m_lblUserName->setProperty("username", "true");
    m_lblSex->setProperty("sex", "true");
    m_btnSendMsg->setProperty("sendmsg", "true");
    m_lblTelValue->setProperty("link", "true");
    m_lblMailValue->setProperty("link", "true");
    m_lblDepartmentValue->setProperty("link", "true");

    m_lblUserName->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_lblUserName->setCursor(Qt::IBeamCursor);
    m_lblTelValue->setCursor(Qt::PointingHandCursor);
    m_lblMailValue->setCursor(Qt::PointingHandCursor);
    m_lblDepartmentValue->setCursor(Qt::PointingHandCursor);

    m_lblTelValue->installEventFilter(this);            // 安装事件过滤器
    m_lblMailValue->installEventFilter(this);           // 安装事件过滤器
    m_lblDepartmentValue->installEventFilter(this);     // 安装事件过滤器

    m_lblUserName->setText(tr("shines77"));
    m_lblTel->setText(tr("手机"));
    m_lblTelValue->setText(tr("13911116666"));
    m_lblMail->setText(tr("邮箱"));
    m_lblMailValue->setText(tr("wokss@163.com"));
    m_lblDepartment->setText(tr("部门"));
    m_lblDepartmentValue->setText(tr("行业服务部/开发应用组"));

    m_btnSendMsg->setText(tr("发消息"));

    IconHelper::SetIcon(m_lblSex, QChar(0xe646), 14);
}

void CUserDetailDlg::Relayout()
{
    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_btnUserAvatar);
    layoutMain->addWidget(m_lblUserName);
    layoutMain->addWidget(m_lblSex);
    layoutMain->addStretch();
    layoutMain->setSpacing(6);
    layoutMain->setMargin(0);

    int nIndex = 0;
    QGridLayout *layoutTop = new QGridLayout();
    layoutTop->addLayout(layoutMain, 0, 0, 1, 5);

    nIndex++;
    layoutTop->addWidget(m_lblSeparatorLine, nIndex, 0, 1, 5);

    nIndex++;
    layoutTop->addWidget(m_lblTel, nIndex, 0, 1, 1);
    layoutTop->addWidget(m_lblTelValue, nIndex, 1, 1, 4);

    nIndex++;
    layoutTop->addWidget(m_lblMail, nIndex, 0, 1, 1);
    layoutTop->addWidget(m_lblMailValue, nIndex, 1, 1, 4);

    nIndex++;
    layoutTop->addWidget(m_lblDepartment, nIndex, 0, 1, 1);
    layoutTop->addWidget(m_lblDepartmentValue, nIndex, 1, 1, 4);

    nIndex++;
    layoutTop->addWidget(m_btnSendMsg, nIndex, 0, 1, 5);

    layoutTop->setSpacing(6);
    layoutTop->setContentsMargins(20, 20, 20, 20);
    setLayout(layoutTop);

    QHBoxLayout *layoutUserAvatar = new QHBoxLayout(m_pAvatar);
    layoutUserAvatar->addWidget(m_lblAvatar);
    layoutUserAvatar->setSpacing(6);
    layoutUserAvatar->setMargin(8);
}

bool CUserDetailDlg::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_lblTelValue)       // 指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress)  // mouse button pressed
        {
            QDesktopServices::openUrl(QUrl(QString("tel:%1").arg(m_lblTelValue->text())));
        }
    }
    else if (obj == m_lblMailValue) // 指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress)  // mouse button pressed
        {
            QDesktopServices::openUrl(QUrl(QString("mailto:%1").arg(m_lblMailValue->text())));
        }
    }

    return QWidget::eventFilter(obj, event);
}

void CUserDetailDlg::OnBtnUserAvatarClicked()
{
    m_pAvatar->show();

    QPoint ptBtn = m_btnUserAvatar->mapToGlobal(m_btnUserAvatar->pos());
    QPoint point(ptBtn);
    point.setX(ptBtn.x() - m_btnUserAvatar->pos().x() - (m_pAvatar->width() - m_btnUserAvatar->width()) / 2);
    point.setY(ptBtn.y() - m_btnUserAvatar->pos().y() + m_btnUserAvatar->height() + 2);
    m_pAvatar->move(point);
}
