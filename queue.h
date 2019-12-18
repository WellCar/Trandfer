#ifndef _QUEUE_H
#define _QUEUE_H

#include"common.h"
#define MAX_SIZE 100

/* define quue struct */
struct link{
	videdata data;
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
void queue_push(struct queue *qd, const videdata * data,int *data_len);
int queue_pop(struct queue *qd, videdata * data,int *data_len);
void queue_destroy(struct queue *qd);
#endif