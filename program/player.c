/* File: player.c */
/* PLAYER dalam game Avatar */

#include "boolean.h"
#include "point.h"
#include "arraydinpos.h"
#include "queue.h"
#include "stackt.h"
#include "listlinier.h"
#include "bangunan.h"
#include "matrikskar.h"
#include "mesinkata.h"
#include "player.h"

#include <stdio.h>

void MakePlayer(Player *P, int N){
	Kode(*P) = N;
	LCreateEmpty(&L(*P));
}

void AddIdxBangunan(Player *P, int Idx){
	InsVLast(&L(*P), Idx);
}

void DelIdxBangunan(Player *P, int Idx){
	DelP(&L(*P), Idx);
}

void UpdatePasukan(TabBangunan *T, Player P){
	int i;

	for(i=GetFirstIdx(*T);i<=(GetLastIdx(*T));i++){
		if(Pemilik(TabElmt(*T, i)) == Kode(P)){
			Pasukan(TabElmt(*T, i)) += A(TabElmt(*T, i));
			if(Pasukan(TabElmt(*T, i)) >= M(TabElmt(*T, i))){
				Pasukan(TabElmt(*T, i)) = M(TabElmt(*T, i));
			}
		}
	}
}

void IdxFromDaftarBangunan(Player P, TabBangunan T, int *idx, char *PesanDaftar, char *PesanInput){
	int choice;

	printf("%s:\n", PesanDaftar);
	PrintListBangunan(L(P), T);

	printf("%s: ", PesanInput);
	scanf("%d", &choice);
	while(choice > NbElmt(L(P)) || choice <= 0){
		printf("Bangunan tidak ada.\n");
		printf("%s: ", PesanInput);
		scanf("%d", &choice);
	}

	*idx = GetAtIdx(L(P), choice);
}

void DoLevelUp(Bangunan *B){
	if(CheckLevelUp(*B)){
		LevelUp(B);
		printf("Level ");
		PrintNama(*B);
		printf("-mu meningkat menjadi %d!\n", Lvl(*B));
	}
	else{
		printf("GABISA LEVELUP KAKA :((((\n");
	}
	printf("\n");
}

void TakeTurn(Player *PCurrent, Player *PEnemy, TabBangunan *T, MATRIKS Peta){
	int idx;

	UpdatePasukan(T, *PCurrent);

	printf("\n");
	PrintPeta(Peta);
	printf("Player %d\n", Kode(*PCurrent));
	PrintListBangunan(L(*PCurrent), *T);
	printf("Skill Available: not implemented yet\n\n");

	printf("ENTER COMMAND: ");
	BacaInput();
	while(!IsKataEND_TURN(CKata)){

		if(IsKataLEVEL_UP(CKata)){
			IdxFromDaftarBangunan(*PCurrent, *T, &idx, "Daftar Bangunan", "Bangunan yang akan di level up");
			// printf("%d\n", idx);
			DoLevelUp(&TabElmt(*T, idx));
			getchar();
		}
		else{
			printf("INPUT YG BENER LAH\n");
		}
		
		printf("ENTER COMMAND: ");
		BacaInput();
	}
	if(IsKataEND_TURN(CKata)){
		TakeTurn(PEnemy, PCurrent, T, Peta);
	}
}

