/*
Date: 2019-12-16
Version: 0001
Ltc: Hotzone
Mail:jiangjian@hotzone.cn
*/
#include "queue.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *tcp_thread(void *);
void *deal_thread(void *);
struct queue qd;

int main(int argc,char **argv)
{
	pthread_t tcpclient,deal;
	pthread_mutex_init(&mutex,NULL);
	if(pthread_create(&tcpclient,NULL,tcp_thread,NULL) != 0)
	{
		perror("Create thread for rcp_thread failed\n");
		exit(EXIT_FAILURE);
	}
	if(pthread_create(&deal,NULL,deal_thread,NULL) != 0)
	{
		perror("Create thread for deal failed\n");
		exit(EXIT_FAILURE);
	}
	pthread_join(tcpclient,NULL);
	pthread_join(deal,NULL);
	return 0;
}


void *tcp_thread(void * argv)
{	
	int sockfd,ret;
	struct sockaddr_in server_addr;
	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
		printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
		return 0;
	}   
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SER_PORT);
	if( inet_pton(AF_INET,SER_IP, &server_addr.sin_addr) <= 0){ 
		return 0;
	}   

	if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){ 
		printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
		return 0;
	} 
	while(1)
	{
		if(queue_empty(&qd))
		{
			// Send KeepAlive
		}else
		{
			// Send normal data
		}
		

	}
}

void *deal_thread(void *argv)
{
	printf("deal_thread \n");
	/* Data deal */
	
}