/**
 * @file      basedlg.h
 * @brief     弹出窗口基类
 * @author    阿木大叔
 * @date      2020-10-27
 * @version   1.0
 * @copyright Copyright(C) 2020 NVR All rights reserved.
 */

#ifndef CBASEDLG_H
#define CBASEDLG_H

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QWidget>

#include "Public.h"
#include "PushButtonEx.h"

class CBaseDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CBaseDlg(QWidget *parent = 0);
    ~CBaseDlg();

public:
    void SetTitle(const QString &title);
    void SetTitleHeight(int nHeight);
    void SetTitleVisible(bool bVisable);
    void SetDlgFlags(Qt::WindowFlags type);
    void EnableMoveWindow(bool bEnable) { m_bEnableMove = bEnable; }  // 设置窗口是否可以拖动

protected:
    QWidget *centralWidget() const;
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    void InitCtrls();

public slots:
    virtual void OnBtnMinClicked();
    virtual void OnBtnMaxClicked();
    virtual void OnBtnCloseClicked();
    virtual void OnDisconnected();

private:
    QVBoxLayout *m_layoutMain;
    QWidget *m_widgetMain;
    QVBoxLayout *m_vLayoutWidgetMain;
    QWidget *m_widgetTitle;
    QHBoxLayout *m_hLayoutTitle;
    QLabel *m_labelTitle;
    QWidget *m_widgetMenu;
    QHBoxLayout *horizontalLayout;
    CPushButtonEx *m_btnMin;
    CPushButtonEx *m_btnMax;
    CPushButtonEx *m_btnClose;
    QWidget *m_widgetMainPane;

    bool m_bWndMaxSize;   // 窗口是否最大化
    bool m_bEnableMove;   // 窗口是否允许拖动
};

#endif // CBASEDLG_H
