/*
Date: 2019-12-16
Version: 0001
Ltc: Hotzone
Mail:jiangjian@hotzone.cn
*/

#include "common.h"
#include "queue.h"

// extern glogbel varible 
extern pthread_mutex_t mutex;
extern struct queue qd;

void decode(char * buffer,videdata *data,int len);

void* upd(void* argv)
{
	int ufd,ret;
	struct sockaddr_in server_addr,client_addr;
	int addrlen = sizeof(client_addr);
	ufd = socket(AF_INET,SOCK_DGRAM,0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(UDP_SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(UDP_SERVER_IP);
	ret = bind(ufd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	if( ret < 0){
		perror("UDP|  Bind fail:\n");
	}

	char * buffer = (char *)malloc(BUFFER_SIZE);
	videdata * data = (videdata *)malloc(sizeof(videdata));
	while(1)
	{
		memset(buffer,0,BUFFER_SIZE);
		memset(data,0,sizeof(videdata));
		ret = recvfrom(ufd,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server_addr,&addrlen);
#ifdef  DEBUG
		printf("UDP| ----------------------------------------------------- |UDP \n");
		for (size_t i = 0; i <= ret; i++)
		{
			/* code */
			printf("%c",*(buffer+i));
		}
		printf("\nUDP| ----------------------------------------------------- |UDP \n");
#endif
		if(ret <= 17 )
		{
			printf("UDP|  udp thread recv %d bytes data, ignore this data,and continue\n",ret);
			continue;
		}else{
			printf("UDP|  udp thread recv %d bytes data\n",ret);
			data->pay_load = (char *)malloc(ret-17);
			decode(buffer,data,ret);
			pthread_mutex_lock(&mutex);
			queue_push(&qd,data,&ret);
			pthread_mutex_unlock(&mutex);
			//free(data->pay_load);
		}
	}
	close(ufd);
}

void decode(char * buffer,videdata *data,int len)
{
	memcpy(data->head,buffer,2);
	memcpy(data->pay_load_size,buffer+2,2);
	memcpy(&data->flag,buffer+4,1);
	memcpy(&data->_type,buffer+5,1);
	memcpy(data->start_time,buffer+6,4);
	memcpy(data->end_time,buffer+10,4);
	memcpy(&data->total,buffer+14,1);
	memcpy(&data->index,buffer+15,1);
	memcpy(data->pay_load,buffer+16,len-17);
	memcpy(&data->check,buffer+len-1,1);
	printf("UDP|  Decode net data to local VIDEDATA done\n");
}



