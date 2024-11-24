#ifndef CSLIDER_H
#define CSLIDER_H

#include <QWidget>

class CSlider : public QWidget
{
    Q_OBJECT
public:
    explicit CSlider(QWidget *parent = 0);

    struct TItemRect
    {
        QRectF rcArar;
        int m_nValue;

        TItemRect(): m_nValue(-1) {
            //
        }
        ~TItemRect() {
            //
        }
    };

public:
    void EnableRange(bool bRange) { m_bOnlyEnd = !bRange; }
    void SetRange(int nMin, int nMax);
    void SetStep(int nStep);
    void EnablePercent(bool bPercent) { m_bPercent = bPercent; }

    // 双滑块模式
    void SetPos(int nStart, int nEnd);

    // 单滑块模式
    void SetCurPos(int nPos);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void UpdateItemList();
    TItemRect GetStartValue();
    TItemRect GetEndValue();
    bool GetStartAndEndValue(TItemRect &itemStart, TItemRect &itemEnd);
    void UpdateStartValue(QPoint ptPos);
    void UpdateEndValue(QPoint ptPos);

signals:
    void SignalValueChange(int nValue);             // 单滑块模式
    void SignalValueChange(int nStart, int nEnd);   // 双滑块模式

private:
    int m_nMin;
    int m_nMax;
    int m_nTotal;
    int m_nStart;
    int m_nEnd;
    int m_nStep;

    QRect m_rcBg;
    QList<TItemRect> m_listItems;
    bool m_bSelected;

    bool m_bSelStart;
    bool m_bSelEnd;

    bool m_bMousePress;
    bool m_bOnlyEnd;
    bool m_bPercent;
};

#endif // CSLIDER_H
