#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"
namespace Ui {
class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = nullptr);
    ~registerDialog();

signals:
    void backToLogin(); // 返回到登录界面的信号

private slots:
    void on_get_code_clicked();//获取验证码判断合法性
    void slot_reg_mod_finish(ReqId id,QString res,ErrorCodes err);
    // 删除未实现的cancelreg_clicked()槽函数声明
    // void cancelreg_clicked();

    void CancelClicked();
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void showTip(QString str,bool b_ok);
    void initHttpHandlers();
private:
    Ui::registerDialog *ui;
    QMap<ReqId,std::function<void(const QJsonObject&)>>_handlers;
};

#endif // REGISTERDIALOG_H
