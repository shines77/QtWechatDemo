#ifndef CCHATHISTORYLIST_H
#define CCHATHISTORYLIST_H

#include <QWidget>
#include <QtWidgets>

#include "ChatMessage.h"

namespace Ui {
class CChatHistoryList;
}

class CChatHistoryList : public QWidget
{
    Q_OBJECT
public:
    explicit CChatHistoryList(QWidget *parent = Q_NULLPTR);
    ~CChatHistoryList();

    void dealMessage(ChatMessage *message, QListWidgetItem *item, QString text, QString time, ChatMessage::MsgType msgType);
    void dealMessageTime(QString curMsgTime);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::CChatHistoryList *ui;
};

#endif // CCHATHISTORYLIST_H
