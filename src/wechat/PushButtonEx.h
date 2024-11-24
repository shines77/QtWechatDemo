/**
 * @file      PushButtonEx.h
 * @brief     自定义按钮
 * @author    阿木大叔
 * @date      2020-09-27
 * @version   1.0
 * @copyright Copyright(C) 2020 NVR All rights reserved.
 */

#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QVariant>

class CPushButtonEx : public QPushButton
{
    Q_OBJECT

public:
    explicit CPushButtonEx(QWidget *parent = 0);
    ~CPushButtonEx();

public:
    QVariant Data() { return m_varData; }
    void SetData(QVariant varData) { m_varData = varData; }
    void SetExArea(bool bExArea) { m_bExArea = bExArea; }
    void SetAspectRatio(double fRadio) { m_bRadio = true; m_fRadio = fRadio; }

protected:
    void mouseReleaseEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *event);

signals:
    void SignalClicked();           // 点击正常区域
    void SignalClickedExArea();     // 点击扩展区域

private:
    QVariant m_varData;
    bool m_bExArea;
    bool m_bRadio;
    double m_fRadio;
};

#endif // CPUSHBUTTON_H
