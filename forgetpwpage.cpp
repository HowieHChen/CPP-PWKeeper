#include "forgetpwpage.h"
#include "ui_forgetpwpage.h"

ForgetPWPage::ForgetPWPage(QWidget *parent) :
    BasePage(parent),
    ui(new Ui::ForgetPWPage)
{
    ui->setupUi(this);
    this->setWindowTitle("忘记密码");
    ForgetPWPage::setTabOrder(ui->lineEdit_fUserName,ui->lineEdit_fMail);
    ForgetPWPage::setTabOrder(ui->lineEdit_fMail,ui->lineEdit_fNewPassword);
    ForgetPWPage::setTabOrder(ui->lineEdit_fNewPassword,ui->lineEdit_fRepeatPassword);
    ForgetPWPage::setTabOrder(ui->lineEdit_fRepeatPassword,ui->lineEdit_fUserName);
}

ForgetPWPage::~ForgetPWPage()
{
    delete ui;
}

void ForgetPWPage::on_pushButton_Back_clicked()
{
    emit fSignalShowSignIN();
    this->close();
}


void ForgetPWPage::on_pushButton_ResetPW_clicked()
{
    bool tResult = resultSignUp;
    QString tName = ui->lineEdit_fUserName->text();
    QString tPassword = ui->lineEdit_fNewPassword->text();
    QString tRepeatPassowrd = ui->lineEdit_fRepeatPassword->text();
    QString tMail=ui->lineEdit_fMail->text();
    if(tName==""||
       tMail==""||
       tPassword==""||
       tRepeatPassowrd=="")
    {
        ui->lineEdit_fUserName->clear();
        ui->lineEdit_fMail->clear();
        ui->lineEdit_fNewPassword->clear();
        ui->lineEdit_fRepeatPassword->clear();
        ui->lineEdit_fUserName->setPlaceholderText("请填写完整信息");
        return;
    }
    if(tPassword!=tRepeatPassowrd)
    {
        ui->lineEdit_fNewPassword->clear();
        ui->lineEdit_fRepeatPassword->clear();
        ui->lineEdit_fNewPassword->setPlaceholderText("两次输入的密码不一致");
        return;
    }
    emit SignalForgetPW(tName,tPassword,tMail,tResult,reasonF);
    if(tResult==false)
    {
        ui->lineEdit_fUserName->clear();
        ui->lineEdit_fMail->clear();
        ui->lineEdit_fNewPassword->clear();
        ui->lineEdit_fRepeatPassword->clear();
        if(reasonF==1)
        {
            ui->lineEdit_fUserName->setPlaceholderText("用户不存在");
        }
        else if(reasonF==2)
        {
            ui->lineEdit_fUserName->setPlaceholderText("邮箱错误");
        }
        else
        {
            ui->lineEdit_fUserName->setPlaceholderText("密码重置失败请重试");
        }
        return;
    }
    this->close();
}

