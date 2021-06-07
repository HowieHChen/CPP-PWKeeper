#ifndef SIGNINPAGE_H
#define SIGNINPAGE_H

#include <QWidget>
#include "basepage.h"
#include "userprofile.h"
#include "signuppage.h"
#include "forgetpwpage.h"
#include "mainpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SignInPage; }
QT_END_NAMESPACE

class SignInPage : public BasePage
{
    Q_OBJECT
    UserProfile *currentUser;
    SignUpPage *newSignUp;
    ForgetPWPage *newForget;
    MainPage *newMain;

public:
    SignInPage(QWidget *parent = nullptr);
    ~SignInPage();

    //加载设置
    void loadingSettings();
signals:

private slots:
    //登录槽函数
    void on_pushButton_SignIn_clicked();

    //注册用户槽函数
    void on_pushButton_SignUp_clicked();

    //重置密码槽函数
    void on_pushButton_ForgetPW_clicked();

    //返回登录界面
    void on_showSignInAction();

    //注销后返回登录界面
    void on_signOutShowSignIn();

    //注册用户
    //bool&返回注册结果,int&返回失败原因
    void on_doSignUp(QString,QString,QString,bool&,int&);

    //重置密码
    //bool&返回重置结果,int&返回失败原因
    void on_doForgetPW(QString,QString,QString,bool&,int&);

private:
    Ui::SignInPage *ui;
};
#endif // SIGNINPAGE_H
