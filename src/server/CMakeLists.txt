#定义***_LIST包含了当前目录下所有源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)

#指定***_LIST生成可执行文件server
add_executable(server ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})

#链接时库文件
target_link_libraries(server muduo_net muduo_base mysqlclient hiredis pthread)