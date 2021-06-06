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

    void loadingSettings();
signals:

private slots:
    void on_pushButton_SignIn_clicked();

    void on_pushButton_SignUp_clicked();

    void on_pushButton_ForgetPW_clicked();

    void on_showSignInAction();
    void on_signOutShowSignIn();
    void on_doSignUp(QString,QString,QString,bool&,int&);
    void on_doForgetPW(QString,QString,QString,bool&,int&);
private:
    Ui::SignInPage *ui;
};
#endif // SIGNINPAGE_H
