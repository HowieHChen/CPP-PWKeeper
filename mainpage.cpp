#include "mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent) :
    BasePage(parent),
    ui(new Ui::MainPage)
{
    initPage();
    //连接用户管理服务
    mainUser = new UserProfile;
    mainUser->readProfile();
    SwitchControl1 = new SwitchControl();
    SwitchControl2 = new SwitchControl();
    SwitchControl3 = new SwitchControl();
    ui->setupUi(this);
    getUserProfile();
    //连接密码管理服务
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

//读取用户信息和设置
void MainPage::getUserProfile()
{
    userName = mainUser->getLastName();
    userPassword = mainUser->getLastPassword();
    userMail = mainUser->getLastMail();
    saveLastName = mainUser->saveLastName;
    saveLastPassword = mainUser->saveLastPassword;
    closeDirectly = mainUser->closeDirectly;
    //qDebug()<<"UserInfo:"<<userName<<" "<<userPassword<<" "<<userMail;
    //qDebug()<<"Settings:"<<saveLastName<<" "<<saveLastPassword<<" "<<closeDirectly;
}

//保存用户设置
void MainPage::saveUserProfile()
{
    mainUser->saveLastName=saveLastName;
    mainUser->saveLastPassword=saveLastPassword;
    mainUser->closeDirectly=closeDirectly;
    mainUser->saveSettings();
}

//刷新开关状态
void MainPage::refreshSwitchControl()
{
    SwitchControl1->setToggle(saveLastName);
    SwitchControl2->setToggle(saveLastPassword);
    SwitchControl3->setToggle(closeDirectly);
}

//刷新密码列表
void MainPage::refreshLabelList()
{
    mainPWM->readAllLabel();
    ui->listWidget_allLabel->clear();
    ui->listWidget_allLabel->addItems(mainPWM->getAllLabel());
}

//设置Tab键的按下顺序
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

//查询页面槽函数
void MainPage::on_pushButton_view_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_view);
}

//添加页面槽函数
void MainPage::on_pushButton_add_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_add);
}

//导出页面槽函数
void MainPage::on_pushButton_out_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_out);
}

//注销槽函数
void MainPage::on_pushButton_signout_clicked()
{
    //生成对话框，跳转到对应槽函数
    customDialog = new BaseDialog;
    customDialog->createDialog(0,"确定要注销吗？","注销将退出当前登陆账号");
    connect(customDialog,SIGNAL(buttonCancel_clicked()),this,SLOT(dialog_notify()));
    connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_signoutOK()));
    customDialog->setWindowModality(Qt::ApplicationModal);
    customDialog->show();
}

//设置页面槽函数
void MainPage::on_pushButton_settings_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->page_settings);
}

//开关槽函数
void MainPage::switchcontrol1_clicked(bool bChecked)
{
    saveLastName = bChecked;
    if(!saveLastName)
    {
        //不记住用户时也将不记住密码
        saveLastPassword=0;
        refreshSwitchControl();
    }
    saveUserProfile();
    //qDebug() << "saveName:" << saveLastName;
}

void MainPage::switchcontrol2_clicked(bool bChecked)
{
    saveLastPassword = bChecked;
    if(saveLastPassword)
    {
        //记住密码时也将记住用户
        saveLastName=1;
        refreshSwitchControl();
    }
    saveUserProfile();
    //qDebug() << "savePassword:" << saveLastPassword;
}

void MainPage::switchcontrol3_clicked(bool bChecked)
{
    closeDirectly = bChecked;
    //切换关闭按钮功能
    refreshCloseDirectly(closeDirectly);
    saveUserProfile();
    //qDebug() << "closeDirectly:" << closeDirectly;
}

//添加密码槽函数
void MainPage::on_pushButton_additem_clicked()
{
    QString tlabel = ui->lineEdit_21label->text();
    QString tname = ui->lineEdit_22name->text();
    QString tpassword = ui->lineEdit_23password->text();
    QString ttarget = ui->lineEdit_24target->text();
    QString tothers = ui->lineEdit_25others->text();
    //对用户行为进行初步过滤
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
        ui->lineEdit_21label->clear();
        return;
    }
    //尝试添加
    mainPWM->addNewLabel(tlabel,tname,tpassword,ttarget,tothers);
    ui->lineEdit_21label->clear();
    ui->lineEdit_22name->clear();
    ui->lineEdit_23password->clear();
    ui->lineEdit_24target->clear();
    ui->lineEdit_25others->clear();
    ui->lineEdit_21label->setPlaceholderText("标签");
    ui->lineEdit_22name->setPlaceholderText("用户名");
    ui->lineEdit_23password->setPlaceholderText("密码");
    refreshLabelList();
    //生成对话框提示
    customDialog = new BaseDialog;
    customDialog->createDialog(1,"添加成功","该项目已经添加到您的密码本");
    connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_notify()));
    customDialog->setWindowModality(Qt::ApplicationModal);
    customDialog->show();
}

//生成随机密码槽函数
void MainPage::on_pushButton_createPassword_clicked()
{
    QString randPW = mainPWM->getRandomPW(6,18);
    ui->lineEdit_23password->setText(randPW);
}

//保存修改槽函数
void MainPage::on_pushButton_save_clicked()
{
    QString tlabel = ui->lineEdit_11label->text();
    QString tname = ui->lineEdit_12name->text();
    QString tpassword = ui->lineEdit_13password->text();
    QString ttarget = ui->lineEdit_14target->text();
    QString tothers = ui->lineEdit_15others->text();
    //对用户行为进行初步过滤
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
    //
    if(tlabel != mainPWM->getNowLabel() && mainPWM->labelExist(tlabel))
    {
        ui->lineEdit_21label->setPlaceholderText("标签已存在");
        ui->lineEdit_21label->clear();
        return;
    }
    //尝试保存修改
    mainPWM->editSelectedLabel(tlabel,tname,tpassword,ttarget,tothers);
    ui->lineEdit_21label->setPlaceholderText("标签");
    ui->lineEdit_22name->setPlaceholderText("用户名");
    ui->lineEdit_23password->setPlaceholderText("密码");
    refreshLabelList();
    //生成对话框提示
    customDialog = new BaseDialog;
    customDialog->createDialog(1,"保存成功","该项目的信息已经更新");
    connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_notify()));
    customDialog->setWindowModality(Qt::ApplicationModal);
    customDialog->show();
}

//删除密码槽函数
void MainPage::on_pushButton_delete_clicked()
{
    QList sl = ui->listWidget_allLabel->selectedItems();
    if(sl.isEmpty())
    {
        //未选中项目直接退出
        return;
    }
    //生成对话框，跳转到对应槽函数
    customDialog = new BaseDialog;
    customDialog->createDialog(0,"确定要删除吗？","将会删除此项目，此操作不可撤销");
    connect(customDialog,SIGNAL(buttonCancel_clicked()),this,SLOT(dialog_notify()));
    connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_deleteOK()));
    customDialog->setWindowModality(Qt::ApplicationModal);
    customDialog->show();
}

//选中列表项槽函数
void MainPage::on_listWidget_allLabel_itemClicked(QListWidgetItem *item)
{
    //选中列表项目就刷新右侧详细内容
    //qDebug()<< "Selected item:" <<item->text();
    QString tLabel=item->text();
    mainPWM->readSelectedLabel(tLabel);
    ui->lineEdit_11label->setText(mainPWM->getNowLabel());
    ui->lineEdit_12name->setText(mainPWM->getNowName());
    ui->lineEdit_13password->setText(mainPWM->getNowPassword());
    ui->lineEdit_14target->setText(mainPWM->getNowTarget());
    ui->lineEdit_15others->setText(mainPWM->getNowOthers());
}

//对话框点击确认删除按钮
void MainPage::dialog_deleteOK()
{
    mainPWM->deleSelectedLabel(mainPWM->getNowLabel());
    ui->lineEdit_11label->clear();
    ui->lineEdit_12name->clear();
    ui->lineEdit_13password->clear();
    ui->lineEdit_14target->clear();
    ui->lineEdit_15others->clear();
    refreshLabelList();
    //生成对话框提示
    customDialog = new BaseDialog;
    customDialog->createDialog(1,"删除成功","该项目已从您的密码本中移除");
    connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_notify()));
    customDialog->setWindowModality(Qt::ApplicationModal);
    customDialog->show();
}

//对话框点击确认注销按钮
void MainPage::dialog_signoutOK()
{
    emit mSignalShowSignIN();
    recyclePage();
    saveUserProfile();
    delete mainUser;
    mainUser = NULL;
    delete mainPWM;
    mainPWM = NULL;
    this->close();
    //qDebug()<<"Done";
}

//对话框点击确认按钮
void MainPage::dialog_notify()
{
    delete customDialog;
    customDialog = NULL;
}

//导出密码槽函数
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
        //生成对话框提示
        customDialog = new BaseDialog;
        customDialog->createDialog(1,"导出成功","文件" + fileName + ".txt 已保存至" + '\n' + filePath);
        connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_notify()));
        customDialog->setWindowModality(Qt::ApplicationModal);
        customDialog->show();
    }
    else
    {
        //生成对话框提示
        customDialog = new BaseDialog;
        customDialog->createDialog(1,"导出失败","文件" + fileName + "可能已存在" + '\n' + "请尝试更换文件名");
        connect(customDialog,SIGNAL(buttonOK_clicked()),this,SLOT(dialog_notify()));
        customDialog->setWindowModality(Qt::ApplicationModal);
        customDialog->show();
    }
    ui->lineEdit_21label->clear();
    ui->lineEdit_fileName->setPlaceholderText("文件名");
}

