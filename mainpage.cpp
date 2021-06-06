#include "mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent) :
    BasePage(parent),
    ui(new Ui::MainPage)
{
    initPage();
    mainUser = new UserProfile;
    mainUser->readProfile();
    SwitchControl1 = new SwitchControl();
    SwitchControl2 = new SwitchControl();
    SwitchControl3 = new SwitchControl();
    ui->setupUi(this);
    getUserProfile();
    mainPWM = new PasswordManage(userName);
    mainPWM->readAllLabel();
    refreshLabelList();
    largeTitle();
    refreshCloseDirectly(closeDirectly);
    this->setWindowTitle("PWKeeper");
    ui->stackedWidget->setCurrentWidget(ui->page_view);
    ui->container_saveUser->addWidget(SwitchControl1);
    ui->container_savePassword->addWidget(SwitchControl2);
    ui->container_closeDirectly->addWidget(SwitchControl3);
    connect(SwitchControl1,SIGNAL(toggled(bool)),this,SLOT(switchcontrol1_clicked(bool)));
    connect(SwitchControl2,SIGNAL(toggled(bool)),this,SLOT(switchcontrol2_clicked(bool)));
    connect(SwitchControl3,SIGNAL(toggled(bool)),this,SLOT(switchcontrol3_clicked(bool)));
    refreshSwitchControl();
    setTheTabOrder();
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::getUserProfile()
{
    userName = mainUser->getLastName();
    userPassword = mainUser->getLastPassword();
    userMail = mainUser->getLastMail();
    saveLastName = mainUser->saveLastName;
    saveLastPassword = mainUser->saveLastPassword;
    closeDirectly = mainUser->closeDirectly;
    qDebug()<<"UserInfo:"<<userName<<" "<<userPassword<<" "<<userMail;
    qDebug()<<"Settings:"<<saveLastName<<" "<<saveLastPassword<<" "<<closeDirectly;
}
void MainPage::saveUserProfile()
{
    mainUser->saveLastName=saveLastName;
    mainUser->saveLastPassword=saveLastPassword;
    mainUser->closeDirectly=closeDirectly;
    mainUser->saveSettings();
}

void MainPage::refreshSwitchControl()
{
    SwitchControl1->setToggle(saveLastName);
    SwitchControl2->setToggle(saveLastPassword);
    SwitchControl3->setToggle(closeDirectly);
}

void MainPage::refreshLabelList()
{
    mainPWM->readAllLabel();
    ui->listWidget_allLabel->clear();
    ui->listWidget_allLabel->addItems(mainPWM->getAllLabel());
}

void MainPage::setTheTabOrder()
{
    //查询页
    MainPage::setTabOrder(ui->lineEdit_11label,ui->lineEdit_12name);
    MainPage::setTabOrder(ui->lineEdit_12name,ui->lineEdit_13password);
    MainPage::setTabOrder(ui->lineEdit_13password,ui->lineEdit_14target);
    MainPage::setTabOrder(ui->lineEdit_14target,ui->lineEdit_15others);
    MainPage::setTabOrder(ui->lineEdit_15others,ui->lineEdit_11label);
    //添加页
    MainPage::setTabOrder(ui->lineEdit_21label,ui->lineEdit_22name);
    MainPage::setTabOrder(ui->lineEdit_22name,ui->lineEdit_23password);
    MainPage::setTabOrder(ui->lineEdit_23password,ui->lineEdit_24target);
    MainPage::setTabOrder(ui->lineEdit_24target,ui->lineEdit_25others);
    MainPage::setTabOrder(ui->lineEdit_25others,ui->lineEdit_21label);
}

void MainPage::on_pushButton_view_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_view);
}


void MainPage::on_pushButton_add_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_add);
}


void MainPage::on_pushButton_out_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_out);
}


void MainPage::on_pushButton_signout_clicked()
{
    customDialog = new BaseDialog;
    customDialog->createDialog(0,"确定要注销吗？","注销将退出当前登陆账号");
    connect(customDialog,SIGNAL(buttonCancel_clicked()),this,SLOT(dialog_notify()));
    connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_signoutOK()));
    customDialog->setWindowModality(Qt::ApplicationModal);
    customDialog->show();
}


void MainPage::on_pushButton_settings_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->page_settings);
}

void MainPage::switchcontrol1_clicked(bool bChecked)
{
    saveLastName = bChecked;
    if(!saveLastName)
    {
        saveLastPassword=0;
        refreshSwitchControl();
    }
    saveUserProfile();
    qDebug()<<saveLastName;
}

void MainPage::switchcontrol2_clicked(bool bChecked)
{
    saveLastPassword = bChecked;
    if(saveLastPassword)
    {
        saveLastName=1;
        refreshSwitchControl();
    }
    saveUserProfile();
}

void MainPage::switchcontrol3_clicked(bool bChecked)
{
    closeDirectly = bChecked;
    refreshCloseDirectly(closeDirectly);
    saveUserProfile();
}

void MainPage::on_pushButton_additem_clicked()
{
    QString tlabel = ui->lineEdit_21label->text();
    QString tname = ui->lineEdit_22name->text();
    QString tpassword = ui->lineEdit_23password->text();
    QString ttarget = ui->lineEdit_24target->text();
    QString tothers = ui->lineEdit_25others->text();
    if(tlabel == "")
    {
        ui->lineEdit_21label->setPlaceholderText("标签不能为空");
        return;
    }
    if(tname == "")
    {
        ui->lineEdit_22name->setPlaceholderText("用户名不能为空");
        return;
    }
    if(tpassword == "")
    {
        ui->lineEdit_23password->setPlaceholderText("密码不能为空");
        return;
    }
    if(mainPWM->labelExist(tlabel))
    {
        ui->lineEdit_21label->setPlaceholderText("标签已存在");
        return;
    }
    mainPWM->addNewLabel(tlabel,tname,tpassword,ttarget,tothers);
    ui->lineEdit_21label->clear();
    ui->lineEdit_22name->clear();
    ui->lineEdit_23password->clear();
    ui->lineEdit_24target->clear();
    ui->lineEdit_25others->clear();
    refreshLabelList();
    customDialog = new BaseDialog;
    customDialog->createDialog(1,"添加成功","该项目已经添加到您的密码本");
    connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_notify()));
    customDialog->setWindowModality(Qt::ApplicationModal);
    customDialog->show();
}


void MainPage::on_pushButton_createPassword_clicked()
{
    QString randPW = mainPWM->getRandomPW(6,18);
    ui->lineEdit_23password->setText(randPW);
}


void MainPage::on_pushButton_save_clicked()
{
    QString tlabel = ui->lineEdit_11label->text();
    QString tname = ui->lineEdit_12name->text();
    QString tpassword = ui->lineEdit_13password->text();
    QString ttarget = ui->lineEdit_14target->text();
    QString tothers = ui->lineEdit_15others->text();
    if(tlabel == "")
    {
        ui->lineEdit_21label->setPlaceholderText("标签不能为空");
        return;
    }
    if(tname == "")
    {
        ui->lineEdit_22name->setPlaceholderText("用户名不能为空");
        return;
    }
    if(tpassword == "")
    {
        ui->lineEdit_23password->setPlaceholderText("密码不能为空");
        return;
    }
    mainPWM->editSelectedLabel(tlabel,tname,tpassword,ttarget,tothers);
    refreshLabelList();
    customDialog = new BaseDialog;
    customDialog->createDialog(1,"保存成功","该项目的信息已经更新");
    connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_notify()));
    customDialog->setWindowModality(Qt::ApplicationModal);
    customDialog->show();
}


void MainPage::on_pushButton_delete_clicked()
{
    QList sl = ui->listWidget_allLabel->selectedItems();
    if(sl.isEmpty())
    {
        return;
    }
    customDialog = new BaseDialog;
    customDialog->createDialog(0,"确定要删除吗？","将会删除此项目，此操作不可撤销");
    connect(customDialog,SIGNAL(buttonCancel_clicked()),this,SLOT(dialog_notify()));
    connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_deleteOK()));
    customDialog->setWindowModality(Qt::ApplicationModal);
    customDialog->show();
}


void MainPage::on_listWidget_allLabel_itemClicked(QListWidgetItem *item)
{
    qDebug()<<item->text();
    QString tLabel=item->text();
    mainPWM->readSelectedLabel(tLabel);
    ui->lineEdit_11label->setText(mainPWM->getNowLabel());
    ui->lineEdit_12name->setText(mainPWM->getNowName());
    ui->lineEdit_13password->setText(mainPWM->getNowPassword());
    ui->lineEdit_14target->setText(mainPWM->getNowTarget());
    ui->lineEdit_15others->setText(mainPWM->getNowOthers());
}

void MainPage::dialog_deleteOK()
{
    mainPWM->deleSelectedLabel(mainPWM->getNowLabel());
    ui->lineEdit_11label->clear();
    ui->lineEdit_12name->clear();
    ui->lineEdit_13password->clear();
    ui->lineEdit_14target->clear();
    ui->lineEdit_15others->clear();
    refreshLabelList();
    customDialog = new BaseDialog;
    customDialog->createDialog(1,"删除成功","该项目已从您的密码本中移除");
    connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_notify()));
    customDialog->setWindowModality(Qt::ApplicationModal);
    customDialog->show();
}

void MainPage::dialog_signoutOK()
{
    emit mSignalShowSignIN();
    recyclePage();
    saveUserProfile();
    delete mainUser;
    mainUser = NULL;
    delete customDialog;
    customDialog = NULL;
    this->hide();
}


void MainPage::dialog_notify()
{
    delete customDialog;
    customDialog = NULL;
}

void MainPage::on_pushButton_output_clicked()
{
    QString fileName = ui->lineEdit_fileName->text();
    if(fileName == "")
    {
        ui->lineEdit_fileName->setPlaceholderText("请输入文件名");
        return;
    }
    QString filePath = QFileDialog::getExistingDirectory(this,"请选择导出的路径",QDir::homePath());
    QString fullName = filePath + "/" + fileName + ".txt";
    if(mainPWM->outputAllInfo(fullName))
    {
        customDialog = new BaseDialog;
        customDialog->createDialog(1,"导出成功","文件" + fileName + ".txt 已保存至" + '\n' + filePath);
        connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_notify()));
        customDialog->setWindowModality(Qt::ApplicationModal);
        customDialog->show();
    }
    else
    {
        customDialog = new BaseDialog;
        customDialog->createDialog(1,"导出失败","文件" + fileName + "可能已存在" + '\n' + "请尝试更换文件名");
        connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_notify()));
        customDialog->setWindowModality(Qt::ApplicationModal);
        customDialog->show();
    }
}

