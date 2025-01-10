# 设置CMake最低版本要求为3.16.0，如果版本低于此版本则报错
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# 设置CMAKE_SYSTEM_VERSION为10.0，并强制缓存
set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

# 定义项目名称为Dizzy，并指定使用C++语言
project(Dizzy CXX)

# 如果CMAKE_VS_PLATFORM_NAME未设置，则默认设置为x64
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()

# 如果当前架构不是x64，则报错并终止配置
if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!!!")
endif()

# 设置全局配置类型为Debug和Release
set(CMAKE_CONFIGURATION_TYPES
        "Debug"
        "Release"
        CACHE STRING "" FORCE
)

# 如果使用MSVC编译器，则清除CMake默认提供的编译器标志
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
endif()

# 如果使用MSVC编译器，则清除CMake默认提供的链接器标志
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

# 包含CMake/Utils.cmake文件中的公用工具函数
include(CMake/Utils.cmake)

# 包含CMake/GlobalSettingsInclude.cmake文件中的全局设置，如果文件不存在则忽略
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

# 启用解决方案文件夹功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 添加子项目Dizzy，确保Dizzy.dll先编译完成
add_subdirectory(Dizzy)

# 添加子项目Sandbox
add_subdirectory(Sandbox)

# 设置Sandbox为启动项目
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

# 创建一个自定义目标来确保Dizzy库在Sandbox之前构建
add_custom_target(build_Dizzy ALL
        DEPENDS Dizzy
)

# 确保Sandbox依赖于build_Dizzy
add_dependencies(Sandbox build_Dizzy)



