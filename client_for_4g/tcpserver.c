#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define TCP_SERVER_IP	"127.0.0.1"
#define TCP_SERVER_PORT	18888
#define BUFFER_SIZE (1024*20)

int main(int argc, char** argv){
    int  listenfd, connfd;
    struct sockaddr_in  servaddr;
    char  buff[BUFFER_SIZE];
    int  n;

    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(TCP_SERVER_PORT);

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    if( listen(listenfd, 10) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    printf("======waiting for client's request======\n");
    if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
	    printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
    }
    while(1){
        n = recv(connfd, buff, BUFFER_SIZE, 0);
        buff[n] = '\0';
        printf("recv msg from client: %s...,Bytes:%d\n", buff,n);
    }
    close(connfd);
    close(listenfd);
    return 0;
}
