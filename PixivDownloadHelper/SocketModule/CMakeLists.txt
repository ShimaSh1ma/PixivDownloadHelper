cmake_minimum_required(VERSION 3.10)

project(SocketModule)

# 自动查找src目录下所有的.cpp文件
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# 添加包含的头文件目录
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.h")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)