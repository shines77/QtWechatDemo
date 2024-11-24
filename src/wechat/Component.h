#ifndef CCOMPONENT_H
#define CCOMPONENT_H

#include <QWidget>
#include <QtWidgets>

#include "Slider.h"

class CComponent : public QWidget
{
    Q_OBJECT

public:
    explicit CComponent(QWidget *parent = 0);

private:
    void CreateAllCtrls();
    void InitCtrls();
    void InitSlots();
    void InitNoticeCtrl();
    void InitPopConfirm();
    void InitSlider();
    void Relayout();

private:
    QGroupBox *m_groupNotice;
    QPushButton *m_btnOpenNotice1;
    QPushButton *m_btnOpenNotice2;
    QPushButton *m_btnOpenLT;
    QPushButton *m_btnOpenRT;
    QPushButton *m_btnOpenLB;
    QPushButton *m_btnOpenRB;

    QGroupBox *m_groupPopConfirm;
    QPushButton *m_btnTop;
    QPushButton *m_btnLeft;
    QPushButton *m_btnRight;
    QPushButton *m_btnBottom;

    QGroupBox *m_groupSlider;
    CSlider *m_pSlider;
    CSlider *m_pSlider2;

    QPushButton *m_btnTL;
    QPushButton *m_btnTR;
    QPushButton *m_btnLT;
    QPushButton *m_btnRT;
    QPushButton *m_btnLB;
    QPushButton *m_btnRB;
    QPushButton *m_btnBL;
    QPushButton *m_btnBR;
};

#endif // CCOMPONENT_H
