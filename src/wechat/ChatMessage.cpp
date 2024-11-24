#include "ChatMessage.h"

#include <QFontMetrics>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <QDebug>

ChatMessage::ChatMessage(QWidget *parent) : QWidget(parent)
{
    m_msgType = Msg_System;

    m_loading = Q_NULLPTR;
    m_loadingMovie = Q_NULLPTR;

    m_isSending = false;

    QFont font = this->font();
    font.setFamily("MicrosoftYaHei");
    font.setPointSize(12);
    /*
    font.setWordSpacing(0);
    font.setLetterSpacing(QFont::PercentageSpacing,0);
    font.setLetterSpacing(QFont::PercentageSpacing, 100);         // 300%, 100为默认  // 设置字间距%
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);             // 设置字间距为3像素  // 设置字间距像素值
    //*/
    this->setFont(font);

    m_leftPixmap = QPixmap(":/avatar/avatar/unknown.png");
    m_rightPixmap = QPixmap(":/avatar/avatar/man-cs.png");

    m_loadingMovie = new QMovie(this);
    m_loadingMovie->setFileName(":/icons/icon/send-loading.gif");

    m_loading = new QLabel(this);
    m_loading->setMovie(m_loadingMovie);
    m_loading->resize(16, 16);
    m_loading->setAttribute(Qt::WA_TranslucentBackground, true);
    m_loading->setAutoFillBackground(false);
}

ChatMessage::~ChatMessage()
{
    //
}

void ChatMessage::setTextSuccess()
{
    m_loading->hide();
    m_loadingMovie->stop();
    m_isSending = true;
}

void ChatMessage::setText(const QString &text, const QString &time, QSize allSize, ChatMessage::MsgType msgType)
{
    m_text = text;
    m_msgType = msgType;
    m_time = time;
    m_curTime = QDateTime::fromTime_t(time.toInt()).toString("hh:mm");
    m_allSize = allSize;
    if (msgType == Msg_Me) {
        if (!m_isSending) {
            m_loading->move(m_frameRightRect.x() - m_loading->width() - 10, m_frameRightRect.y() +
                            m_frameRightRect.height() / 2 - m_loading->height() / 2);
            m_loading->show();
            m_loadingMovie->start();
        }
    }
    else {
        m_loading->hide();
    }

    this->update();
}

QSize ChatMessage::calcFrameRect(const QString &text, MsgType msgType)
{
    static const int kMinFrameHeight = 30;
    static const int frameSpacingX = 20;

    static const int iconWidth = 40;
    static const int iconHeight = 40;
    static const int iconMarginX = 5;
    static const int iconMarginTop = 10;
    static const int iconSpacingX = 20;
    static const int kAngleWidth = 6;

    static const int kTextSpacingX = 12;

    m_text = text;

    m_frameWidth = this->width() - frameSpacingX - 2 * (iconWidth + iconSpacingX + iconMarginX);
    m_textWidth = m_frameWidth - kTextSpacingX * 2;
    m_spaceWid = this->width() - m_textWidth;
    m_iconLeftRect = QRect(iconSpacingX, iconMarginTop, iconWidth, iconHeight);
    m_iconRightRect = QRect(this->width() - iconSpacingX - iconWidth, iconMarginTop, iconWidth, iconHeight);

    QSize size = calcRealFrameRect(m_text, msgType);     // 整个的size
    qDebug() << "fontRect Size:" << size;

    int nFrameHeight = (size.height() < kMinFrameHeight) ? kMinFrameHeight : size.height();

    m_angleLeftRect = QRect(iconWidth + iconSpacingX + iconMarginX, m_lineHeight / 2,
                            kAngleWidth, nFrameHeight - m_lineHeight);
    m_angleRightRect = QRect(this->width() - iconMarginX - iconWidth - iconSpacingX - kAngleWidth,
                             m_lineHeight / 2, kAngleWidth, nFrameHeight - m_lineHeight);

    if (size.width() < (m_textWidth + m_spaceWid)) {
        m_frameLeftRect.setRect(m_angleLeftRect.x() + m_angleLeftRect.width(), m_lineHeight / 4 * 3,
                                size.width() - m_spaceWid + 2 * kTextSpacingX, nFrameHeight - m_lineHeight);
        m_frameRightRect.setRect(this->width() - size.width() + m_spaceWid - 2 * kTextSpacingX -
                                 iconWidth - iconSpacingX - iconMarginX - kAngleWidth,
                                 m_lineHeight / 4 * 3, size.width() - m_spaceWid + 2 * kTextSpacingX,
                                 nFrameHeight - m_lineHeight);
    }
    else {
        m_frameLeftRect.setRect(m_angleLeftRect.x() + m_angleLeftRect.width(),
                                m_lineHeight / 4 * 3, m_frameWidth, nFrameHeight - m_lineHeight);
        m_frameRightRect.setRect(iconWidth + frameSpacingX + iconSpacingX + iconMarginX - kAngleWidth,
                                 m_lineHeight / 4 * 3, m_frameWidth, nFrameHeight - m_lineHeight);
    }
    m_textLeftRect.setRect(m_frameLeftRect.x() + kTextSpacingX, m_frameLeftRect.y() + iconMarginTop,
                           m_frameLeftRect.width() - 2 * kTextSpacingX, m_frameLeftRect.height() - 2 * iconMarginTop);
    m_textRightRect.setRect(m_frameRightRect.x() + kTextSpacingX, m_frameRightRect.y() + iconMarginTop,
                            m_frameRightRect.width() - 2 * kTextSpacingX, m_frameRightRect.height() - 2 * iconMarginTop);

    return QSize(size.width(), nFrameHeight);
}

QSize ChatMessage::calcRealFrameRect(QString text, MsgType msgType)
{
    QFontMetricsF fm(this->font());
    m_lineHeight = fm.lineSpacing();
    int nCount = text.count("\n");
    int nMaxWidth = 0;
    if (nCount == 0) {
        nMaxWidth = fm.width(text);
        QString value = text;
        if (nMaxWidth > m_textWidth) {
            nMaxWidth = m_textWidth;
            int size = m_textWidth / fm.width(" ");
            int num = fm.width(value) / m_textWidth;
            int ttmp = num * fm.width(" ");
            num = fm.width(value) / m_textWidth;
            nCount += num;
            QString temp = "";
            for (int i = 0; i < num; i++) {
                temp += value.mid(i * size, (i + 1) * size) + "\n";
            }
            text.replace(value, temp);
        }
    }
    else {
        for (int i = 0; i < (nCount + 1); i++) {
            QString value = text.split("\n").at(i);
            nMaxWidth = (fm.width(value) > nMaxWidth) ? fm.width(value) : nMaxWidth;
            if (fm.width(value) > m_textWidth) {
                nMaxWidth = m_textWidth;
                int size = m_textWidth / fm.width(" ");
                int num = fm.width(value) / m_textWidth;
                num = ((i + num) * fm.width(" ") + fm.width(value)) / m_textWidth;
                nCount += num;
                QString temp = "";
                for (int i = 0; i < num; i++) {
                    temp += value.mid(i * size, (i + 1) * size) + "\n";
                }
                text.replace(value, temp);
            }
        }
    }
    return QSize(nMaxWidth + m_spaceWid, m_lineHeight * (nCount + 1) + m_lineHeight * 2);
}

void ChatMessage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); // 消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    if (m_msgType == MsgType::Msg_Other) { // 别人
        // 头像
        // painter.drawRoundedRect(m_iconLeftRect, m_iconLeftRect.width(), m_iconLeftRect.height());
        painter.drawPixmap(m_iconLeftRect, m_leftPixmap);

        // 框加边
        QColor clrFrameEdge(234, 234, 234);
        painter.setBrush(QBrush(clrFrameEdge));
        painter.drawRoundedRect(m_frameLeftRect.x() - 1, m_frameLeftRect.y() - 1,
                                m_frameLeftRect.width() + 2, m_frameLeftRect.height() + 2, 4, 4);
        // 框
        QColor clrFrameBorder(255, 255, 255);
        painter.setBrush(QBrush(clrFrameBorder));
        painter.drawRoundedRect(m_frameLeftRect, 4, 4);

        // 尖角
        QPointF points[3] = {
            QPointF(m_angleLeftRect.x(), 30),
            QPointF(m_angleLeftRect.x() + m_angleLeftRect.width(), 25),
            QPointF(m_angleLeftRect.x() + m_angleLeftRect.width(), 35),
        };

        QPen pen;
        pen.setColor(clrFrameBorder);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        // 三角加边
        QPen penAngleEdge;
        penAngleEdge.setColor(clrFrameEdge);
        painter.setPen(penAngleEdge);
        painter.drawLine(QPointF(m_angleLeftRect.x() - 1, 30), QPointF(m_angleLeftRect.x() + m_angleLeftRect.width(), 24));
        painter.drawLine(QPointF(m_angleLeftRect.x() - 1, 30), QPointF(m_angleLeftRect.x() + m_angleLeftRect.width(), 36));

        // 内容
        QPen penText;
        penText.setColor(QColor(51, 51, 51));
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textLeftRect, m_text, option);
    }
    else if (m_msgType == MsgType::Msg_Me) { // 自己
        // 头像
        // painter.drawRoundedRect(m_iconRightRect, m_iconRightRect.width(), m_iconRightRect.height());
        painter.drawPixmap(m_iconRightRect, m_rightPixmap);

        // 框
        QColor clrFrameBorder(75, 164, 242);
        painter.setBrush(QBrush(clrFrameBorder));
        painter.drawRoundedRect(m_frameRightRect, 4, 4);

        // 三角
        QPointF points[3] = {
            QPointF(m_angleRightRect.x() + m_angleRightRect.width(), 30),
            QPointF(m_angleRightRect.x(), 25),
            QPointF(m_angleRightRect.x(), 35),
        };

        QPen pen;
        pen.setColor(clrFrameBorder);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        // 内容
        QPen penText;
        penText.setColor(Qt::white);
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textRightRect, m_text, option);
    }
    else if (m_msgType == MsgType::Msg_Time) { // 时间
        QPen penText;
        penText.setColor(QColor(153, 153, 153));
        painter.setPen(penText);
        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        QFont font = this->font();
        font.setFamily("MicrosoftYaHei");
        font.setPointSize(10);
        painter.setFont(font);
        painter.drawText(this->rect(), m_curTime, option);
    }
    else if (m_msgType == MsgType::Msg_System) {
        //
    }
}
