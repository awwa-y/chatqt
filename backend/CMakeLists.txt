cmake_minimum_required(VERSION 3.15)
project(server_qt)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows特定设置
if(MSVC)
    add_compile_options(/W4 /WX)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# 寻找Boost库
find_package(Boost 1.70 REQUIRED COMPONENTS system thread)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    message(STATUS "Boost found: ${Boost_VERSION}")
else()
    message(FATAL_ERROR "Boost库未找到，请确保已安装Boost")
endif()

# ==================== JSONCpp 配置 ====================
# 使用绝对路径
set(JSONCPP_BASE_DIR "${CMAKE_SOURCE_DIR}/jsoncpp_src/jsoncpp-1.9.5")

# 检查目录结构
if(NOT EXISTS "${JSONCPP_BASE_DIR}")
    message(FATAL_ERROR "JSONCpp目录不存在: ${JSONCPP_BASE_DIR}")
endif()

if(NOT EXISTS "${JSONCPP_BASE_DIR}/include/json/json.h")
    message(FATAL_ERROR "JSONCpp头文件未找到，请检查目录结构")
endif()

if(NOT EXISTS "${JSONCPP_BASE_DIR}/src/lib_json/json_reader.cpp")
    message(FATAL_ERROR "JSONCpp源文件未找到，请检查目录结构")
endif()

# 添加包含目录
include_directories("${JSONCPP_BASE_DIR}/include")

# JSONCpp源文件
set(JSONCPP_SOURCES
    "${JSONCPP_BASE_DIR}/src/lib_json/json_reader.cpp"
    "${JSONCPP_BASE_DIR}/src/lib_json/json_value.cpp" 
    "${JSONCPP_BASE_DIR}/src/lib_json/json_writer.cpp"
)

# 项目源文件
set(SOURCES
    main.cpp
    CServer.cpp
    HttpConnection.cpp
    LogicSystem.cpp
    ${JSONCPP_SOURCES}
)

# 头文件
set(HEADERS
    CServer.h
    HttpConnection.h
    LogicSystem.h
    Singleton.h
    const.h
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Boost::system
    Boost::thread
    ws2_32
    wsock32
)

# 输出设置
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    OUTPUT_NAME "server_qt"
)

message(STATUS "=== 配置完成 ===")
message(STATUS "目标文件: ${PROJECT_NAME}.exe")
message(STATUS "输出目录: ${CMAKE_BINARY_DIR}/bin")
message(STATUS "JSONCpp已集成")