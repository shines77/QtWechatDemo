#include "slider.h"
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <QMouseEvent>

CSlider::CSlider(QWidget *parent) : QWidget(parent)
{
    m_nTotal = 100;
    m_nStart = 0;
    m_nEnd = 90;
    m_nStep = 10;

    m_bSelected = false;
    m_bSelStart = false;
    m_bSelEnd = false;
    m_bMousePress = false;
    m_bOnlyEnd = true;
    m_bPercent = false;

    SetRange(0, 100);
    setMouseTracking(true);
}

void CSlider::SetRange(int nMin, int nMax)
{
    m_nMin = nMin;
    m_nMax = nMax;

    m_nTotal = m_nMax - m_nMin;
}

void CSlider::SetPos(int nStart, int nEnd)
{
    m_nStart = nStart;
    m_nEnd = nEnd;
}

void CSlider::SetStep(int nStep)
{
    m_nStep = nStep;
}

void CSlider::SetCurPos(int nPos)
{
    m_nStart = 0;
    m_nEnd = nPos;
}

void CSlider::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QColor colorBg = QColor("#F5F5F5");
    QColor colorSel = QColor("#91D5FF");
    QColor colorEllipse = QColor("#FFFFFF");
    QColor colorToolTip = QColor(0, 0, 0, 180);

    if (m_bSelected)
        colorBg = QColor("#E1E1E1");

    if (m_bSelected)
        colorSel = QColor("#69C0FF");

    QFont ft = painter.font();
    QRect rcClient = rect();

    QPoint ptCenter = rcClient.center();
    painter.setPen(Qt::NoPen);
    painter.setBrush(colorBg);
    painter.drawRoundedRect(m_rcBg, 5, 5);

    TItemRect itemStart = GetStartValue();
    TItemRect itemEnd = GetEndValue();

    QRect rcSel(m_rcBg);
    rcSel.setLeft(itemStart.rcArar.center().x());
    rcSel.setRight(itemEnd.rcArar.center().x());
    painter.setBrush(QColor(colorSel));
    painter.drawRect(rcSel);

    if (m_bOnlyEnd)
    {
        QRect rcAllSel(m_rcBg);
        rcAllSel.setRight(rcSel.right());
        painter.drawRoundedRect(rcAllSel, 5, 5);
    }

    if (m_bSelStart)
    {
        painter.save();
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(145, 213, 255, 150));
        painter.drawEllipse(itemStart.rcArar.marginsAdded(QMargins(8, 8, 8, 8)));
        painter.restore();
    }

    if (m_bSelEnd)
    {
        painter.save();
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(145, 213, 255, 150));
        painter.drawEllipse(itemEnd.rcArar.marginsAdded(QMargins(8, 8, 8, 8)));
        painter.restore();
    }

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(colorSel));

    if (!m_bOnlyEnd)
        painter.drawEllipse(itemStart.rcArar.marginsAdded(QMargins(4, 4, 4, 4)));

    painter.drawEllipse(itemEnd.rcArar.marginsAdded(QMargins(4, 4, 4, 4)));
    painter.restore();


    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(colorEllipse));

    if (!m_bOnlyEnd)
        painter.drawEllipse(itemStart.rcArar.marginsAdded(QMargins(2, 2, 2, 2)));

    painter.drawEllipse(itemEnd.rcArar.marginsAdded(QMargins(2, 2, 2, 2)));
    painter.restore();

    if (m_bSelStart)
    {
        QRectF rcTooltip(itemStart.rcArar);
        rcTooltip = rcTooltip.marginsAdded(QMargins(14, 14, 14, 14));
        rcTooltip.setBottom(itemStart.rcArar.top() - 10);
        rcTooltip.setTop(rcTooltip.bottom() - rcTooltip.width());

        painter.save();
        painter.setPen(Qt::NoPen);
        painter.setBrush(colorToolTip);
        painter.drawRoundedRect(rcTooltip, 5, 5);

        QPointF ptCenter(rcTooltip.left() + rcTooltip.width() / 2, rcTooltip.bottom());
        QPolygon trianglePolygon;
        trianglePolygon << QPoint(ptCenter.x() - 5, ptCenter.y());
        trianglePolygon << QPoint(ptCenter.x() + 5, ptCenter.y());
        trianglePolygon << QPoint(ptCenter.x(), ptCenter.y() + 5);
        painter.drawPolygon(trianglePolygon);

        painter.setPen(QColor("#FFFFFF"));

        if (m_bPercent)
            painter.drawText(rcTooltip, Qt::AlignCenter, QString("%1%").arg(itemStart.m_nValue));
        else
            painter.drawText(rcTooltip, Qt::AlignCenter, QString("%1").arg(itemStart.m_nValue));

        painter.restore();
    }

    if (m_bSelEnd)
    {
        QRectF rcTooltip(itemEnd.rcArar);
        rcTooltip = rcTooltip.marginsAdded(QMargins(14, 14, 14, 14));
        rcTooltip.setBottom(itemStart.rcArar.top() - 10);
        rcTooltip.setTop(rcTooltip.bottom() - rcTooltip.width());

        painter.save();
        painter.setPen(Qt::NoPen);
        painter.setBrush(colorToolTip);
        painter.drawRoundedRect(rcTooltip, 5, 5);

        QPointF ptCenter(rcTooltip.left() + rcTooltip.width() / 2, rcTooltip.bottom());
        QPolygon trianglePolygon;
        trianglePolygon << QPoint(ptCenter.x() - 5, ptCenter.y());
        trianglePolygon << QPoint(ptCenter.x() + 5, ptCenter.y());
        trianglePolygon << QPoint(ptCenter.x(), ptCenter.y() + 5);
        painter.drawPolygon(trianglePolygon);

        painter.setPen(QColor("#FFFFFF"));

        if (m_bPercent)
            painter.drawText(rcTooltip, Qt::AlignCenter, QString("%1%").arg(itemEnd.m_nValue));
        else
            painter.drawText(rcTooltip, Qt::AlignCenter, QString("%1").arg(itemEnd.m_nValue));

        painter.restore();
    }
}

void CSlider::resizeEvent(QResizeEvent *event)
{
    UpdateItemList();
}

void CSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bMousePress)
    {
        if (m_bSelStart)
            UpdateStartValue(event->pos());

        if (m_bSelEnd)
            UpdateEndValue(event->pos());
    }
    else
    {
        m_bSelected = false;
        m_bSelStart = false;
        m_bSelEnd = false;

        TItemRect itemStart;
        TItemRect itemEnd;

        GetStartAndEndValue(itemStart, itemEnd);

        if (m_rcBg.contains(event->pos()))
            m_bSelected = true;
        else
            m_bSelected = false;

        if (!m_bOnlyEnd && itemStart.rcArar.marginsAdded(QMargins(4, 4, 4, 4)).contains(event->pos()))
        {
            m_bSelStart = true;
            m_bSelected = true;
            setCursor(Qt::PointingHandCursor); // 设置鼠标样式
        }
        else if (itemEnd.rcArar.marginsAdded(QMargins(4, 4, 4, 4)).contains(event->pos()))
        {
            m_bSelEnd = true;
            m_bSelected = true;
            setCursor(Qt::PointingHandCursor); // 设置鼠标样式
        }
        else
        {
            setCursor(Qt::ArrowCursor);     // 设置鼠标样式
        }
    }

    update();
}

void CSlider::mousePressEvent(QMouseEvent *event)
{
    m_bMousePress = true;

    if (m_rcBg.contains(event->pos()))
    {
        if (m_bOnlyEnd)
        {
            UpdateEndValue(event->pos());
        }
        else
        {
            TItemRect itemStart = GetStartValue();
            TItemRect itemEnd = GetEndValue();

            if (event->pos().x() < itemStart.rcArar.left())
                UpdateStartValue(event->pos());
            else if (event->pos().x() > itemEnd.rcArar.right())
                UpdateEndValue(event->pos());
            else
            {
                if (qAbs(itemStart.rcArar.right() - event->pos().x()) < qAbs(itemEnd.rcArar.left() - event->pos().x()))
                    UpdateStartValue(event->pos());
                else
                    UpdateEndValue(event->pos());
            }
        }

        update();
    }
}

void CSlider::mouseReleaseEvent(QMouseEvent *event)
{
    m_bMousePress = false;
}

void CSlider::UpdateItemList()
{
    m_listItems.clear();

    QRect rcClient = rect();
    const int nHeight = 2;

    QPoint ptCenter = rcClient.center();
    m_rcBg = rcClient;
    m_rcBg.setTop(ptCenter.y() - nHeight);
    m_rcBg.setBottom(ptCenter.y() + nHeight);
    m_rcBg.setLeft(m_rcBg.left() + 20);
    m_rcBg.setRight(m_rcBg.right() - 20);

    double nStepW = (double)m_rcBg.width() / (m_nTotal / m_nStep);
    int nItemW = m_rcBg.height();

    int nStep = 0;
    for (int i = m_nMin; i <= m_nTotal; i+=m_nStep)
    {
        QRectF rcItem(m_rcBg);
        rcItem.setLeft(m_rcBg.left() + nStep * (nStepW));
        rcItem.setRight(rcItem.left() + nItemW);

        TItemRect item;
        item.rcArar = rcItem;
        item.m_nValue = i;

        m_listItems << item;
        nStep++;
    }
}

CSlider::TItemRect CSlider::GetStartValue()
{
    foreach (TItemRect item, m_listItems)
    {
        if (item.m_nValue == m_nStart)
            return item;
    }

    return CSlider::TItemRect();
}

CSlider::TItemRect CSlider::GetEndValue()
{
    foreach (TItemRect item, m_listItems)
    {
        if (item.m_nValue == m_nEnd)
            return item;
    }

    return CSlider::TItemRect();
}

bool CSlider::GetStartAndEndValue(CSlider::TItemRect &itemStart, CSlider::TItemRect &itemEnd)
{
    foreach (TItemRect item, m_listItems)
    {
        if (item.m_nValue == m_nStart)
            itemStart = item;

        if (item.m_nValue == m_nEnd)
        {
            itemEnd = item;
            return true;
        }
    }

    return false;
}

void CSlider::UpdateStartValue(QPoint ptPos)
{
    double nStepW = (double)m_rcBg.width() / (m_nTotal / m_nStep);
    nStepW /= 2;

    if (ptPos.x() <= m_rcBg.left())
        m_nStart = m_nMin;
    else if (ptPos.x() >= m_rcBg.right())
        m_nStart = m_nEnd;
    else
    {
        foreach (TItemRect item, m_listItems)
        {
            if (qAbs(item.rcArar.center().x() - ptPos.x()) < nStepW)
            {
                if (item.m_nValue <= m_nEnd)
                    m_nStart = item.m_nValue;

                break;
            }
        }
    }

    emit SignalValueChange(m_nStart, m_nEnd);
}

void CSlider::UpdateEndValue(QPoint ptPos)
{
    double nStepW = (double)m_rcBg.width() / (m_nTotal / m_nStep);
    nStepW /= 2;

    if (ptPos.x() <= m_rcBg.left())
        m_nEnd = m_nStart;
    else if (ptPos.x() >= m_rcBg.right())
        m_nEnd = m_nMax;
    else
    {
        foreach (TItemRect item, m_listItems)
        {
            if (qAbs(item.rcArar.center().x() - ptPos.x()) < nStepW)
            {
                if (item.m_nValue >= m_nStart)
                    m_nEnd = item.m_nValue;

                break;
            }
        }
    }

    if (m_bOnlyEnd)
        emit SignalValueChange(m_nEnd);
    else
        emit SignalValueChange(m_nStart, m_nEnd);
}
