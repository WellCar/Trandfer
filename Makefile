# Date: 2019-12-16
# Version: 0001
# Ltc: Hotzone
# Mail:jiangjian@hotzone.cn

SRC	:=main.c tcp.c udp.c queue.c
MAIN	:=main
EX_LIB	:=-lpthread
CFLAGS	:=-g -Wall
TEST	:=udpclient tcpserver

ALL:${SRC} ${TEST}
	${CC}  -o ${MAIN} ${SRC} ${EX_LIB}

.PHONY:clean test
clean:
	rm ${MAIN} ${TEST}

udpclient:udpclient.c
	${CC}  -o $@ $<

tcpserver:tcpserver.c
	${CC}  -o $@ $<

test:
	${MAKE} -C test
	
