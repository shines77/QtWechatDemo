#ifndef PUBLIC_H
#define PUBLIC_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "IconHelper.h"

enum EMainTabPage
{
    TAB_PAGE_MESSAGE = 0,       // 消息会话
    TAB_PAGE_CONTACTS = 1,      // 通讯录
    TAB_PAGE_FAVORITES = 2,     // 收藏夹
    TAB_PAGE_CALENDAR = 3,      // 日程
    TAB_PAGE_WORKSPACE = 4,     // 工作台
    TAB_PAGE_WEDOC = 5,         // 微文档
    TAB_PAGE_WEDRIVE = 6,       // 微盘
    TAB_PAGE_MEETING = 7,       // 会议
};

struct TUserInfo
{
    QString strName;
    QString strPart;
    QString strEmail;
    QString strAvatar;
    // ...
};

#endif // PUBLIC_H
