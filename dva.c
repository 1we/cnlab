#include<stdio.h>
int n, e, dist[20][20], graph[20][20];

void initialize()
{	int i, j;
	for(i = 1; i<= 20; i++)
		for(j = 1;  j <= 20;  j++) 	dist[i][j] = graph[i][j] = 0;
}
void getgraph()
{	int i, strt, end;
	printf("Enter no. of Routers & Edges in the graph:");
	scanf("%d%d", &n, &e);
	while(e-- > 0)
	{	printf("Enter start router --> end router\n");
		scanf("%d%d",&strt, &end);
		graph[strt][end] = graph[end][strt] = 1;
}	}
void gettable(int src)
{	int i, j;
	printf("\nEnter details of Source router %d\n",src);
	printf("Enter distance from Source router to Adjacent routers...\n");
	for(i=1; i <= n; i++) 
		if(graph[src][i] == 1) 
			printf("%d to %d :", src, i),
			scanf("%d", &dist[src][i]);
	printf("\nEnter the routing table details of Adjacent routers...\n");
	for(i = 1; i <= n; i++)
		if(graph[src][i] == 1)
		{	printf("Enter the details of routing table of router %d\n", i);
			for(j = 1; j <= n; j++)
			{	if(i == j) continue;
				printf("Distance from router %d to %d :", i, j);
				scanf("%d", &dist[i][j]);
}		}	}
void process(int src, int dest)
{	int min=32765, i, delay, via;
	for(i = 1; i <= n; i++)
		if(graph[src][i] == 1)
		{	delay = dist[src][i] + dist[i][dest];
			if(delay < min)
				min = delay,	via = i;
		}	
	printf("\nSuitable path from source router %d to destination router %d "
			"is through router %d with delay %d units\n",src, dest, via, min);
}
main()
{	int src, dest;
	initialize();
	getgraph();
	printf("\nEnter the Source & Destination router\n");
	scanf("%d%d",&src, &dest);
	gettable(src);
	process(src, dest); 
}
 
