#ifndef CCONTACTPANEL_H
#define CCONTACTPANEL_H

#include <QWidget>

class CFriendList;
class CChatTopToolbar;
class CPushButtonEx;

class CContactPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CContactPanel(QWidget *parent = 0);

private:
    void CreateAllCtrls();
    void InitCtrls();
    void InitSlots();
    void Relayout();

private:
    CFriendList *m_pFriendList;
};

#endif // CCONTACTPANEL_H
