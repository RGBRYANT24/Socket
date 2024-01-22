# 指定cmake最低版本
cmake_minimum_required(VERSION 3.21)
# 定义项目名称
project(demo)

# 指定-std=c++11
set(CMAKE_CXX_STANDARD 11)

# 找当前目录下所有源文件, 保存到DIR_SRCS中
aux_source_directory(. DIR_SRCS)
aux_source_directory(./src DIR_SRC_SRCS)

# 指定生成目标
add_executable(main ${DIR_SRCS} ${DIR_SRC_SRCS})
