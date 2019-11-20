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

void TransferPemilik(int idxB, Player *PCurrent, Player *PEnemy, TabBangunan T){
	Bangunan *B = &TabElmt(T, idxB);
	// Bangunan B menjadi milik PCurrent

	if(Pemilik(*B) == Kode(*PEnemy)){
		DelIdxBangunan(PEnemy, idxB);
	}
	Pemilik(*B) = Kode(*PCurrent);
	AddIdxBangunan(PCurrent, idxB);
}

void DoAttack(int idxB1, int idxB2, Player *PCurrent, Player *PEnemy, TabBangunan T){
	// B1 menyerang B2
	int N;
	Bangunan *B1 = &TabElmt(T, idxB1);
	Bangunan *B2 = &TabElmt(T, idxB2);

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
		}
		else{
			// N >= Pasukan(*B2)
			Pasukan(*B2) = N - Pasukan(*B2);
			// TRANSFER PEMILIK
			UpdateToLevel(B2, 1);
			TransferPemilik(idxB2, PCurrent, PEnemy, T);
			printf("Bangunan menjadi milikmu!\n");
		}
	}
	else{
		if(N < Pasukan(*B2)*4/3){
			Pasukan(*B2) = Pasukan(*B2) - N*3/4;
			printf("Bangunan gagal direbut.\n");
		}
		else{
			// N >= Pasukan(*B2)*4/3
			Pasukan(*B2) = N - Pasukan(*B2)*4/3;
			// TRANSFER PEMILIK
			UpdateToLevel(B2, 1);
			TransferPemilik(idxB2, PCurrent, PEnemy, T);
			printf("Bangunan menjadi milikmu!\n");
		}
	}
}

void DoMove(int idxB1, int idxB2, TabBangunan T){

	// B1 menyerang B2
	int N;
	Bangunan *B1 = &TabElmt(T, idxB1);
	Bangunan *B2 = &TabElmt(T, idxB2);

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


void TakeTurn(Player *PCurrent, Player *PEnemy, TabBangunan *T, MATRIKS Peta){
	int idx;
	int idx2;
	boolean ExtraTurn;

	ExtraTurn = false;
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
					DoAttack(idx, idx2, PCurrent, PEnemy, *T);
				}
			}
			else{
				printf("Bangunan telah menyerang giliran ini.\n");
			}
			getchar();
		}
		else if(IsKataLEVEL_UP(CKata)){
			IdxFromDaftarBangunan(*PCurrent, *T, &idx, "Daftar Bangunan", "Bangunan yang akan di level up");
			// printf("%d\n", idx);
			DoLevelUp(&TabElmt(*T, idx));
			getchar();
		}
		else if(IsKataMOVE(CKata)){
			IdxFromDaftarBangunan(*PCurrent, *T, &idx, "Daftar Bangunan", "Pilih bangunan");
			if(!hasMoved(TabElmt(*T, idx))){
				if(idx != -1){
					IdxFromAdjacentBangunan(idx, *PCurrent, *T, &idx2, "Daftar bangunan terdekat", "Bangunan yang akan menerima", true);
				}
				if(idx != -1 && idx2 != -1){
					DoMove(idx, idx2, *T);
				}
			}
			else{
				printf("Bangunan telah berpindah pasukan giliran ini.\n");
			}
			getchar();
			// printf("move not implemented yet\n");
		}
		else if(IsKataSKILL(CKata)){
			if(IsQEmpty(Q(*PCurrent))){
				printf("Skill tidak tersedia.\n");
			}
			else{
				DoSkill(PCurrent, PEnemy, T, &ExtraTurn);
			}
			// printf("skill not implemented yet\n");
		}
		else if(IsKataUNDO(CKata)){
			printf("undo not implemented yet\n");
		}
		else if(IsKataSAVE(CKata)){
			printf("save not implemented yet\n");
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

boolean IsSkill2(Player P) {
	return NbElmt(L(P)) == 2; /* Masih ada kemungkinan salah karena skill2 didapat kalau jumlah bangunan pemain berkurang sebanyak tepat 1 */
}
/* Mengembalikan true apabila kondisi memenuhi untuk menambah skill 2 : shield ke dalam queue */

/*boolean IsSkill3(); */
/* Mengembalikan true apabila kondisi memenuhi untuk menambah skill 3 : extra turn ke dalam queue */
/*boolean IsSkill4(); */
/* Mengembalikan true apabila kondisi memenuhi untuk menambah skill 4 : attack up ke dalam queue */
/*boolean IsSkill5(); */
/* Mengembalikan true apabila kondisi memenuhi untuk menambah skill 5 : critical hit ke dalam queue */
/*boolean IsSkill6(); */
/* Mengembalikan true apabila kondisi memenuhi untuk menambah skill 6 : instant reinforcement ke dalam queue */
boolean IsSkill7(Player P) {
	return NbElmt(L(P)) == 10; /* Masih ada kemungkinan salah karena skill7 didapat jika jumlah bangunan bertambah menjadi 10 */
}
/* Mengembalikan true apabila kondisi memenuhi untuk menambah skill 7 : barrage ke dalam queue */