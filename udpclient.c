#include "common.h"

#define PAY_LOAD 1024*9
static int encode_data(const videdata * data,char * buffer,const char * pay_load,int pay_load_len);

int main()
{
	int lfd,ret,addrlen,res;
	int i = 0;
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
		.check = 'O',
	};
	char pay_load[PAY_LOAD];
	memset(pay_load,0xFF,PAY_LOAD);

	lfd = socket(AF_INET,SOCK_DGRAM,0);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(UDP_SERVER_PORT);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	char * buffer = (char *)malloc(BUFFER_SIZE);
	int buffer_len = encode_data(&send_data,buffer,pay_load,PAY_LOAD);
	while(1)
	{
		res = sendto(lfd,buffer,buffer_len,0,(struct sockaddr*)&saddr,sizeof(saddr));
		printf("Send %d done %d\n",res,i++);
		sleep(1);	
	}	
	close(lfd);
	return 0;
}

static int  encode_data(const videdata * data,char * buffer,const char * pay_load,int pay_load_len)
{
	memcpy(buffer,data->head,2);
	memcpy(buffer+2,data->pay_load_size,2);
	memcpy(buffer+4,&data->flag,1);
	memcpy(buffer+5,&data->_type,1);
	memcpy(buffer+6,data->start_time,4);
	memcpy(buffer+10,data->end_time,4);
	memcpy(buffer+14,&data->total,1);
	memcpy(buffer+15,&data->index,1);
	memcpy(buffer+16,pay_load,pay_load_len);
	memcpy(buffer+16+pay_load_len,&data->check,1);
	return 17+pay_load_len;
}

