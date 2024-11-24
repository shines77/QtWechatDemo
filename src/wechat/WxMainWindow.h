#ifndef WXMAINWINDOW_H
#define WXMAINWINDOW_H

#include <QWidget>
#include <QtWidgets>

#include "Public.h"

namespace Ui {
class WxMainWindow;
}

class CPushButtonEx;
class NavPanel;
class CMessagePanel;
class CContactPanel;
class CFavoritePanel;

class WxMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WxMainWindow(QWidget *parent = nullptr);
    ~WxMainWindow();

private:
    void CreateAllCtrls();
    void InitCtrls();
    void InitSlots();
    void Relayout();

    void InitTrayIcon();
    void UpdateCtrlText();

    void mouseDoubleClickEvent( QMouseEvent *event );
    void paintEvent(QPaintEvent *event);

signals:
    void SignalTabChanged(EMainTabPage eMainTabPage);

private slots:
    void OnTabChanged(EMainTabPage eMainTabPage);

    void OnMinWindows();
    void OnMaxWindows();
    void OnClose();

    void ChangeTabPage();

    void OnSystemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::WxMainWindow *ui;

    QWidget *m_widgetTitle;
    QStackedWidget *m_pStackedWidget;
    NavPanel *m_pNavPanel;

    CPushButtonEx *m_btnMin;
    CPushButtonEx *m_btnMax;
    CPushButtonEx *m_btnClose;

    QSystemTrayIcon *m_trayIcon;
    QMenu *m_systemTrayMenu;

    CMessagePanel  *m_pMessagePanel;
    CContactPanel  *m_pContactPanel;
    CFavoritePanel *m_pFavoritePanel;

    bool m_bMaxWindows;
    EMainTabPage m_eMainTabPage;
};

#endif // WXMAINWINDOW_H
