# 设置CMake最低版本要求为3.16.0，如果版本低于此版本则报错
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# 定义项目名称为Dizzy，并指定使用C++语言
project(Dizzy CXX)

# 设置项目名称为Dizzy
set(PROJECT_NAME Dizzy)

# 设置Dizzy项目的头文件列表
set(DIZZY_HEADERS
        "src/Dizzy.h"
        "src/Dizzy/Application.h"
        "src/Dizzy/Core.h"
        "src/Dizzy/EntryPoint.h"
        "src/Dizzy/Logger.h"
        "src/Dizzy/Events/Event.h"
        "src/Dizzy/Events/KeyEvent.h"
        "src/Dizzy/Events/MouseEvent.h"
        "src/Dizzy/Events/ApplicationEvent.h"
)

# 设置Dizzy项目的源文件列表
set(DIZZY_SOURCES
        "src/Dizzy/Application.cpp"
        "src/Dizzy/Logger.cpp"
)

# 将头文件和源文件合并到ALL_FILES变量中
set(ALL_FILES
        ${DIZZY_HEADERS}
        ${DIZZY_SOURCES}
)

# 添加共享库目标，目标名称为PROJECT_NAME，源文件为ALL_FILES变量
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

# 设置目标的根命名空间为Dizzy
set(ROOT_NAMESPACE Dizzy)

# 设置目标的VS_GLOBAL_KEYWORD属性为Win32Proj
set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
)

# 设置目标的输出目录，分别针对Debug和Release配置
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}//bin/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/${PROJECT_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}//bin/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/${PROJECT_NAME}/"
)

# 启用发布配置下的交叉优化
set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)

# 设置目标的包含目录，包含spdlog库的头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/3rd/spdlog/include"
)

# 设置目标的编译定义，包括平台定义、DLL构建标志和字符集定义
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "DIZZY_PLATFORM_WINDOWS;"
        "DIZZY_BUILD_DLL;"
)

# 设置目标的编译选项，针对MSVC编译器
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
            /Oi;  # 内联函数优化
            /Gy   # 函数级别的链接优化
            >
            /permissive-;  # 使用标准C++模式
            /std:c++17;    # 使用C++17标准
            /sdl;          # 启用安全开发生命周期检查
            /W3;           # 设置警告级别为3
            /EHsc          # EHsc编译选项
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};  # 使用默认的调试信息格式
            /utf-8;        # 使用UTF-8编码
            ${DEFAULT_CXX_EXCEPTION_HANDLING}          # 使用默认的异常处理模式
    )
    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
            /OPT:REF;  # 引用优化
            /OPT:ICF   # 常量折叠优化
            >
            /DEBUG;        # 生成调试信息
            /SUBSYSTEM:CONSOLE  # 设置子系统为控制台应用程序
    )
endif ()

#上级目录路径
get_filename_component(PARENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}" PATH)

#使用相对路径来拷贝Dizzy.dll到Sandbox的输出目录
add_custom_command(TARGET Dizzy POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PARENT_BINARY_DIR}/Dizzy"
        "${PARENT_BINARY_DIR}/Sandbox")
