#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class BaseDialog;
}

class BaseDialog : public QWidget
{
    Q_OBJECT

public:
    explicit BaseDialog(QWidget *parent = nullptr);
    ~BaseDialog();

    //初始化对话框
    void createDialog(int tType,QString tHead,QString tContent);

private slots:
    //取消按钮点击槽函数
    void on_buttonCancel_clicked();

    //确认按钮点击槽函数
    void on_buttonOK_clicked();

signals:
    //取消按钮点击信号
    void buttonCancel_clicked();

    //确认按钮点击信号
    void buttonOK_clicked();

private:
    Ui::BaseDialog *ui;
};

#endif // BASEDIALOG_H
