#include "../listlinier.h"
#include "../../boolean/boolean.h"
#include "../../arraydinpos/arraydinpos.h"

#include <stdio.h>
#include <stdlib.h>

int main(){
	List L;
	addressL P;

	LCreateEmpty(&L);
	printf("isEmpty? : %d\n", IsLEmpty(L));

	printf("InsVFirst 1, ");
	InsVFirst(&L, 1);
	printf("InsVLast 2, ");
	InsVLast(&L, 2);
	printf("InsVLast 3, ");
	InsVLast(&L, 3);
	PrintInfo(L);
	printf("\n");

	printf("NbElmt: %d\n", NbElmt(L));

	printf("DelFirst, ");
	DelFirst(&L, &P);
	PrintInfo(L);
	printf("\n");

	printf("DelP 2, ");
	DelP(&L, 2);
	PrintInfo(L);
	printf("\n");

	printf("DelLast, ");
	DelLast(&L, &P);
	PrintInfo(L);
	printf("\n");

}
