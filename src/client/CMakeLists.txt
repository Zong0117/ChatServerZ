#包含源文件
aux_source_directory(. SRC_LIST)

#生成路径
add_executable(client ${SRC_LIST})

#链接库
target_link_libraries(client pthread)