#include "UserProfiles.h"
#include "ui_userprofiles.h"

#include <QDesktopServices>

UserProfiles::UserProfiles(QWidget *parent) : BoderPanel(parent),
    ui(new Ui::UserProfiles)
{
    ui->setupUi(this);

    m_pMovie = NULL;

    setAttribute(Qt::WA_StyledBackground);              // 禁止父窗口样式影响子控件样式
    setProperty("form", "BaseDlg");

    CreateAllCtrls();
    InitCtrls();
    Relayout();
}

UserProfiles::~UserProfiles()
{
    delete ui;
}

void UserProfiles::CreateAllCtrls()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_pMovie, QMovie);
}

void UserProfiles::InitCtrls()
{
    m_pMovie->setFileName(":/avatar/avatar/luffy.gif");
    ui->labelIcon->setMovie(m_pMovie);
    m_pMovie->setScaledSize(ui->labelIcon->size());
    m_pMovie->start();

    CMaskPanel *w = new CMaskPanel();
    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addWidget(w);
    layoutMain->setMargin(0);

    ui->labelIcon->setLayout(layoutMain);
}

void UserProfiles::Relayout()
{
    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addWidget(ui->widgetMain);
    layoutMain->setMargin(0);

    centralWidget()->setLayout(layoutMain);
}

void UserProfiles::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://gitee.com/shines77"));
}

CMaskPanel::CMaskPanel(QWidget *parent)
{
    // 设置边框阴影
    this->setAttribute(Qt::WA_TranslucentBackground, true);
}

void CMaskPanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);         // 创建画家对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255));

    QRect rcAvatarBg(rect());
    QPainterPath path;
    path.addEllipse(0, 0, rcAvatarBg.width(), rcAvatarBg.height()); // 添加一个圆
    path.addRect(0, 0, rcAvatarBg.width(), rcAvatarBg.height());    // 添加一个矩形
    path.setFillRule(Qt::OddEvenFill);  // 奇偶填充规则
    painter.drawPath(path);
}
