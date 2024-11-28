#include "ChatHistoryList.h"

#include <QDateTime>
#include <QDebug>

CChatHistoryList::CChatHistoryList(QWidget *parent) : QListWidget(parent)
{
    CreateAllCtrls();
    InitCtrls();
    Relayout();
}

CChatHistoryList::~CChatHistoryList()
{
    //
}

void CChatHistoryList::CreateAllCtrls()
{
    //
}

void CChatHistoryList::InitCtrls()
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void CChatHistoryList::Relayout()
{
    //
}

uint CChatHistoryList::getTimeStamp()
{
    uint time = QDateTime::currentDateTime().toTime_t();
    return time;
}

bool CChatHistoryList::needShowDateTime(uint time) const
{
    bool needShowTime = true;

    if (this->count() > 0) {
        QListWidgetItem *lastItem = this->item(this->count() - 1);
        ChatMsgItem *message = (ChatMsgItem *)this->itemWidget(lastItem);
        uint lastTime = message->time();
        int elapsedTime = time - lastTime;

        qDebug() << "(curTime - lastTime):" << elapsedTime;

        // 两个消息相差一分钟, 则显示时间
        needShowTime = (elapsedTime > 60);
    }
    return needShowTime;
}

void CChatHistoryList::addTimeMessage(uint time)
{
    QListWidgetItem *timeItem = new QListWidgetItem(this);
    ChatMsgItem *timeMessage = new ChatMsgItem(this);

    QString strTime = ChatMsgItem::FormatDateTime(time);

    QSize size = QSize(this->width(), 40);
    timeMessage->resize(size);
    timeItem->setSizeHint(size);
    timeMessage->setText(ChatMsgItem::Time, time, strTime);

    this->setItemWidget(timeItem, timeMessage);
}

void CChatHistoryList::addTimeMessage()
{
    // 时间戳
    uint time = CChatHistoryList::getTimeStamp();
    addTimeMessage(time);
}

void CChatHistoryList::tryAddTimeMessage(uint time)
{
    if (needShowDateTime(time)) {
        addTimeMessage(time);
    }
}

void CChatHistoryList::tryAddTimeMessage()
{
    // 时间戳
    uint time = CChatHistoryList::getTimeStamp();
    tryAddTimeMessage(time);
}

void CChatHistoryList::updateMessage(QListWidgetItem *item, ChatMsgItem *message,
                                     ChatMsgItem::MsgType type, uint time, const QString &text)
{
    message->setFixedWidth(this->width());
    QSize size = message->calcFrameRect(text, type);
    qDebug() << "calcFrameRect:" << size;
    item->setSizeHint(size);
    //message->setText(type, time, text);
    message->update();
}

void CChatHistoryList::dealMessage(QListWidgetItem *item, ChatMsgItem *message,
                                   ChatMsgItem::MsgType type, uint time, const QString &text)
{
    message->setFixedWidth(this->width());
    QSize size = message->calcFrameRect(text, type);
    qDebug() << "calcFrameRect:" << size;
    item->setSizeHint(size);
    message->setText(type, time, text);
    this->setItemWidget(item, message);
}

void CChatHistoryList::addMessage(ChatMsgItem::MsgType type, uint time, const QString &text)
{
    QListWidgetItem *item = new QListWidgetItem(this);
    ChatMsgItem *message = new ChatMsgItem(this);

    dealMessage(item, message, type, time, text);
}

void CChatHistoryList::addMessage(ChatMsgItem::MsgType type, const QString &text)
{
    // 时间戳
    uint time = QDateTime::currentDateTime().toTime_t();
    addMessage(type, time, text);
}

void CChatHistoryList::sendMessage(const QString &text)
{
    ChatMsgItem::MsgType lastMsgType = ChatMsgItem::MsgType::System;
    if (this->count() > 0) {
        QListWidgetItem *lastItem = this->item(this->count() - 1);
        ChatMsgItem *message = (ChatMsgItem *)this->itemWidget(lastItem);
        if (message != Q_NULLPTR) {
            lastMsgType = message->type();
        }
    }

    // 时间戳
    uint time = QDateTime::currentDateTime().toTime_t();
    qDebug() << "addMessage:" << time << text << this->count();

    tryAddTimeMessage(time);

    if (lastMsgType != ChatMsgItem::MsgType::Me) {
        addMessage(ChatMsgItem::MsgType::Me, time, text);
    }
    else {
        addMessage(ChatMsgItem::MsgType::Other, time, text);
    }
    this->setCurrentRow(this->count() - 1);
}

void CChatHistoryList::sendMessage(ChatMsgItem::MsgType type, const QString &text)
{
    // 发送中
    bool isSending = true;

    // 时间戳
    uint time = QDateTime::currentDateTime().toTime_t();
    qDebug() << "addMessage:" << time << text << this->count();

    if ((this->count() % 2) != 0) {
        if (isSending) {
            tryAddTimeMessage(time);
            addMessage(type, time, text);
        }
        else {
            bool isOver = true;
            for (int i = this->count() - 1; i > 0; i--) {
                ChatMsgItem *message = (ChatMsgItem *)this->itemWidget(this->item(i));
                if (message->text() == text) {
                    isOver = false;
                    message->stopLoadingMovie();
                }
            }
            if (isOver) {
                tryAddTimeMessage(time);
                addMessage(type, time, text);
                //message->setTextSuccess();
            }
        }
    }
    else {
        if (text != "") {
            tryAddTimeMessage(time);
            addMessage(type, time, text);
        }
    }
    this->setCurrentRow(this->count() - 1);
}

void CChatHistoryList::resizeMessages(QResizeEvent *event)
{
    Q_UNUSED(event);

    for (int i = 0; i < this->count(); i++) {
        QListWidgetItem *item = this->item(i);
        ChatMsgItem *message = (ChatMsgItem *)this->itemWidget(item);

        if (item != Q_NULLPTR && message != Q_NULLPTR) {
            updateMessage(item, message, message->type(), message->time(), message->text());
        }
    }

    this->setCurrentRow(this->count() - 1);
}

void CChatHistoryList::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
}
