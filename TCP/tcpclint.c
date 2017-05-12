#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//include<sys/socket.h>			//for sockaddr
//include<netinet/in.h>			//for sockaddr_in 
#include<sys/fcntl.h>				//for O_RDONLY
#include<netdb.h>				
#define SERVER_PORT 5000
#define BUF_SIZE 4096

int main(int argc, char *argv[])
{	int c,s,bytes;
	char buf[BUF_SIZE],fname[255];
	struct hostent *h;
	struct sockaddr_in soc;
	
	if(argc!=3)	
		printf("Usage: #%s filename IPaddress\n\n",argv[1]),exit(1);

	h=gethostbyname(argv[2]);		//get server address
	if(!h)	 printf("\nError: gethostbyname failed"),	exit(0);

	memset(&soc,0,sizeof(soc));		//allocate memory for 'soc'
	soc.sin_family = AF_INET;			//assign values
	memcpy(&soc.sin_addr.s_addr, h->h_addr, h->h_length);
	soc.sin_port = htons(SERVER_PORT);
	
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s<0) printf("\nError: socket creation failed"),	exit(0);
	printf("\nSocket created for communication...");

	c = connect(s, (struct sockaddr*) &soc, sizeof(soc));
	if(c<0) printf("\nError: connection to server failed"),	exit(0);
	printf("\nConnected to Server...");
	
	if(!write(s, argv[1], 255)) 
		printf("\nError: Failed to write to socket"),exit(0);
	else 
	{	printf("\nFilename transmitted to the server..."
			"\ndata received from the server...\n\n");
	}
	while(bytes=read(s, buf, BUF_SIZE))
		write(1, buf, bytes);
}
