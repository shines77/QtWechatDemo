#include "PopConfirm.h"

#include <QVariant>
#include <QDebug>
#include <QPainter>
#include <QEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Public.h"
#include "PushButtonEx.h"
#include "IconHelper.h"

#ifdef WIN32
#include <Windows.h>
#pragma comment(lib, "User32.lib")
#endif

CPopConfirm::CPopConfirm(QWidget *parent) : QWidget(parent)
{
    m_eAlignment = AlignTop;

    m_labelIcon = NULL;
    m_labelTitle = NULL;
    m_btnYes = NULL;
    m_btnNo = NULL;

    setAttribute(Qt::WA_StyledBackground);              // 禁止父窗口样式影响子控件样式
    setProperty("form", "BaseDlg");
    setAttribute(Qt::WA_TranslucentBackground, true);

    CreateAllCtrls();
    InitCtrls();
    Relayout();

    connect(m_btnYes, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_btnNo, SIGNAL(clicked()), this, SLOT(close()));
}

void CPopConfirm::Show(CPopConfirm::EAlignment eAlignment)
{
    show();

    QPoint point;
    QPoint ptParent = parentWidget()->mapToGlobal(QPoint(0, 0));

    m_eAlignment = eAlignment;
    switch (m_eAlignment)
    {
        case AlignTop:
        {
            QPoint pointTp(ptParent.x() + parentWidget()->width() / 2, ptParent.y());
            point.setX(pointTp.x() - width() / 2);
            point.setY(pointTp.y() - height());
        }
        break;

        case AlignLeft:
        {
            QPoint pointTp(ptParent.x(), ptParent.y() + parentWidget()->height() / 2);
            point.setX(pointTp.x() - width());
            point.setY(pointTp.y() - height() / 2);
        }
        break;

        case AlignRight:
        {
            QPoint pointTp(ptParent.x() + parentWidget()->width(), ptParent.y() + parentWidget()->height() / 2);
            point.setX(pointTp.x());
            point.setY(pointTp.y() - height() / 2);
        }
        break;

        case AlignBottom:
        {
            QPoint pointTp(ptParent.x() + parentWidget()->width() / 2, ptParent.y() + parentWidget()->height());
            point.setX(pointTp.x() - width() / 2);
            point.setY(pointTp.y());
        }
        break;

        case AlignTopLeft:
        {
            point.setX(ptParent.x());
            point.setY(ptParent.y() - height());
        }
        break;

        case AlignTopRight:
        {
            point.setX(ptParent.x() +  parentWidget()->width() - width());
            point.setY(ptParent.y() - height());
        }
        break;

        case AlignLeftTop:
        {
            point.setX(ptParent.x() - width());
            point.setY(ptParent.y());
        }
        break;

        case AlignRightTop:
        {
            point.setX(ptParent.x() +  parentWidget()->width());
            point.setY(ptParent.y());
        }
        break;

        case AlignLeftBottom:
        {
            point.setX(ptParent.x() - width());
            point.setY(ptParent.y());
        }
        break;

        case AlignRightBottom:
        {
            point.setX(ptParent.x() + parentWidget()->width());
            point.setY(ptParent.y());
        }
        break;

        case AlignBottomLeft:
        {
            point.setX(ptParent.x());
            point.setY(ptParent.y() + parentWidget()->height());
        }
        break;

        case AlignBottomRight:
        {
            point.setX(ptParent.x() + parentWidget()->width() - width());
            point.setY(ptParent.y() + parentWidget()->height());
        }
        break;
    }

    QRect rcStart, rcEnd;
    rcStart = QRect(point.x() - 50, point.y(), width(), height());
    rcEnd = QRect(point.x(), point.y(), width(), height());

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(rcStart);
    animation->setEndValue(rcEnd);
    animation->start();
}

void CPopConfirm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);         // 创建画家对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QFont ft = painter.font();
    QRect rcClient = rect();

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width() - 20, this->height() - 20);

    painter.fillPath(path, QBrush(Qt::white));

    QColor color(92, 93, 95, 50);
    int arr[10] = { 150, 120, 80, 50, 40, 30, 20, 10, 5, 5};
    for (int i = 0; i < 10; i++)
    {
         QPainterPath path;
         path.setFillRule(Qt::WindingFill);
         if(i == 5)
             path.addRect(10-i-1, 10-i-1, this->width()-(10-i)*2, this->height()-(10-i)*2);
         else
            path.addRoundedRect(10-i-1, 10-i-1, this->width()-(10-i)*2, this->height()-(10-i)*2,2,2);

         color.setAlpha(arr[i]);
         painter.setPen(color);
         painter.drawPath(path);
    }

    QRect rcText = rcClient;
    const int nLength = 5;
    const int nMargin = 10;
    QPolygon trianglePolygon;

    switch (m_eAlignment)
    {
        case AlignTop:
        {
            rcText = rcText.marginsRemoved(QMargins(5, 5, 5, 10));
            trianglePolygon << QPoint(rcText.left() + rcText.width() / 2 - nLength, rcText.bottom());
            trianglePolygon << QPoint(rcText.left() + rcText.width() / 2 + nLength, rcText.bottom());
            trianglePolygon << QPoint(rcText.left() + rcText.width() / 2, rcText.bottom() + nLength);
        }
        break;

        case AlignLeft:
        {
            rcText = rcText.marginsRemoved(QMargins(5, 5, 10, 5));
            trianglePolygon << QPoint(rcText.right(), rcText.top() + rcText.height() / 2 - nLength);
            trianglePolygon << QPoint(rcText.right(), rcText.top() + rcText.height() / 2 + nLength);
            trianglePolygon << QPoint(rcText.right() + 5, rcText.top() + rcText.height() / 2);
        }
        break;

        case AlignRight:
        {
            rcText = rcText.marginsRemoved(QMargins(10, 5, 5, 5));
            trianglePolygon << QPoint(rcText.left(), rcText.top() + rcText.height() / 2 - nLength);
            trianglePolygon << QPoint(rcText.left(), rcText.top() + rcText.height() / 2 + nLength);
            trianglePolygon << QPoint(rcText.left() - 5, rcText.top() + rcText.height() / 2);
        }
        break;

        case AlignBottom:
        {
            rcText = rcText.marginsRemoved(QMargins(5, 10, 5, 5));
            trianglePolygon << QPoint(rcText.left() + rcText.width() / 2 - nLength, rcText.top());
            trianglePolygon << QPoint(rcText.left() + rcText.width() / 2 + nLength, rcText.top());
            trianglePolygon << QPoint(rcText.left() + rcText.width() / 2, rcText.top() - nLength);
        }
        break;

        case AlignTopLeft:
        {
            rcText = rcText.marginsRemoved(QMargins(5, 5, 5, 10));
            trianglePolygon << QPoint(rcText.left() + nMargin - nLength, rcText.bottom());
            trianglePolygon << QPoint(rcText.left() + nMargin + nLength, rcText.bottom());
            trianglePolygon << QPoint(rcText.left() + nMargin, rcText.bottom() + nLength);
        }
        break;

        case AlignTopRight:
        {
            rcText = rcText.marginsRemoved(QMargins(5, 5, 5, 10));
            trianglePolygon << QPoint(rcText.right() - nMargin - nLength, rcText.bottom());
            trianglePolygon << QPoint(rcText.right() - nMargin + nLength, rcText.bottom());
            trianglePolygon << QPoint(rcText.right() - nMargin, rcText.bottom() + nLength);
        }
        break;

        case AlignLeftTop:
        {
            rcText = rcText.marginsRemoved(QMargins(5, 5, 10, 5));
            trianglePolygon << QPoint(rcText.right(), rcText.top() + nMargin - nLength);
            trianglePolygon << QPoint(rcText.right(), rcText.top() + nMargin + nLength);
            trianglePolygon << QPoint(rcText.right() + 5, rcText.top() + nMargin);
        }
        break;

        case AlignRightTop:
        {
            rcText = rcText.marginsRemoved(QMargins(10, 5, 5, 5));
            trianglePolygon << QPoint(rcText.left(), rcText.top() + nMargin - nLength);
            trianglePolygon << QPoint(rcText.left(), rcText.top() + nMargin + nLength);
            trianglePolygon << QPoint(rcText.left() - 5, rcText.top() + nMargin);
        }
        break;

        case AlignLeftBottom:
        {
            rcText = rcText.marginsRemoved(QMargins(5, 5, 10, 5));
            trianglePolygon << QPoint(rcText.right(), rcText.top() + nMargin - nLength);
            trianglePolygon << QPoint(rcText.right(), rcText.top() + nMargin + nLength);
            trianglePolygon << QPoint(rcText.right() + 5, rcText.top() + nMargin);
        }
        break;

        case AlignRightBottom:
        {
            rcText = rcText.marginsRemoved(QMargins(10, 5, 5, 5));
            trianglePolygon << QPoint(rcText.left(), rcText.top() + nMargin - nLength);
            trianglePolygon << QPoint(rcText.left(), rcText.top() + nMargin + nLength);
            trianglePolygon << QPoint(rcText.left() - 5, rcText.top() + nMargin);
        }
        break;

        case AlignBottomLeft:
        {
            rcText = rcText.marginsRemoved(QMargins(5, 10, 5, 5));
            trianglePolygon << QPoint(rcText.left() + nMargin - nLength, rcText.top());
            trianglePolygon << QPoint(rcText.left() + nMargin + nLength, rcText.top());
            trianglePolygon << QPoint(rcText.left() + nMargin, rcText.top() - nLength);
        }
        break;

        case AlignBottomRight:
        {
            rcText = rcText.marginsRemoved(QMargins(5, 10, 5, 5));
            trianglePolygon << QPoint(rcText.right() - nMargin - nLength, rcText.top());
            trianglePolygon << QPoint(rcText.right() - nMargin + nLength, rcText.top());
            trianglePolygon << QPoint(rcText.right() - nMargin, rcText.top() - nLength);
        }
        break;
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#ffffff"));
    painter.drawRoundedRect(rcText, 5, 5);
    painter.drawPolygon(trianglePolygon);
}

bool CPopConfirm::event(QEvent *event)
{
#ifdef WIN32
    // class_ameneded 不能是custommenu的成员, 因为winidchange事件触发时, 类成员尚未初始化
    static bool class_amended = false;
    if (event->type() == QEvent::WinIdChange)
    {
        HWND hwnd = reinterpret_cast<HWND>(winId());
        if (class_amended == false)
        {
            class_amended = true;
            DWORD class_style = ::GetClassLong(hwnd, GCL_STYLE);
            class_style &= ~CS_DROPSHADOW;
            ::SetClassLong(hwnd, GCL_STYLE, class_style); // windows系统函数
        }
    }
#endif

    return QWidget::event(event);
}

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

void CPopConfirm::CreateAllCtrls()
{
    NEW_OBJECT(m_labelIcon, QLabel);
    NEW_OBJECT(m_labelTitle, QLabel);

    NEW_OBJECT(m_btnYes, QPushButton);
    NEW_OBJECT(m_btnNo, QPushButton);
}

void CPopConfirm::InitCtrls()
{
    setFixedSize(300, 120);
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    QString text(QChar(0xe67e));
    IconHelper::SetIcon(m_labelIcon, text);
    m_labelIcon->setFixedSize(30, 30);
    m_labelIcon->setStyleSheet("color:#FAAD14");
    m_btnYes->setFixedSize(40, 25);
    m_btnNo->setFixedSize(40, 25);
    m_btnNo->setObjectName("m_btnNo");

    m_labelTitle->setText("Are you sure to delete this task?");
    m_btnYes->setText("Yes");
    m_btnNo->setText("No");
}

void CPopConfirm::Relayout()
{
    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->addWidget(m_labelIcon);
    layoutTop->addWidget(m_labelTitle);
    layoutTop->setSpacing(8);
    layoutTop->setMargin(0);

    QHBoxLayout *layoutBottom = new QHBoxLayout();
    layoutBottom->addStretch();
    layoutBottom->addWidget(m_btnNo);
    layoutBottom->addWidget(m_btnYes);
    layoutBottom->setSpacing(6);
    layoutBottom->setMargin(0);

    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addLayout(layoutTop);
    layoutMain->addLayout(layoutBottom);
    layoutMain->setSpacing(6);
    layoutMain->setMargin(18);

    setLayout(layoutMain);
}
