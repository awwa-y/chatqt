#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "httpmgr.h"
#include "global.h"
//
registerDialog::registerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registerDialog)
{
    ui->setupUi(this);
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state","normal");
    repolish(ui->err_tip);
    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_reg_mod_finish,this,&registerDialog::slot_reg_mod_finish);
    // 连接获取验证码按钮
    connect(ui->on_get_code, &QPushButton::clicked, this, &registerDialog::on_get_code_clicked);
    
    // 查找并连接取消按钮
    QPushButton *cancelBtn = findChild<QPushButton*>("pushButton_2");
    if (cancelBtn) {
        connect(cancelBtn, &QPushButton::clicked, this, [=]() {
            emit backToLogin(); // 发射返回到登录界面的信号
            this->hide(); // 隐藏注册对话框
        });
    }
    initHttpHandlers();
}
//
registerDialog::~registerDialog()
{
    delete ui;
}
//
void registerDialog::on_get_code_clicked()
{

    auto email=ui->email_edit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+)))");
    bool match =regex.match(email).hasMatch();
    if(match){
        //发送http验证码
        QJsonObject json_obj;
        json_obj["email"]=email;
        HttpMgr::GetInstance()->PostHttpReq(QUrl("http://localhost:8080/get_verifycode"),json_obj,
                                            ReqId::ID_GET_VERIFY_CODE,Modules::REGISTERMOD);
        showTip(tr("邮箱格式正确"),false);
    }
    else{
        showTip(tr("邮箱格式不正确"),false);
    }



}
//
void registerDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err!=ErrorCodes::SUCCESS){
        showTip(tr("网络错误请求"),false);
        return;
    }
    //解析json字符串 res转化为qbytearray
    QJsonDocument jsonDoc=QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull()){
        showTip(tr("json解析失败"),false);
        return;
    }
    //json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析失败"),false);
        return;
    }
    //
    jsonDoc.object();
    _handlers[id](jsonDoc.object());
    return;


}
void registerDialog::showTip(QString str,bool b_ok){
    ui->err_tip->setText(str);
    ui->err_tip->setProperty("state","err");
    repolish(ui->err_tip);
}

void registerDialog::initHttpHandlers()
{
//注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VERIFY_CODE,[this](const QJsonObject& jsonObj){
    int error=jsonObj["error"].toInt();
    if(error!=ErrorCodes::SUCCESS){
        showTip(tr("参数错误"),false);
        return;
    }
    auto email=jsonObj["email"].toString();
    showTip(tr("验证码已经发送到邮箱，查收"),true);
    qDebug()<<"email is"<<email;
});
}



