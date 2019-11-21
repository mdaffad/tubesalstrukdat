/* File: player.c */
/* PLAYER dalam game Avatar */

#include "boolean.h"
#include "point.h"
#include "arraydinpos.h"
#include "queue.h"
#include "stackt.h"
#include "listlinier.h"
#include "skill.h"
#include "bangunan.h"
#include "matrikskar.h"
#include "mesinkata.h"
#include "graf.h"
#include "pcolor.h"
#include "player.h"

#include <stdio.h>

boolean IsSkill2;
boolean IsSkill3;
boolean IsSkill4;
boolean IsSkill5;
boolean IsSkill6;
boolean IsSkill7;

void MakePlayer(Player *P, int N){
	Kode(*P) = N;
	LCreateEmpty(&L(*P));
	QCreateEmpty(&Q(*P), 10);
	Add(&Q(*P), 1); //INSTANT UPGRADE
}

void AddIdxBangunan(Player *P, int Idx){
	InsVLast(&L(*P), Idx);
}

void DelIdxBangunan(Player *P, int Idx){
	DelP(&L(*P), Idx);
}

void UpdateLBangunan(Player *P, TabBangunan T){
	int i;

	LCreateEmpty(&L(*P));

	for(i=GetFirstIdx(T);i<=(GetLastIdx(T));i++){
		if(Pemilik(TabElmt(T, i)) == Kode(*P)){
			AddIdxBangunan(P, i);
		}
	}
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

void ResetAttackMove(TabBangunan *T){
	int i;

	for(i=GetFirstIdx(*T);i<=(GetLastIdx(*T));i++){
		hasAttacked(TabElmt(*T, i)) = false;
		hasMoved(TabElmt(*T, i)) = false;
	}
}

void IdxFromDaftarBangunan(Player P, TabBangunan T, int *idx, char *PesanDaftar, char *PesanInput){
	int choice;

	if(!IsLEmpty(L(P))){
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
	else{
		printf("Tidak ada bangunan.\n");
		*idx = -1;
	}
	
}

void IdxFromAdjacentBangunan(int indeksInput, Player P, TabBangunan T, int *idx, char *PesanDaftar, char *PesanInput, boolean self){
	// jika self=true, bangunan milik sendiri
	int choice;
	List tmp;
	Bangunan tmpBangunan;
	int i;

	// find adj put in list
	LCreateEmpty(&tmp);
	// loop all tab
	for(i=1; i<=TabNbElmt(T); i++){
		tmpBangunan = TabElmt(T, i);
		if(self){
			if(Pemilik(tmpBangunan) == Kode(P) && isConnected(indeksInput, i)){
				InsVLast(&tmp, i);
			}
		}
		else{
			if(Pemilik(tmpBangunan) != Kode(P) && isConnected(indeksInput, i)){
				InsVLast(&tmp, i);
			}
		}
	}
	// list terisi semua yg adjacent dgn bangunan T[indeksInput]
	if(!IsLEmpty(tmp)){
		printf("%s:\n", PesanDaftar);
	
		PrintListBangunan(tmp, T);

		printf("%s: ", PesanInput);
		scanf("%d", &choice);
		while(choice > NbElmt(tmp) || choice <= 0){
			printf("Bangunan tidak ada.\n");
			printf("%s: ", PesanInput);
			scanf("%d", &choice);
		}

		*idx = GetAtIdx(tmp, choice);
	}
	else{
		printf("Tidak ada bangunan yang terhubung.\n");
		*idx = -1;
	}
	
}

void DoLevelUp(int idx, TabBangunan T, Stack *S){
	Bangunan *B;
	B = &TabElmt(T, idx);

	if(CheckLevelUp(*B)){
		PushUndef(S);
		PushBangunan(S, TabElmt(T, idx), idx);

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

void TransferPemilik(int idxB, Player *PCurrent, Player *PEnemy, TabBangunan T){
	Bangunan *B = &TabElmt(T, idxB);
	// Bangunan B menjadi milik PCurrent

	if(Pemilik(*B) == Kode(*PEnemy)){
		DelIdxBangunan(PEnemy, idxB);
	}
	Pemilik(*B) = Kode(*PCurrent);
	AddIdxBangunan(PCurrent, idxB);
}

void DoAttack(int idxB1, int idxB2, Player *PCurrent, Player *PEnemy, TabBangunan T, Stack *S, boolean *IsSkill2, boolean *IsSkill3, boolean *IsSkill7){
	// B1 menyerang B2
	int N;
	Bangunan *B1 = &TabElmt(T, idxB1);
	Bangunan *B2 = &TabElmt(T, idxB2);

	PushUndef(S);
	PushBangunan(S, *B1, idxB1);
	PushBangunan(S, *B2, idxB2);

	printf("Jumlah pasukan: ");
	scanf("%d", &N);
	while(N > Pasukan(*B1) || N < 0){
		printf("GA VALID WOY!.\n");
		printf("Jumlah pasukan: ");
		scanf("%d", &N);
	}

	Pasukan(*B1) = Pasukan(*B1) - N;
	hasAttacked(*B1) = true;
	// KASUS TIDAK ADA PERTAHANAN
	if(P(*B2) == false){
		if(N < Pasukan(*B2)){
			Pasukan(*B2) = Pasukan(*B2) - N;
			printf("Bangunan gagal direbut.\n");
			*IsSkill2 = false;
			*IsSkill3 = false;
			*IsSkill7 = false;
		}
		else{
			// N >= Pasukan(*B2)
			Pasukan(*B2) = N - Pasukan(*B2);
			// TRANSFER PEMILIK
			UpdateToLevel(B2, 1);
			TransferPemilik(idxB2, PCurrent, PEnemy, T);
			printf("Bangunan menjadi milikmu!\n");
			if(NbElmt(L(*PEnemy)) == 2) *IsSkill2 = true;
			if(Tipe(*B2) == 3) *IsSkill3 = true;
			if(NbElmt(L(*PCurrent)) == 10) *IsSkill7 = true; /* Activate Skill 7*/
			else *IsSkill7 = false;
		}
	}
	else{
		if(N < Pasukan(*B2)*4/3){
			Pasukan(*B2) = Pasukan(*B2) - N*3/4;
			printf("Bangunan gagal direbut.\n");
			*IsSkill2 = false;
			*IsSkill7 = false;
		}
		else{
			// N >= Pasukan(*B2)*4/3
			Pasukan(*B2) = N - Pasukan(*B2)*4/3;
			// TRANSFER PEMILIK
			UpdateToLevel(B2, 1);
			TransferPemilik(idxB2, PCurrent, PEnemy, T);
			printf("Bangunan menjadi milikmu!\n");
			if(NbElmt(L(*PEnemy)) == 2) *IsSkill2 = true;
			if(NbElmt(L(*PCurrent)) == 10) *IsSkill7 = true; /* Activate Skill 7*/
			else *IsSkill7 = false;
		}
	}
}

void DoMove(int idxB1, int idxB2, TabBangunan T, Stack *S){

	// pasukan B1 bergerak ke B2
	int N;
	Bangunan *B1 = &TabElmt(T, idxB1);
	Bangunan *B2 = &TabElmt(T, idxB2);

	PushUndef(S);
	PushBangunan(S, *B1, idxB1);
	PushBangunan(S, *B2, idxB2);

	printf("Jumlah pasukan: ");
	scanf("%d", &N);
	while(N > Pasukan(*B1) || N < 0){
		printf("GA VALID WOY!.\n");
		printf("Jumlah pasukan: ");
		scanf("%d", &N);
	}

	Pasukan(*B1) = Pasukan(*B1) - N;
	Pasukan(*B2) = Pasukan(*B2) + N;
	hasMoved(*B1) = true;
	
	printf("%d pasukan dari ", N);
	PrintNama(*B1); printf(" "); TulisPOINT(Pos(*B1)); printf(" ");
	printf("telah berpindah ke ");
	PrintNama(*B2); printf(" "); TulisPOINT(Pos(*B2)); printf(".\n");
}

void DoSkill(Player *PCurrent, Player *PEnemy, TabBangunan *T, boolean *ExtraTurn){
	int Skill;
	Bangunan* tmpB;
	int i;


	Del(&Q(*PCurrent), &Skill);

	switch(Skill){
		case 1: {
			// IU
			printf("Instant Upgrade!!\n");
			
			for(i=GetFirstIdx(*T);i<=(GetLastIdx(*T));i++){
				tmpB = &TabElmt(*T, i);

				if(Pemilik(*tmpB) == Kode(*PCurrent) && Lvl(*tmpB) < 4){
					UpdateToLevel(tmpB, Lvl(*tmpB)+1);
				}
			}
			printf("Level bangunanmu telah meningkat!\n");
			break;
		} case 2: {
			// SHIELD
			break;
		} case 3: {
			// EXTRA TURN
			printf("EXTRA TURN!!\n");
			*ExtraTurn = true;
			printf("Kamu mendapat tambahan satu giliran!\n");
			break;
		} case 4: {
			// ATTACK UP
			break;
		} case 5: {
			// CRITICAL HIT
			
			break;
		} case 6: {
			// INSTANT REINFORCEMENT
			printf("Instant Reinforcement!!\n");
			for(i=GetFirstIdx(*T);i<=(GetLastIdx(*T));i++){
				tmpB = &TabElmt(*T, i);

				if(Pemilik(*tmpB) == Kode(*PCurrent)){
					Pasukan(*tmpB) += 5;
				}
			}
			break;
		} case 7: {
			// BARRAGE
			printf("Barrage!!\n");

			for(i=GetFirstIdx(*T);i<=(GetLastIdx(*T));i++){
				tmpB = &TabElmt(*T, i);

				if(Pemilik(*tmpB) == Kode(*PEnemy)){
					if(Pasukan(*tmpB) > 10){
						Pasukan(*tmpB) -= 10;	
					}
					else{
						Pasukan(*tmpB) = 0;
					}
				}
			}
			printf("Jumlah pasukan di semua bangunan musuh berkurang 10!\n");
			break;
		}
	}

}

void AddSkill(Player *P, boolean IsSkill2, boolean IsSkill3, boolean IsSkill4, boolean IsSkill5, boolean IsSkill6, boolean IsSkill7) {
	if(IsSkill2) Add(&Q(*P), 2);
	if(IsSkill3) Add(&Q(*P), 3);
	if(IsSkill4) Add(&Q(*P), 4);
	if(IsSkill5) Add(&Q(*P), 5);
	if(IsSkill6) Add(&Q(*P), 6);
	if(IsSkill7) Add(&Q(*P), 7);
}

void TakeTurn(Player *PCurrent, Player *PEnemy, TabBangunan *T, MATRIKS Peta){
	int idx;
	int idx2;
	boolean ExtraTurn;
	boolean mayUndo;
	Stack S;
	Bangunan tmpB;
	IsSkill2 = false;
	IsSkill3 = false;
	IsSkill4 = false;
	IsSkill5 = false;
	IsSkill6 = false;
	IsSkill7 = false;


	mayUndo = true;
	ExtraTurn = false;
	SCreateEmpty(&S);
	UpdatePasukan(T, *PCurrent);
	ResetAttackMove(T);

	printf("\n");
	PrintPeta(Peta, *T);
	printf("Player %d\n", Kode(*PCurrent));
	PrintListBangunan(L(*PCurrent), *T);
	printf("Skill Available: "); 
	if(!IsQEmpty(Q(*PCurrent))){
		PrintSkillName(InfoHead(Q(*PCurrent))); printf("\n\n");
	}
	else{
		printf("-\n\n");
	}

	

	printf("ENTER COMMAND: ");
	BacaInput();
	while(!IsKataEND_TURN(CKata) && !IsKataEXIT(CKata)){

		if(IsKataATTACK(CKata)){
			IdxFromDaftarBangunan(*PCurrent, *T, &idx, "Daftar Bangunan", "Bangunan yang digunakan untuk menyerang");
			if(!hasAttacked(TabElmt(*T, idx))){
				if(idx != -1){
					IdxFromAdjacentBangunan(idx, *PCurrent, *T, &idx2, "Daftar bangunan yang dapat diserang", "Bangunan yang diserang", false);
				}
				if(idx != -1 && idx2 != -1){
					DoAttack(idx, idx2, PCurrent, PEnemy, *T, &S, &IsSkill2, &IsSkill3, &IsSkill7);
					AddSkill(PEnemy, IsSkill2, IsSkill3, false, false, false, IsSkill7);
				}
			}
			else{
				printf("Bangunan telah menyerang giliran ini.\n");
			}
			getchar();
		}
		else if(IsKataLEVEL_UP(CKata)){
			IdxFromDaftarBangunan(*PCurrent, *T, &idx, "Daftar Bangunan", "Bangunan yang akan di level up");
			DoLevelUp(idx, *T, &S);
			getchar();
		}
		else if(IsKataMOVE(CKata)){
			IdxFromDaftarBangunan(*PCurrent, *T, &idx, "Daftar Bangunan", "Pilih bangunan");
			if(!hasMoved(TabElmt(*T, idx))){
				if(idx != -1){
					IdxFromAdjacentBangunan(idx, *PCurrent, *T, &idx2, "Daftar bangunan terdekat", "Bangunan yang akan menerima", true);
				}
				if(idx != -1 && idx2 != -1){
					DoMove(idx, idx2, *T, &S);
				}
			}
			else{
				printf("Bangunan telah berpindah pasukan giliran ini.\n");
			}
			getchar();
		}
		else if(IsKataSKILL(CKata)){
			if(IsQEmpty(Q(*PCurrent))){
				printf("Skill tidak tersedia.\n");
			}
			else{
				mayUndo = false;
				DoSkill(PCurrent, PEnemy, T, &ExtraTurn);
			}
			// printf("skill not implemented yet\n");
		}
		else if(IsKataUNDO(CKata)){
			// 
			if(mayUndo){
				if(IsSEmpty(S)){
					printf("Mau nge-UNDO paan si :(\n");
				}
				else{
					do {
						PopBangunan(&S, &tmpB, &idx);
						if(idx != -1){
							TabElmt(*T, idx) = tmpB;
						}
					} while(idx != -1);

					UpdateLBangunan(PCurrent, *T);
					UpdateLBangunan(PEnemy, *T);

					printf("UNDO berhasil dilakukan!\n");
				}
			}
			else{
				printf("Anda sudah menggunakan SKILL dan tidak bisa UNDO lagi!\n");
			}
			

		}
		else if(IsKataSAVE(CKata)){
			printf("save not implemented yet\n");
		}
		else if(IsKataSTATUS(CKata)){
			printf("\n");
			PrintPeta(Peta, *T);
			printf("Player %d\n", Kode(*PCurrent));
			PrintListBangunan(L(*PCurrent), *T);
			printf("Skill Available: "); 
			if(!IsQEmpty(Q(*PCurrent))){
				PrintSkillName(InfoHead(Q(*PCurrent))); printf("\n\n");
			}
			else{
				printf("-\n\n");
			}
		}
		else{
			printf("INPUT YG BENER LAH\n");
		}
		printf("ENTER COMMAND: ");
		BacaInput();
	}

	if(IsKataEND_TURN(CKata)){
		if(ExtraTurn){
			TakeTurn(PCurrent, PEnemy, T, Peta);
		}
		else{
			TakeTurn(PEnemy, PCurrent, T, Peta);
		}
		
	}
	else if(IsKataEXIT(CKata)){
		printf("ByeBye!\n");
	}
}