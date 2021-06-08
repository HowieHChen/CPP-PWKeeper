#include "forgetpwpage.h"
#include "ui_forgetpwpage.h"

ForgetPWPage::ForgetPWPage(QWidget *parent) :
    BasePage(parent),
    ui(new Ui::ForgetPWPage)
{
    ui->setupUi(this);
    this->setWindowTitle("忘记密码");
    this->setWindowModality(Qt::ApplicationModal);
    //设置Tab键的按下顺序
    ForgetPWPage::setTabOrder(ui->lineEdit_fUserName,ui->lineEdit_fMail);
    ForgetPWPage::setTabOrder(ui->lineEdit_fMail,ui->lineEdit_fNewPassword);
    ForgetPWPage::setTabOrder(ui->lineEdit_fNewPassword,ui->lineEdit_fRepeatPassword);
    ForgetPWPage::setTabOrder(ui->lineEdit_fRepeatPassword,ui->lineEdit_fUserName);
}

ForgetPWPage::~ForgetPWPage()
{
    delete ui;
}

//返回登录界面槽函数
void ForgetPWPage::on_pushButton_Back_clicked()
{
    emit fSignalShowSignIN();
    this->close();
}

//重置密码槽函数
void ForgetPWPage::on_pushButton_ResetPW_clicked()
{
    resultSignUp = false;
    QString tTip;
    QString tName = ui->lineEdit_fUserName->text();
    QString tPassword = ui->lineEdit_fNewPassword->text();
    QString tRepeatPassowrd = ui->lineEdit_fRepeatPassword->text();
    QString tMail=ui->lineEdit_fMail->text();
    //对用户行为进行初步过滤
    if(tName==""||
       tMail==""||
       tPassword==""||
       tRepeatPassowrd=="")
    {
        ui->lineEdit_fUserName->clear();
        ui->lineEdit_fMail->clear();
        ui->lineEdit_fNewPassword->clear();
        ui->lineEdit_fRepeatPassword->clear();
        //生成对话框提示
        newForgetPWDialog = new BaseDialog;
        newForgetPWDialog->createDialog(1,"重置失败","请填写完整信息");
        newForgetPWDialog->show();
        return;
    }
    if(tPassword!=tRepeatPassowrd)
    {
        ui->lineEdit_fNewPassword->clear();
        ui->lineEdit_fRepeatPassword->clear();
        //生成对话框提示
        newForgetPWDialog = new BaseDialog;
        newForgetPWDialog->createDialog(1,"重置失败","两次输入的密码不一致");
        newForgetPWDialog->show();
        return;
    }
    //尝试重置密码
    emit SignalForgetPW(tName,tPassword,tMail,resultSignUp,reasonF);
    if(resultSignUp==false)
    {
        ui->lineEdit_fUserName->clear();
        ui->lineEdit_fMail->clear();
        ui->lineEdit_fNewPassword->clear();
        ui->lineEdit_fRepeatPassword->clear();
        if(reasonF==1)
        {
            tTip = "用户不存在";
        }
        else if(reasonF==2)
        {
            tTip = "邮箱不匹配";
        }
        else
        {
            tTip = "密码重置失败请重试";
        }
        newForgetPWDialog = new BaseDialog;
        newForgetPWDialog->createDialog(1,"重置失败",tTip);
        newForgetPWDialog->show();
        return;
    }
    this->close();
}
