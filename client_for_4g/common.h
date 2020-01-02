#ifndef _COMMON_H
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
#include <sys/time.h>
#define MSG_HEADER	3
#define MSG_TYPE	1
#define MSG_ID		4
#define MSG_DATA	1000
#define MSG_CHECK	2
#define MSG_REAR	2
#define KEEP_ALIVE_BUFFER_LEN	50

#define SER_IP	"192.168.101.6"
#define SER_PORT	18888



enum STATUS{
	SUCCESS = 0,
	FAILED = 1
};

typedef unsigned char byte;
typedef struct _data {
	byte	head[MSG_HEADER];
	byte	type[MSG_TYPE];
	byte	id[MSG_ID];
	byte	data[MSG_DATA];
	byte	check_sum[MSG_CHECK];
	byte	rear[MSG_REAR];
}DATA;

#endif
