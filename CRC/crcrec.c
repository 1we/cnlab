#include<stdio.h>
#include<stdlib.h>
#define GR1 0x0810	//G = 0x11021

static int R=0;

void updateCRC(int x)
{
	int i, x_msb;
	for(i=7;i >= 0;i--) 
	{
		x_msb = (x >> i) & 1; 		/* k = msb of x*/
		R = (R & 0x8000)?( ((R ^ GR1) << 1) + (x_msb ^ 1) ):((R << 1) + x_msb);
		R &= 0xffff;
}	}

int main(int argc, char** argv)
{	
int c;
	FILE *fp;
	if(argc ==1)
		printf("Usage:#%s filename\n\n",argv[0]), 	exit(0);
	if( (fp = fopen(argv[1],"r")) == NULL)
		printf("Error: Cannot open '%s' file.\n\n",argv[1]),	exit(1);
	printf("Message Received...\n");
	while ((c=getc(fp)) != EOF)
		updateCRC(c);
	printf("\nCRC Computed : %s",R==0? "No errors detected...\n":"Error in Transmission...\n");
	fclose(fp);
}
