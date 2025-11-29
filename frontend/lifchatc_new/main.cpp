#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 简单的样式设置（不依赖外部样式表）
    a.setStyle("Fusion");
    
    // 设置应用程序信息
    a.setApplicationName("LifeChat");
    a.setApplicationVersion("1.0");

    MainWindow w; // 直接创建 MainWindow 实例
    w.show();      // 显示主窗口（内部已包含 loginDialog）
    return a.exec();

}
