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
	Bangunan B;
	MakeBangunan(&B, 1, 5, 7);
	PrintBangunan(B);
	return 0;
}