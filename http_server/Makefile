httpd:httpd.o main.o
	gcc -o $@ $^ -lpthread
%.o: %.c 
	gcc -c $<

.PHONY:clean
clean:
	rm -rf httpd httpd.o main.o
