#ifndef APPRECIATEDLG_H
#define APPRECIATEDLG_H

#include <QWidget>

#include "BaseDlg.h"

namespace Ui {
class AppreciateDlg;
}

class AppreciateDlg : public CBaseDlg
{
    Q_OBJECT

public:
    explicit AppreciateDlg(QWidget *parent = 0);
    ~AppreciateDlg();

private:
    void CreateAllCtrls();
    void InitCtrls();
    void Relayout();

private:
    Ui::AppreciateDlg *ui;
};

#endif // APPRECIATEDLG_H
