#include "./boolean/boolean.h"
#include "./point/point.h"
#include "./arraydinpos/arraydinpos.h"
#include "./mesinkar/mesinkar.h"
#include "./mesinkata/mesinkata.h"
#include "./queue/queue.h"
#include "./stackt/stackt.h"
#include "./listlinier/listlinier.h"
#include "./bangunan/bangunan.h"
#include "./matrikskar/matrikskar.h"
#include "./player/player.h"
#include "./graf/graf.h"
#include "./pcolor/pcolor.h"

#include <stdio.h>
#include <stdlib.h>

void BacaConfig(TabBangunan *T, MATRIKS *Peta, Player *P1, Player *P2, Graph *G){
	int N, M, B;
	int x, y, tipe;
	int i, j;
	char c;
	adrNode Pn;
	Bangunan tmp;

	// STARTKATA("./bin/config.txt");
	// STARTKATA("./bin/petakecil.txt");
	STARTKATA("./bin/petakecilbgt.txt");

	N = BacaAngka();
	M = BacaAngka();
	MakeMATRIKS(N, M, Peta);
	// printf("%d x %d\n", NBrsEff(*Peta), NKolEff(*Peta));

	MakeEmpty(T, 40);

	MakePlayer(P1, 1);
	MakePlayer(P2, 2);

	B = BacaAngka();

	for(i=1; i<=B; i++){
		tipe = CharToTipe(BacaHuruf());
		x = BacaAngka();
		y = BacaAngka();
		MakeBangunan(&tmp, tipe, x, y);

		if(i==1){
			AddIdxBangunan(P1, i);
			Pemilik(tmp) = 1;
		}

		if(i==2){
			AddIdxBangunan(P2, i);
			Pemilik(tmp) = 2;
		}

		TabElmt(*T, i) = tmp;
	}

	CreateGraph(0, G);

	// Inisialisasi Node 1 - B
	for(i=1; i<=B; i++){
		InsertNode(G, i, &Pn);
	}

	// Sambungkan jika pada matrix angka 1
	for(i=1; i<=B; i++){
		for(j=1; j<=B; j++){
			x = BacaAngka();
			if(x==1){
				Connect(G, i, j);
			}
		}
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
	Graph G;
	int choice;

	menuAwal(&choice);

	switch(choice){
		case 1: {
			printf("start!\n");
			BacaConfig(&T, &Peta, &P1, &P2, &G);
			TakeTurn(&P1, &P2, &T, Peta, G);
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

