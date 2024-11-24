#include "FavoritePanel.h"

#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "FriendList.h"

#ifdef WIN32
#include <Windows.h>
#pragma comment(lib, "User32.lib")
#endif

CFavoritePanel::CFavoritePanel(QWidget *parent) : QWidget(parent)
{
    m_pFriendList = NULL;

    CreateAllCtrls();
    InitCtrls();
    InitSlots();
    Relayout();
}

#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

void CFavoritePanel::CreateAllCtrls()
{
    NEW_OBJECT(m_pFriendList, CFriendList);
}

void CFavoritePanel::InitCtrls()
{
    m_pFriendList->setFixedWidth(250);
    m_pFriendList->SetContactMode(true);
}

void CFavoritePanel::InitSlots()
{
    //
}

void CFavoritePanel::Relayout()
{
    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_pFriendList);
    layoutMain->addStretch();
    layoutMain->setSpacing(0);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}

void CFavoritePanel::UpdateFriendList()
{
#ifdef WIN32
    MessageBeep(500);
#endif
}

void CFavoritePanel::OnMainTabChanged(EMainTabPage eMainTabPage)
{
    if (TAB_PAGE_FAVORITES == eMainTabPage)
        UpdateFriendList();
}
