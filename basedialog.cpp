#include "basedialog.h"
#include "ui_basedialog.h"

BaseDialog::BaseDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("PWKeeper");
    this->setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //绘制窗口阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor(102,102,102));
    shadow->setBlurRadius(20);
    ui->BaseFrame->setGraphicsEffect(shadow);
}

BaseDialog::~BaseDialog()
{
    delete ui;
}

void BaseDialog::createDialog(int tType, QString tHead, QString tContent)
{
    if(tType == 1)
    {
        ui->buttonCancel->hide();
    }
    ui->label_Head->setText(tHead);
    ui->label_Content->setText(tContent);
}

void BaseDialog::on_buttonCancel_clicked()
{
    emit buttonCancel_clicked();
    this->close();
}


void BaseDialog::on_pushButton_clicked()
{
    emit buttonOK_clicked();
    this->close();
}

