#ifndef BODERPANEL_H
#define BODERPANEL_H

#include <QWidget>
#include <QtWidgets>

class BoderPanel : public QWidget
{
    Q_OBJECT
public:
    explicit BoderPanel(QWidget *parent = nullptr);

public:
    void SetMainLayout(QLayout *layout);

protected:
    QWidget *centralWidget() const;

private:
    void InitMainCtrl();

private:
    QWidget *m_widgetMain;
};

#endif // BODERPANEL_H
