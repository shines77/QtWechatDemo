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
    void setText(MsgType type, uint time, const QString &text);

    QSize calcFrameRect(const QString &text, MsgType type);
    QSize calcRealFrameRect(QString text, MsgType type);

    inline MsgType type() { return m_type; }
    inline uint    time() { return m_time; }
    inline QString text() { return m_text; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    MsgType m_type;
    uint    m_time;
    QString m_text;

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
