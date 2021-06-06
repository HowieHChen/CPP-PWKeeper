#include "basepage.h"
#include "ui_basepage.h"

BasePage::BasePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BasePage)
{
    ui->setupUi(this);
    this->setWindowTitle("BasePage");
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //绘制窗口阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor(102,102,102));
    shadow->setBlurRadius(20);
    ui->BaseFrame->setGraphicsEffect(shadow);
    ui->label_ApplicationLarge->hide();
}

BasePage::~BasePage()
{
    delete ui;
}

//注册系统托盘常驻
void BasePage::initPage()
{
    systemtrayicon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/icons/Res/icons/action/svg/production/ic_account_balance_wallet_24px.svg");
    systemtrayicon->setIcon(icon);
    systemtrayicon->setToolTip(QObject::tr("PWKeeper"));
    createActions();
    createMenu();
    systemtrayicon->show();
    connect(systemtrayicon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
}

//注销系统托盘常驻
void BasePage::recyclePage()
{
    delete systemtrayicon;
    systemtrayicon = NULL;
}

void BasePage::largeTitle()
{
    ui->label_ApplicationSmall->hide();
    ui->label_ApplicationLarge->show();
}

//最小化按钮
void BasePage::on_toolButton_Minimize_clicked()
{
    showMinimized();
}

//关闭按钮
void BasePage::on_toolButton_Quit_clicked()
{
    if(closeDirectly)
    {
        on_exitAppAction();
    }
    else
    {
        this->hide();
    }
}

//自定义标题栏事件
//窗口坐标
static QPoint last(0,0);
//标题栏高度
const int TITLE_HEIGHT = 50;

//鼠标拖动窗口
void BasePage::mousePressEvent(QMouseEvent *event)
{
    if(event->position().y()<TITLE_HEIGHT)
    {
        last = event->globalPosition().toPoint();
    }
}

void BasePage::mouseMoveEvent(QMouseEvent *event)
{
    if(event->position().y()<TITLE_HEIGHT)
    {
        int dx = event->globalPosition().x() - last.x();
        int dy = event->globalPosition().y() - last.y();
        last = event->globalPosition().toPoint();
        this->move(this->x()+dx,this->y()+dy);
    }
}

void BasePage::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->position().y()<TITLE_HEIGHT)
    {
        int dx = event->globalPosition().x() - last.x();
        int dy = event->globalPosition().y() - last.y();
        this->move(this->x()+dx,this->y()+dy);
    }
}

//系统托盘事件响应
void BasePage::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
       case QSystemTrayIcon::Trigger:
           break;
       case QSystemTrayIcon::DoubleClick:
           this->show();
           break;
       default:
           break;
    }
}

void BasePage::createActions()
{
    mShowMainAction = new QAction(QObject::tr("打开PWKeeper"),this);
    connect(mShowMainAction,SIGNAL(triggered()),this,SLOT(on_showMainAction()));

    mExitAppAction = new QAction(QObject::tr("退出"),this);
    connect(mExitAppAction,SIGNAL(triggered()),this,SLOT(on_exitAppAction()));

}

void BasePage::createMenu()
{
    mMenu = new QMenu(this);
    mMenu->addAction(mShowMainAction);
    mMenu->addSeparator();
    mMenu->addAction(mExitAppAction);
    systemtrayicon->setContextMenu(mMenu);
}

void BasePage::on_showMainAction()
{
    this->show();
}

void BasePage::on_exitAppAction()
{
    delete systemtrayicon;
    systemtrayicon=NULL;
    exit(0);
}

void BasePage::refreshCloseDirectly(bool tclose)
{
    closeDirectly = tclose;
}
