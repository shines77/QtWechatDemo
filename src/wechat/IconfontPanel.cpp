#include "IconfontPanel.h"

#include <QVBoxLayout>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QApplication>
#include <QClipboard>

#include "Public.h"
#include "PushButtonEx.h"
#include "IconHelper.h"
#include "TipWidget.h"
#include "NotificationPanel.h"

CIconFontPanel::CIconFontPanel(QWidget *parent) : QWidget(parent)
{
   m_pScrollArea = NULL;
   m_widgetContent = NULL;

   CreateAllCtrls();
   InitCtrls();
   InitSolts();
   Relayout();

   ParseJsonFile();
}

void CIconFontPanel::OnBtnClicked()
{
    CPushButtonEx *btnSender = (CPushButtonEx *)sender();
    QClipboard *clipboard = QApplication::clipboard();   // 获取系统剪贴板指针

    clipboard->setText(QString("0x%1").arg(QString::number(btnSender->Data().toInt(), 16)));

    AutoTip->SetMesseage(QString("0x%1 复制成功").arg(QString::number(btnSender->Data().toInt(), 16)));
}

void CIconFontPanel::CreateAllCtrls()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_pScrollArea, QScrollArea);
    NEW_OBJECT(m_widgetContent, QWidget);
}

void CIconFontPanel::InitCtrls()
{
    m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    // 隐藏横向滚动条
    m_pScrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    m_pScrollArea->setWidgetResizable(true);
    m_pScrollArea->setWidget(m_widgetContent);
    m_pScrollArea->setStyleSheet(".QScrollArea { border-style:none; }");

    m_widgetContent->setAttribute(Qt::WA_StyledBackground);
    m_widgetContent->setProperty("form", "IconfontPanel");
}

void CIconFontPanel::InitSolts()
{
    //
}

void CIconFontPanel::Relayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_pScrollArea);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void CIconFontPanel::ParseJsonFile()
{
    int nRow = 0;
    int nCol = 0;
    QGridLayout *layoutMain = new QGridLayout(m_widgetContent);

    QFile file(":/qss/res/WechatDemo.json");
    if (file.open(QFile::ReadOnly))
    {
        QByteArray json = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument doucment = QJsonDocument::fromJson(json, &jsonError);
        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
        {
            if (doucment.isObject())
            {
                QJsonObject object = doucment.object();
                if(object.contains("glyphs"))
                {
                    QJsonValue glyphs = object.value("glyphs");
                    if (glyphs.isArray())
                    {
                        QJsonArray arrIcon = glyphs.toArray();
                        for (int i = 0; i < arrIcon.size(); i++)
                        {
                            QJsonValue jsonIcon = arrIcon.at(i);

                            if (jsonIcon.isObject())
                            {
                                QJsonObject objectIcon = jsonIcon.toObject();

                                QChar cUnicode = objectIcon.take("unicode_decimal").toInt();
                                QString strUnicodeHex = objectIcon.take("unicode").toString();

                                CPushButtonEx *btn = new CPushButtonEx(m_widgetContent);
                                btn->SetAspectRatio(2.2);
                                IconHelper::SetIcon(btn, cUnicode, 30);
                                btn->setProperty("IconfontBtn", "true");   // iconfont 单独为一类别
                                btn->SetData(cUnicode);
                                btn->setToolTip(QString("0x%1").arg(strUnicodeHex));
                                layoutMain->addWidget(btn, nRow, nCol);
                                connect(btn, SIGNAL(clicked()), this, SLOT(OnBtnClicked()));

                                nCol++;

                                if (nCol > 4)
                                {
                                    nRow++;
                                    nCol = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
