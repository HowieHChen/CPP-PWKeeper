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
    void createDialog(int tType,QString tHead,QString tContent);

private slots:
    void on_buttonCancel_clicked();
    void on_buttonOK_clicked();

signals:
    void buttonCancel_clicked();
    void buttonOK_clicked();

private:
    Ui::BaseDialog *ui;
};

#endif // BASEDIALOG_H
