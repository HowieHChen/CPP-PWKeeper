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

    void initPage();
    void recyclePage();
    void largeTitle();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void createActions();
    void createMenu();


    void refreshCloseDirectly(bool tclose);
private slots:
    void on_toolButton_Minimize_clicked();
    void on_toolButton_Quit_clicked();

    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void on_showMainAction();
    void on_exitAppAction();
signals:

private:
    Ui::BasePage *ui;

    bool closeDirectly=0;
};

#endif // BASEPAGE_H
