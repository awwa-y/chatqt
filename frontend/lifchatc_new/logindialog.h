#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QTimer>
namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();

public slots:
    // 登录按钮点击槽函数
    void on_pushButton_clicked();

    // 注册按钮点击槽函数
    void on_resgiterPushButton_clicked();

signals:
    // 切换到注册界面的信号
    void switchRegister();

private:
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H
