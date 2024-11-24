#ifndef USERPROFILES_H
#define USERPROFILES_H

#include <QWidget>

#include "BoderPanel.h"

namespace Ui {
class UserProfiles;
}

class CMaskPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CMaskPanel(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
};

class UserProfiles : public BoderPanel
{
    Q_OBJECT
public:
    explicit UserProfiles(QWidget *parent = nullptr);
    ~UserProfiles();

private slots:
    void on_pushButton_clicked();

private:
    void CreateAllCtrls();
    void InitCtrls();
    void Relayout();

private:
    Ui::UserProfiles *ui;
    QMovie *m_pMovie;
};

#endif // USERPROFILES_H
