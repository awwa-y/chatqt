#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"
#include <QStackedWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void SlotSwitchReg();
    void Swicthlog();

private:
    // 测试资源加载的辅助函数
    void TestResourceLoading();
    // 向登录对话框添加图片
    void AddImageToLoginDialog();

    Ui::MainWindow *ui;
    loginDialog *_login_dlg;
    registerDialog *_reg_dlg;
    QStackedWidget *_stack_widget;
};
#endif // MAINWINDOW_H
