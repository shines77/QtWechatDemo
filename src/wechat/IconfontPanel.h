#ifndef CICONFONTPANEL_H
#define CICONFONTPANEL_H

#include <QWidget>
#include <QScrollArea>

class CIconFontPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CIconFontPanel(QWidget *parent = 0);

private slots:
    void OnBtnClicked();

private:
    void CreateAllCtrls();
    void InitCtrls();
    void InitSolts();
    void Relayout();
    void ParseJsonFile();

private:
    QScrollArea *m_pScrollArea;
    QWidget *m_widgetContent;
};

#endif // CICONFONTPANEL_H
