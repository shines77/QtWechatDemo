#include "UserPanel.h"

#include <QVariant>
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

CUserDetailPanel::CUserDetailPanel(QWidget *parent)
{
    m_bEnter = false;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "UserDetailPanel");

    m_pixBg = QPixmap(":/qss/res/user_bg.png");
    m_pixBigBg = m_pixBg.copy(20, 20, m_pixBg.width() - 40, m_pixBg.height() - 40);
}

void CUserDetailPanel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);     // 创建画家对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QFont ft = painter.font();

    QRect rcClient = rect();
    //rcClient.marginsRemoved(QMargins(0, 0, 0, 0));

    painter.save();
    painter.translate(0, 0);    // 移动绘制原点
    painter.scale(rcClient.width() / 400.0, rcClient.height() / 470.0);

    QRect rectMain(0, 0, 400, 470);

    QRect rcImg(rectMain);
    rcImg.setBottom(rcImg.top() + 230);

    if (m_bEnter)
    {
        QPixmap p = m_pixBigBg.scaled(rcImg.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(rcImg, p);
    }
    else
    {
        QPixmap p = m_pixBg.scaled(rcImg.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(rcImg, p);
    }

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255));
    QRect rcAvatarBg(20, 190, 77, 77);
    painter.drawEllipse(rcAvatarBg);

    QRect rcAvatar = rcAvatarBg.marginsRemoved(QMargins(5, 5, 5, 5));
    QPixmap p1 = QPixmap(":/avatar/avatar/young-man.png").scaled(rcAvatar.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(rcAvatar, p1);
    painter.restore();

    QFont ftTemp = ft;
    ftTemp.setPointSize(15);
    ftTemp.setBold(true);
    painter.setFont(ftTemp);
    painter.setPen(QColor("#4DD9D5"));
    painter.drawText(QRect(160, 240, 220, 42), Qt::AlignRight | Qt::AlignVCenter, tr("顾一城"));
    painter.setFont(ft);

    int nItem = 0;
    const int nSpaceH = 42;

    {
        int nOffset = nItem * nSpaceH;

        painter.save();
        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(20, 277 + nOffset, 307, 20), Qt::AlignLeft | Qt::AlignTop, tr("Qt"));

        QRect rcSlider1(20, 300 + nOffset, 307, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E6EBF5"));
        painter.drawRoundedRect(rcSlider1, 5, 5);

        QRect rcSel(20, 300 + nOffset, 307 * 0.9, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#1890FF"));
        painter.drawRoundedRect(rcSel, 5, 5);
        painter.drawRect(rcSel.marginsRemoved(QMargins(5, 0, 0, 0)));

        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(340, 295 + nOffset, 40, 40), Qt::AlignLeft | Qt::AlignTop, tr("90%"));

        painter.restore();

        nItem++;
    }

    {
        int nOffset = nItem * nSpaceH;

        painter.save();
        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(20, 277 + nOffset, 307, 20), Qt::AlignLeft | Qt::AlignTop, tr("Qss"));

        QRect rcSlider1(20, 300 + nOffset, 307, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E6EBF5"));
        painter.drawRoundedRect(rcSlider1, 5, 5);

        QRect rcSel(20, 300 + nOffset, 307 * 0.2, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#13CE66"));
        painter.drawRoundedRect(rcSel, 5, 5);
        painter.drawRect(rcSel.marginsRemoved(QMargins(5, 0, 0, 0)));

        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(340, 295 + nOffset, 40, 40), Qt::AlignLeft | Qt::AlignTop, tr("20%"));

        painter.restore();

        nItem++;
    }

    {
        int nOffset = nItem * nSpaceH;

        painter.save();
        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(20, 277 + nOffset, 307, 20), Qt::AlignLeft | Qt::AlignTop, tr("C++"));

        QRect rcSlider1(20, 300 + nOffset, 307, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E6EBF5"));
        painter.drawRoundedRect(rcSlider1, 5, 5);

        QRect rcSel(20, 300 + nOffset, 307 * 0.95, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#FF9900"));
        painter.drawRoundedRect(rcSel, 5, 5);
        painter.drawRect(rcSel.marginsRemoved(QMargins(5, 0, 0, 0)));

        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(340, 295 + nOffset, 40, 40), Qt::AlignLeft | Qt::AlignTop, tr("95%"));

        painter.restore();

        nItem++;
    }

    {
        int nOffset = nItem * nSpaceH;

        painter.save();
        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(20, 277 + nOffset, 307, 20), Qt::AlignLeft | Qt::AlignTop, tr("Linux"));

        QRect rcSlider1(20, 300 + nOffset, 307, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E6EBF5"));
        painter.drawRoundedRect(rcSlider1, 5, 5);

        QRect rcSel(20, 300 + nOffset, 307 * 0.8, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E46CBB"));
        painter.drawRoundedRect(rcSel, 5, 5);
        painter.drawRect(rcSel.marginsRemoved(QMargins(5, 0, 0, 0)));

        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(340, 295 + nOffset, 40, 40), Qt::AlignLeft | Qt::AlignTop, tr("80%"));

        painter.restore();

        nItem++;
    }

    painter.restore();
}

void CUserDetailPanel::enterEvent(QEvent *event)
{
    m_bEnter = true;
    update();
}

void CUserDetailPanel::leaveEvent(QEvent *event)
{
    m_bEnter = false;
    update();
}

CUserPanel::CUserPanel(QWidget *parent) : QWidget(parent)
{
    m_pUserPanel = NULL;

    setAttribute(Qt::WA_StyledBackground);              // 禁止父窗口样式影响子控件样式
    setProperty("form", "UserPanel");
    setAttribute(Qt::WA_TranslucentBackground, true);

    CreateAllCtrls();
    InitCtrls();
    InitSlots();
    Relayout();
}

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

void CUserPanel::CreateAllCtrls()
{
    NEW_OBJECT(m_pUserPanel, CUserDetailPanel);
}

void CUserPanel::InitCtrls()
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

void CUserPanel::InitSlots()
{
    //
}

void CUserPanel::Relayout()
{
    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addWidget(m_pUserPanel);
    layoutMain->setSpacing(8);
    layoutMain->setMargin(8);
    setLayout(layoutMain);
}
