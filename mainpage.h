#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include "basepage.h"

namespace Ui {
class MainPage;
}

class MainPage : public BasePage
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();
signals:
    void mSignalShowSignIN();
private slots:
    void on_pushButton_view_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_out_clicked();

    void on_pushButton_signout_clicked();

    void on_pushButton_settings_clicked();

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
