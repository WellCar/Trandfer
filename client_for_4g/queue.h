#ifndef _QUEUE_H
#define _QUEUE_H


#include<stdio.h>
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
#define MSG_HEADER	3
#define MSG_TYPE	1
#define MSG_ID		4
#define MSG_DATA	1000
#define MSG_CHECK	2
#define MSG_REAR	2

#define SER_IP	"127.0.0.1"
#define SER_PORT	18888

#define MAX_SIZE	100

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

/* define quue struct */
struct link{
	DATA data;
    int data_len;
	struct link * next;
};

struct queue{
	struct link * front;
	struct link * rear;
	int size;
};

void queue_init(struct queue * qd);
int queue_empty(struct queue * qd);
void queue_push(struct queue *qd, const DATA * data,int *data_len);
int queue_pop(struct queue *qd, DATA * data,int *data_len);
void queue_destroy(struct queue *qd);
#endif