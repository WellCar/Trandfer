/*
Date: 2019-12-16
Version: 0001
Ltc: Hotzone
Mail:jiangjian@hotzone.cn
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"config.h"

int main()
{
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	int res_s,res_r;

	int fd_log = open(".log",O_RDWR|O_CREAT,0644);
	int flag_failed = 0;
	struct sockaddr_in addr;
	char buf_flag[1] ={};
	socklen_t len=sizeof(addr);
	addr.sin_family =AF_INET;
	addr.sin_port =htons(PORT);
	addr.sin_addr.s_addr = inet_addr(IP);

	unsigned char * buffer = (unsigned char *)malloc(BUFFER_LEN);
	unsigned char * recv_buffer = (unsigned char *)malloc(BUFFER_LEN);
	while(1)
	{	
		/* Fill data by rand */
		for (size_t i = 0; i < len; i++)
		{
			*(buffer+i) = rand()%6+1;
		}

		res_s = sendto(sockfd,&buffer,BUFFER_LEN,0,(struct sockaddr*)&addr,sizeof(addr));
		printf("CLI| send %d byte to server\n",res_s);
		res_r = recvfrom(sockfd,&recv_buffer,BUFFER_LEN,0,(struct sockaddr*)&addr,&len);
		if(res_s == res_r)
		{
			if(0 == memcmp(buffer,recv_buffer,res_r))
			{
				write(fd_log,"Passed |\r\n",20);
			}else
			{
				write(fd_log,"Failed |\r\n",10);			
				flag_failed++;
			}
		}else
		{
			write(fd_log,"Failed |\r\n",10);			
			flag_failed++;
		}
		sleep(TIME_DELAY);
	}
	free(buffer);
	free(recv_buffer);
	close(sockfd);
}
