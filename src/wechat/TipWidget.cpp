#include "TipWidget.h"

#include <QPropertyAnimation>

TTipWidget *TTipWidget::m_pTipWidget = NULL;

TTipWidget::TTipWidget()
    : m_pParent(nullptr)
    , m_bEnter(false)
    , m_nTransparent(200)
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAlignment(Qt::AlignCenter);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &TTipWidget::OnTimer);

    setVisible(false);
}

TTipWidget::~TTipWidget()
{
    deleteLater();

    if (m_pTimer != NULL) {
        delete m_pTimer;
        m_pTimer = NULL;
    }
}

void TTipWidget::enterEvent(QEvent *)
{
    m_bEnter = true;
    //setStyleSheet(QString("color:white;font:12px \"Microsoft YaHei\";border-radius:1px;background-color:rgba(24, 144, 255);"));
}

void TTipWidget::leaveEvent(QEvent *)
{
    m_bEnter = false;
}

void TTipWidget::OnTimer()
{
    if (m_bEnter)
        return;

    if (nullptr != m_pParent)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
        animation->setDuration(150);
        animation->setStartValue(QRect((m_pParent->width() - width()) >> 1, 40, width(), height()));
        animation->setEndValue(QRect((m_pParent->width() - width()) >> 1, -height(), width(), height()));
        animation->start();

        connect(animation, &QPropertyAnimation::finished, this, &TTipWidget::hide);
    }

    m_pTimer->stop();
}

void TTipWidget::SetMesseage(const QString &strMessage, const QPoint *pPoint)
{
    if (strMessage.isEmpty())
    {
        return;
    }

    QFontMetrics fm1(font());
    setFixedSize(fm1.width(strMessage) + 30, 30);

    m_pParent = parentWidget();

    if (nullptr != m_pParent && width() > m_pParent->width())
    {
        setFixedSize(m_pParent->width() - 60, 60);
        setWordWrap(true);
    }
    else
    {
        setWordWrap(false);
    }

    setText(strMessage);

    if (nullptr != m_pParent)
    {
        if (nullptr != pPoint)
        {
            move(m_pParent->mapFromGlobal(*pPoint));
            m_pParent = nullptr;
        }
        else
        {
            QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
            animation->setDuration(150);
            animation->setStartValue(QRect((m_pParent->width() - width()) >> 1, -height(), width(), height()));
            animation->setEndValue(QRect((m_pParent->width() - width()) >> 1, 40, width(), height()));
            animation->start();
        }
    }

    setStyleSheet(QString("color:white;font:12px \"Microsoft YaHei\";border-radius:2px;background-color:rgba(24, 144, 255);"));
    setVisible(true);

    m_pTimer->start(3 * 1000);
}

TTipWidget *TTipWidget::Instance()
{
    if (NULL == m_pTipWidget)
        m_pTipWidget = new TTipWidget();

    return m_pTipWidget;
}

void TTipWidget::ExitInstance()
{
    if (NULL != m_pTipWidget)
    {
        delete m_pTipWidget;
        m_pTipWidget = NULL;
    }
}
