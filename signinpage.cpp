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
    initPage();
    currentUser = new UserProfile;
    currentUser->readAllUser();
}

SignInPage::~SignInPage()
{
    delete ui;
}


void SignInPage::on_pushButton_SignIn_clicked()
{
    QString tName = ui->lineEdit_Name->text();
    QString tPassword = ui->lineEdit_Password->text();
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
    if(currentUser->userSignIn(tName,tPassword))
    {
        recyclePage();
        this->newMain = new MainPage;
        connect(newMain,SIGNAL(mSignalShowSignIN()),this,SLOT(on_signOutShowSignIn()));
        //connect(newForget,SIGNAL(SignalForgetPW(QString,QString,QString,bool&,int&)),this,SLOT(on_doForgetPW(QString,QString,QString,bool&,int&)));
        newMain->show();
        this->hide();
    }
    else
    {
        ui->lineEdit_Name->clear();
        ui->lineEdit_Password->clear();
        ui->lineEdit_Name->setPlaceholderText("密码错误");
    }
}


void SignInPage::on_pushButton_SignUp_clicked()
{
    this->newSignUp = new SignUpPage;
    connect(newSignUp,SIGNAL(SignalShowSignIN()),this,SLOT(on_showSignInAction()));
    connect(newSignUp,SIGNAL(SignalSignUp(QString,QString,QString,bool&,int&)),this,SLOT(on_doSignUp(QString,QString,QString,bool&,int&)));
    newSignUp->show();
    //this->hide();
}


void SignInPage::on_pushButton_ForgetPW_clicked()
{
    this->newForget = new ForgetPWPage;
    connect(newForget,SIGNAL(fSignalShowSignIN()),this,SLOT(on_showSignInAction()));
    connect(newForget,SIGNAL(SignalForgetPW(QString,QString,QString,bool&,int&)),this,SLOT(on_doForgetPW(QString,QString,QString,bool&,int&)));
    newForget->show();
    //this->hide();
}

void SignInPage::on_showSignInAction()
{
    this->show();
}

void SignInPage::on_signOutShowSignIn()
{
    this->show();
    initPage();
}

void SignInPage::on_doSignUp(QString tName,QString tPassword,QString tMail,bool &tResult,int &tReasonF)
{
    qDebug()<<"try call userSignUp";
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
    }
}

void SignInPage::on_doForgetPW(QString tName,QString tNewPassword,QString tMail,bool &tResult,int &tReasonF)
{
    tResult=false;
    tReasonF=0;
    if(!currentUser->userExist(tName))
    {
        tReasonF=1;
        return;
    }
    if(currentUser->mailCheck(tName,tMail))
    {
        tReasonF=2;
        return;
    }
    if(currentUser->userForgetPW(tName,tMail,tNewPassword))
    {
        tResult=true;
        tReasonF=3;
    }
}
