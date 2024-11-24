#include "NavPanel.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "PushButtonEx.h"
#include "IconHelper.h"
#include "UserDetailDlg.h"

#include <QDebug>

CNavPanel::CNavPanel(QWidget *parent) : QWidget(parent)
{
    m_btnUserAvatar = NULL;
    m_btnMessage = NULL;
    m_btnContacts = NULL;
    m_btnFavorites = NULL;
    m_btnCalendar = NULL;
    m_btnWorkspace = NULL;
    m_btnMore = NULL;
    m_lblSeparatorLine = NULL;
    m_pUserDetailDlg = NULL;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "NavPanel");

    CreateAllCtrls();
    InitCtrls();
    InitSlots();
    Relayout();
}

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

void CNavPanel::CreateAllCtrls()
{
    NEW_OBJECT(m_btnUserAvatar, CPushButtonEx);
    NEW_OBJECT(m_btnMessage, CPushButtonEx);
    NEW_OBJECT(m_btnContacts, CPushButtonEx);
    NEW_OBJECT(m_btnFavorites, CPushButtonEx);
    NEW_OBJECT(m_btnCalendar, CPushButtonEx);
    NEW_OBJECT(m_btnWorkspace, CPushButtonEx);
    NEW_OBJECT(m_btnMore, CPushButtonEx);
    NEW_OBJECT(m_lblSeparatorLine, QLabel);
    NEW_OBJECT(m_pUserDetailDlg, CUserDetailDlg);
}

void CNavPanel::InitCtrls()
{
    m_btnUserAvatar->setFixedSize(35, 35);

    //QSize sizeBtn(50, 50);
    int sizeBtn = 50;
    m_btnMessage->setFixedHeight(sizeBtn);
    m_btnContacts->setFixedHeight(sizeBtn);
    m_btnFavorites->setFixedHeight(sizeBtn);
    m_btnCalendar->setFixedHeight(sizeBtn);
    m_btnWorkspace->setFixedHeight(sizeBtn);
    m_btnMore->setFixedHeight(sizeBtn);

    m_btnUserAvatar->setIcon(QIcon(":/avatar/avatar/user-avatar.jpeg"));
    m_btnUserAvatar->setIconSize(m_btnUserAvatar->size());

    IconHelper::SetIcon(m_btnMessage, QChar(0xe645));
    IconHelper::SetIcon(m_btnContacts, QChar(0xe63a));
    IconHelper::SetIcon(m_btnFavorites, QChar(0xe668), 24);
    IconHelper::SetIcon(m_btnCalendar, QChar(0xe603), 24);
    IconHelper::SetIcon(m_btnWorkspace, QChar(0xe6a9));
    //IconHelper::SetIcon(m_btnWeDoc, QChar(0xe670));
    //IconHelper::SetIcon(m_btnWeDrive, QChar(0xe663));
    //IconHelper::SetIcon(m_btnMeeting, QChar(0xe673));
    IconHelper::SetIcon(m_btnMore, QChar(0xe642));

    m_btnMessage->setToolTip(tr("聊天"));
    m_btnContacts->setToolTip(tr("通讯录"));
    m_btnFavorites->setToolTip(tr("收藏"));
    m_btnCalendar->setToolTip(tr("控件演示"));
    m_btnWorkspace->setToolTip(tr("图标集"));
    m_btnMore->setToolTip(tr("更多..."));

    m_lblSeparatorLine->setFixedHeight(1);
    m_lblSeparatorLine->setStyleSheet("background-color: #4A7ABA;");
    m_pUserDetailDlg->hide();

    // 初始化tab
    QSignalMapper *pSignalMapperPushed = new QSignalMapper(this);
    pSignalMapperPushed->setMapping(m_btnMessage, TAB_PAGE_MESSAGE);
    pSignalMapperPushed->setMapping(m_btnContacts, TAB_PAGE_CONTACTS);
    pSignalMapperPushed->setMapping(m_btnFavorites, TAB_PAGE_FAVORITES);
    pSignalMapperPushed->setMapping(m_btnCalendar, TAB_PAGE_CALENDAR);
    pSignalMapperPushed->setMapping(m_btnWorkspace, TAB_PAGE_WORKSPACE);

    QList<CPushButtonEx *> listBtns = findChildren<CPushButtonEx *>();
    foreach (QPushButton *btn, listBtns)
    {
        if (btn != m_btnUserAvatar)
            connect(btn, SIGNAL(clicked()), pSignalMapperPushed, SLOT(map()));
    }

    connect(pSignalMapperPushed, SIGNAL(mapped(int)), this, SLOT(OnSignalPushedMapped(int)));

    m_btnMessage->setCheckable(true);
    m_btnContacts->setCheckable(true);
    m_btnFavorites->setCheckable(true);
    m_btnCalendar->setCheckable(true);
    m_btnWorkspace->setCheckable(true);
}

void CNavPanel::InitSlots()
{
    connect(m_btnUserAvatar, SIGNAL(clicked()), this, SLOT(OnBtnUserAvatarClicked()));
    connect(m_btnMore, SIGNAL(clicked()), this, SLOT(OnBtnMoreClicked()));
}

void CNavPanel::Relayout()
{
    QHBoxLayout *layoutUserAvatar = new QHBoxLayout();
    layoutUserAvatar->addWidget(m_btnUserAvatar);
    layoutUserAvatar->setContentsMargins(10, 28, 16, 18);

    QVBoxLayout *layoutCenter = new QVBoxLayout();
    layoutCenter->addLayout(layoutUserAvatar);
    layoutCenter->addWidget(m_btnMessage);
    layoutCenter->addWidget(m_btnContacts);
    layoutCenter->addWidget(m_btnFavorites);
    layoutCenter->addWidget(m_lblSeparatorLine);
    layoutCenter->addWidget(m_btnCalendar);
    layoutCenter->addWidget(m_btnWorkspace);
    layoutCenter->addStretch();
    layoutCenter->addWidget(m_btnMore);

    layoutCenter->setSpacing(0);
    layoutCenter->setMargin(0);

    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addStretch();
    layoutMain->addLayout(layoutCenter);
    layoutMain->addStretch();
    layoutMain->setSpacing(0);
    layoutMain->setContentsMargins(1, 1, 1, 1);
    setLayout(layoutMain);
}

void CNavPanel::OnBtnUserAvatarClicked()
{
    m_pUserDetailDlg->show();

    QPoint ptBtn = m_btnUserAvatar->mapToGlobal(m_btnUserAvatar->pos());
    QPoint point(ptBtn);
    point.setX(ptBtn.x() - m_btnUserAvatar->pos().x() + m_btnUserAvatar->width() + 2);
    point.setY(ptBtn.y() - m_btnUserAvatar->pos().y());
    m_pUserDetailDlg->move(point);
}

void CNavPanel::OnSignalPushedMapped(int nCmd)
{
    emit SignalTabChanged(EMainTabPage(nCmd));
}

void CNavPanel::OnMainTabChanged(EMainTabPage eMainTabPage)
{
    m_btnMessage->setChecked(false);
    m_btnContacts->setChecked(false);
    m_btnFavorites->setChecked(false);
    m_btnCalendar->setChecked(false);
    m_btnWorkspace->setChecked(false);

    switch (eMainTabPage)
    {
    case TAB_PAGE_MESSAGE:
        {
            m_btnMessage->setChecked(true);
        }
        break;

    case TAB_PAGE_CONTACTS:
        {
            m_btnContacts->setChecked(true);
        }
        break;

    case TAB_PAGE_FAVORITES:
        {
            m_btnFavorites->setChecked(true);
        }
        break;

    case TAB_PAGE_CALENDAR:
        {
            m_btnCalendar->setChecked(true);
        }
        break;

    case TAB_PAGE_WORKSPACE:
        {
            m_btnWorkspace->setChecked(true);
        }
        break;

    default:
        break;
    }
}

void CNavPanel::OnBtnMoreClicked()
{
    // 创建菜单对象
    QMenu *pMenu = new QMenu();

    QAction *pCollect = new QAction(tr("收藏"), pMenu);
    QAction *pMsgMgr = new QAction(tr("消息管理器"), pMenu);
    QAction *pInvite = new QAction(tr("邀请同事加入"), pMenu);
    QAction *pSign = new QAction(tr("工作签名"), pMenu);

    QAction *pFeedback = new QAction(tr("意见反馈"), pMenu);
    QAction *pSetting = new QAction(tr("设置"), pMenu);
    QAction *pAbout = new QAction(tr("关于"), pMenu);

    // 把 QAction 对象添加到菜单上
    pMenu->addAction(pCollect);
    pMenu->addAction(pMsgMgr);
    pMenu->addSeparator();  // 添加分割线
    pMenu->addAction(pInvite);
    pMenu->addSeparator();  // 添加分割线
    pMenu->addAction(pSign);
    pMenu->addAction(pFeedback);
    pMenu->addSeparator();  // 添加分割线
    pMenu->addAction(pSetting);
    pMenu->addAction(pAbout);    

    connect(pMenu, SIGNAL(triggered(QAction *)), this, SLOT(OnMenuTriggered(QAction *)));

    QPoint ptMenu = mapToGlobal(pos());
    ptMenu.setX(ptMenu.x() + width());
    ptMenu.setY(ptMenu.y() + height());
    ptMenu.setY(ptMenu.y() - 252);
    pMenu->exec(ptMenu);

    // 释放内存
    QList<QAction *> list = pMenu->actions();
    foreach(QAction *pAction, list)
        delete pAction;

    delete pMenu;
}

void CNavPanel::OnMenuTriggered(QAction *action)
{
    Q_UNUSED(action);
}
