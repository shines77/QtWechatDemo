#include "WxMainWindow.h"
#include "ui_WxMainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>

#include "PushButtonEx.h"
#include "IconHelper.h"
#include "MsgQueue.h"
#include "NavPanel.h"
#include "ChatPanel.h"
#include "ContactPanel.h"
#include "FavoritePanel.h"
#include "NotificationPanel.h"
#include "Component.h"
#include "DataMgrPanel.h"
#include "IconfontPanel.h"
#include "TipWidget.h"

WxMainWindow::WxMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WxMainWindow)
{
    ui->setupUi(this);

    m_widgetTitle = NULL;
    m_pStackedWidget = NULL;

    m_btnMin = NULL;
    m_btnMax = NULL;
    m_btnClose = NULL;
    m_trayIcon = NULL;
    m_systemTrayMenu = NULL;

    m_pNavPanel = NULL;

    m_pChatPanel = NULL;
    m_pContactPanel = NULL;
    m_pFavoritePanel = NULL;

    m_eMainTabPage = TAB_PAGE_MESSAGE;

    m_bMaxWindows = false;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setProperty("form", "WxMainWindow");
    setProperty("canMove", "true");

    NotificationMgr::GetInstance()->Init(this);

    CreateAllCtrls();
    InitCtrls();
    InitSlots();
    Relayout();

    InitTrayIcon();
    ChangeTabPage();
}

WxMainWindow::~WxMainWindow()
{
    delete ui;
}

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

void WxMainWindow::CreateAllCtrls()
{
    NEW_OBJECT(m_widgetTitle, QWidget);
    NEW_OBJECT(m_pStackedWidget, QStackedWidget);

    NEW_OBJECT(m_btnMin, CPushButtonEx);
    NEW_OBJECT(m_btnMax, CPushButtonEx);
    NEW_OBJECT(m_btnClose, CPushButtonEx);
    NEW_OBJECT(m_trayIcon, QSystemTrayIcon);
    NEW_OBJECT(m_systemTrayMenu, QMenu);

    NEW_OBJECT(m_pNavPanel, CNavPanel);
    NEW_OBJECT(m_pChatPanel, CChatPanel);
    NEW_OBJECT(m_pContactPanel, CContactPanel);
    NEW_OBJECT(m_pFavoritePanel, CFavoritePanel);
}

void WxMainWindow::InitCtrls()
{
    m_pNavPanel->setFixedWidth(60);

    m_pStackedWidget->insertWidget(TAB_PAGE_MESSAGE, m_pChatPanel);
    m_pStackedWidget->insertWidget(TAB_PAGE_CONTACTS, new CDataMgrPanel(this));  m_pContactPanel->hide();
    m_pStackedWidget->insertWidget(TAB_PAGE_FAVORITES, m_pFavoritePanel);
    m_pStackedWidget->insertWidget(TAB_PAGE_CALENDAR, new CComponent(this));
    m_pStackedWidget->insertWidget(TAB_PAGE_WORKSPACE, new CIconFontPanel(this));

    m_btnMin->setFixedSize(36, 26);
    m_btnMax->setFixedSize(36, 26);
    m_btnClose->setFixedSize(36, 26);

    IconHelper::SetIcon(m_btnMin, QChar(0xe7d8), 15);
    IconHelper::SetIcon(m_btnMax, QChar(0xe693), 15);
    IconHelper::SetIcon(m_btnClose, QChar(0xe64f), 15);

    m_btnMin->setToolTip(tr("最小化"));
    m_btnMax->setToolTip(tr("最大化"));
    m_btnClose->setToolTip(tr("关闭"));

    m_btnMin->setProperty("toolbar", "true");
    m_btnMax->setProperty("toolbar", "true");
    m_btnClose->setProperty("toolbar_close", "true");

    AutoTip->setParent(this);   // 设置实例的引用者
}

void WxMainWindow::InitSlots()
{
    connect(m_pNavPanel, SIGNAL(SignalTabChanged(EMainTabPage)), this, SLOT(OnTabChanged(EMainTabPage)));
    connect(this, SIGNAL(SignalTabChanged(EMainTabPage)), m_pNavPanel, SLOT(OnMainTabChanged(EMainTabPage)));
    connect(this, SIGNAL(SignalTabChanged(EMainTabPage)), m_pFavoritePanel, SLOT(OnMainTabChanged(EMainTabPage)));

    connect(m_btnMin, SIGNAL(clicked()), this, SLOT(OnMinWindows()));
    connect(m_btnMax, SIGNAL(clicked()), this, SLOT(OnMaxWindows()));
    connect(m_btnClose, SIGNAL(clicked()), this, SLOT(OnClose()));
    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
                SLOT(OnSystemTrayIconActivated(QSystemTrayIcon::ActivationReason)));
}

void WxMainWindow::Relayout()
{
    QHBoxLayout *layoutTitle = new QHBoxLayout(m_widgetTitle);
    layoutTitle->addStretch();
    layoutTitle->addWidget(m_btnMin);
    layoutTitle->addWidget(m_btnMax);
    layoutTitle->addWidget(m_btnClose);
    layoutTitle->setSpacing(0);
    layoutTitle->setMargin(0);

    QVBoxLayout *layoutMainPanel = new QVBoxLayout();
    layoutMainPanel->addWidget(m_widgetTitle);
    layoutMainPanel->addWidget(m_pStackedWidget);
    layoutMainPanel->setSpacing(0);
    layoutMainPanel->setMargin(0);

    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_pNavPanel);
    layoutMain->addLayout(layoutMainPanel);
    layoutMain->setSpacing(0);
    layoutMain->setMargin(1);

    setLayout(layoutMain);
}

void WxMainWindow::InitTrayIcon()
{
    QAction *onlineAction = new QAction(tr("在线"), m_systemTrayMenu);
    QAction *offlineAction = new QAction(tr("离线"), m_systemTrayMenu);
    QAction *hiddenAction = new QAction(tr("隐身"), m_systemTrayMenu);
    QAction *afkAction = new QAction(tr("暂离"), m_systemTrayMenu);

    QMenu *pChildStatus = new QMenu(m_systemTrayMenu);
    pChildStatus->setTitle(tr("当前状态"));
    pChildStatus->addAction(onlineAction);
    pChildStatus->addAction(offlineAction);
    pChildStatus->addAction(hiddenAction);
    pChildStatus->addAction(afkAction);

    QAction *settingAction = new QAction(tr("设置"), this);
    QAction *feedbackAction = new QAction(tr("意见反馈"), this);
    QAction *helpAction = new QAction(tr("帮助"), this);

    QAction *restoreAction = new QAction(tr("打开主窗口"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    QAction *aboutAction = new QAction(tr("关于微信"), this);
    QAction *quitAction = new QAction(tr("退出微信"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_systemTrayMenu->addAction(settingAction);
    m_systemTrayMenu->addMenu(pChildStatus);
    m_systemTrayMenu->addSeparator();
    m_systemTrayMenu->addAction(restoreAction);
    m_systemTrayMenu->addSeparator();
    m_systemTrayMenu->addAction(feedbackAction);
    m_systemTrayMenu->addAction(helpAction);
    m_systemTrayMenu->addAction(aboutAction);
    m_systemTrayMenu->addSeparator();
    m_systemTrayMenu->addAction(quitAction);

    m_trayIcon->setContextMenu(m_systemTrayMenu);
    m_trayIcon->setIcon(QIcon(":/qss/res/WechatDemo_Tray.png"));    // 设置托盘图标显示
    m_trayIcon->setToolTip(tr("Windows 微信"));                      // 显示提示信息
    m_trayIcon->show();
}

void WxMainWindow::UpdateCtrlText()
{
    if (m_bMaxWindows)
    {
        m_btnMax->setToolTip(tr("向下还原"));
        IconHelper::SetIcon(m_btnMax, QChar(0xe64e), 15);
        setProperty("canMove", "false");
    }
    else
    {
        m_btnMax->setToolTip(tr("最大化"));
        IconHelper::SetIcon(m_btnMax, QChar(0xe693), 15);
        setProperty("canMove", "true");
    }
}

void WxMainWindow::ChangeTabPage()
{
    m_pStackedWidget->setCurrentIndex(m_eMainTabPage);

    update();

    emit SignalTabChanged(m_eMainTabPage);
}

void WxMainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    if (!m_widgetTitle->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        return;

    OnMaxWindows();
}

void WxMainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); // 创建画家对象
    painter.setRenderHint(QPainter::Antialiasing, true); // 反走样

    QRect rcClient = rect();

    if (TAB_PAGE_MESSAGE == m_eMainTabPage /*|| TAB_PAGE_CONTACTS == m_eMainTabPage*/)
    {
        QRect rcClientLeft(rcClient);
        rcClientLeft.setRight(m_pNavPanel->width() + 250);
        rcClientLeft.setTop(rcClientLeft.top() + 1);
        rcClientLeft.setBottom(rcClientLeft.bottom() - 1);
        rcClientLeft.setLeft(rcClientLeft.left() + m_pNavPanel->width());

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E6E8EB"));
        painter.drawRect(rcClientLeft);

        QRect rcClientRight(rcClient);
        rcClientRight.setRight(rcClient.right() - 1);
        rcClientRight.setTop(rcClientLeft.top());
        rcClientRight.setBottom(rcClientLeft.bottom());
        rcClientRight.setLeft(rcClientLeft.right());

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#F2F3F5"));
        painter.drawRect(rcClientRight);

        QPen pen(QColor("#D4D6D9"));
        painter.setPen(pen);
        painter.drawLine(rcClientLeft.topRight(), rcClientLeft.bottomRight());
    }
}

void WxMainWindow::OnTabChanged(EMainTabPage eMainTabPage)
{
    if (m_eMainTabPage == eMainTabPage)
        return;

    m_eMainTabPage = eMainTabPage;

    ChangeTabPage();
}

void WxMainWindow::OnMinWindows()
{
    setWindowState(Qt::WindowMinimized);
    update();
}

void WxMainWindow::OnMaxWindows()
{
    m_bMaxWindows = !m_bMaxWindows;

    if (m_bMaxWindows)
        setWindowState(Qt::WindowMaximized);
    else
        setWindowState(Qt::WindowNoState);

    UpdateCtrlText();
    update();
}

void WxMainWindow::OnClose()
{
    hide();
}

void WxMainWindow::OnSystemTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)             // 系统托盘中的图标被单击
        showNormal();
    else if (reason == QSystemTrayIcon::DoubleClick)    // 系统托盘中的图标被双击
        showNormal();
}
