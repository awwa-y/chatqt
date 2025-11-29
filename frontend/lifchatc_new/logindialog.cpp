#include "logindialog.h"
#include "ui_logindialog.h"
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QDirIterator>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);

    // 使用资源文件路径加载图片
    QString imagePath = ":/res/pict.ico";
    QPixmap pix(imagePath);

    if (pix.isNull()) {
        // 加载失败时显示提示
        ui->logoLabel->setText("图片缺失\n检查路径：\n" + imagePath);
        qDebug() << "图片加载失败！路径：" << imagePath;
    } else {
        // 加载成功
        ui->logoLabel->setPixmap(pix);
        ui->logoLabel->setScaledContents(true);
        qDebug() << "图片加载成功！路径：" << imagePath;
    }
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButton_clicked()
{
    // 登录按钮点击逻辑
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "提示", "用户名或密码不能为空！");
        return;
    }
    
    // 这里可以添加实际的登录验证逻辑
    qDebug() << "登录请求：用户名=" << username;
    QMessageBox::information(this, "提示", "登录成功！");
}

void loginDialog::on_resgiterPushButton_clicked()
{
    // 注册按钮点击逻辑，发射switchRegister信号
    qDebug() << "请求切换到注册界面";
    emit switchRegister(); // 发射信号，由MainWindow处理切换逻辑
}
