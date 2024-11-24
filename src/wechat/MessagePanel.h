#ifndef CMESSAGEPANEL_H
#define CMESSAGEPANEL_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QWebEngineView>

#include "Public.h"

class CFriendList;
class CChatTopToolbar;
class CPushButtonEx;

class CMessagePanel : public QWidget
{
    Q_OBJECT
public:
    explicit CMessagePanel(QWidget *parent = 0);

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
    CFriendList     *m_pFriendList;
    CChatTopToolbar *m_pTopToolbar;
    QWebEngineView  *m_pViewChat;
    QTextEdit       *m_txtEdit;
    CPushButtonEx   *m_btnSend;
    QLabel          *m_lblSeparatorLine;
};

#endif // CMESSAGEPANEL_H
