#include "../graf.h"
#include <stdio.h>

int main(){
	Graph G;
	adrNode Pn;
	adrSuccNode P;
	int a, b;

	CreateGraph(1, &G);
	InsertNode(&G, 2, &Pn);
	InsertNode(&G, 3, &Pn);

	Connect(&G, 1, 2);
	Connect(&G, 1, 3);
	Connect(&G, 2, 3);

	printf("Enter 2 Nums: ");
	scanf("%d %d", &a, &b);

	if(isConnected(G, a, b)){
		printf("Connected\n");
	}
	else{
		printf("Not Connected\n");
	}

	return 0;
}