cc=gcc
sem=sem

semsrc=comm.c sem.c

.PHONY :all
all:$(sem)
$(sem):$(semsrc)
	$(cc) -o $@ $^

.PHONY :clean 
clean:
	rm -rf $(sem)

