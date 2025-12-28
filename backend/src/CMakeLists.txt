cmake_minimum_required(VERSION 3.15)
project(server_qt)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows特定设置
if(MSVC)
    add_compile_options(/W4)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# ==================== JSONCpp 静态库配置 ====================
# 直接使用编译好的 JSONCpp 静态库
set(JSONCPP_LIBRARY "C:/cppsoft/jsoncpp-master/build_vs2022/lib/Release/jsoncpp.lib")
set(JSONCPP_INCLUDE_DIR "C:/cppsoft/jsoncpp-master/include")

# 验证文件存在
if(NOT EXISTS ${JSONCPP_LIBRARY})
    message(FATAL_ERROR "JSONCpp 静态库不存在: ${JSONCPP_LIBRARY}")
endif()

if(NOT EXISTS "${JSONCPP_INCLUDE_DIR}/json/json.h")
    message(FATAL_ERROR "JSONCpp 头文件不存在: ${JSONCPP_INCLUDE_DIR}/json/json.h")
endif()

message(STATUS "✓ 使用 JSONCpp 静态库: ${JSONCPP_LIBRARY}")
message(STATUS "✓ JSONCpp 头文件目录: ${JSONCPP_INCLUDE_DIR}")

# 包含目录
include_directories(
    ${JSONCPP_INCLUDE_DIR}
)

# 设置项目源文件
set(SOURCES
    main.cpp
    CServer.cpp
    HttpConnection.cpp
    LogicSystem.cpp
)

# 设置头文件
set(HEADERS
    CServer.h
    HttpConnection.h
    LogicSystem.h
    Singleton.h
    const.h
)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${JSONCPP_LIBRARY}  # 链接 JSONCpp 静态库
)

# 设置输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

message(STATUS "✓ 项目配置完成，JSONCpp 静态库已集成")