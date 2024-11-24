/**
 * @file      IconHelper.h
 * @brief     字体图标
 * @author    阿木大叔
 * @date      2020-10-27
 * @version   1.0
 * @copyright Copyright(C) 2020 NVR All rights reserved.
 */

#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QPushButton>
#include <QToolButton>
#include <QAction>
#include <QLabel>
#include <QStandardItem>

class IconHelper : public QObject
{
    Q_OBJECT

public:
    static bool Load();
    static void SetIcon(QLabel *label, const QString &iconCode, uint dwSize = 26);
    static void SetIcon(QPushButton *btn, const QString &iconCode, uint dwSize = 20);
    static void SetIcon(QPushButton *btn, const QString &iconCode, const QString &strColor, uint dwSize = 20);
    static void SetIcon(QToolButton *btn, const QString &iconCode, const QString &strColor = "#FFFFFF", uint dwIconSize = 26);
    static void SetIcon(QAction *action, const QString &iconCode, const QString &strColor = "#000000", uint dwIconSize = 40);
    static void SetIcon(QLabel *label, const QString &strMainIcon, const QString &strSecIcon, const QString &strThirdIcon = "", uint dwIconSize = 24);
    static void SetIcon(QStandardItem *item, const QString &iconCode, uint dwSize = 26);

    static QPixmap GetPixmap(const QString &strColor, const QString &iconCode,
                             uint dwSize, uint dwPixWidth, uint dwPixHeight);

    // 生成三张叠加在一起的图片，主图为背景，辅图在右下角
    static QPixmap GetPixmap(const QString &strMainIcon, const QString &strSecIcon, const QString &strThirdIcon,
                             uint dwPixWidth, uint dwPixHeight);

    static QPixmap GetDragChnPixmap(QString strText);

    static QFont GetFont() {
        return m_iconFont;
    }

private:
    static QFont m_iconFont;    // 图形字体
};

#endif // ICONHELPER_H
