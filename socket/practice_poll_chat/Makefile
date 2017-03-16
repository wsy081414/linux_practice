

.PHONY :all
all:client server

client:client.c
	gcc -o $@ $^ -g
server:server.c
	gcc -o $@ $^ -g

.PHONY :clean
clean:
	rm -rf client server
