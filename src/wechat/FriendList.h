#ifndef CFRIENDLIST_H
#define CFRIENDLIST_H

#include <QWidget>
#include <QtWidgets>

#include "Public.h"

class CPushButtonEx;

class CFriendList : public QWidget
{
    Q_OBJECT
public:
    explicit CFriendList(QWidget *parent = 0);

    void SetContactMode(bool bContacts);

private slots:
    void OnItemClicked(QListWidgetItem *item, QListWidgetItem *previous);

signals:
    void SignalFriendChanged(TUserInfo tUserInfo);

private:
    void CreateAllCtrls();
    void InitCtrls();
    void InitList();
    void InitTree();
    void InitSlots();
    void Relayout();

private:
    QLineEdit       *m_lineEditSearch;
    QLabel          *m_lblSearch;
    CPushButtonEx   *m_btnAdd;
    QListWidget     *m_listCtrlFriends;
    QTreeWidget     *m_treeCtrlContacts;
};

#endif // CFRIENDLIST_H
