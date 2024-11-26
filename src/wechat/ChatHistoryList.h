#ifndef CCHATHISTORYLIST_H
#define CCHATHISTORYLIST_H

#include <QWidget>
#include <QtWidgets>

#include "ChatMsgItem.h"

namespace Ui {
class CChatHistoryList;
}

class CChatHistoryList : public QWidget
{
    Q_OBJECT
public:
    explicit CChatHistoryList(QWidget *parent = Q_NULLPTR);
    ~CChatHistoryList();

    void dealMessage(ChatMsgItem *message, QListWidgetItem *item,
                     QString text, QString time, ChatMsgItem::MsgType type);
    void dealTimeMessage(QString msgTime);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::CChatHistoryList *ui;
};

#endif // CCHATHISTORYLIST_H
