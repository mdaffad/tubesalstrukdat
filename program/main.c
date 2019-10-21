#include "boolean.h"
#include "point.h"
#include "arraydinpos.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include "queue.h"
#include "stackt.h"
#include "listlinier.h"
#include "bangunan.h"
#include "matrikskar.h"

#include <stdio.h>
#include <stdlib.h>

int main(){
	// test print bangunan
	TabBangunan T;
	Bangunan B;

	MakeEmpty(&T, 100);

	for(int i=1; i<=10; i++){
		MakeBangunan(&B, 1, i, 0);
		TabElmt(T, i) = B;
	}
	
	PrintArrayBangunan(T);
	return 0;
}