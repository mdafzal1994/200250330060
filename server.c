#include<stdio.h>

#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<linux/in.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include<stdio.h>

int sfd,cfd,check;
struct sockaddr_in saddr;
struct sockaddr_in caddr;
int len;
unsigned char buff[1024];

////////////////////////////////////////////////////////////////////////////////////////////
////// msege que//////////////////////

void msg_qu()
{

struct mq_attr cdac_atrr;

               cdac_atrr.mq_flags=0;       /* Flags (ignored for mq_open()) */
               cdac_atrr.mq_maxmsg=4;      /* Max. # of messages on queue */
               cdac_atrr.mq_msgsize=128;     /* Max. message size (bytes) */
               cdac_atrr.mq_curmsgs=0;     /* # of messages currently in queue
                                       (ignored for mq_open()) */


char mq_buff[512];

mqd_t  mqfd;

       mqfd= mq_open("/cdacmq",O_RDONLY|O_CREAT,S_IRUSR|S_IWUSR,&cdac_atrr);
        if(mqfd==-1)
        {
          perror("file not open\n");

        }

   int prior;
        ssize_t len;
                len=mq_receive(mqfd,mq_buff,128,&prior);
        if(len==-1){

         perror("mesg not send\n");
        }

                 printf("%s\n",mq_buff);



        mq_close(mqfd);


}




//////////////////////////////////
int main()
{
                
                struct sockaddr_in saddr;
                char buff1[40];
		char buff2[40];
		char buff3[40];
		char buff4[40];
                
		int tcpsock_fd=socket(AF_INET,SOCK_STREAM,0);//listen tcp	
                if(tcpsock_fd<0)
                {
                 printf("socket creation failed for tcp\n");
                 return -1;
                }

		 saddr.sin_family=AF_INET;
                 saddr.sin_port=htons(2086);
                 saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
		
                 int sock_temp=bind(tcpsock_fd,(struct sockaddr *)&saddr,sizeof(saddr));//tcp
		 
		
		saddr.sin_port=htons(2087);
                 saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
		//Binding TCP socket for client_temp_thur
                 int sock_thur=bind(tcpsock_fd,(struct sockaddr *)&saddr,sizeof(saddr));//tcp
		 

		saddr.sin_port=htons(2088);
                 saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
		//Binding TCP socket for client_Acc
                 int sock_acc=bind(tcpsock_fd,(struct sockaddr *)&saddr,sizeof(saddr));//tcp
		 


		saddr.sin_port=htons(2089);
                 saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
		//Binding TCP socket for client_gyro
                 int sock_gyro=bind(tcpsock_fd,(struct sockaddr *)&saddr,sizeof(saddr));//tcp
		 

		while(1)
		{

			int gyro=listen(sock_gyro,10);
			int acc=listen(sock_acc,10);
			int thur=listen(sock_thur,10);
			int temp=listen(sock_temp,10);

			read(gyro,buff4,sizeof(buff4));
			read(acc,buff3,sizeof(buff3));
			read(thur,buff1,sizeof(buff2));
			read(temp,buff1,sizeof(buff1));
			
			


		}
	close(cfd);
	
