ROOT_PATH=$(shell pwd)
INCLUDE_PATH=-I$(ROOT_PATH)/../lib/include
LIB_PATH=-L$(ROOT_PATH)/../lib/lib
lib=-lmysqlclient 
cc=g++

.PHONY:all
all:cgi_insert cgi_select cgi_delete cgi_update
	cp cgi_insert $(ROOT_PATH)/../wwwroot/cgi_bin/
	cp cgi_select $(ROOT_PATH)/../wwwroot/cgi_bin/
	cp cgi_delete $(ROOT_PATH)/../wwwroot/cgi_bin/
	cp cgi_update $(ROOT_PATH)/../wwwroot/cgi_bin/

cgi_insert:cgi_mysql_insert.cpp sql_api.cpp
	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib)

cgi_select:cgi_mysql_select.cpp sql_api.cpp
	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib)

cgi_delete:cgi_mysql_delete.cpp sql_api.cpp
	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib)
cgi_update:cgi_mysql_update.cpp sql_api.cpp
	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib)
.PHONY:clean
clean:
	rm -rf cgi_insert cgi_select
