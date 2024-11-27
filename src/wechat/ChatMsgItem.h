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
        System,     // 系统
        Me,         // 自己
        Other,      // 别人
        Time,       // 时间
    };

    static QString FormatDateTime(uint time);

    void setTextSuccess();
    void setText(MsgType type, uint time, const QString &text);

    QSize calcFrameRect(const QString &text, MsgType type);
    QSize calcRealFrameRect(QString text, MsgType type);

    inline MsgType type() { return m_type; }
    inline uint    time() { return m_time; }
    inline QString text() { return m_text; }

protected:
    void paintEvent(QPaintEvent *event);

    void CreateAllCtrls();
    void InitCtrls();
    void Relayout();

private:
    MsgType m_type;
    uint    m_time;
    QString m_text;

    int m_frameMarginX;
    int m_frameWidth;
    int m_maxTextWidth;
    int m_lineHeight;

    QRect m_iconRect;
    QRect m_angleRect;
    QRect m_frameRect;
    QRect m_textRect;

    QPixmap *m_iconPixmap;

    QLabel *m_loading;
    QMovie *m_loadingMovie;

    bool m_isSending;
};

#endif // CHAT_MSG_ITEM_H
