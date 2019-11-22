#include <stdio.h>
#include "../queue.h"
#include "../../boolean/boolean.h"

#include <stdlib.h>

int main(){
	Queue Q;

	QCreateEmpty(&Q,2);
	printf("isEmpty? : %d\n", IsQEmpty(Q));

	printf("Add 1, ");
	Add(&Q, 1);
    printf("Add 2, ");
	Add(&Q, 2);
	printf("\n");
    printf("isFull? : %d\n", IsQFull(Q));
    printf("QNBElmt? : %d\n", QNBElmt(Q));

    int X;
    Del (&Q, &X);
    printf("Del? : %d\n", X);
    Del (&Q, &X);
    printf("Del? : %d\n", X);
    return 0;
}