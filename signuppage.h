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
    void SignalShowSignIN();
    void SignalSignUp(QString,QString,QString,bool&,int&);
private slots:
    void on_pushButton_BackSignIn_clicked();

    void on_pushButton_DoSignUp_clicked();

private:
    Ui::SignUpPage *ui;
    bool resultSignUp=false;
    //reasonF存储失败原因：0未知，1用户已存在，2未失败
    int reasonF = 0;
};

#endif // SIGNUPPAGE_H
