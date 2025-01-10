cmake_minimum_required(VERSION 3.30)

## 手动编译Glad的 .c源文件
#add_library(Glad STATIC ./src/glad.c)
#
#target_include_directories(Glad PUBLIC
#        ${PROJECT_SOURCE_DIR}/Dizzy/3rd/glad/include
#)

project(Glad)

add_library(glad include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)