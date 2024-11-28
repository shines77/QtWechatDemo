#ifndef CDATAMGRPANEL_H
#define CDATAMGRPANEL_H

#include <QWidget>
#include <QtWidgets>

class AppreciateDlg;

class CDataMgrPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CDataMgrPanel(QWidget *parent = 0);

private:
    void CreateAllCtrls();
    void InitCtrls();
    void InitTopPic();
    void InitEcharts();
    void Relayout();

    void resizeEvent(QResizeEvent *event);

public slots:
    void OnBtnAppreciateClicked();

private:
    QScrollArea *m_pScrollArea;
    QWidget *m_widgetContent;
    QWidget *m_widgetTopPic;
    QWidget *m_widgetCards;
    AppreciateDlg *m_pAppreciateDlg;
};

#endif // CDATAMGRPANEL_H
