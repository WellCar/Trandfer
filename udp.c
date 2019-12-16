/*
Date: 2019-12-16
Version: 0001
Ltc: Hotzone
Mail:jiangjian@hotzone.cn
*/

#include "common.h"
extern videdata data;
extern unsigned int flag;
extern pthread_mutex_t mutex;
void* upd(void* argv)
{
	printf("TCP_RECV...\n");
	int ufd,ret;
	struct sockaddr_in server_addr,client_addr;
	ufd = socket(AF_INET,SOCK_DGRAM,0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(UDP_SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(UDP_SERVER_IP);
	ret = bind(ufd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if( ret < 0){
		perror("Bind fail:\n");
	}

	char * buffer = (char *)malloc(sizeof(videdata));
	videdata * recv_data = (videdata *)malloc(sizeof(videdata));
	printf("%ld\n",sizeof(videdata));
	while(1)
	{
		if( flag == 0)
		{
			bzero(buffer,sizeof(buffer));
			int addrlen = sizeof(client_addr);
			ret = recvfrom(ufd,buffer,N,0,(struct sockaddr *)&server_addr,&addrlen);
			printf("UDP_RECV: %s,recv_len:%d\n",buffer,ret);
			memcpy(recv_data,buffer,sizeof(videdata));
			printf("head:%s\n",recv_data->head);
			printf("pay_load_size:%s\n",recv_data->pay_load_size);
			printf("check:%d\n",recv_data->check);
			memcpy(&data,buffer,sizeof(videdata));
			pthread_mutex_lock(&mutex);
			flag = 1;
			pthread_mutex_unlock(&mutex);
		}
	}
	close(ufd);
}


