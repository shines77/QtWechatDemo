#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H

#include <QWidget>

class QPaintEvent;
class QPainter;
class QLabel;
class QMovie;

class ChatMessage : public QWidget
{
    Q_OBJECT
public:
    explicit ChatMessage(QWidget *parent = nullptr);
    ~ChatMessage();

    enum MsgType {
        Msg_System,     // 系统
        Msg_Me,         // 自己
        Msg_Other,      // 别人
        Msg_Time,       // 时间
    };

    void setTextSuccess();
    void setText(const QString & text, const QString & time, QSize allSize, MsgType msgType);

    QSize calcFrameRect(const QString &text, MsgType msgType);
    QSize calcRealFrameRect(QString text, MsgType msgType);

    inline MsgType msgType() { return m_msgType; }
    inline QString text() { return m_text; }
    inline QString time() { return m_time; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    MsgType m_msgType;
    QString m_text;
    QString m_time;
    QString m_curTime;

    QSize m_allSize;

    int m_frameWidth;
    int m_textWidth;
    int m_spaceWid;
    int m_lineHeight;

    QRect m_iconLeftRect;
    QRect m_iconRightRect;
    QRect m_angleLeftRect;
    QRect m_angleRightRect;
    QRect m_frameLeftRect;
    QRect m_frameRightRect;
    QRect m_textLeftRect;
    QRect m_textRightRect;

    QPixmap m_leftPixmap;
    QPixmap m_rightPixmap;

    QLabel *m_loading;
    QMovie *m_loadingMovie;

    bool m_isSending = false;
};

#endif // CHAT_MESSAGE_H
