#ifndef CCHATHISTORYLIST_H
#define CCHATHISTORYLIST_H

#include <QWidget>
#include <QtWidgets>
#include <QListWidget>

#include "ChatMsgItem.h"

class CChatHistoryList : public QListWidget
{
    Q_OBJECT
public:
    explicit CChatHistoryList(QWidget *parent = Q_NULLPTR);
    ~CChatHistoryList();

    static uint getTimeStamp();

    void addTimeMessage(uint time);
    void addTimeMessage();

    void tryAddTimeMessage();
    void tryAddTimeMessage(uint time);

    void dealMessage(QListWidgetItem *item, ChatMsgItem *message,
                     ChatMsgItem::MsgType type, uint time, const QString &text);

    void addMessage(ChatMsgItem::MsgType type, const QString &text);
    void addMessage(ChatMsgItem::MsgType type, uint time, const QString &text);

    void sendMessage(const QString &text);
    void sendMessage(ChatMsgItem::MsgType type, const QString &text);

    void updateMessage(QListWidgetItem *item, ChatMsgItem *message,
                       ChatMsgItem::MsgType type, uint time, const QString &text);
    void resizeMessages(QResizeEvent *event);

protected:
    void resizeEvent(QResizeEvent *event);

    void CreateAllCtrls();
    void InitCtrls();
    void Relayout();

    bool needShowDateTime(uint time) const;

private slots:
    //
};

#endif // CCHATHISTORYLIST_H
