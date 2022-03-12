#定义SRC_LIST包含了当前目录下所有源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
#指定生成server
add_executable(server ${SRC_LIST} ${DB_LIST} ${MODEL_LIST})
#链接时库文件
target_link_libraries(server muduo_net muduo_base mysqlclient pthread)