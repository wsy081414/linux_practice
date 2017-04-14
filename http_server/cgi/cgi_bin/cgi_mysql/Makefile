ROOT_PATH=$(shell pwd)
INCLUDE_PATH=-I$(ROOT_PATH)/../../../lib/include
LIB_PATH=-L$(ROOT_PATH)/../../../lib/lib
lib=-lmysqlclient
cc=g++

.PHONY:all
all:cgi_insert cgi_select
	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib)

cgi_insert:cgi_mysql_insert.cpp sql_api.cpp
	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib)

#cgi_select:cgi_mysql_select.cpp sql_api.cpp
#	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib)

.PHONY:clean
clean:
	rm -rf cgi_insert cgi_select
