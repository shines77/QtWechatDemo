#ifndef CHAT_MSG_ITEM_H
#define CHAT_MSG_ITEM_H

#include <QWidget>

class QPaintEvent;
class QPainter;
class QLabel;
class QMovie;
class QTimer;

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

    void stopLoadingMovie();
    void setText(MsgType type, uint time, const QString &text);

    QSize calcFrameRect(const QString &text, MsgType type);
    QSize calcRealFrameRect(QString text, MsgType type);

    inline MsgType type() { return m_type; }
    inline uint    time() { return m_time; }
    inline QString text() { return m_text; }

protected slots:
    void onLoadingTimeout();

protected:
    void paintEvent(QPaintEvent *event);

    void CreateAllCtrls();
    void InitCtrls();
    void InitSlots();
    void Relayout();

    // kFrameMarginY = kIconMarginY
    static const int kFrameMarginY = 7;
    static const int kFrameSpacingX = 20;
    static const int kAngleWidth = 6;

    static const int kIconWidth = 36;
    static const int kIconHeight = 36;

    static const int kIconMarginX = 26;
    // kFrameMarginY = kIconMarginY
    static const int kIconMarginY = kFrameMarginY;
    static const int kIconSpacingX = 5;

    static const int kTextPaddingX = 10;
    static const int kTextPaddingY = 9;

    static const int kMinFrameHeight = kIconHeight;

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
    QTimer *m_loadingTimer;

    bool m_hasSent;
};

#endif // CHAT_MSG_ITEM_H
