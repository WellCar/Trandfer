# Makefile for client 4g transfer 

CROSS_COMPILE	:=arm-linux-gnueabihf-
GCC	:=$(CROSS_COMPILE)gcc

src	:=main.c queue.c common.c

PHONY	:=all


all:$(src)
	gcc -o main $^ -lpthread
	

server:tcpserver.c
	gcc -o server tcpserver.c

.PHONY:clean

clean:
	rm -fr main server
