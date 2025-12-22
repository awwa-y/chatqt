#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "registerdialog.h"
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include "global.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _login_dlg(nullptr)
    , _reg_dlg(nullptr)
{
    ui->setupUi(this);
    _login_dlg = new loginDialog(this);
    _reg_dlg = new registerDialog(this);
    _login_dlg->show();
    this->setFixedSize(_login_dlg->size());
    connect(_reg_dlg, &registerDialog::backToLogin,
            this, [=]() {
                qDebug() << "收到backToLogin信号，切换到登录界面";
                setCentralWidget(_login_dlg);
                _login_dlg->show();
            }, Qt::QueuedConnection);

    // 连接切换注册信号
    connect(_login_dlg, &loginDialog::switchRegister,
            this, &MainWindow::SlotSwitchReg);
    //connect(_reg_dlg,&registerDialog::backToLogin,
            //this,&MainWindow::Swicthlog);
    // 连接返回登录信号
    /*connect(_reg_dlg, &registerDialog::backToLogin,
            this, [=]() {
                _reg_dlg->hide();
                setCentralWidget(_login_dlg);
                _login_dlg->show();
            });*/
}

MainWindow::~MainWindow()
{
    delete ui;
    if(_login_dlg){
        delete _login_dlg;
        _login_dlg = nullptr;
    }
    if(_reg_dlg){
        delete _reg_dlg;
        _reg_dlg = nullptr;
    }
}

// 测试资源加载功能的独立函数
void MainWindow::TestResourceLoading()
{
    // 尝试加载图片资源（注意拼写：weichat）
    QPixmap testPix(":/res/images/weichat.png");

    if (testPix.isNull()) {
        qDebug() << "❌ 资源系统验证失败：";
        qDebug() << "   无法加载图片资源 :/res/images/wechat.png";
        qDebug() << "   请检查：";
        qDebug() << "   1. res/images/wechat.png 文件是否存在";
        qDebug() << "   2. rc.qrc 中是否正确添加该图片";
        qDebug() << "   3. CMakeLists.txt 是否正确包含资源文件";
    } else {
        qDebug() << "✅ 资源系统验证成功！";
        qDebug() << "   图片尺寸：" << testPix.width() << "x" << testPix.height();
    }
}

// 向登录对话框添加图片
void MainWindow::AddImageToLoginDialog()
{
    if (!_login_dlg) return;

    // 方法1：如果登录对话框UI中有一个名为logoLabel的QLabel
    QLabel* logoLabel = _login_dlg->findChild<QLabel*>("logoLabel");
    if (logoLabel) {
        QPixmap logo(":/res/images/weichat.png");
        if (!logo.isNull()) {
            logoLabel->setPixmap(logo.scaled(
                logoLabel->width(),
                logoLabel->height(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
                ));
            logoLabel->setAlignment(Qt::AlignCenter);
            qDebug() << "登录窗口图片设置成功";
        } else {
            logoLabel->setText("图片加载失败");
            qDebug() << "登录窗口图片设置失败";
        }
    } else {
        // 方法2：如果没有预设的QLabel，动态创建一个
        QLabel* dynamicLabel = new QLabel(_login_dlg);
        dynamicLabel->setGeometry(100, 50, 150, 150); // 设置位置和大小
        QPixmap logo(":/res/images/weichat.png");
        if (!logo.isNull()) {
            dynamicLabel->setPixmap(logo.scaled(
                dynamicLabel->width(),
                dynamicLabel->height(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
                ));
        } else {
            dynamicLabel->setText("图片资源缺失");
        }
        dynamicLabel->setAlignment(Qt::AlignCenter);
        dynamicLabel->show();
    }
}

void MainWindow::SlotSwitchReg()
{
    qDebug() << "切换到注册界面";
    _login_dlg->hide();

    _reg_dlg->show();
    this->setFixedSize(_reg_dlg->size());
}
void MainWindow::Swicthlog(){
    _reg_dlg->hide();
    //setCentralWidget(_login_dlg);
    _login_dlg->show();
}
