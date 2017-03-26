mydaemon:mydaemon.c
	gcc -o $@ $^

.PHONY :output
output:
	mkdir output
	cp mydaemon output
	cp daemon_ctl.sh output

.PHONY :clean
clean:
	rm -rf mydaemon output

