/*
Date: 2019-12-16
Version: 0001
Ltc: Hotzone
Mail:jiangjian@hotzone.cn
*/

#include "common.h"
#include "queue.h"

//#define DEBUG 1
#define MAGE 1024

extern pthread_mutex_t mutex;
extern struct queue qd;
static int  encode_data(const videdata * data,char * buffer,int data_len);

void*  tcp(void* argv)
{
	int sockfd,n,ret;
	struct sockaddr_in  servaddr;
	videdata *data = (videdata *)malloc(sizeof(videdata));
	int data_len;
	char * buffer = (char *)malloc(BUFFER_SIZE);
	while(1)
	{
		if (!queue_empty(&qd))
		{	
			ret = 0;
			data_len = 0;
			memset(buffer,0,BUFFER_SIZE);
			if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
				printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
				return 0;
			}   
			memset(&servaddr, 0, sizeof(servaddr));
			servaddr.sin_family = AF_INET;
			servaddr.sin_port = htons(TCP_SERVER_PORT);
			if( inet_pton(AF_INET,TCP_SERVER_IP, &servaddr.sin_addr) <= 0){ 
				return 0;
			}   

			if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){ 
				printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
				return 0;
			} 	
			pthread_mutex_lock(&mutex);
			queue_pop(&qd,data,&data_len);





			
			pthread_mutex_unlock(&mutex);
			printf("TCP|  queue not empty,Ready to transfer data len= %d\n",data_len);	
			encode_data(data,buffer,data_len);
			char * _buffer = buffer;
#ifdef	DEBUG 
			printf("TCP| ----------------------------------------------------- |TCP \n");
			for (size_t i = 0; i <= 9233; i++)
			{
				/* code */
				printf("%c",*(_buffer+i));
			}
			printf("\nTCP| ----------------------------------------------------- |TCP \n");
#endif
			/*
			while(data_len >= MAGE)
			{
				ret += send(sockfd,(void *)_buffer,data_len-1024*4,0);
				_buffer += MAGE;
				data_len -= MAGE;
			}
			ret +=send(sockfd,(void *)_buffer,data_len,0);
			*/
			ret =send(sockfd,(void *)_buffer,data_len,0);
			if(ret != -1)
			{
				printf("TCP|  tcp thread send %d bytes data \n",ret);	
			}else{
				printf("TCP|  tcp thread send ERROR \n");	
			}
			close(sockfd);
		}
	}
}

static int  encode_data(const videdata * data,char * buffer,int data_len)
{
	memcpy(buffer,data->head,2);
	memcpy(buffer+2,data->pay_load_size,2);
	memcpy(buffer+4,&data->flag,1);
	memcpy(buffer+5,&data->_type,1);
	memcpy(buffer+6,data->start_time,4);
	memcpy(buffer+10,data->end_time,4);
	memcpy(buffer+14,&data->total,1);
	memcpy(buffer+15,&data->index,1);
	memcpy(buffer+16,data->pay_load,data_len-17);
	memcpy(buffer+16+data_len,&data->check,1);
	printf("TCP|  fill %d bytes data to buffer\n",data_len);
}


