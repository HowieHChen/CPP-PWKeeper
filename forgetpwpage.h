#ifndef FORGETPWPAGE_H
#define FORGETPWPAGE_H

#include <QWidget>
#include "basepage.h"

namespace Ui {
class ForgetPWPage;
}

class ForgetPWPage : public BasePage
{
    Q_OBJECT

public:
    explicit ForgetPWPage(QWidget *parent = nullptr);
    ~ForgetPWPage();
signals:
    void fSignalShowSignIN();
    void SignalForgetPW(QString,QString,QString,bool&,int&);
private slots:
    void on_pushButton_Back_clicked();

    void on_pushButton_ResetPW_clicked();

private:
    Ui::ForgetPWPage *ui;
    bool resultSignUp=false;
    //reasonF存储失败原因：0未知，1用户不存在，2邮箱不一致，3未失败
    int reasonF = 0;
};

#endif // FORGETPWPAGE_H
