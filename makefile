# Default target is build
all: build

# Target to generate RPC code
gen:
	rpcgen -C -a oauth.x

# Target to compile the server and client
build:
	gcc -o server oauth_server.c oauth_svc.c oauth_xdr.c -ltirpc -I/usr/include/tirpc -g
	gcc -o client oauth_client.c oauth_clnt.c oauth_xdr.c library/client/utils.c  -ltirpc -I/usr/include/tirpc -g

run_server:
	./server

run_client:
	./client localhost client.in
# Clean up generated files and executables
clean:
	rm -f client server oauth.h oauth_svc.c oauth_clnt.c oauth_xdr.c oauth_client.c oauth_server.c Makefile.oauth

# Phony targets
.PHONY: gen build clean