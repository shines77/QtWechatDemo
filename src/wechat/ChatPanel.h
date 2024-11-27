#ifndef CCHATPANEL_H
#define CCHATPANEL_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QWebEngineView>

#include "Public.h"

class CFriendList;
class CChatTopToolbar;
class CPushButtonEx;
class CChatHistoryList;

class CChatPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CChatPanel(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void CreateAllCtrls();
    void InitCtrls();
    void InitSlots();
    void Relayout();

    void SendGetRequest(QString strMsg);

    bool eventFilter(QObject *obj, QEvent *e);

signals:
    //
public slots:
    void OnBtnSendClicked();
    void OnRecvMsg(QByteArray strMsg, QObject *obj);
    void OnFriendChanged(TUserInfo tUserInfo);

private:
    CFriendList         *m_pFriendList;
    CChatTopToolbar     *m_pTopToolbar;
    //QWebEngineView      *m_pViewChat;
    CChatHistoryList    *m_pChatHistoryList;
    QTextEdit           *m_txtEdit;
    CPushButtonEx       *m_btnSend;
    QLabel              *m_lblSeparatorLine;
};

#endif // CCHATPANEL_H
