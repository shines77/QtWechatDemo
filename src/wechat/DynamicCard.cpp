#include "DynamicCard.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVariant>
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QGraphicsDropShadowEffect>

#include "Public.h"
#include "IconHelper.h"

CCard::CCard(QWidget *parent)
{
    m_nCurValue = 0;
    m_nValue = 832;
    m_nIndex = 0;
    m_pUpdateTimer = NULL;
    m_icon = 0xe647;
    m_colorBg = QColor("#2D8CF0");
    m_bEnter = false;

    setAttribute(Qt::WA_StyledBackground);              // 禁止父窗口样式影响子控件样式
    setProperty("form", "BaseDlg");
    setAttribute(Qt::WA_TranslucentBackground, true);

    m_pUpdateTimer = new QTimer(this);
    connect(m_pUpdateTimer, SIGNAL(timeout()), this, SLOT(OnTimerUpdateTimeOut()));
}

void CCard::SetValue(int nValue)
{
    m_nCurValue = 0;
    m_nValue = nValue;
    m_nIndex = 0;
}

void CCard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);    // 创建画家对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QFont ft = painter.font();

    QRect rcClient = rect();
    rcClient.marginsRemoved(QMargins(0, 0, 0, 0));

    painter.translate(0, 0);    // 移动绘制原点
    painter.scale(rcClient.width() / 257.0, rcClient.height() / 112.0);

    QRect rectMain(0, 0, 257, 112);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawRoundedRect(rectMain, 5, 5);

    QRect rectLeft(0, 0, 90, 112);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_colorBg);
    painter.drawRoundedRect(rectLeft, 5, 5);
    painter.drawRect(rectLeft.marginsRemoved(QMargins(10, 0, 0, 0)));

    QFont ftTemp = IconHelper::GetFont();

    if (m_bEnter)
        ftTemp.setPixelSize(40);
    else
        ftTemp.setPixelSize(28);

    painter.setFont(ftTemp);
    painter.setPen(QColor("#FFFFFF"));
    painter.drawText(rectLeft, Qt::AlignCenter, QChar(m_icon));
    painter.setFont(ft);

    QRect rectNum(rectMain);
    rectNum.setLeft(rectLeft.right());
    rectNum.setBottom(rectMain.bottom() - 38);

    ftTemp = ft;
    ftTemp.setPointSize(28);
    painter.setFont(ftTemp);
    painter.setPen(QColor("#515A6E"));
    painter.drawText(rectNum, Qt::AlignCenter, QString::number(m_nCurValue));
    painter.setFont(ft);

    QRect rectDetail(rectNum);
    rectDetail.setTop(rectNum.bottom());
    rectDetail.setBottom(rectMain.bottom());

    ftTemp = ft;
    ftTemp.setPointSize(15);
    painter.setFont(ftTemp);
    painter.setPen(QColor("#515A6E"));
    painter.drawText(rectDetail, Qt::AlignCenter, m_strTitle);
    painter.setFont(ft);
}

void CCard::resizeEvent(QResizeEvent *event)
{
    setFixedWidth(height() * (double)257 / 112);
}

void CCard::showEvent(QShowEvent *event)
{
    m_pUpdateTimer->stop();
    m_nIndex = 0;
    m_nCurValue = 0;
    m_pUpdateTimer->start(10);
}

void CCard::enterEvent(QEvent *event)
{
    m_bEnter = true;
    update();
}

void CCard::leaveEvent(QEvent *event)
{
    m_bEnter = false;
    update();
}

void CCard::OnTimerUpdateTimeOut()
{
    m_pUpdateTimer->stop();

    if (m_nCurValue < m_nValue)
    {
        const int nNewInterval = 100;
        if (m_pUpdateTimer->interval() < nNewInterval)
        {
            m_nCurValue = qPow(1.5, m_nIndex);
            m_nIndex++;

            if (m_nCurValue >= m_nValue)
            {
                m_nCurValue = m_nValue - 5;
                m_pUpdateTimer->start(nNewInterval);
            }
            else
            {
                m_pUpdateTimer->start();
            }
        }
        else
        {
            m_nCurValue++;

            if (m_nCurValue >= m_nValue)
            {
                m_nCurValue = m_nValue;
                m_pUpdateTimer->stop();
            }
            else
            {
                m_pUpdateTimer->start();
            }
        }
    }
    else
    {
        m_pUpdateTimer->stop();
    }

    update();
}

////////////////////////////////////////////////////////////////////////////
/// \brief CDynamicCard::CDynamicCard
/// \param parent
///
///
CDynamicCard::CDynamicCard(QWidget *parent) : QWidget(parent)
{
    m_pCard = NULL;

    setAttribute(Qt::WA_StyledBackground);              // 禁止父窗口样式影响子控件样式
    setProperty("form", "BaseDlg");
    setAttribute(Qt::WA_TranslucentBackground, true);

    CreateAllCtrls();
    InitCtrls();
    InitSlots();
    Relayout();
}

void CDynamicCard::SetValue(int nValue)
{
    m_pCard->SetValue(nValue);
}

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

void CDynamicCard::CreateAllCtrls()
{
    NEW_OBJECT(m_pCard, CCard);
}

void CDynamicCard::InitCtrls()
{
    // 设置边框阴影
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    // 设置具体阴影
    QGraphicsDropShadowEffect *shadowBorder = new QGraphicsDropShadowEffect(this);
    shadowBorder->setOffset(0, 0);
    // 阴影颜色
    shadowBorder->setColor(QColor(0x44, 0x44, 0x44, 127));
    // 阴影半径
    shadowBorder->setBlurRadius(8);
    setGraphicsEffect(shadowBorder);
}

void CDynamicCard::InitSlots()
{
    //
}

void CDynamicCard::Relayout()
{
    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addWidget(m_pCard);
    layoutMain->setSpacing(8);
    layoutMain->setMargin(10);
    setLayout(layoutMain);
}
