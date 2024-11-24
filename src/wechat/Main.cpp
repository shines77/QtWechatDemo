#include <QApplication>
#include <QFile>

#include "WxMainWindow.h"
#include "IconHelper.h"
#include "AppInit.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setQuitOnLastWindowClosed(false);

    // 更改程序启动后任务栏图标
    app.setWindowIcon(QIcon(":/qss/res/WechatDemo.png"));

    // 加载样式表
    QFile file(":/qss/res/WechatDemo.css");
    if (file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = "#D4D4D4";
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }

    AppInit::Instance()->start();
    IconHelper::Load();

    WxMainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
