#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include <QWidget>
#include "basepage.h"

namespace Ui {
class SignUpPage;
}

class SignUpPage : public BasePage
{
    Q_OBJECT

public:
    explicit SignUpPage(QWidget *parent = nullptr);
    ~SignUpPage();
signals:
    //返回登录界面
    void SignalShowSignIN();

    //所有用户操作均有SignInPage完成，发出注册用户信号给SignInPage
    //bool&返回注册结果,int&返回失败原因
    void SignalSignUp(QString,QString,QString,bool&,int&);

private slots:
    //返回登录界面槽函数
    void on_pushButton_BackSignIn_clicked();

    //注册用户槽函数
    void on_pushButton_DoSignUp_clicked();

private:
    Ui::SignUpPage *ui;
    //记录注册结果
    bool resultSignUp=false;

    //存储失败原因：0未知，1用户已存在，2未失败
    int reasonF = 0;
};

#endif // SIGNUPPAGE_H
