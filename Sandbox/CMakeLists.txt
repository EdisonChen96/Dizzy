# 设置CMake最低版本要求为3.16.0，如果版本低于此版本则报错
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# 定义项目名称为Dizzy，并指定使用C++语言
project(Dizzy CXX)

# 设置项目名称为Sandbox
set(PROJECT_NAME Sandbox)

# 设置Sandbox的源文件列表
set(SANDBOX_SOURCES
        "src/SandboxApp.cpp"
)

## 递归查找文件夹下的 *.cpp *.c 文件保存到 SANDBOX_SOURCES
#file(GLOB_RECURSE SANDBOX_SOURCES *.cpp *.c)

# 将所有源文件合并到ALL_FILES变量中
set(ALL_FILES
        ${SANDBOX_SOURCES}
)

# 添加可执行文件目标，目标名称为PROJECT_NAME，源文件为ALL_FILES
add_executable(${PROJECT_NAME} ${ALL_FILES})

# 设置目标的根命名空间为Sandbox
set(ROOT_NAMESPACE Sandbox)

# 设置目标的VS_GLOBAL_KEYWORD属性为Win32Proj
set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
)

# 设置目标的输出目录，分别针对Debug和Release配置
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/$<CONFIG>/${PROJECT_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/$<CONFIG>/${PROJECT_NAME}/"
)

# 启用发布配置下的交叉优化
set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)

# 设置目标的包含目录，包含Dizzy项目和spdlog库的头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../Dizzy/src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Dizzy/3rd/spdlog/include"
)

# 设置目标的编译定义，包括平台定义和字符集定义
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "DIZZY_PLATFORM_WINDOWS;"
        "UNICODE;"
        "_UNICODE"
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

# 设置目标的链接库，链接Dizzy库
target_link_libraries(${PROJECT_NAME} PRIVATE
        Dizzy
)

#上级目录路径
get_filename_component(PARENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}" PATH)

#使用相对路径来拷贝Dizzy.dll到Sandbox的输出目录
add_custom_command(TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PARENT_BINARY_DIR}/Dizzy"
        "${PARENT_BINARY_DIR}/Sandbox")



