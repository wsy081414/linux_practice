cli=client.c
com=comm.c
ser=server.c
cc=gcc

clisrc=client
sersrc=server

.PHONY :all
all:$(clisrc) $(sersrc)

$(clisrc):$(cli) $(com)
	$(cc) -o $@ $^
$(sersrc):$(ser) $(com)
	$(cc) -o $@ $^

.PHONY :clean
clean:
	rm -rf $(clisrc) $(sersrc)
