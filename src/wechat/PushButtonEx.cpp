#include "PushButtonEx.h"

#include <QMouseEvent>
#include <QPainter>

CPushButtonEx::CPushButtonEx(QWidget *parent) : QPushButton(parent)
{
    m_varData = 0;
    m_bExArea = false;
    m_fRadio = 0.0;
    m_bRadio = false;

    setCursor(Qt::PointingHandCursor); // 设置鼠标样式
}

CPushButtonEx::~CPushButtonEx()
{
    //
}

void CPushButtonEx::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_bExArea) {
        return QPushButton::mouseReleaseEvent(event);
    }

    QRect rcEx = rect();
    rcEx.setTopLeft(QPoint(rcEx.bottom() / 4 * 3, rcEx.right() / 4 * 3));

    if (!rcEx.contains(event->pos()))
        emit SignalClicked();
    else
        emit SignalClickedExArea();

    return QPushButton::mouseReleaseEvent(event);
}

void CPushButtonEx::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    if (m_bRadio)
    {
        setFixedHeight(width() / m_fRadio);

        this->setStyleSheet(QString("QPushButton{font: bold %1px;} QPushButton:hover{font: bold %2px;} QPushButton:pressed{font: bold %3px;}")
                           .arg(this->height() / 2).arg(this->height() / 2 + 6).arg(this->height() / 2 + 2));
    }
}
