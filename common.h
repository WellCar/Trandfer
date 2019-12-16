#ifndef	_COMMON_H
#define _COMMON_H

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>


#define N (1024*9)
typedef unsigned char byte;
typedef struct{
	byte head[2];
	byte pay_load_size[2];
	byte flag;
	byte _type;
	byte start_time;
	byte end_time;
	byte total;
	byte index;
	byte pay_load[N];
	byte check;
}videdata;

/*
TCP Server setting
*/
#define TCP_SERVER_IP	"127.0.0.1"
#define TCP_SERVER_PORT	18888

/*
UPD Server setting
*/
#define UDP_SERVER_IP	"127.0.0.1"
#define UDP_SERVER_PORT	16666

void* upd(void* argv);
void* tcp(void* argv);

/*
Queue 
*/

#endif
