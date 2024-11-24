#ifndef CFAVORITEPANEL_H
#define CFAVORITEPANEL_H

#include <QWidget>

#include "Public.h"

class CFriendList;
class CChatTopToolbar;
class CPushButtonEx;

class CFavoritePanel : public QWidget
{
    Q_OBJECT
public:
    explicit CFavoritePanel(QWidget *parent = 0);

signals:
    void SignalTabChanged(EMainTabPage eMainTabPage);

protected slots:
    void OnMainTabChanged(EMainTabPage eMainTabPage);

private:
    void CreateAllCtrls();
    void InitCtrls();
    void InitSlots();
    void Relayout();

    void UpdateFriendList();

private:
    CFriendList *m_pFriendList;
};

#endif // CFAVORITEPANEL_H
