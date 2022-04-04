#指定SRC_LIST为当前路径下所有源文件
aux_source_directory(. SRC_LIST)
#根据SRC_LIST生成可执行文件client
add_executable(client ${SRC_LIST})
#链接库文件
target_link_libraries(client pthread)
