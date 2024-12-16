cmake_minimum_required(VERSION 3.10)

project(pixivDownloader)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 寻找 Qt 库
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# 寻找 OpenSSL 库
find_package(OpenSSL REQUIRED)

# 设置头文件包含目录
include_directories(include)
# 添加子模块
add_subdirectory(SocketModule)

# 自动查找src目录下所有的.cpp文件
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# 添加包含的头文件目录
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    OpenSSL::SSL
    OpenSSL::Crypto
    SocketModule
)