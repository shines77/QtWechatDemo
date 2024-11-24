#ifndef _TTipWidget_H_
#define _TTipWidget_H_

#include <QWidget>
#include <QLabel>
#include <QTimer>

class TTipWidget :public QLabel
{
    Q_OBJECT

public:
    static TTipWidget *Instance();
    static void ExitInstance();
    void SetMesseage(const QString &strMessage, const QPoint *pPoint=nullptr);

private:
    TTipWidget();
    ~TTipWidget();

    void OnTimer();
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    static TTipWidget *m_pTipWidget;
    QWidget *m_pParent;
    QTimer  *m_pTimer;
    bool     m_bEnter;
    int      m_nTransparent;
};

#define AutoTip TTipWidget::Instance()

#endif // _TTipWidget_H_
