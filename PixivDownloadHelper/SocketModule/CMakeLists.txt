cmake_minimum_required(VERSION 3.10)

project(SocketModule)

# 自动查找src目录下所有的.cpp文件
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# 自动查找src目录下所有的.h文件
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "src/*.h" "include/*.h")

# 寻找 OpenSSL 库
find_package(OpenSSL REQUIRED)

# 添加源文件
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# 链接库文件
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
)

# 指定公开头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

# 指定内部头文件引用路径
target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/SocketModule>
)

# 指定产物静态库输出路径
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/lib
)
