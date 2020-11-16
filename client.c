#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
 
int main(void)
{
  int sockfd = 0,n = 0, hostname = 0;
  char recvBuff[1024];
  struct sockaddr_in serv_addr;
  struct hostent* host;
 
  memset(recvBuff, '0' ,sizeof(recvBuff));
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
      printf("\n Error : Could not create socket \n");
      return 1;
    }
 
  host = gethostbyname("server.melanie.cs164");

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5000);
  serv_addr.sin_addr.s_addr = *(long*)host->h_addr_list[0];
 
  if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
      printf("\n Error : Connect Failed \n");
      return 1;
    }

	char message[1025];
 
	printf("Enter message: ");
	scanf("%s", message); 
	

  	write(sockfd, message, strlen(message));


  	while((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
	{
      		recvBuff[n] = 0;
      		if(fputs(recvBuff, stdout) == EOF)
    		{
      			printf("\n Error : Fputs error");
    		}
      		printf("\n");
  	}
 
  if( n < 0)
    {
      printf("\n Read Error \n");
    }
 
 
  return 0;
}
