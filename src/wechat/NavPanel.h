#ifndef CNAVPANEL_H
#define CNAVPANEL_H

#include <QWidget>
#include <QtWidgets>

#include "Public.h"

class CPushButtonEx;
class CUserDetailDlg;

class CNavPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CNavPanel(QWidget *parent = 0);

private:
    void CreateAllCtrls();
    void InitCtrls();
    void InitSlots();
    void Relayout();

signals:
    void SignalTabChanged(EMainTabPage eMainTabPage);

public slots:
    void OnBtnUserAvatarClicked();

private slots:
    void OnSignalPushedMapped(int nCmd);
    void OnMainTabChanged(EMainTabPage eMainTabPage);
    void OnBtnMoreClicked();
    void OnMenuTriggered(QAction *action);

private:
    CPushButtonEx *m_btnUserAvatar;
    CPushButtonEx *m_btnMessage;
    CPushButtonEx *m_btnFavorites;
    CPushButtonEx *m_btnContacts;
    CPushButtonEx *m_btnCalendar;
    CPushButtonEx *m_btnWorkspace;
    CPushButtonEx *m_btnMore;

    QLabel *m_lblSeparatorLine;

    CUserDetailDlg *m_pUserDetailDlg;
};

#endif // CNAVPANEL_H
