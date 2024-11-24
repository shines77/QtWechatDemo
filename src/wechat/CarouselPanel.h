#ifndef CAROUSELPANEL_H
#define CAROUSELPANEL_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPushButton>

class CarouselPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CarouselPanel(QWidget *parent = 0);

public:
    void SetImageList(QStringList listImgFileName);
    void StartPlay();

private:
    void CreateAllCtrls();
    void InitCtrls();
    void InitSlots();
    void Relayout();
    void UpdateChangeBtns();

    void paintEvent(QPaintEvent *event);

private slots:
    void OnImageChangeTimeout();
    void OnImageSwitchButtonClicked(int nIndex);

private:
    QTimer *m_pTimerImageChange;
    QPropertyAnimation* m_pAnimationOpacity;
    QList<QPushButton*> m_listBtns;

    int m_nCurrentImageIndex;
    QPixmap m_pixCurrent;
    QPixmap m_pixNext;
    QList<QString> m_listImgFileName;
};

#endif // CAROUSELPANEL_H
