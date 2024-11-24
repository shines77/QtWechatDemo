#include "ContactPanel.h"

#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "FriendList.h"

CContactPanel::CContactPanel(QWidget *parent) : QWidget(parent)
{
    m_pFriendList = NULL;

    CreateAllCtrls();
    InitCtrls();
    InitSlots();
    Relayout();
}

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

void CContactPanel::CreateAllCtrls()
{
    NEW_OBJECT(m_pFriendList, CFriendList);
}

void CContactPanel::InitCtrls()
{
    m_pFriendList->setFixedWidth(250);
    m_pFriendList->SetContactMode(true);
}

void CContactPanel::InitSlots()
{
    //
}

void CContactPanel::Relayout()
{
    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_pFriendList);
    layoutMain->addStretch();
    layoutMain->setSpacing(0);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}
