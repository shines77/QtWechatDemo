#include "ChatMsgItem.h"

#include <QFontMetrics>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <QDebug>

ChatMsgItem::ChatMsgItem(QWidget *parent) : QWidget(parent)
{
    m_type = System;
    m_time = 0;

    m_frameMarginX = 0;
    m_frameWidth = 0;
    m_maxTextWidth = 0;
    m_lineHeight = 0;

    m_loading = Q_NULLPTR;
    m_loadingMovie = Q_NULLPTR;

    m_isSending = false;

    QFont font = this->font();
    font.setFamily(tr("宋体"));
    font.setPointSize(12);
    /*
    font.setWordSpacing(0);
    font.setLetterSpacing(QFont::PercentageSpacing,0);
    font.setLetterSpacing(QFont::PercentageSpacing, 100);         // 300%, 100为默认  // 设置字间距%
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);             // 设置字间距为3像素  // 设置字间距像素值
    //*/
    this->setFont(font);

    // m_leftPixmap = QPixmap(":/avatar/avatar/unknown.png");
    // m_rightPixmap = QPixmap(":/avatar/avatar/man-cs.png");
    m_iconPixmap = Q_NULLPTR;

    m_loadingMovie = new QMovie(this);
    m_loadingMovie->setFileName(":/icons/icon/send-loading.gif");

    m_loading = new QLabel(this);
    m_loading->setMovie(m_loadingMovie);
    m_loading->resize(16, 16);
    m_loading->setAttribute(Qt::WA_TranslucentBackground, true);
    m_loading->setAutoFillBackground(false);
}

ChatMsgItem::~ChatMsgItem()
{
    if (m_loadingMovie != Q_NULLPTR) {
        delete m_loadingMovie;
        m_loadingMovie = Q_NULLPTR;
    }

    if (m_loading != Q_NULLPTR) {
        delete m_loading;
        m_loading = Q_NULLPTR;
    }

    if (m_iconPixmap != Q_NULLPTR) {
        delete m_iconPixmap;
        m_iconPixmap = Q_NULLPTR;
    }
}

void ChatMsgItem::setTextSuccess()
{
    m_loading->hide();
    m_loadingMovie->stop();
    m_isSending = true;
}

void ChatMsgItem::setText(ChatMsgItem::MsgType type, uint time, const QString &text)
{
    m_type = type;
    m_time = time;
    m_text = text;

    if (type == MsgType::Me) {
        if (m_iconPixmap == Q_NULLPTR)
            m_iconPixmap = new QPixmap(":/avatar/avatar/man-cs.png");
    }
    else if (type == MsgType::Other) {
        if (m_iconPixmap == Q_NULLPTR)
            m_iconPixmap = new QPixmap(":/avatar/avatar/unknown.png");
    }

    if (type == MsgType::Me) {
        if (!m_isSending) {
            m_loading->move(m_frameRect.x() - m_loading->width() - 10, m_frameRect.y() +
                            m_frameRect.height() / 2 - m_loading->height() / 2);
            m_loading->show();
            m_loadingMovie->start();
        }
    }
    else {
        m_loading->hide();
    }

    this->update();
}

QSize ChatMsgItem::calcFrameRect(const QString &text, MsgType type)
{
    static const int kMinFrameHeight = 30;
    static const int kFrameSpacingX = 20;
    static const int kAngleWidth = 6;

    static const int kIconWidth = 40;
    static const int kIconHeight = 40;

    static const int kIconMarginX = 20;
    static const int kIconMarginY = 10;
    static const int kIconSpacingX = 5;

    static const int kTextPaddingX = 12;
    // kTextPaddingY = kIconMarginY
    static const int kTextPaddingY = 10;

    m_text = text;

    m_frameWidth = this->width() - kFrameSpacingX - (kIconWidth + kIconMarginX + kIconSpacingX) * 2;
    m_maxTextWidth = m_frameWidth - kTextPaddingX * 2;
    m_frameMarginX = this->width() - m_maxTextWidth;
    if (type == MsgType::Other)
        m_iconRect = QRect(kIconMarginX, kIconMarginY, kIconWidth, kIconHeight);
    else if (type == MsgType::Me)
        m_iconRect = QRect(this->width() - kIconMarginX - kIconWidth, kIconMarginY, kIconWidth, kIconHeight);
    else
        m_iconRect = QRect(0, 0, 0, 0);

    QSize realSize = calcRealFrameRect(m_text, type);     // 整个的 size
    qDebug() << "FrameRect Real Size:" << realSize;

    int nFrameHeight = (realSize.height() < kMinFrameHeight) ? kMinFrameHeight : realSize.height();

    if (type == MsgType::Other) {
        m_angleRect = QRect(kIconMarginX + kIconWidth + kIconSpacingX, m_lineHeight / 2,
                            kAngleWidth, nFrameHeight - m_lineHeight);
    }
    else if (type == MsgType::Me) {
        m_angleRect = QRect(this->width() - kIconSpacingX - kIconWidth - kIconMarginX - kAngleWidth,
                            m_lineHeight / 2, kAngleWidth, nFrameHeight - m_lineHeight);
    }
    else {
        m_angleRect = QRect(0, 0, 0, 0);
    }

    // this->width() = m_frameMarginX + m_maxTextWidth
    if (realSize.width() < this->width()) {
        if (type == MsgType::Other) {
            m_frameRect.setRect(m_angleRect.x() + m_angleRect.width(),
                                m_lineHeight / 4 * 3,
                                // realSize.width() - m_frameMarginX + kTextPaddingX * 2,
                                realSize.width() - (this->width() - m_frameWidth),
                                nFrameHeight - m_lineHeight);
        }
        else if (type == MsgType::Me) {
            m_frameRect.setRect(this->width() - (realSize.width() - m_frameMarginX) - kTextPaddingX * 2 -
                                (kIconMarginX + kIconWidth + kIconSpacingX + kAngleWidth),
                                m_lineHeight / 4 * 3,
                                // realSize.width() - m_frameMarginX + kTextPaddingX * 2,
                                realSize.width() - (this->width() - m_frameWidth),
                                nFrameHeight - m_lineHeight);
        }
        else {
            m_frameRect.setRect(0, 0, 0, 0);
        }
    }
    else {
        if (type == MsgType::Other) {
            m_frameRect.setRect(m_angleRect.x() + m_angleRect.width(),
                                m_lineHeight / 4 * 3, m_frameWidth, nFrameHeight - m_lineHeight);
        }
        else if (type == MsgType::Me) {
            m_frameRect.setRect(kFrameSpacingX + kIconMarginX + kIconWidth + kIconSpacingX - kAngleWidth,
                                m_lineHeight / 4 * 3, m_frameWidth, nFrameHeight - m_lineHeight);
        }
        else {
            m_frameRect.setRect(0, 0, 0, 0);
        }
    }

    if (type == MsgType::Other) {
        m_textRect.setRect(m_frameRect.x() + kTextPaddingX, m_frameRect.y() + kTextPaddingY,
                           m_frameRect.width() - kTextPaddingX * 2, m_frameRect.height() - kTextPaddingY * 2);
    }
    else if (type == MsgType::Me) {
        m_textRect.setRect(m_frameRect.x() + kTextPaddingX, m_frameRect.y() + kTextPaddingY,
                           m_frameRect.width() - kTextPaddingX * 2, m_frameRect.height() - kTextPaddingY * 2);
    }
    else {
        m_textRect.setRect(0, 0, 0, 0);
    }

    return QSize(realSize.width(), nFrameHeight);
}

QSize ChatMsgItem::calcRealFrameRect(QString text, MsgType type)
{
    Q_UNUSED(type);

    QFontMetricsF fm(this->font());
    // This value is always equal to leading() + height().
    m_lineHeight = fm.lineSpacing();
    int nCount = text.count("\n");
    int nMaxWidth = 0;
    if (nCount == 0) {
        nMaxWidth = fm.width(text);
        QString value = text;
        if (nMaxWidth > m_maxTextWidth) {
            nMaxWidth = m_maxTextWidth;
            int numWord = m_maxTextWidth / fm.width(" ");
            int numLine = fm.width(value) / m_maxTextWidth;
            nCount += numLine;
            QString wrapText = "";
            for (int i = 0; i < numLine; i++) {
                wrapText += value.mid(i * numWord, (i + 1) * numWord) + "\n";
            }
            text.replace(value, wrapText);
        }
    }
    else {
        for (int i = 0; i < (nCount + 1); i++) {
            QString value = text.split("\n").at(i);
            nMaxWidth = (fm.width(value) > nMaxWidth) ? fm.width(value) : nMaxWidth;
            if (fm.width(value) > m_maxTextWidth) {
                nMaxWidth = m_maxTextWidth;
                int numWord = m_maxTextWidth / fm.width(" ");
                int numLine = fm.width(value) / m_maxTextWidth;
                numLine = ((i + numLine) * fm.width(" ") + fm.width(value)) / m_maxTextWidth;
                nCount += numLine;
                QString wrapText = "";
                for (int i = 0; i < numLine; i++) {
                    wrapText += value.mid(i * numWord, (i + 1) * numWord) + "\n";
                }
                text.replace(value, wrapText);
            }
        }
    }
    return QSize(nMaxWidth + m_frameMarginX, m_lineHeight * (nCount + 1) + m_lineHeight * 2);
}

QString ChatMsgItem::FormatDateTime(uint time)
{
    return QDateTime::fromTime_t(time).toString("YY年MM月DD日 hh:mm");
}

void ChatMsgItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); // 消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    if (m_type == MsgType::Other) { // 别人
        // 头像
        // painter.drawRoundedRect(m_iconRect, m_iconRect.width(), m_iconRect.height());
        painter.drawPixmap(m_iconRect, *m_iconPixmap);

        // Frame边框
        QColor clrFrameBorder(234, 234, 234);
        painter.setBrush(QBrush(clrFrameBorder));
        painter.drawRoundedRect(m_frameRect.x() - 1, m_frameRect.y() - 1,
                                m_frameRect.width() + 2, m_frameRect.height() + 2, 4, 4);
        // Frame(背景)
        QColor clrFrameBG(255, 255, 255);
        painter.setBrush(QBrush(clrFrameBG));
        painter.drawRoundedRect(m_frameRect, 4, 4);

        // 尖角
        QPointF anglePoints[3] = {
            QPointF(m_angleRect.x(), 30),
            QPointF(m_angleRect.x() + m_angleRect.width(), 25),
            QPointF(m_angleRect.x() + m_angleRect.width(), 35),
        };

        QPen penAngle;
        penAngle.setColor(clrFrameBG);
        painter.setPen(penAngle);
        painter.drawPolygon(anglePoints, 3);

        // 尖角加边
        QPen penAngleEdge;
        penAngleEdge.setColor(clrFrameBorder);
        painter.setPen(penAngleEdge);
        painter.drawLine(QPointF(m_angleRect.x() - 1, 30), QPointF(m_angleRect.x() + m_angleRect.width(), 24));
        painter.drawLine(QPointF(m_angleRect.x() - 1, 30), QPointF(m_angleRect.x() + m_angleRect.width(), 36));

        // 内容
        QPen penText;
        penText.setColor(QColor(51, 51, 51));
        painter.setPen(penText);

        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textRect, m_text, option);
    }
    else if (m_type == MsgType::Me) { // 自己
        // 头像
        // painter.drawRoundedRect(m_iconRect, m_iconRect.width(), m_iconRect.height());
        painter.drawPixmap(m_iconRect, *m_iconPixmap);

        // Frame边框和背景
        QColor clrFrameBG(75, 164, 242);
        painter.setBrush(QBrush(clrFrameBG));
        painter.drawRoundedRect(m_frameRect, 4, 4);

        // 尖角
        QPointF anglePoints[3] = {
            QPointF(m_angleRect.x() + m_angleRect.width(), 30),
            QPointF(m_angleRect.x(), 25),
            QPointF(m_angleRect.x(), 35),
        };

        QPen penAngle;
        penAngle.setColor(clrFrameBG);
        painter.setPen(penAngle);
        painter.drawPolygon(anglePoints, 3);

        // 内容
        QPen penText;
        penText.setColor(Qt::white);
        painter.setPen(penText);

        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textRect, m_text, option);
    }
    else if (m_type == MsgType::Time) { // 时间
        QPen penText;
        penText.setColor(QColor(153, 153, 153));
        painter.setPen(penText);

        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

        // Format timestamp of message
        QString strTime = FormatDateTime(m_time);

        QFont font = this->font();
        font.setFamily(tr("宋体"));
        font.setPointSize(12);
        painter.setFont(font);
        painter.drawText(this->rect(), strTime, option);
    }
    else if (m_type == MsgType::System) {
        //
    }
}
