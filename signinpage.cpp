#include "signinpage.h"
#include "ui_signinpage.h"

SignInPage::SignInPage(QWidget *parent)
    : BasePage(parent)
    , ui(new Ui::SignInPage)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
    SignInPage::setTabOrder(ui->lineEdit_Name,ui->lineEdit_Password);
    SignInPage::setTabOrder(ui->lineEdit_Password,ui->lineEdit_Name);
    //连接用户管理服务
    currentUser = new UserProfile;
    currentUser->readProfile();
    loadingSettings();
}

SignInPage::~SignInPage()
{
    delete ui;
}

//加载设置
void SignInPage::loadingSettings()
{
    if(currentUser->saveLastName)
    {
        ui->lineEdit_Name->setText(currentUser->getLastName());
    }
    else
    {
        ui->lineEdit_Name->clear();
    }
    if(currentUser->saveLastPassword)
    {
        ui->lineEdit_Password->setText(currentUser->getLastPassword());
    }
    else
    {
        ui->lineEdit_Password->clear();
    }
}

//登录槽函数
void SignInPage::on_pushButton_SignIn_clicked()
{
    QString tName = ui->lineEdit_Name->text();
    QString tPassword = ui->lineEdit_Password->text();
    //对用户行为进行初步过滤
    if(tName==""||
       tPassword=="")
    {
        ui->lineEdit_Name->clear();
        ui->lineEdit_Password->clear();
        ui->lineEdit_Name->setPlaceholderText("请输入完整信息");
        return;
    }
    if(!currentUser->userExist(tName))
    {
        ui->lineEdit_Name->clear();
        ui->lineEdit_Password->clear();
        ui->lineEdit_Name->setPlaceholderText("用户不存在");
        return;
    }
    //尝试登陆
    if(currentUser->userSignIn(tName,tPassword))
    {
        ui->lineEdit_Name->setPlaceholderText("用户名");
        delete currentUser;
        currentUser = NULL;
        this->newMain = new MainPage;
        connect(newMain,SIGNAL(mSignalShowSignIN()),this,SLOT(on_signOutShowSignIn()));
        newMain->show();
        this->close();
        //登陆成功跳转主界面
    }
    else
    {
        ui->lineEdit_Name->clear();
        ui->lineEdit_Password->clear();
        ui->lineEdit_Name->setPlaceholderText("密码错误");
    }
}

//注册用户槽函数
void SignInPage::on_pushButton_SignUp_clicked()
{
    this->newSignUp = new SignUpPage;
    connect(newSignUp,SIGNAL(SignalShowSignIN()),this,SLOT(on_showSignInAction()));
    connect(newSignUp,SIGNAL(SignalSignUp(QString,QString,QString,bool&,int&)),this,SLOT(on_doSignUp(QString,QString,QString,bool&,int&)));
    newSignUp->show();
    this->hide();
}

//重置密码槽函数
void SignInPage::on_pushButton_ForgetPW_clicked()
{
    this->newForget = new ForgetPWPage;
    connect(newForget,SIGNAL(fSignalShowSignIN()),this,SLOT(on_showSignInAction()));
    connect(newForget,SIGNAL(SignalForgetPW(QString,QString,QString,bool&,int&)),this,SLOT(on_doForgetPW(QString,QString,QString,bool&,int&)));
    newForget->show();
    this->hide();
}

//返回登录界面
void SignInPage::on_showSignInAction()
{
    this->show();
}

//注销后返回登录界面
void SignInPage::on_signOutShowSignIn()
{
    this->show();
    currentUser = new UserProfile;
    currentUser->readProfile();
    loadingSettings();
    //注销用户后重新连接用户管理服务
}

//注册用户
void SignInPage::on_doSignUp(QString tName,QString tPassword,QString tMail,bool &tResult,int &tReasonF)
{
    //qDebug()<<"try call userSignUp";
    tResult=false;
    tReasonF=0;
    if(currentUser->userExist(tName))
    {
        tReasonF=1;
        return;
    }
    if(currentUser->userSignUp(tName,tMail,tPassword))
    {
        tResult=true;
        tReasonF=2;
        loadingSettings();
    }
}

//重置密码
void SignInPage::on_doForgetPW(QString tName,QString tNewPassword,QString tMail,bool &tResult,int &tReasonF)
{
    //qDebug()<<"try call userForgetPW";
    tResult=false;
    tReasonF=0;
    if(!currentUser->userExist(tName))
    {
        tReasonF=1;
        return;
    }
    if(!currentUser->mailCheck(tName,tMail))
    {
        tReasonF=2;
        return;
    }
    if(currentUser->userForgetPW(tName,tMail,tNewPassword))
    {
        tResult=true;
        tReasonF=3;
        loadingSettings();
    }
}

