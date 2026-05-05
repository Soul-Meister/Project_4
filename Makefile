.PHONY: clean

rsh: rsh.c
	gcc -g -o rsh -Wall -std=gnu11 rsh.c -lpthread

server: server.c
	gcc -g -o server -Wall -std=gnu11 server.c

clean:
	rm -f rsh server