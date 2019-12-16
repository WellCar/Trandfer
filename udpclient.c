#include "common.h"
 

void data_fill(videdata *buffer);
int main()
{
	int lfd,ret,addrlen;
	struct sockaddr_in saddr;
	videdata send_data = {
		.head = "X",
		.pay_load_size = "A",
		.flag = 'A',
		._type = 'B',
		.start_time = '1',
		.end_time = '2',
		.total = 'C',
		.index = 'D',
		.pay_load = {0xFF},
		.check = 'O',
	};
	/*
	videdata * send_data = (videdata *)malloc(sizeof(videdata));
	send_data->head = "X";
	send_data->.pay_load_size = "A";
	send_data->flag = 'A';
	send_data->_type = 'B';
	send_data->start_time = '1';
	send_data->end_time = '2';
	send_data->total = 'C';
	send_data->index = 'D';
	send_data->pay_load = {0xFF};
	send_data->check = 'O';
	char * buffer =  (char *)malloc(sizeof(send_data));
	printf("sizeof(send_data):%d\n",sizeof(send_data));
	memcpy(buffer,&send_data,sizeof(send_data));
	*/

	lfd = socket(AF_INET,SOCK_DGRAM,0);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(UDP_SERVER_PORT);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int i = 0;
	while(1)
	{
		int res =0;
		res = sendto(lfd,(char *)&send_data,sizeof(send_data),0,(struct sockaddr*)&saddr,sizeof(saddr));
		printf("Send %d done %d\n",res,i++);
		usleep(1000);	
	}	
	close(lfd);
	return 0;
}

