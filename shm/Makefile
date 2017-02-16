cc=gcc
client=client
server=server

clientsrc=client.c comm.c
serversrc=server.c comm.c

.PHONY :all
all:$(client) $(server)
$(client):$(clientsrc)
	$(cc) -o $@ $^

$(server):$(serversrc)
	$(cc) -o $@ $^

.PHONY :clean
clean:
	rm -rf $(client) $(server)
