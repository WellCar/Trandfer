/*
Date: 2019-12-16
Version: 0001
Ltc: Hotzone
Mail:jiangjian@hotzone.cn
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include"config.h"

int main()
{
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	int res =0 ;

    struct sockaddr_in addr;
    addr.sin_family =AF_INET;
    addr.sin_port =htons(PORT);
    addr.sin_addr.s_addr=inet_addr(IP);

    int ret =bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(0>ret)
    {
        printf("bind\n");
        return -1;

    }
    struct sockaddr_in cli;
    socklen_t len=sizeof(cli);

	unsigned char * buffer = (unsigned char *)malloc(BUFFER_LEN*2);
    while(1)
    {
        res = recvfrom(sockfd,&buffer,BUFFER_LEN,0,(struct sockaddr*)&cli,&len);
        printf("SER| Recv %d bytes data\n",res);
        sendto(sockfd,&buffer,res,0,(struct sockaddr*)&cli,len);
		printf("SER| Send %d bytes data\n",res);
    }
    close(sockfd);

}