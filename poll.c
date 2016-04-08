#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<poll.h>
int main()
{
	struct pollfd _pd[2];
	_pd[0].fd=0;
	_pd[0].events=POLLIN;
	_pd[0].revents=0;
	_pd[1].fd=1;
	_pd[1].events=POLLOUT;
	_pd[1].revents=0;
	int timeout=3000;
	while(1){
		switch(poll(_pd,2,timeout))
		{
			case -1:
				printf("poll failed...\n");
				break;
			case 0:
				printf("time out...\n");
				break;
			default:
				{
					char buf[1024];
					memset(buf,'\0',sizeof(buf));
					int i=0;
					for(;i<2;i++)
					{
						int fd=_pd[i].fd;
						if(fd==0&&(_pd[i].revents&POLLIN))
						{
							ssize_t len=read(0,buf,sizeof(buf)-1);
							if(len<0)
							{
								perror("read");
								break;
							}
						    if((_pd[1].revents&POLLOUT))
							{
								printf("%s\n",buf);
							}
						}
					}
				}
		}
	}
	return 0;
}



