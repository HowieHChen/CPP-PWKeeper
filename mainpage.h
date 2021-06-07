#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QListWidget>
#include <QFileDialog>

#include "basepage.h"
#include "basedialog.h"
#include "userprofile.h"
#include "passwordmanage.h"
#include "switchcontrol.h"

namespace Ui {
class MainPage;
}

class MainPage : public BasePage
{
    Q_OBJECT
    UserProfile *mainUser;
    PasswordManage *mainPWM;
    BaseDialog *customDialog;

    SwitchControl *SwitchControl1;
    SwitchControl *SwitchControl2;
    SwitchControl *SwitchControl3;

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

    //读取用户信息和设置
    void getUserProfile();

    //保存用户设置
    void saveUserProfile();

    //刷新开关状态
    void refreshSwitchControl();

    //刷新密码列表
    void refreshLabelList();

    //设置Tab键的按下顺序
    void setTheTabOrder();

signals:
    //注销信号
    void mSignalShowSignIN();

private slots:
    //查询页面槽函数
    void on_pushButton_view_clicked();

    //添加页面槽函数
    void on_pushButton_add_clicked();

    //导出页面槽函数
    void on_pushButton_out_clicked();

    //注销槽函数
    void on_pushButton_signout_clicked();

    //设置页面槽函数
    void on_pushButton_settings_clicked();

    //开关槽函数
    void switchcontrol1_clicked(bool);
    void switchcontrol2_clicked(bool);
    void switchcontrol3_clicked(bool);

    //添加密码槽函数
    void on_pushButton_additem_clicked();

    //生成随机密码槽函数
    void on_pushButton_createPassword_clicked();

    //保存修改槽函数
    void on_pushButton_save_clicked();

    //删除密码槽函数
    void on_pushButton_delete_clicked();

    //选中列表项槽函数
    void on_listWidget_allLabel_itemClicked(QListWidgetItem *item);

    //对话框点击确认删除按钮
    void dialog_deleteOK();

    //对话框点击确认注销按钮
    void dialog_signoutOK();

    //对话框点击确认按钮
    void dialog_notify();

    //导出密码槽函数
    void on_pushButton_output_clicked();

private:
    Ui::MainPage *ui;

    //保存用户设置
    bool saveLastName = 0;
    bool saveLastPassword = 0;
    bool closeDirectly = 0;

    //保存当前用户信息
    QString userName;
    QString userPassword;
    QString userMail;
};

#endif // MAINPAGE_H
