.PHONY:all
all:httpd cgi


httpd :httpd.o main.o
	gcc -o $@ $^ -lpthread
%.o :%.c 
	gcc -c $<

.PHONY:cgi
cgi:
	cd cgi;cd cgi_bin;make;make output;cd -;cd ..;
	cp -rf /home/yuzhe/code/http_server/cgi/cgi_bin /home/yuzhe/code/http_server/wwwroot

.PHONY :clean
clean:
	rm -rf httpd httpd.o main.o  cgi_math; cd cgi;cd cgi_bin;make clean;cd -;cd .. 
	rm -rf /home/yuzhe/code/http_server/wwwroot/cgi_bin
.PHONY :output
output:all
	mkdir output
	cp -rf log output/
	cp -rf conf output/
	cp -rf wwwroot output/
	cp -r http_ctl.sh output/
	cp -r httpd output/

