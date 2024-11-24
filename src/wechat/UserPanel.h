#ifndef CUSERPANEL_H
#define CUSERPANEL_H

#include <QWidget>
#include <QPixmap>

class CUserDetailPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CUserDetailPanel(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    QPixmap m_pixBg;
    QPixmap m_pixBigBg;
    bool m_bEnter;
};

class CUserPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CUserPanel(QWidget *parent = 0);

private:
    void CreateAllCtrls();
    void InitCtrls();
    void InitSlots();
    void Relayout();

private:
    CUserDetailPanel *m_pUserPanel;
};

#endif // CUSERPANEL_H
