cmake_minimum_required(VERSION 3.10)

project(pixivDownloader)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译器选项
if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    else()
    add_compile_options(/Ox)
    endif()
else()
    add_compile_options(-O3)
endif()

# 自动查找src目录下所有的.cpp文件
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# 添加包含的头文件目录
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.h")

# 添加子模块
add_subdirectory(SocketModule)

# 寻找 Qt 库
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(MOC_OUTPUT_DIR "${CMAKE_BINARY_DIR}/moc")
set(CMAKE_MOC_OUTPUT_DIRECTORY ${MOC_OUTPUT_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#添加资源文件
qt5_add_resources(RESOURCES resource/resource.qrc)

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE main.icns)
    set(APP_ICON_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resource/icon/${MACOSX_BUNDLE_ICON_FILE})
    set_source_files_properties(${APP_ICON_PATH} 
        PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${RESOURCES} ${APP_ICON_PATH})
elseif(MSVC)
    # 设置 .rc 文件路径
    set(RC_FILE "${CMAKE_CURRENT_SOURCE_DIR}/resource/icon/resource.rc")
    # 使用自定义命令来编译 .rc 文件为资源对象文件 (.o)
    add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/resource.o
        COMMAND ${CMAKE_RC_COMPILER} /fo ${CMAKE_BINARY_DIR}/resource.o ${RC_FILE}
        DEPENDS ${RC_FILE})
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${RESOURCES} ${APP_ICON_PATH} ${CMAKE_BINARY_DIR}/resource.o)
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        SocketModule
)

# 设置资源图片目录路径变量
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resource")

# 在项目构建时，将资源文件或目录复制到目标目录
file(COPY ${RESOURCE_DIR} DESTINATION ${CMAKE_BINARY_DIR})
