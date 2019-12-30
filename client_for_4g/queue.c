#include"queue.h"
#include<assert.h>

//#define DEBUG 1
void queue_init(struct queue * qd)
{
	qd->front = NULL;
	qd->rear = NULL;
	qd->size = 0;
}

int queue_empty(struct queue * qd)
{
	return (qd->size == 0) ? 1:0;
}

void queue_push(struct queue *qd, const DATA * data,int *data_len)
{
	struct  link * node = (struct link *)malloc(sizeof(struct link));
	assert(node != NULL);

	node->data = *data;
	node->data_len = *data_len;
	node->next = NULL;
	if(qd->size <= MAX_SIZE)
	{
		if(queue_empty(qd))
		{
			qd->front = node;
			qd->rear = node;
		}
		else
		{
			qd->rear->next = node;
			qd->rear = node;
		}
		++qd->size;
#ifdef DEBUG	
		printf("Now QueueSize=%d\n",(qd->size));
#endif
	}else
	{
		printf("ERROR: Queue FULL \n");exit(-1);
	}
}

int queue_pop(struct queue *qd, videdata * data,int * data_len)
{
	if(queue_empty(qd))
	{
		printf("Queue is emtpy ,can not exetue POP \n");
		return 0;
	}
	struct link * tmp = qd->front;
	*data = qd->front->data;
	*data_len = qd->front->data_len;
	qd->front = qd->front->next;
	free(tmp);
	--qd->size;
#ifdef DEBUG	
	printf("Now QueueSize=%d\n",(qd->size));
#endif
	return 1;
}

void queue_destroy(struct queue *qd)
{
	struct link * tmp;
	while(qd->front)
	{
		tmp = qd->front;
		qd->front = qd->front->next;
		free(tmp);
	}
}