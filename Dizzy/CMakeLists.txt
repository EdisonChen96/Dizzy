# 设置CMake最低版本要求为3.16.0，如果版本低于此版本则报错
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# 定义项目名称为Dizzy，并指定使用C++语言
project(Dizzy CXX)

# 设置项目名称为Dizzy
set(PROJECT_NAME Dizzy)


################################################################################################################################
#   构建Dizzy动态链接库
################################################################################################################################

# 设置Dizzy项目的头文件列表
file(GLOB_RECURSE DIZZY_HEADERS "src/**/*.h")

# 设置Dizzy项目的源文件列表
file(GLOB_RECURSE DIZZY_SOURCES "src/**/*.cpp")

# 将头文件和源文件合并到ALL_FILES变量中
set(ALL_FILES
        ${DIZZY_HEADERS}
        ${DIZZY_SOURCES}
)

# 构建Dizzy动态库文件
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})


################################################################################################################################
#   静态链接glfw库
################################################################################################################################



if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")  #设置目标的编译选项，针对MINGW编译器
    set(GLFW_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rd/glfw/lib-mingw")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(GLFW_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rd/glfw/lib-vc22")
endif ()

# 指定glfw的包含目录
target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/3rd/glfw/include"
)

MESSAGE(${GLFW_LIB_DIR})

# 指定glfw静态库的搜索路径
# 根据所使用的编译器，将编译后的库文件放在这里
target_link_directories(${PROJECT_NAME} PUBLIC
        ${GLFW_LIB_DIR})

# 链接GLFW静态库
target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw3
        opengl32.lib)

################################################################################################################################
#   编译选项
################################################################################################################################

# 设置目标的包含目录，包含第三方库库的头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/3rd/spdlog/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/3rd/glfw/include"
        "${GLFW_LIB_DIR}"
)

# 设置目标的编译定义，包括平台定义、DLL构建标志和字符集定义
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "DIZZY_PLATFORM_WINDOWS;"
        "DIZZY_BUILD_DLL;"
)

# 启用发布配置下的交叉优化
set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)


# 检测编译器类型
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")  #设置目标的编译选项，针对MINGW编译器
    # 预编译固定的头文件
    target_precompile_headers(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/dzpch.h")

    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
            -flto;  # 启用LTO
            -fno-fat-lto-objects  # 使用瘦LTO对象文件
            >
            -std=c++17;  # 使用C++17标准
            -Wall;       # 开启所有警告
            -Wextra      # 开启额外警告
    )
    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
            -flto;  # 启用LTO
            >
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")  #设置目标的编译选项，针对MSVC编译器
    # 添加预编译头文件
    target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/dzpch.h")

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
else ()
    message("Unknown Compiler!!!")
endif ()



################################################################################################################################
#   自定义custom命令拷贝Dizzy.dll
################################################################################################################################

#上级目录路径
get_filename_component(PARENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}" PATH)

#使用相对路径来拷贝Dizzy.dll到Sandbox的输出目录
add_custom_command(TARGET Dizzy POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PARENT_BINARY_DIR}/Dizzy"
        "${PARENT_BINARY_DIR}/Sandbox")
