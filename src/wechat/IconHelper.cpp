#include "IconHelper.h"

#include <QApplication>
#include <QFontDatabase>
#include <QPainter>

QFont IconHelper::m_iconFont;

bool IconHelper::Load()
{
    int nFontId = QFontDatabase::addApplicationFont(":/qss/res/WechatDemo.ttf");
    QStringList strlistFontName = QFontDatabase::applicationFontFamilies(nFontId);

    if (strlistFontName.count() > 0)
    {
        m_iconFont = QFont(strlistFontName.at(0));
        m_iconFont.setStyleStrategy(QFont::PreferAntialias);
        return true;
    }

    return false;
}

void IconHelper::SetIcon(QLabel *label, const QString &iconCode, uint dwSize)
{
    if (NULL == label)
        return;

    m_iconFont.setPixelSize(dwSize); // 图标字体的大小不会随DPI的改变而发生变化。
    label->setFont(m_iconFont);
    label->setText(iconCode);
    label->setAlignment(Qt::AlignCenter);
}

void IconHelper::SetIcon(QPushButton *btn, const QString &iconCode, uint dwSize /*= 26*/)
{
    if (NULL == btn)
        return;

    m_iconFont.setPixelSize(dwSize); // 图标字体的大小不会随DPI的改变而发生变化。
    btn->setFont(m_iconFont);
    btn->setText(iconCode);
    btn->setProperty("class", "IconfontBtn");   // iconfont 单独为一类别
}

void IconHelper::SetIcon(QPushButton *btn, const QString &iconCode, const QString &strColor, uint dwSize)
{
    if (NULL == btn)
        return;

    m_iconFont.setPixelSize(dwSize); // 图标字体的大小不会随DPI的改变而发生变化。
    btn->setFont(m_iconFont);
    btn->setText(iconCode);
    btn->setStyleSheet(QString("background:none;border-style:none;color:%1").arg(strColor));
}

void IconHelper::SetIcon(QToolButton *btn, const QString &iconCode, const QString &strColor /*= "#FFFFFF"*/,
                         uint dwIconSize /*= 26*/)
{
    if (NULL == btn)
        return;

    QPixmap pixNormal = GetPixmap(strColor, iconCode, dwIconSize, dwIconSize, dwIconSize);

    btn->setIcon(QIcon(pixNormal));
    btn->setIconSize(QSize(dwIconSize, dwIconSize));
}

void IconHelper::SetIcon(QAction *action, const QString &iconCode, const QString &strColor /*= "#000000"*/,
                         uint dwIconSize /*= 40*/)
{
    if (NULL == action)
        return;

    QPixmap pixNormal = GetPixmap(strColor, iconCode, dwIconSize, 30, 30);  // TODO: 待研究

    action->setIcon(QIcon(pixNormal));
    action->setIconVisibleInMenu(true);
}

void IconHelper::SetIcon(QLabel *label, const QString &strMainIcon /*= ""*/, const QString &strSecIcon /*= ""*/,
                         const QString &strThirdIcon /*= ""*/, uint dwIconSize /*= 24*/)
{
    if (NULL == label)
        return;

    QPixmap pixImage = GetPixmap(strMainIcon, strSecIcon, strThirdIcon, dwIconSize, dwIconSize);
    label->setPixmap(pixImage);
}

void IconHelper::SetIcon(QStandardItem *item, const QString &iconCode, uint dwSize)
{
    if (NULL == item)
        return;

    m_iconFont.setPixelSize(dwSize); // 图标字体的大小不会随DPI的改变而发生变化。
    item->setFont(m_iconFont);
    item->setText(iconCode);
}

QPixmap IconHelper::GetPixmap(const QString &strColor, const QString &iconCode,
                              uint dwSize, uint dwPixWidth, uint dwPixHeight)
{
    QPixmap pix(dwPixWidth, dwPixHeight);
    pix.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing); // 抗锯齿和使用平滑转换算法
    painter.setPen(QColor(strColor));
    painter.setBrush(QColor(strColor));

    m_iconFont.setPixelSize(dwSize);
    painter.setFont(m_iconFont);
    painter.drawText(pix.rect(), Qt::AlignCenter, iconCode);
    painter.end();
    return pix;
}

QPixmap IconHelper::GetPixmap(const QString &strMainIcon, const QString &strSecIcon,
                              const QString &strThirdIcon, uint dwPixWidth, uint dwPixHeight)
{
    QPixmap pix(dwPixWidth, dwPixHeight);
    pix.fill(Qt::transparent);

    QRect rcClient = pix.rect();
    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing); // 抗锯齿和使用平滑转换算法
    painter.drawImage(rcClient, QImage(strMainIcon));

    // 右下角
    if (strSecIcon.length() > 0)
    {
        QRect rcSecIcon = rcClient;
        QImage imgSecIcon = QImage(strSecIcon);
        rcSecIcon.setTopLeft(QPoint(rcSecIcon.right() - imgSecIcon.width(), rcSecIcon.bottom() - imgSecIcon.height()));
        painter.drawImage(rcSecIcon, imgSecIcon);
    }

    // 左下角
    if (strThirdIcon.length() > 0)
    {
        QRect rcThirdIcon = rcClient;
        QImage imgThirdIcon = QImage(strThirdIcon);
        rcThirdIcon.setTopRight(QPoint(rcThirdIcon.left() + imgThirdIcon.width(), rcThirdIcon.bottom() - imgThirdIcon.height()));
        painter.drawImage(rcThirdIcon, imgThirdIcon);
    }

    painter.end();
    return pix;
}

QPixmap IconHelper::GetDragChnPixmap(QString strText)
{
    const int nSpace = 5;

    QFontMetrics cs(QApplication::font());

    int nW = cs.width(strText) + nSpace * 2;
    int nH = cs.height()+ nSpace * 2;

    QPixmap pix(nW, nH);
    QRect rcClient = pix.rect();

    pix.fill(QColor(65, 70, 98, 255));

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing); // 抗锯齿和使用平滑转换算法

    painter.save();
    painter.setPen(QPen(QColor(0x3d, 0x77, 0xda), 1, Qt::SolidLine, Qt::RoundCap));
    rcClient.setTopLeft(QPoint(rcClient.top() + 1, rcClient.left() + 1));
    rcClient.setBottomRight(QPoint(rcClient.bottom() - 1, rcClient.right() - 1));
    painter.drawRect(pix.rect());
    painter.restore();

    painter.save();
    painter.setPen(Qt::white);
    painter.drawText(pix.rect(), Qt::AlignCenter, strText);
    painter.restore();

    painter.end();

    return pix;
}
