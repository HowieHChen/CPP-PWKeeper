#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QString>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

#include "userprofile.h"

namespace Ui {
class BasePage;
}

class BasePage : public QWidget
{
    Q_OBJECT
    QMenu *mMenu;
    QAction *mShowMainAction;
    QAction *mExitAppAction;
    QSystemTrayIcon  *systemtrayicon;

public:
    explicit BasePage(QWidget *parent = nullptr);
    ~BasePage();

    //系统托盘常驻
    void initPage();

    //从系统托盘移除
    void recyclePage();

    //设置窗口大标题
    void largeTitle();

    //窗口拖动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    //托盘菜单
    void createActions();
    void createMenu();

    //切换关闭按钮功能
    void refreshCloseDirectly(bool tclose);

private slots:
    //最小化按钮槽函数
    void on_toolButton_Minimize_clicked();

    //关闭按钮槽函数
    void on_toolButton_Quit_clicked();

    //托盘事件
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void on_showMainAction();
    void on_exitAppAction();

signals:

private:
    Ui::BasePage *ui;

    //关闭按钮功能，缺省为1（直接退出）
    bool closeDirectly=1;

    //保存是否有托盘常驻，缺省为0（无）
    bool isInt = 0;
};

#endif // BASEPAGE_H
