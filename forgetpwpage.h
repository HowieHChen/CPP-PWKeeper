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
    //返回登录界面
    void fSignalShowSignIN();

    //所有用户操作均有SignInPage完成，发出重置密码信号给SignInPage
    //bool&返回重置结果,int&返回失败原因
    void SignalForgetPW(QString,QString,QString,bool&,int&);

private slots:
    //返回登录界面槽函数
    void on_pushButton_Back_clicked();

    //重置密码槽函数
    void on_pushButton_ResetPW_clicked();

private:
    Ui::ForgetPWPage *ui;

    //记录重置结果
    bool resultSignUp=false;

    //存储失败原因：0未知，1用户不存在，2邮箱不一致，3未失败
    int reasonF = 0;
};

#endif // FORGETPWPAGE_H
