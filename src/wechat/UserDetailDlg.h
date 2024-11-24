#ifndef CUSERDETAILDLG_H
#define CUSERDETAILDLG_H

#include <QWidget>
#include <QtWidgets>

class CPushButtonEx;

class CUserDetailDlg : public QWidget
{
    Q_OBJECT
public:
    explicit CUserDetailDlg(QWidget *parent = 0);
    ~CUserDetailDlg();

public:
    void SetUserInfo(QString strName, QString ico);

private:
    void CreateAllCtrls();
    void InitCtrls();
    void Relayout();

    bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void OnBtnUserIconClicked();

private:
    QWidget *m_widgetTop;
    CPushButtonEx *m_btnUserIcon;
    QLabel *m_lblUserName;
    QLabel *m_lblSex;

    QLabel *m_lblSeparatorLine;

    QLabel *m_lblTel;
    QLabel *m_lblTelValue;
    QLabel *m_lblMail;
    QLabel *m_lblMailValue;
    QLabel *m_lblDepartment;
    QLabel *m_lblDepartmentValue;

    CPushButtonEx *m_btnSendMsg;

    QWidget *m_pAvatar;
    QLabel *m_lblAvatar;
};

#endif // CUSERDETAILDLG_H
