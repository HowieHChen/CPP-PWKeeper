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

    void getUserProfile();
    void saveUserProfile();
    void refreshSwitchControl();
    void refreshLabelList();
    void setTheTabOrder();
signals:
    void mSignalShowSignIN();
    void mSignalCloseDirectly();
private slots:
    void on_pushButton_view_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_out_clicked();

    void on_pushButton_signout_clicked();

    void on_pushButton_settings_clicked();

    void switchcontrol1_clicked(bool);
    void switchcontrol2_clicked(bool);
    void switchcontrol3_clicked(bool);

    void on_pushButton_additem_clicked();

    void on_pushButton_createPassword_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_delete_clicked();

    void on_listWidget_allLabel_itemClicked(QListWidgetItem *item);

    void dialog_deleteOK();
    void dialog_signoutOK();
    void dialog_notify();
    void on_pushButton_output_clicked();

private:
    Ui::MainPage *ui;


    bool saveLastName = 0;
    bool saveLastPassword = 0;
    bool closeDirectly = 0;
    QString userName;
    QString userPassword;
    QString userMail;
};

#endif // MAINPAGE_H
