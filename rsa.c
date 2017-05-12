#include<stdio.h>
#include<fcntl.h>
#define MAX 100
#define MSGFILE "a.txt"
int gcd(int x, int y)
{
return y==0? x:gcd(y,x%y);
}
int rsa(int txt, int ed, int n)
{	int i=1,rem=1;
	while(i++<=ed)
		rem=(rem*txt)%n;
	return rem;
}
short prime(int no)
{	int i;
	for(i=2; i<=no/2; i++)
		if(no%i==0) 
		return 0;
	return 1;
}
int main()
{ 	char	msg[MAX];
 	int 	pt[MAX], ct[MAX], p, q, n, z, e, d, i, len;
	FILE 	*fd;
	do{
	printf("\nEnter 2 large prime numbers (p & q):\n");
	scanf("%d %d", &p, &q);
	}while(!prime(p) || !prime(q));
	n = p * q;
	z = (p - 1) * (q - 1);
	do
	{	printf("\nEnter a prime number for encryption (e) relative to %d(z):",z);
		scanf("%d",&e);
	}while(!prime(e) || e>n || gcd(e,z)!=1); 
	for(d = 2; d < z; d++)				//calculate decryptio key 'd'
		if((e*d)%z == 1)
			break;
	printf("Enter the Message\n");			//get message from owner.
	len=read(1,msg,MAX)-1;
	for(i = 0; i < len; i++)				//store it in plain text array
		pt[i]=msg[i];
	printf("\nPrivate Key Pair(e, n) = (%d, %d)\nPublic Key Pair (d, n) = (%d, %d)\n\n", e, n, d, n);		
	printf("\nCipher Text=");
	for(i = 0; i < len; i++)				//convert plain to cipher text
		printf("%d ", ct[i] = rsa(pt[i], e, n));
	printf("\n\nPlain Text=");	
	for(i = 0; i < len; i++)				//convert cipher to plain text
		printf("%c",rsa(ct[i],d,n));
	printf("\n\n"); 
}
