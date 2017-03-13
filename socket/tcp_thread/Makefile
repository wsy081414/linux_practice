
.PHONY: all
all:client server


client:client.c
	gcc -o $@ $^ -pthread
server:server.c
	gcc -o $@ $^ -pthread

.PHONY: clean
clean:
	rm -rf client server
