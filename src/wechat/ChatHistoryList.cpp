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

void CChatHistoryList::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); // 时间戳

    bool isSending = true; // 发送中

    qDebug() << "addMessage" << text << time << ui->listWidget->count();

    if ((ui->listWidget->count() % 2) != 0) {
        if (isSending) {
            dealMessageTime(time);

            ChatMessage* message = new ChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(message, item, text, time, ChatMessage::Msg_Me);
        }
        else {
            bool isOver = true;
            for (int i = ui->listWidget->count() - 1; i > 0; i--) {
                ChatMessage *message = (ChatMessage *)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if (message->text() == text) {
                    isOver = false;
                    message->setTextSuccess();
                }
            }
            if (isOver) {
                dealMessageTime(time);

                ChatMessage *message = new ChatMessage(ui->listWidget->parentWidget());
                QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
                dealMessage(message, item, text, time, ChatMessage::Msg_Me);
                message->setTextSuccess();
            }
        }
    }
    else {
        if (text != "") {
            dealMessageTime(time);

            ChatMessage *message = new ChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
            dealMessage(message, item, text, time, ChatMessage::Msg_Other);
        }
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
}

void CChatHistoryList::dealMessage(ChatMessage *message, QListWidgetItem *item, QString text,
                                   QString time, ChatMessage::MsgType msgType)
{
    message->setFixedWidth(this->width());
    QSize size = message->calcFrameRect(text, msgType);
    item->setSizeHint(size);
    message->setText(text, time, size, msgType);
    ui->listWidget->setItemWidget(item, message);
}

void CChatHistoryList::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if (ui->listWidget->count() > 0) {
        QListWidgetItem *lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        ChatMessage *message = (ChatMessage *)ui->listWidget->itemWidget(lastItem);
        int lastTime = message->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << (curTime - lastTime);
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
        // isShowTime = true;
    }
    else {
        isShowTime = true;
    }
    if (isShowTime) {
        ChatMessage *messageTime = new ChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem *itemTime = new QListWidgetItem(ui->listWidget);

        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, ChatMessage::Msg_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

void CChatHistoryList::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    ui->textEdit->resize(this->width() - 20, ui->widget->height() - 20);
    ui->textEdit->move(10, 10);

    ui->pushButton->move(ui->textEdit->width() + ui->textEdit->x() - ui->pushButton->width() - 10,
                         ui->textEdit->height() + ui->textEdit->y() - ui->pushButton->height() - 10);

    for (int i = 0; i < ui->listWidget->count(); i++) {
        ChatMessage *message = (ChatMessage *)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem *item = ui->listWidget->item(i);

        dealMessage(message, item, message->text(), message->time(), message->msgType());
    }
}
