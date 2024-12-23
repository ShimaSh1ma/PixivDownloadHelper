cmake_minimum_required(VERSION 3.10)

project(SocketModule)

# 自动查找src目录下所有的.cpp文件
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# 寻找 OpenSSL 库
find_package(OpenSSL REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/SocketModule>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

#安装库及头文件

# install(TARGETS ${PROJECT_NAME}
#     ARCHIVE DESTINATION lib
# )

# install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME})
