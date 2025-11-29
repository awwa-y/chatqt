cmake_minimum_required(VERSION 3.19)
# 设置项目名称为lifchatc_new以匹配目录名
project(lifchatc_new LANGUAGES CXX)

# 查找Qt依赖
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)
qt_standard_project_setup()

# 编译资源文件（路径：项目根目录/res/rc.qrc）
qt6_add_resources(RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/res/rc.qrc")

# 定义可执行文件（包含所有源文件+资源）
qt_add_executable(lifchatc_new
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    global.cpp
    global.h
    logindialog.cpp
    logindialog.h
    logindialog.ui
    registerdialog.cpp
    registerdialog.h
    registerdialog.ui
    ${RESOURCES}
    singleton.h
    httpmgr.h httpmgr.cpp  # 必须包含资源变量
)

# 链接Qt库
target_link_libraries(lifchatc_new
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
)
