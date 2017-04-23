ROOT_PATH=$(shell pwd)
CLIENT_PATH=${ROOT_PATH}/client
SERVER_PATH=${ROOT_PATH}/server
COMM_PATH=${ROOT_PATH}/comm
WINDOW_PATH=${ROOT_PATH}/window
LOG_PATH=${ROOT_PATH}/log
CONF_PATH=${ROOT_PATH}/conf

CC=g++

SERVER_BIN=server
CLIENT_BIN=client



SERVER_OBJ=$(shell ls ${SERVER_PATH} | egrep ^.*.cpp$ | sed 's/\.cpp/\.o/g')
CLIENT_OBJ=$(shell ls ${CLIENT_PATH} | egrep ^.*.cpp$ | sed 's/\.cpp/\.o/g')

.PHONY:all
all:
	echo $(CLIENT_OBJ)


#all:${SERVER_SRC} ${CLIENT_SRC}
#
#$(SERVER_SRC):$(SERVER_OBJ)
#	$(CC) -o $@ $^
#%.o:$(SERVER_PATH)/%.cpp
#	$(CC) -c $<
#
#$(CLIENT_SRC):$(CLIENT_OBJ)
#	$(CC) -o $@ $^
#%.o:$(CLIENT_PATH)/%.cpp
#	$(cc) -c %<

.PHONY:clean
clean:

