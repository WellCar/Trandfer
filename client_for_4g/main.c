/*
Date: 2019-12-16
Version: 0001
Ltc: Hotzone
Mail:jiangjian@hotzone.cn
*/
#include "queue.h"

#define KEEP_ALIVE_BUFFER_LEN	50

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct queue qd;

DATA kell_alive;
byte * keep_alive_buffer;

void sys_init()
{
	queue_init(&qd);
}

void update_keep_alive_data()
{
	memset(keep_alive_buffer,0,KEEP_ALIVE_BUFFER_LEN);
	keep_alive_buffer = (byte*)malloc(KEEP_ALIVE_BUFFER_LEN);
	*(keep_alive_buffer) = 0xAA;
	*(keep_alive_buffer+1) = 0xAB;
	*(keep_alive_buffer+2) = 0xAC;
	memcpy(keep_alive_buffer+3,"XXXX",4);
	*(keep_alive_buffer+7) = 0x02;
	*(keep_alive_buffer+8) = 0x10;
	memcpy(keep_alive_buffer+9,"44",4);
	*(keep_alive_buffer+13) = 0x01;
	*(keep_alive_buffer+14) = 0xFF;
	memcpy(keep_alive_buffer+15,"XX",2);
	*(keep_alive_buffer+17) = 0xFF;
	*(keep_alive_buffer+18) = 0xAB;
} 

void *deal_thread(void *argv)
{
	printf("deal_thread \n");
	/* Data deal */
	while (1)
	{
		/* code */
		sleep(1);
	}
	
}

void *tcp_thread(void * argv)
{	
	printf("tcp_thread\n");
	sys_init();
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
			printf("Send Keep Alive bytes[");
			/*ERROR Cannot use sleep ,Need to chang*/
			sleep(1);
			// Send KeepAlive
			update_keep_alive_data();
			int ret = send(sockfd,keep_alive_buffer,KEEP_ALIVE_BUFFER_LEN,0);
			if(ret == -1)
			{
				printf("Send keep alive failed\n");
			}else
			{
				printf("%d]...\n",ret);
			}
		}else
		{
			// Send normal data
			sleep(1);
		}
	}
}

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

