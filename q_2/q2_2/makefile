

all: client_server

client_server: client.c server.c
		gcc -o client client.c
		gcc -o server server.c
.PHONY:
		clean all

clean:
		-rm client server
