#include "Component.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "public.h"
#include "NotificationPanel.h"
#include "PopConfirm.h"

CComponent::CComponent(QWidget *parent) : QWidget(parent)
{
    m_groupNotice = NULL;
    m_btnOpenNotice1 = NULL;
    m_btnOpenNotice2 = NULL;
    m_btnOpenLT  = NULL;
    m_btnOpenRT  = NULL;
    m_btnOpenLB  = NULL;
    m_btnOpenRB  = NULL;

    m_groupPopConfirm = NULL;
    m_btnTop  = NULL;
    m_btnLeft  = NULL;
    m_btnRight  = NULL;
    m_btnBottom  = NULL;
    m_btnTL = NULL;
    m_btnTR = NULL;
    m_btnLT = NULL;
    m_btnRT = NULL;
    m_btnLB = NULL;
    m_btnRB = NULL;
    m_btnBL = NULL;
    m_btnBR = NULL;

    m_groupSlider = NULL;
    m_pSlider = NULL;
    m_pSlider2 = NULL;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "BaseDlg");

    CreateAllCtrls();
    InitCtrls();
    InitSlots();
    Relayout();
}

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

void CComponent::CreateAllCtrls()
{
    NEW_OBJECT(m_groupNotice, QGroupBox);
    NEW_OBJECT(m_groupPopConfirm, QGroupBox);

    NEW_OBJECT(m_btnOpenNotice1, QPushButton);
    NEW_OBJECT(m_btnOpenNotice2, QPushButton);
    NEW_OBJECT(m_btnOpenLT, QPushButton);
    NEW_OBJECT(m_btnOpenRT, QPushButton);
    NEW_OBJECT(m_btnOpenLB, QPushButton);
    NEW_OBJECT(m_btnOpenRB, QPushButton);

    NEW_OBJECT(m_btnTop, QPushButton);
    NEW_OBJECT(m_btnLeft, QPushButton);
    NEW_OBJECT(m_btnRight, QPushButton);
    NEW_OBJECT(m_btnBottom, QPushButton);
    NEW_OBJECT(m_btnTL, QPushButton);
    NEW_OBJECT(m_btnTR, QPushButton);
    NEW_OBJECT(m_btnLT, QPushButton);
    NEW_OBJECT(m_btnRT, QPushButton);
    NEW_OBJECT(m_btnLB, QPushButton);
    NEW_OBJECT(m_btnRB, QPushButton);
    NEW_OBJECT(m_btnBL, QPushButton);
    NEW_OBJECT(m_btnBR, QPushButton);

    NEW_OBJECT(m_groupSlider, QGroupBox);
    NEW_OBJECT(m_pSlider, CSlider);
    NEW_OBJECT(m_pSlider2, CSlider);
}

void CComponent::InitCtrls()
{
    InitNoticeCtrl();
    InitPopConfirm();
    InitSlider();
}

void CComponent::InitNoticeCtrl()
{
    m_groupNotice->setFixedHeight(120);
    m_groupNotice->setTitle(tr("通知提醒框"));
    m_btnOpenNotice1->setText("自动关闭");
    m_btnOpenNotice2->setText("不关闭");
    m_btnOpenNotice1->setToolTip("最简单的用法，4.5 秒后自动关闭。");
    m_btnOpenNotice2->setToolTip("不自动关闭");
    m_btnOpenNotice1->setFixedWidth(188);
    m_btnOpenNotice2->setFixedWidth(188);

    m_btnOpenLT->setText("左上");
    m_btnOpenRT->setText("右上");
    m_btnOpenLB->setText("左下");
    m_btnOpenRB->setText("右下");

    QGridLayout *layoutComponent = new QGridLayout();
    layoutComponent->addWidget(m_btnOpenNotice1, 0, 0, 1, 2);
    layoutComponent->addWidget(m_btnOpenLT, 0, 2, 1, 1);
    layoutComponent->addWidget(m_btnOpenRT, 0, 3, 1, 1);

    layoutComponent->addWidget(m_btnOpenNotice2, 1, 0, 1, 2);
    layoutComponent->addWidget(m_btnOpenLB, 1, 2, 1, 1);
    layoutComponent->addWidget(m_btnOpenRB, 1, 3, 1, 1);

    layoutComponent->setSpacing(8);
    layoutComponent->setMargin(10);

    m_groupNotice->setLayout(layoutComponent);
}

void CComponent::InitPopConfirm()
{
    //m_groupPopConfirm->setFixedHeight(220);
    m_groupPopConfirm->setTitle(tr("气泡确认框"));
    m_btnTop->setText("Top");
    m_btnLeft->setText("Left");
    m_btnRight->setText("Right");
    m_btnBottom->setText("Bottom");

    m_btnTL->setText("TL");
    m_btnTR->setText("TR");
    m_btnLT->setText("LT");
    m_btnRT->setText("RT");
    m_btnLB->setText("LB");
    m_btnRB->setText("RB");
    m_btnBL->setText("BL");
    m_btnBR->setText("BR");

    QGridLayout *layoutComponent = new QGridLayout();
    layoutComponent->addWidget(m_btnTL, 0, 1, 1, 1);
    layoutComponent->addWidget(m_btnTop, 0, 2, 1, 1);
    layoutComponent->addWidget(m_btnTR, 0, 3, 1, 1);
    layoutComponent->addWidget(m_btnLT, 1, 0, 1, 1);
    layoutComponent->addWidget(m_btnRT, 1, 4, 1, 1);
    layoutComponent->addWidget(m_btnLeft, 2, 0, 1, 1);
    layoutComponent->addWidget(m_btnRight, 2, 4, 1, 1);
    layoutComponent->addWidget(m_btnLB, 3, 0, 1, 1);
    layoutComponent->addWidget(m_btnRB, 3, 4, 1, 1);
    layoutComponent->addWidget(m_btnBL, 4, 1, 1, 1);
    layoutComponent->addWidget(m_btnBottom, 4, 2, 1, 1);
    layoutComponent->addWidget(m_btnBR, 4, 3, 1, 1);

    layoutComponent->setSpacing(8);
    layoutComponent->setMargin(10);

    m_groupPopConfirm->setLayout(layoutComponent);
}

void CComponent::InitSlider()
{
    m_groupSlider->setFixedHeight(220);
    m_groupSlider->setTitle(tr("滑动输入条"));

    m_pSlider->EnableRange(true);
    m_pSlider->SetRange(0, 1000);
    m_pSlider->SetStep(1);
    m_pSlider->SetPos(10, 100);

    m_pSlider2->EnableRange(false);
    m_pSlider2->SetRange(0, 100);
    m_pSlider2->SetStep(1);
    m_pSlider2->SetCurPos(50);
    m_pSlider2->EnablePercent(true);

    QVBoxLayout *layoutComponent = new QVBoxLayout();
    layoutComponent->addWidget(m_pSlider);
    layoutComponent->addWidget(m_pSlider2);
    layoutComponent->setSpacing(6);
    layoutComponent->setMargin(6);
    m_groupSlider->setLayout(layoutComponent);
}

void CComponent::InitSlots()
{
    connect(m_btnOpenNotice1, &QPushButton::clicked, [this]
    {
        NotificationMgr::GetInstance()->Notice("This is the content of the notification. This is the content of the notification. This is the content of the notification.",
                                               "Notification Title");
    });

    connect(m_btnOpenNotice2, &QPushButton::clicked, [this]
    {
        NotificationMgr::GetInstance()->Notice("I will never close automatically. This is a purposely very very long description that has many many characters and words.",
                                               "Notification Title", false);
    });

    connect(m_btnOpenLT, &QPushButton::clicked, [this]
    {
        NotificationMgr::GetInstance()->Notice("This is the content of the notification. This is the content of the notification. This is the content of the notification.",
                                               "Notification Title", true, NotificationMgr::AlignLeft | NotificationMgr::AlignTop);
    });

    connect(m_btnOpenRT, &QPushButton::clicked, [this]
    {
        NotificationMgr::GetInstance()->Notice("I will never close automatically. This is a purposely very very long description that has many many characters and words.",
                                               "Notification Title", true, NotificationMgr::AlignRight | NotificationMgr::AlignTop);
    });

    connect(m_btnOpenLB, &QPushButton::clicked, [this]
    {
        NotificationMgr::GetInstance()->Notice("I will never close automatically. This is a purposely very very long description that has many many characters and words.",
                                               "Notification Title", true, NotificationMgr::AlignLeft | NotificationMgr::AlignBottom);
    });

    connect(m_btnOpenRB, &QPushButton::clicked, [this]
    {
        NotificationMgr::GetInstance()->Notice("I will never close automatically. This is a purposely very very long description that has many many characters and words.",
                                               "Notification Title", true, NotificationMgr::AlignRight | NotificationMgr::AlignBottom);
    });

    /////////////////////////////

    connect(m_btnTop, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnTop);
        pPopconfirm->Show(CPopConfirm::AlignTop);
    });

    connect(m_btnLeft, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnLeft);
        pPopconfirm->Show(CPopConfirm::AlignLeft);
    });

    connect(m_btnRight, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnRight);
        pPopconfirm->Show(CPopConfirm::AlignRight);
    });

    connect(m_btnBottom, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnBottom);
        pPopconfirm->Show(CPopConfirm::AlignBottom);
    });

    connect(m_btnTL, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnTL);
        pPopconfirm->Show(CPopConfirm::AlignTopLeft);
    });

    connect(m_btnTR, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnTR);
        pPopconfirm->Show(CPopConfirm::AlignTopRight);
    });

    connect(m_btnLT, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnLT);
        pPopconfirm->Show(CPopConfirm::AlignLeftTop);
    });

    connect(m_btnRT, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnRT);
        pPopconfirm->Show(CPopConfirm::AlignRightTop);
    });

    connect(m_btnLB, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnLB);
        pPopconfirm->Show(CPopConfirm::AlignLeftBottom);
    });

    connect(m_btnRB, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnRB);
        pPopconfirm->Show(CPopConfirm::AlignRightBottom);
    });

    connect(m_btnBL, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnBL);
        pPopconfirm->Show(CPopConfirm::AlignBottomLeft);
    });

    connect(m_btnBR, &QPushButton::clicked, [this]
    {
        CPopConfirm *pPopconfirm = new CPopConfirm(m_btnBR);
        pPopconfirm->Show(CPopConfirm::AlignBottomRight);
    });
}

void CComponent::Relayout()
{
    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addWidget(m_groupNotice);
    layoutMain->addWidget(m_groupPopConfirm);
    layoutMain->addWidget(m_groupSlider);
    //layoutMain->addStretch();
    layoutMain->setSpacing(8);
    layoutMain->setMargin(25);

    setLayout(layoutMain);
}
