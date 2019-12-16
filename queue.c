#include "common.h"

#define SIZE 32

typedef struct QNode //节点结构
{
	videdata data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct Link_queue//队列的链表结构
{
	QueuePtr front,rear; //队列的头、尾指针
}LinkQueue;

typedef int Status;

#define ERR_OK 0
#define ERR_NO 1

//入队操作
Status Enqueue(LinkQueue* Q,QElemType e)
{
	QueuePtr newNode = (QueuePtr)malloc(sizeof(QNode)); //新建队列节点

	size_t len = strlen(e);

	newNode->data = (QElemType)malloc(len+2*sizeof(char));    //为节点数据域分配内存

	//数据域循环赋值
	int i=0;
	for(i=0;i<len;i++)
	{
		newNode->data[i] = e[i];
	}
	newNode->data[len] = '\0';


	newNode->next = NULL;

	Q->rear->next = newNode; //队列的尾指针指向的当前节点的下一个位置，指向s
	Q->rear = newNode;    //队列的尾指针向后移动至新节点
	return ERR_OK;

}

//出队操作,使用后需要释放e的内存
Status DeQueue(LinkQueue* Q,QElemType* e)
{
	QueuePtr p;

	p = Q->front->next; //要出队的是头结点的下一个节点
	//*e = p->data;    //将要出队的节点数据赋值给e
	size_t len = strlen(p->data);

	*e=(QElemType)malloc(len+2*sizeof(char));


	int i=0;
	for(i=0;i<len;i++)
	{
		(*e)[i] = p->data[i];
	}
	(*e)[len]='\0';

	Q->front->next = p->next;

	if(Q->rear == p) //尾指针指向p说明队列空了
	{
		Q->rear = Q->front;
	}

	free(p->data);
	free(p);
	return ERR_OK;
}

