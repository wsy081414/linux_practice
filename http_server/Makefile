.PHONY:all
all:httpd cgi


httpd :httpd.o main.o
	gcc -o $@ $^ -lpthread
%.o :%.c 
	gcc -c $<

.PHONY:cgi
cgi:
	cd cgi;cd cgi_bin;make;make output;cd -;cd ..

.PHONY :clean
clean:
	rm -rf httpd httpd.o main.o output; cd cgi;cd cgi_bin;make clean;cd -;cd .. 
.PHONY :output
output:all
	mkdir output/
	cp -rf log output/
	cp -rf conf output/
	cp -rf wwwroot output/
	mkdir -p output/wwwroot/cgi_bin
	cp -f cgi_math output/wwwroot/cgi_bin/
	cp -r http_ctl.sh output/

