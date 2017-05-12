#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//include<sys/socket.h>			//for sockaddr
//include<netinet/in.h>			//for sockaddr_in 
#include<sys/fcntl.h>				//for O_RDONLY
#include<netdb.h>				
#define SERVER_PORT 5000
#define BUF_SIZE 4096

int main()
{	int 	s, b, l, fd, sa, bytes, on = 1;
 	char 	buf[BUF_SIZE], fname[255];
	struct sockaddr_in 	soc;	
 	memset(&soc, 0, sizeof(soc));		//reset soc structure
	soc.sin_family = AF_INET;			//assign values
 	soc.sin_addr.s_addr = htonl(INADDR_ANY);
 	soc.sin_port = htons(SERVER_PORT);
 	s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
 	if(s<0) 		printf("Error: socket creation failed"), exit(0);
 	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
	b = bind(s, (struct sockaddr*)&soc, sizeof(soc));
 	if(b<0) 	printf("Error: bind failed"), exit(0);
 	listen(s, 5);					//listen soc for any request
            while(1)
 	{	printf("\nWaiting for request...\n");
		sa = accept(s, 0, 0);			//create a socket for comnucn
		if(sa < 0) printf("Error:accept failed");
		printf("\nRequest received...");

		memset(fname, 0, sizeof(fname));
   		read(sa, fname, BUF_SIZE);		//read file name from soc
		printf("\nrequested filename: %s", fname);
		fd = open(fname, O_RDONLY);	//open file to READ 
   		if(fd < 0)
		{	printf("\nError message sent to client...\n");
			write(sa, "could not open requested file", 40);
		}
		else {
   		while(bytes = read(fd, buf, BUF_SIZE))
 			write(sa, buf, bytes);		//write the contents to soc
		printf("\nFile Transmitted to Client...\n");
		close(fd);
		}
   		close(sa);
}	}
 
