#include<stdio.h>
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

int main()
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


return 0;
}












void receve_data(int)
{

     if


}
int main(int argc, char const *argv[])
{
	cfd = socket(AF_INET,SOCK_STREAM,0);

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(5678);

	bind(sfd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));

	check=listen(sfd,10);
	if(check == -1)
		printf("error in listen\n");

	len = sizeof(struct sockaddr_in);
	cfd = accept(sfd,(struct sockaddr *)&caddr, &len);
	
	if(cfd == -1)
		printf("error while accept\n");

	write(cfd,"hello client\n",13);
	read(cfd,buff,1024);

	printf("client send:%s\n",buff);
	
	close(cfd);
	close(sfd);
}
