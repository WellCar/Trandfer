/*
Date: 2019-12-16
Version: 0001
Ltc: Hotzone
Mail:jiangjian@hotzone.cn
*/

#include "common.h"

extern pthread_mutex_t mutex;
videdata data;
unsigned int flag = 0;

void*  tcp(void* argv)
{
	printf("TCP_SEND...\n");
	int sockfd ,n;
	struct sockaddr_in  servaddr;

	while(1)
	{
		if(flag == 1)
		{
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
			int ret = send(sockfd,&data,sizeof(data),0);
			pthread_mutex_lock(&mutex);
			flag = 0;
			pthread_mutex_unlock(&mutex);
			printf("TCP send %d bytes done\n",ret);
			close(sockfd);
		}
	}
}



