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


void LoadPlayer(Player *Pl, int Kode){
	int x;

	LCreateEmpty(&L(*Pl));
	QCreateEmpty(&Q(*Pl), 10);

	//Player
	Kode(*Pl) = Kode;
	//List
	x = BacaAngka();
	while(x != 99){
		InsVLast(&L(*Pl), x);
		x = BacaAngka();
	}

	x = BacaAngka();
	//Q
	while(x != 99){
		Add(&Q(*Pl), x);
		x = BacaAngka();
	}

	x = BacaAngka(); cShield(*Pl) = x;
	x = BacaAngka(); ignoreP(*Pl) = x;
	x = BacaAngka(); isCrit(*Pl) = x;
	x = BacaAngka(); xTurn(*Pl) = x;
}

void LoadBangunan(Bangunan *B){
	int x;

	x = BacaAngka(); Tipe(*B) = x;
	x = BacaAngka(); Pemilik(*B) = x;
	x = BacaAngka(); Pasukan(*B) = x;
	x = BacaAngka(); Lvl(*B) = x;
	x = BacaAngka(); A(*B) = x;
	x = BacaAngka(); M(*B) = x;
	x = BacaAngka(); P(*B) = x;
	x = BacaAngka(); Absis(Pos(*B)) = x;
	x = BacaAngka(); Ordinat(Pos(*B)) = x;
	x = BacaAngka(); hasAttacked(*B) = x;
	x = BacaAngka(); hasMoved(*B) = x;
}

void LoadFile(TabBangunan *T, MATRIKS *Peta, Player *P1, Player *P2, Graph *G, int *Turn){
	int N, M, B;
	int x;
	int i, j;
	char c;
	adrNode Pn;

	MakeEmpty(T, 40);

	// Baca dari load file, untuk saat ini diasumsikan load file selalu valis
	printf("Lokasi load file: ");
	BacaInput();
	CKata.TabKata[CKata.Length+1] = 0;
	STARTKATA(&CKata.TabKata[1]);

	LoadPlayer(P1, 1);
	LoadPlayer(P2, 2);

	B = BacaAngka();
	for(i=1; i<=B; i++){
		LoadBangunan(&TabElmt(*T, i));
	}

	N = BacaAngka();
	M = BacaAngka();
	MakeMATRIKS(N, M, Peta);

	CreateGraph(0, G);

	// Inisialisasi Node 1 - B
	for(i=1; i<=B; i++){
		InsertNode(G, i, &Pn);
	}

	for(i=1; i<=B; i++){
		for(j=1; j<=B; j++){
			x = BacaAngka();
			if(x==1){
				Connect(G, i, j);
			}
		}
	}

	x = BacaAngka();
	*Turn = x;

	FillPeta(Peta, *T);

}

void BacaConfig(TabBangunan *T, MATRIKS *Peta, Player *P1, Player *P2, Graph *G){
	int N, M, B;
	int x, y, tipe;
	int i, j;
	char c;
	adrNode Pn;
	Bangunan tmp;

	STARTKATA("./bin/petakecilbgt.txt");

	N = BacaAngka();
	M = BacaAngka();
	MakeMATRIKS(N, M, Peta);

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

void title(){
	printf("\n");
	printf("                    __      __    _______         _____     \n");
	printf("                  /\\\\ \\    / //\\ |__   __| /\\    |  __ \\    \n");
	printf("                 /  \\\\ \\  / //  \\   | |   /  \\   | |__) |   \n");
	printf("                / /\\ \\\\ \\/ // /\\ \\  | |  / /\\ \\  |  _  /    \n");
	printf("               / ____ \\\\  // ____ \\ | | / ____ \\ | | \\ \\    \n");
	printf("              /_/    \\_\\\\//_/    \\_\\|_|/_/    \\_\\|_|  \\_\\   \n");
	printf("              _    _____  ____/ ___/ /   _    _____ _____   \n");
	printf("             | |/|/ / _ \\/ __/ / _  /   | |/|/ / _ `/ __/   \n");
	printf("             |__,__/\\___/_/ /_/\\_,_/    |__,__/\\_,_/_/      \n");
	printf("\n");
}

void menuAwal(int *choice){
	title();
	printf("                      SELAMAT DATANG DI PERMAINAN\n");
	printf("                          AVATAR: WORLD WAR\n\n");
	printf("                            1. Start Game\n");
	printf("                            2. Load Game\n");
	printf("                            >> ");

	*choice = InputAngka();
	while(*choice != 1 && *choice != 2){
		printf("                        Pilihan tidak tersedia.\n");
		printf("                            >> ");
		*choice = InputAngka();
	}
	getchar();
}

int main(){
	Player P1, P2;
	MATRIKS Peta;
	TabBangunan T;
	Graph G;
	int choice, Turn;

	menuAwal(&choice);

	switch(choice){
		case 1: {
			printf("\n\n\n");
			BacaConfig(&T, &Peta, &P1, &P2, &G);
			TakeTurn(&P1, &P2, &T, Peta, G, false);
			break;
		}
		case 2: {
			LoadFile(&T, &Peta, &P1, &P2, &G, &Turn);
			if(Turn == 1){
				TakeTurn(&P1, &P2, &T, Peta, G, true);
			}
			else{
				TakeTurn(&P2, &P1, &T, Peta, G, true);
			}
			break;
		}
	}

	return 0;
}

