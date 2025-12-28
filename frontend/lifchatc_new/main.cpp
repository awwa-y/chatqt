#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "global.h"// for ReqId, Modules, ErrorCodes, gate_url_prefix
// 显式告诉 Clangd 这些类型被使用
static void use_global_types() {
    ReqId id = ID_GET_VERIFY_CODE;
    Modules mod = REGISTERMOD;
    ErrorCodes err = SUCCESS;
    QString url = gate_url_prefix;
    (void)id; (void)mod; (void)err; (void)url; // 避免未使用变量警告
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else{
        qDebug("Open failed");
    }*/
    a.setWindowIcon(QIcon(":/res/pict.ico"));
    QString fileName="config.ini";
    QString app_path=QCoreApplication::applicationDirPath();

    QString config_path=QDir::toNativeSeparators(app_path +QDir::separator()+fileName);
    QSettings settings(config_path,QSettings::IniFormat);
    QString gate_host=settings.value("GateServer/host").toString();
    QString gate_port=settings.value("GateServer/port").toString();

    gate_url_prefix="http://"+gate_host+":"+gate_port;
    // 直接创建 MainWindow 实例

    MainWindow w;
    w.show();

    return a.exec();

}
