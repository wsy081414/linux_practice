

.PHONY :all
all:client server

client:client.c
	gcc -o $@ $^
server:server.c
	gcc -o $@ $^

.PHONY :clean
	rm -rf server client
