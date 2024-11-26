#include "ChatHistoryList.h"
#include "ui_ChatHistoryList.h"

#include <QDateTime>
#include <QDebug>

CChatHistoryList::CChatHistoryList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CChatHistoryList)
{
    ui->setupUi(this);

    resize(600, 800);
}

CChatHistoryList::~CChatHistoryList()
{
    delete ui;
}

void CChatHistoryList::dealMessage(QListWidgetItem *item, ChatMsgItem *message,
                                   ChatMsgItem::MsgType type, uint time, const QString &text)
{
    message->setFixedWidth(this->width());
    QSize size = message->calcFrameRect(text, type);
    item->setSizeHint(size);
    message->setText(type, time, text);
    ui->listWidget->setItemWidget(item, message);
}

void CChatHistoryList::dealMessage(ChatMsgItem::MsgType type, uint time, const QString &text)
{
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    ChatMsgItem *message = new ChatMsgItem(ui->listWidget->parentWidget());

    dealMessage(item, message, type, time, text);
}

void CChatHistoryList::dealTimeMessage(uint timestamp)
{
    bool isShowTime = false;
    if (ui->listWidget->count() > 0) {
        QListWidgetItem *lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        ChatMsgItem *message = (ChatMsgItem *)ui->listWidget->itemWidget(lastItem);
        int lastTime = message->time();
        int curTime = timestamp;
        qDebug() << "(curTime - lastTime): " << (curTime - lastTime);
        // 两个消息相差一分钟, 则显示时间
        isShowTime = ((curTime - lastTime) > 60);
    }
    else {
        isShowTime = true;
    }

    if (isShowTime) {
        QListWidgetItem *timeItem = new QListWidgetItem(ui->listWidget);
        ChatMsgItem *timeMessage = new ChatMsgItem(ui->listWidget->parentWidget());

        QSize size = QSize(this->width(), 40);
        timeMessage->resize(size);
        timeItem->setSizeHint(size);
        QString strTime = QDateTime::fromTime_t(timestamp).toString("hh:mm");
        timeMessage->setText(ChatMsgItem::Time, timestamp, strTime);
        ui->listWidget->setItemWidget(timeItem, timeMessage);
    }
}

void CChatHistoryList::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    ui->textEdit->setText("");

    // 时间戳
    uint time = QDateTime::currentDateTime().toTime_t();
    // 发送中
    bool isSending = true;

    qDebug() << "addMessage: " << time << text << ui->listWidget->count();

    if ((ui->listWidget->count() % 2) != 0) {
        if (isSending) {
            dealTimeMessage(time);
            dealMessage(ChatMsgItem::Me, time, text);
        }
        else {
            bool isOver = true;
            for (int i = ui->listWidget->count() - 1; i > 0; i--) {
                ChatMsgItem *message = (ChatMsgItem *)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if (message->text() == text) {
                    isOver = false;
                    message->setTextSuccess();
                }
            }
            if (isOver) {
                dealTimeMessage(time);
                dealMessage(ChatMsgItem::Me, time, text);
                //message->setTextSuccess();
            }
        }
    }
    else {
        if (text != "") {
            dealTimeMessage(time);
            dealMessage(ChatMsgItem::Other, time, text);
        }
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
}

void CChatHistoryList::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    ui->textEdit->resize(this->width() - 20, ui->widget->height() - 20);
    ui->textEdit->move(10, 10);

    ui->pushButton->move(ui->textEdit->x() + ui->textEdit->width() - ui->pushButton->width() - 10,
                         ui->textEdit->y() + ui->textEdit->height() - ui->pushButton->height() - 10);

    for (int i = 0; i < ui->listWidget->count(); i++) {
        QListWidgetItem *item = ui->listWidget->item(i);
        ChatMsgItem *message = (ChatMsgItem *)ui->listWidget->itemWidget(ui->listWidget->item(i));

        dealMessage(item, message, message->type(), message->time(), message->text());
    }
}
