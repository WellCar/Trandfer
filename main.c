/*
Date: 2019-12-16
Version: 0001
Ltc: Hotzone
Mail:jiangjian@hotzone.cn
*/

#include "common.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc,char **argv)
{
	pthread_t tid[2];
	pthread_mutex_init(&mutex,NULL);
	int ret = pthread_create(&tid[0],NULL,upd,NULL);
	if(ret !=0){
		perror("Create thread for upd_recv failed.\n");
		exit(EXIT_FAILURE);
	}
	ret = pthread_create(&tid[1],NULL,tcp,NULL);
	if(ret !=0){
		perror("Create thread tcp_send failed.\n");
		exit(EXIT_FAILURE);
	}
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}

