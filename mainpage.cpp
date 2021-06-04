#include "mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent) :
    BasePage(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
    initPage();
}

MainPage::~MainPage()
{
    delete ui;
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
    emit mSignalShowSignIN();
    recyclePage();
    this->hide();
}


void MainPage::on_pushButton_settings_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_settings);
}

