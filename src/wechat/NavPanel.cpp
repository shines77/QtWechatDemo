#include "NavPanel.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "PushButtonEx.h"
#include "IconHelper.h"
#include "UserDetailDlg.h"

#include <QDebug>

NavPanel::NavPanel(QWidget *parent) : QWidget(parent)
{
    m_btnUserIcon = NULL;
    m_btnMessage = NULL;
    m_btnContacts = NULL;
    m_btnFavorites = NULL;
    m_btnCalendar = NULL;
    m_btnWorkspace = NULL;
    m_btnWeDoc = NULL;
    m_btnWeDrive = NULL;
    m_btnMeeting = NULL;
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

void NavPanel::CreateAllCtrls()
{
    NEW_OBJECT(m_btnUserIcon, CPushButtonEx);
    NEW_OBJECT(m_btnMessage, CPushButtonEx);
    NEW_OBJECT(m_btnContacts, CPushButtonEx);
    NEW_OBJECT(m_btnFavorites, CPushButtonEx);
    NEW_OBJECT(m_btnCalendar, CPushButtonEx);
    NEW_OBJECT(m_btnWorkspace, CPushButtonEx);
    NEW_OBJECT(m_btnWeDoc, CPushButtonEx);
    NEW_OBJECT(m_btnWeDrive, CPushButtonEx);
    NEW_OBJECT(m_btnMeeting, CPushButtonEx);
    NEW_OBJECT(m_btnMore, CPushButtonEx);
    NEW_OBJECT(m_lblSeparatorLine, QLabel);
    NEW_OBJECT(m_pUserDetailDlg, CUserDetailDlg);
}

void NavPanel::InitCtrls()
{
    m_btnUserIcon->setFixedSize(35, 35);

    //QSize sizeBtn(50, 50);
    int sizeBtn = 50;
    m_btnMessage->setFixedHeight(sizeBtn);
    m_btnContacts->setFixedHeight(sizeBtn);
    m_btnFavorites->setFixedHeight(sizeBtn);
    m_btnCalendar->setFixedHeight(sizeBtn);
    m_btnWorkspace->setFixedHeight(sizeBtn);
    m_btnWeDoc->setFixedHeight(sizeBtn);
    m_btnWeDrive->setFixedHeight(sizeBtn);
    m_btnMeeting->setFixedHeight(sizeBtn);
    m_btnMore->setFixedHeight(sizeBtn);

    m_btnUserIcon->setIcon(QIcon(":/avatar/avatar/user-avatar.jpeg"));
    m_btnUserIcon->setIconSize(m_btnUserIcon->size());

    IconHelper::SetIcon(m_btnMessage, QChar(0xe645));
    IconHelper::SetIcon(m_btnContacts, QChar(0xe63a));
    IconHelper::SetIcon(m_btnFavorites, QChar(0xe668), 24);
    IconHelper::SetIcon(m_btnCalendar, QChar(0xe603), 24);
    IconHelper::SetIcon(m_btnWorkspace, QChar(0xe6a9));
    IconHelper::SetIcon(m_btnWeDoc, QChar(0xe670));
    IconHelper::SetIcon(m_btnWeDrive, QChar(0xe663));
    IconHelper::SetIcon(m_btnMeeting, QChar(0xe673));
    IconHelper::SetIcon(m_btnMore, QChar(0xe642));

    m_lblSeparatorLine->setFixedHeight(1);
    m_lblSeparatorLine->setStyleSheet("background-color:#4A7ABA");
    m_pUserDetailDlg->hide();

    // 初始化tab
    QSignalMapper *pSignalMapperPushed = new QSignalMapper(this);
    pSignalMapperPushed->setMapping(m_btnMessage, TAB_PAGE_MESSAGE);
    pSignalMapperPushed->setMapping(m_btnContacts, TAB_PAGE_CONTACTS);
    pSignalMapperPushed->setMapping(m_btnFavorites, TAB_PAGE_FAVORITES);
    pSignalMapperPushed->setMapping(m_btnCalendar, TAB_PAGE_CALENDAR);
    pSignalMapperPushed->setMapping(m_btnWorkspace, TAB_PAGE_WORKSPACE);
    pSignalMapperPushed->setMapping(m_btnWeDoc, TAB_PAGE_WEDOC);
    pSignalMapperPushed->setMapping(m_btnWeDrive, TAB_PAGE_WEDRIVE);
    pSignalMapperPushed->setMapping(m_btnMeeting, TAB_PAGE_MEETING);

    QList<CPushButtonEx *> listBtns = findChildren<CPushButtonEx *>();
    foreach (QPushButton *btn, listBtns)
    {
        if (btn != m_btnUserIcon)
            connect(btn, SIGNAL(clicked()), pSignalMapperPushed, SLOT(map()));
    }

    connect(pSignalMapperPushed, SIGNAL(mapped(int)), this, SLOT(OnSignalPushedMapped(int)));

    m_btnMessage->setCheckable(true);
    m_btnContacts->setCheckable(true);
    m_btnFavorites->setCheckable(true);
    m_btnCalendar->setCheckable(true);
    m_btnWorkspace->setCheckable(true);
    m_btnWeDoc->setCheckable(true);
    m_btnWeDrive->setCheckable(true);
    m_btnMeeting->setCheckable(true);
}

void NavPanel::InitSlots()
{
    connect(m_btnUserIcon, SIGNAL(clicked()), this, SLOT(OnBtnUserIconClicked()));
    connect(m_btnMore, SIGNAL(clicked()), this, SLOT(OnBtnMoreClicked()));
}

void NavPanel::Relayout()
{
    QHBoxLayout *layoutUserIcon = new QHBoxLayout();
    layoutUserIcon->addWidget(m_btnUserIcon);
    layoutUserIcon->setContentsMargins(10, 28, 16, 18);

    QVBoxLayout *layoutCenter = new QVBoxLayout();
    layoutCenter->addLayout(layoutUserIcon);
    layoutCenter->addWidget(m_btnMessage);
    layoutCenter->addWidget(m_btnContacts);
    layoutCenter->addWidget(m_btnFavorites);
    layoutCenter->addWidget(m_btnCalendar);
    layoutCenter->addWidget(m_btnWorkspace);
    layoutCenter->addWidget(m_lblSeparatorLine);
    layoutCenter->addWidget(m_btnWeDoc);
    layoutCenter->addWidget(m_btnWeDrive);
    layoutCenter->addWidget(m_btnMeeting);
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

void NavPanel::OnBtnUserIconClicked()
{
    m_pUserDetailDlg->show();

    QPoint ptBtn = m_btnUserIcon->mapToGlobal(m_btnUserIcon->pos());
    QPoint point(ptBtn);
    point.setX(ptBtn.x() - m_btnUserIcon->pos().x() + m_btnUserIcon->width() + 2);
    point.setY(ptBtn.y() - m_btnUserIcon->pos().y());
    m_pUserDetailDlg->move(point);
}

void NavPanel::OnSignalPushedMapped(int nCmd)
{
    emit SignalTabChanged(EMainTabPage(nCmd));
}

void NavPanel::OnMainTabChanged(EMainTabPage eMainTabPage)
{
    m_btnMessage->setChecked(false);
    m_btnContacts->setChecked(false);
    m_btnFavorites->setChecked(false);
    m_btnCalendar->setChecked(false);
    m_btnWorkspace->setChecked(false);
    m_btnWeDoc->setChecked(false);
    m_btnWeDrive->setChecked(false);
    m_btnMeeting->setChecked(false);

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

    case TAB_PAGE_WEDOC:
        {
            m_btnWeDoc->setChecked(true);
        }
        break;

    case TAB_PAGE_WEDRIVE:
        {
            m_btnWeDrive->setChecked(true);
        }
        break;

    case TAB_PAGE_MEETING:
        {
            m_btnMeeting->setChecked(true);
        }
        break;
    }
}

void NavPanel::OnBtnMoreClicked()
{
    // 创建菜单对象
    QMenu *pMenu = new QMenu();

    QAction *pCollect = new QAction(tr("收藏"), pMenu);
    QAction *pMsgMgr = new QAction(tr("消息管理器"), pMenu);
    QAction *pInvite = new QAction(tr("邀请同事加入"), pMenu);
    QAction *pSign = new QAction(tr("工作签名"), pMenu);

    QAction *pRest = new QAction(tr("休息一下"), pMenu);
    QAction *pGoOffwork = new QAction(tr("下班了"), pMenu);

    QMenu *pChildRest = new QMenu(pMenu);
    pChildRest->setTitle(tr("休息一下"));
    pChildRest->addAction(pRest);
    pChildRest->addAction(pGoOffwork);

    QAction *pSetting = new QAction(tr("设置"), pMenu);
    QAction *pAbout = new QAction(tr("关于"), pMenu);
    QAction *pFeedback = new QAction(tr("吐个槽"), pMenu);

    // 把QAction对象添加到菜单上
    pMenu->addAction(pCollect);
    pMenu->addAction(pMsgMgr);
    pMenu->addSeparator();  // 添加分割线
    pMenu->addAction(pInvite);
    pMenu->addSeparator();  // 添加分割线
    pMenu->addAction(pSign);
    pMenu->addMenu(pChildRest);
    pMenu->addSeparator();  // 添加分割线
    pMenu->addAction(pSetting);
    pMenu->addAction(pAbout);
    pMenu->addSeparator();  // 添加分割线
    pMenu->addAction(pFeedback);

    connect(pMenu, SIGNAL(triggered(QAction *)), this, SLOT(OnMenuTriggered(QAction *)));

    QPoint ptMenu = mapToGlobal(pos());
    ptMenu.setX(ptMenu.x() + width());
    ptMenu.setY(ptMenu.y() + height());
    ptMenu.setY(ptMenu.y() - 252);
    pMenu->exec(ptMenu);

    // 释放内存
    QList<QAction *> list = pMenu->actions();
    foreach (QAction *pAction, list)
        delete pAction;

    delete pMenu;
}

void NavPanel::OnMenuTriggered(QAction *action)
{
    Q_UNUSED(action);
}
