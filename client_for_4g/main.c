/*
Date: 2019-12-16
Version: 0001
Ltc: Hotzone
Mail:jiangjian@hotzone.cn
*/
#include "queue.h"

#define KEEP_ALIVE_BUFFER_LEN	50

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct queue  * qd;

DATA kell_alive;
byte * keep_alive_buffer;
byte * data_buffer;

int is_big()
{
	int a = 1;
	char *p = (char *)&a;
	return (*p == 1) ? 1:0;
}

void assign_memory()
{
	qd = (struct  queue*)malloc(sizeof(struct queue));
	keep_alive_buffer = (byte*)malloc(KEEP_ALIVE_BUFFER_LEN);
	data_buffer = (byte*)malloc(26);
}

unsigned short check_sum(char * d,int len)
{
	char b =0;
	unsigned short crc = 0xFFFF;
	int i = 0;
	int j = 0;
	for(i=0;i<len;i++)
	{
		for(j=0;j<8;j++)
		{
			b = ((d[i]<<j)&0x80)^((crc&0x8000)>>8);
			crc <<= 1;
			if(b != 0)
			{
				crc ^= 0x1021;
			}
		}
	}
	return crc;
}

void sys_init()
{
	assign_memory();
	queue_init(qd);
}

void meg_head_set()
{
	*(keep_alive_buffer) = 0xAA;
	*(keep_alive_buffer+1) = 0xAB;
	*(keep_alive_buffer+2) = 0xAC;
}

void msg_type_set()
{
	*(keep_alive_buffer+3) = 0x01;
}

void msg_id_set()
{
	memcpy(keep_alive_buffer+4,"XXXX",4);
}

void msg_check_sum_set()
{
	unsigned short crc = check_sum(keep_alive_buffer+45,2);
	if(is_big())
	{
		memcpy(keep_alive_buffer+45,(char *)&crc,2);
	}else
	{
		memcpy(keep_alive_buffer+45,(char *)&crc,2);
	}
	
}

void msg_data_set()
{
	*(keep_alive_buffer+8) = 0x02;
	*(keep_alive_buffer+9) = 0x10;
	memcpy(keep_alive_buffer+10,"44",4);
	*(keep_alive_buffer+14) = 0x01;
	*(keep_alive_buffer+15) = 0xFF;
	memcpy(keep_alive_buffer+16,"XX",2);
	*(keep_alive_buffer+18) = 0xFF;
	*(keep_alive_buffer+19) = 0x01;
	memcpy(keep_alive_buffer,data_buffer,26);
}

void msg_rear_set()
{
	*(keep_alive_buffer+47) = 0xAA;
	*(keep_alive_buffer+48) = 0xAB;
	*(keep_alive_buffer+49) = 0xAC;
}

void b_clear()
{
	memset(keep_alive_buffer,0,KEEP_ALIVE_BUFFER_LEN);
	memset(data_buffer,0,26);
}

void update_keep_alive_data()
{
	b_clear();
	meg_head_set();
	msg_type_set();
	msg_id_set();
	msg_data_set();
	msg_check_sum_set();
	msg_rear_set();
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
	}else{
		printf("Connect success.\n");
	}
	while(1)
	{
		if(queue_empty(qd))
		{
			/*ERROR Cannot use sleep ,Need to chang*/
			sleep(1);
			// Send KeepAlive
			update_keep_alive_data();
			size_t ret = send(sockfd,keep_alive_buffer,KEEP_ALIVE_BUFFER_LEN,0);
			if(ret == -1)
			{
				printf("Send keep alive failed\n");
			}else
			{
				printf("Send Keep Alive bytes[%ld] ...\n",ret);
			}
		}else
		{
			// Send normal data
			printf("Delay 1 s\n");
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

