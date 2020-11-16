#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
 
int main(void)
{
  int listenfd = 0,connfd = 0, n = 0, hostname = 0;
  
  struct sockaddr_in serv_addr;
 
  char sendBuff[1025]; 
  int numrv;  
 
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("socket retrieve success\n");
  
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));
      
  serv_addr.sin_family = AF_INET;    
	//hostname = gethostbyname("server.melanie.cs164");
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  serv_addr.sin_port = htons(5000);
 
  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
  
  if(listen(listenfd, 10) == -1){
      printf("Failed to listen\n");
      return -1;
  }
     
  
  	while(1)
    	{
      
      		connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request

		char message[1025];

      		if((n = read(connfd, message, sizeof(message) - 1)) > 0)
		{
			message[n] = 0;
			if(fputs(message, stdout) == EOF) 
			{
				printf("\n Error: Fputs error");
			}
			printf("\n");
		}
	
		if(n < 0) { printf("\n Read Error \n"); }
		message[sizeof(message) + 1] = '\n';
		
		if(strcmp(message, "Hi") == 0 || strcmp(message, "hi") == 0) 
		{
			strcpy(sendBuff, "Hi");
		} else if(strcmp(message, "Bye") == 0 || strcmp(message, "bye") == 0) {
			strcpy(sendBuff, "Bye");
		} else {
			strcpy(sendBuff, "Message from server 33");
		}

      		write(connfd, sendBuff, strlen(sendBuff));
 
	      	close(connfd);    
      		sleep(1);
    	}
 
 
  return 0;
}
