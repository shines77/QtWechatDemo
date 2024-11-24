#ifndef CCHATTOPTOOLBAR_H
#define CCHATTOPTOOLBAR_H

#include <QWidget>
#include <QtWidgets>
#include "public.h"

class CPushButtonEx;
class CUserDetailDlg;

class CChatTopToolbar : public QWidget
{
    Q_OBJECT
public:
    explicit CChatTopToolbar(QWidget *parent = 0);

public slots:
    void OnFriendChanged(TUserInfo tUserInfo);

private:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void CreateAllCtrls();
    void InitCtrls();
    void Relayout();

private:
    QLabel *m_lblUserName;
    QLabel *m_lblState;
    QLabel *m_lblEmail;
    QLabel *m_lblEmailValue;

    QLabel *m_lblSeparatorLine;

    QLabel *m_lblPart;
    QLabel *m_lblPartValue;

    QLabel *m_lblSign;
    QLabel *m_lblSignValue;

    CPushButtonEx *m_btnAddUser;

    CUserDetailDlg *m_pUserDetail;

    TUserInfo m_tUserInfo;
};

#endif // CCHATTOPTOOLBAR_H
