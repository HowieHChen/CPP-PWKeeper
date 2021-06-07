#include "signuppage.h"
#include "ui_signuppage.h"

SignUpPage::SignUpPage(QWidget *parent) :
    BasePage(parent),
    ui(new Ui::SignUpPage)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");
    //设置Tab键的按下顺序
    SignUpPage::setTabOrder(ui->lineEdit_Name,ui->lineEdit_Password);
    SignUpPage::setTabOrder(ui->lineEdit_Password,ui->lineEdit_Mail);
    SignUpPage::setTabOrder(ui->lineEdit_Mail,ui->lineEdit_Name);
}

SignUpPage::~SignUpPage()
{
    delete ui;
}

//返回登录界面槽函数
void SignUpPage::on_pushButton_BackSignIn_clicked()
{
    emit SignalShowSignIN();
    this->close();
}

//注册用户槽函数
void SignUpPage::on_pushButton_DoSignUp_clicked()
{
    resultSignUp = false;
    QString tName = ui->lineEdit_Name->text();
    QString tPassword = ui->lineEdit_Password->text();
    QString tMail=ui->lineEdit_Mail->text();
    //对用户行为进行初步过滤
    if(tName==""||
       tMail==""||
       tPassword=="")
    {
        ui->lineEdit_Name->clear();
        ui->lineEdit_Mail->clear();
        ui->lineEdit_Password->clear();
        ui->lineEdit_Name->setPlaceholderText("请填写完整信息");
        return;
    }
    //尝试注册用户
    emit SignalSignUp(tName,tPassword,tMail,resultSignUp,reasonF);
    if(resultSignUp==false)
    {
        ui->lineEdit_Name->clear();
        ui->lineEdit_Mail->clear();
        ui->lineEdit_Password->clear();
        if(reasonF==1)
        {
            ui->lineEdit_Name->setPlaceholderText("用户已存在");
        }
        else
        {
            ui->lineEdit_Name->setPlaceholderText("注册失败请重试");
        }
        return;
    }
    this->close();
}

