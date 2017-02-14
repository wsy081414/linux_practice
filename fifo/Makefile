Client=Client.c
Server=Server.c
cc=gcc

ClientSrc=Client
ServerSrc=Server

.PHONY :all
all:$(ClientSrc) $(ServerSrc)
$(ClientSrc):$(Client)
	$(cc) -o $@ $^
$(ServerSrc):$(Server)
	$(cc) -o $@ $^


.PHONY :clean
clean:
	rm -rf $(ClientSrc) $(ServerSrc) ./fifo
