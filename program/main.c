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
#include "player.h"

#include <stdio.h>
#include <stdlib.h>

void BacaConfig(TabBangunan *T, MATRIKS *Peta, Player *P1, Player *P2){
	int N, M, B;
	int x, y, tipe;
	int i;
	char c;
	Bangunan tmp;

	STARTKATA();
	N = BacaAngka();
	M = BacaAngka();
	MakeMATRIKS(N, M, Peta);
	// printf("%d x %d\n", NBrsEff(*Peta), NKolEff(*Peta));

	MakeEmpty(T, 40);

	MakePlayer(P1, 1);
	MakePlayer(P2, 2);

	B = BacaAngka();

	for(i=1; i<=B; i++){
		if(i==1){
			AddIdxBangunan(P1, i);
		}

		if(i==2){
			AddIdxBangunan(P2, i);
		}

		tipe = CharToTipe(BacaHuruf());
		x = BacaAngka();
		y = BacaAngka();
		MakeBangunan(&tmp, tipe, x, y);
		TabElmt(*T, i) = tmp;
	}

	FillPeta(Peta, *T);
}

void menuAwal(int *choice){

	printf("halo selamat datang di permainan avatar hehe\n");
	printf("1. start game hehe\n");
	printf("2. load\n");
	printf(">> ");

	scanf("%d", choice);
	while(*choice != 1 && *choice != 2){
		printf("tidak tersedia hehe\n");
		printf(">> ");
		scanf("%d", choice);
	}
	getchar();
}

int main(){
	Player P1, P2;
	MATRIKS Peta;
	TabBangunan T;
	int choice;

	menuAwal(&choice);

	switch(choice){
		case 1: {
			printf("start!\n");
			BacaConfig(&T, &Peta, &P1, &P2);
			TakeTurn(&P1, &P2, &T, Peta);
			break;
		}
		case 2: {
			printf("load harusnya tapi belom dibuat T_T\n");
			// todo
			break;
		}
	}
	
	

	return 0;
}