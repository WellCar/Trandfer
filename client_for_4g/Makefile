# Makefile for client 4g transfer 

src	:=main.c queue.c

PHONY	:=all

all:$(src)
	gcc -o main $^ -lpthread
	
.PHONY:clean

clean:
	rm -fr main 