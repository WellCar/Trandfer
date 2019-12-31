# Makefile for client 4g transfer 

src	:=main.c queue.c

PHONY	:=all


all:$(src) server
	gcc -o main $^ -lpthread
	

server:tcpserver.c
	gcc -o server tcpserver.c

.PHONY:clean

clean:
	rm -fr main server