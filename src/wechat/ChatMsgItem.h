#ifndef CHAT_MSG_ITEM_H
#define CHAT_MSG_ITEM_H

#include <QWidget>

class QPaintEvent;
class QPainter;
class QLabel;
class QMovie;

class ChatMsgItem : public QWidget
{
    Q_OBJECT
public:
    explicit ChatMsgItem(QWidget *parent = nullptr);
    ~ChatMsgItem();

    enum MsgType {
        Msg_System,     // 系统
        Msg_Me,         // 自己
        Msg_Other,      // 别人
        Msg_Time,       // 时间
    };

    void setTextSuccess();
    void setText(const QString & text, const QString & time, QSize allSize, MsgType type);

    QSize calcFrameRect(const QString &text, MsgType type);
    QSize calcRealFrameRect(QString text, MsgType type);

    inline MsgType type() { return m_type; }
    inline QString text() { return m_text; }
    inline QString time() { return m_time; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    MsgType m_type;
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

    bool m_isSending;
};

#endif // CHAT_MSG_ITEM_H
