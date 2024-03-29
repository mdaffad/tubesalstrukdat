/* File: player.c */
/* PLAYER dalam game Avatar */

#include "../boolean/boolean.h"
#include "../point/point.h"
#include "../arraydinpos/arraydinpos.h"
#include "../queue/queue.h"
#include "../stackt/stackt.h"
#include "../listlinier/listlinier.h"
#include "../skill/skill.h"
#include "../bangunan/bangunan.h"
#include "../matrikskar/matrikskar.h"
#include "../mesinkata/mesinkata.h"
#include "../mesinkar/mesinkar.h"
#include "../graf/graf.h"
#include "../pcolor/pcolor.h"
#include "../player/player.h"

#include <stdio.h>

void MakePlayer(Player *P, int N){
	/* Konstruktor untuk Player */
	Kode(*P) = N;
	LCreateEmpty(&L(*P));
	QCreateEmpty(&Q(*P), 10);
	Add(&Q(*P), 1); //INSTANT UPGRADE
	cShield(*P) = 0;
	ignoreP(*P) = false;
	xTurn(*P) = false;
}

void AddIdxBangunan(Player *P, int Idx){
	/* Menambahkan index bangunan pada tab ke list milik player */
	InsVLast(&L(*P), Idx);
}

void DelIdxBangunan(Player *P, int Idx){
	/* Membuang index bangunan pada tab dalam list milik player */
	DelP(&L(*P), Idx);
}

void UpdateLBangunan(Player *P, TabBangunan T){
	/* Mengupdate list bangunan milik player sesuai bangunan pada tabel */
	int i;

	LCreateEmpty(&L(*P));

	for(i=GetFirstIdx(T);i<=(GetLastIdx(T));i++){
		if(Pemilik(TabElmt(T, i)) == Kode(*P)){
			AddIdxBangunan(P, i);
		}
	}
}

void UpdatePasukan(TabBangunan *T, Player P){
	/* Mengupdate pasukan milik player P pada awal giliran */
	int i;

	for(i=GetFirstIdx(*T);i<=(GetLastIdx(*T));i++){
		if(Pemilik(TabElmt(*T, i)) == Kode(P)){
			if(Pasukan(TabElmt(*T, i)) < M(TabElmt(*T, i))){
				Pasukan(TabElmt(*T, i)) += A(TabElmt(*T, i));
			}
		}
	}
}

void ResetAttackMove(TabBangunan *T){
	/* Me-reset semua hasAttacked dan hasMoved pada awal giliran */
	int i;

	for(i=GetFirstIdx(*T);i<=(GetLastIdx(*T));i++){
		hasAttacked(TabElmt(*T, i)) = false;
		hasMoved(TabElmt(*T, i)) = false;
	}
}

void IdxFromDaftarBangunan(Player P, TabBangunan T, int *idx, char *PesanDaftar, char *PesanInput){
	/* Memberikan pilihan bangunan dari setiap bangunan dalam list */
	int choice;

	if(!IsLEmpty(L(P))){
		printf("%s:\n", PesanDaftar);
		PrintListBangunan(L(P), T);
		printf("%s: ", PesanInput);
		choice = InputAngka();
		while(choice > NbElmt(L(P)) || choice <= 0){
			printf("Bangunan tidak ada.\n");
			printf("%s: ", PesanInput);
			choice = InputAngka();
		}

		*idx = GetAtIdx(L(P), choice);
	}

	else{
		printf("Tidak ada bangunan.\n");
		*idx = -1;
	}
	
}

void IdxFromAdjacentBangunan(int indeksInput, Player P, TabBangunan T, int *idx, char *PesanDaftar, char *PesanInput, boolean self, Graph G){
	/* 	Memberikan pilihan bangunan yang terhubung dengan bangunan ke-indeksInput dalam list
		Jika self=true, bangunan milik sendiri, jika false milik 0 atau player lawan */
	int choice;
	List tmp;
	Bangunan tmpBangunan;
	int i;

	// Membuat list untuk menampung semua bangunan yang terhubung
	LCreateEmpty(&tmp);
	for(i=1; i<=TabNbElmt(T); i++){
		tmpBangunan = TabElmt(T, i);
		if(self){
			if(Pemilik(tmpBangunan) == Kode(P) && isConnected(G, indeksInput, i)){
				InsVLast(&tmp, i);
			}
		}
		else{
			if(Pemilik(tmpBangunan) != Kode(P) && isConnected(G, indeksInput, i)){
				InsVLast(&tmp, i);
			}
		}
	}

	// List terisi semua yg adjacent dgn bangunan T[indeksInput]
	if(!IsLEmpty(tmp)){
		printf("%s:\n", PesanDaftar);
	
		PrintListBangunan(tmp, T);

		printf("%s: ", PesanInput);
		choice = InputAngka();
		while(choice > NbElmt(tmp) || choice <= 0){
			printf("Bangunan tidak ada.\n");
			printf("%s: ", PesanInput);
			choice = InputAngka();
		}

		*idx = GetAtIdx(tmp, choice);
	}
	else{
		printf("Tidak ada bangunan yang terhubung.\n");
		*idx = -1;
	}
	
}

void DoLevelUp(int idx, TabBangunan T, Stack *S, Player PCurrent, Player PEnemy){
	/* Melakukan level up pada bangunan ke idx dalam tabel */
	Bangunan *B;
	B = &TabElmt(T, idx);

	if(CheckLevelUp(*B)){
		PushQ(S, Q(PCurrent));
		PushQ(S, Q(PEnemy));
		PushUndef(S);
		PushBangunan(S, TabElmt(T, idx), idx);

		LevelUp(B);
		printf("Level ");
		PrintNama(*B);
		printf("-mu meningkat menjadi %d!\n", Lvl(*B));
	}
	else{
		printf("Syarat level-up belum memenuhi.\n");
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

void DoAttack(int idxB1, int idxB2, Player *PCurrent, Player *PEnemy, TabBangunan T, Stack *S){
	// B1 menyerang B2
	int N;
	int JmlAwlPlayer;
	int JmlAkhPlayer;
	int JmlAwlEnemy;
	int JmlAkhEnemy;
	int TowerAwlPlayer;
	int i;
	boolean IsEnemysFort = false;
	boolean IsAttackSuccess = false;
	Bangunan *B1 = &TabElmt(T, idxB1);
	Bangunan *B2 = &TabElmt(T, idxB2);

	PushQ(S, Q(*PCurrent));
	PushQ(S, Q(*PEnemy));
	PushUndef(S);
	PushBangunan(S, *B1, idxB1);
	PushBangunan(S, *B2, idxB2);

	TowerAwlPlayer = 0;
	for(i=GetFirstIdx(T);i<=(GetLastIdx(T));i++){
		if(Pemilik(TabElmt(T, i)) == Kode(*PCurrent)){
			if(Tipe(TabElmt(T, i)) == 2){
				TowerAwlPlayer += 1;
			}
		}
	}

	JmlAwlPlayer = NbElmt(L(*PCurrent));
	JmlAwlEnemy = NbElmt(L(*PEnemy));

	if(Tipe(*B2) == 3 && Pemilik(*B2) != 0) IsEnemysFort = true; /* Diasumsikan hanya perlu di cek apakah forT sudah dimiliki karena diasumsikan tidak akan serang bangunan sendiri */

	printf("Jumlah pasukan: ");
	N = InputAngka();
	while(N > Pasukan(*B1) || N < 0){
		printf("Jumlah pasukan tidak valid.\n");
		printf("Jumlah pasukan: ");
		N = InputAngka();
	}

	printf("\n");

	Pasukan(*B1) = Pasukan(*B1) - N;
	hasAttacked(*B1) = true;

	if(isCrit(*PCurrent)){
		// KASUS PENYERANGAN DENGAN CRITICAL
		if(N*2 < Pasukan(*B2)){
			Pasukan(*B2) = Pasukan(*B2) - N*2;
			printf("Bangunan gagal direbut.\n");
		}
		else{
			Pasukan(*B2) = (N*2 - Pasukan(*B2))/2;
			// TRANSFER PEMILIK
			UpdateToLevel(B2, 1);
			TransferPemilik(idxB2, PCurrent, PEnemy, T);
			printf("Bangunan menjadi milikmu!\n");
			IsAttackSuccess = true;
		}

		isCrit(*PCurrent) = false;
		// karena berlaku hanya 1x serangan
	}
	else{
		// KASUS TIDAK ADA PERTAHANAN DAN SHIELD ATAU ADA IGNOREP
		if((P(*B2) == false && cShield(*PEnemy) == 0) || ignoreP(*PCurrent)){
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
				IsAttackSuccess = true;
			}
		}
		// KASUS DGN PERTAHANAN ATAU SHIELD, TIDAK ADA IGNOREP
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
				IsAttackSuccess = true;
			}
		}
	}
	

	JmlAkhPlayer = NbElmt(L(*PCurrent));
	JmlAkhEnemy = NbElmt(L(*PEnemy));

	if(IsAttackSuccess && TowerAwlPlayer == 2 && Tipe(*B2) == 2){
		// jika twr awal 2, attack berhasil, type yg diserang = tower
		if(!IsQFull(Q(*PCurrent))) {
			Add(&Q(*PCurrent), 4);
			printf("Kamu mendapat Skill ATTACK UP!\n");
		} else printf("Queue-mu sudah penuh!");
	}
	if(JmlAkhEnemy == 2 && JmlAkhEnemy - JmlAwlEnemy == -1){
		if(!IsQFull(Q(*PEnemy))) {
			Add(&Q(*PEnemy), 2);
			printf("Musuhmu mendapat Skill SHIELD!\n");	
		} else printf("Queue musuhmu sudah penuh!");
		
	}
	if(IsAttackSuccess && IsEnemysFort){
		if(!IsQFull(Q(*PEnemy))) {
			Add(&Q(*PEnemy), 3);
			printf("Musuhmu mendapat Skill EXTRA TURN!\n");
		} else printf("Queue musuhmu sudah penuh!");
	}
	if(JmlAkhPlayer == 10 && JmlAkhPlayer - JmlAwlPlayer == 1){
		if(!IsQFull(Q(*PEnemy))) {
			Add(&Q(*PEnemy), 7);
			printf("Musuhmu mendapat Skill BARRAGE!\n");
		} else printf("Queue musuhmu sudah penuh!");
	}
}

void DoMove(int idxB1, int idxB2, TabBangunan T, Stack *S, Player PCurrent, Player PEnemy){
	/* Pasukan pada bangunan ke-idxB1 berpindah ke bangunan ke-idxB2 dalam tabel */
	int N;
	Bangunan *B1 = &TabElmt(T, idxB1);
	Bangunan *B2 = &TabElmt(T, idxB2);

	PushQ(S, Q(PCurrent));
	PushQ(S, Q(PEnemy));
	PushUndef(S);
	PushBangunan(S, *B1, idxB1);
	PushBangunan(S, *B2, idxB2);

	printf("Jumlah pasukan: ");
	N = InputAngka();
	while(N > Pasukan(*B1) || N < 0){
		printf("Jumlah pasukan tidak valid.\n");
		printf("Jumlah pasukan: ");
		N = InputAngka();
	}

	Pasukan(*B1) = Pasukan(*B1) - N;
	Pasukan(*B2) = Pasukan(*B2) + N;
	hasMoved(*B1) = true;
	
	printf("%d pasukan dari ", N);
	PrintNama(*B1); printf(" "); TulisPOINT(Pos(*B1)); printf(" ");
	printf("telah berpindah ke ");
	PrintNama(*B2); printf(" "); TulisPOINT(Pos(*B2)); printf(".\n");
}

void DoSkill(Player *PCurrent, Player *PEnemy, TabBangunan *T){
	/* Menggunakan skill terdepan pada Queue milik PCurrent */

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
			printf("Level bangunanmu telah meningkat!\n\n");
			break;
		} case 2: {
			// SHIELD
			printf("Shield!!\n");
			cShield(*PCurrent) = 2;
			printf("Bangunanmu akan memiliki pertahanan selama 2 giliran!!\n\n");
			break;
		} case 3: {
			// EXTRA TURN
			printf("EXTRA TURN!!\n");
			xTurn(*PCurrent) = true;
			printf("Kamu mendapat tambahan satu giliran!!\n\n");
			break;
		} case 4: {
			// ATTACK UP
			printf("ATTACK UP!!\n");
			ignoreP(*PCurrent) = true;
			printf("Pertahanan musuh giliran ini tidak akan berpengaruh!!\n\n");
			break;
		} case 5: {
			// CRITICAL HIT
			printf("CRITICAL HIT!\n");
			isCrit(*PCurrent) = true;
			printf("Jumlah pasukan yang menyerang giliran ini efektif 2x dan pertahanan musuh tidak berpengaruh!!\n\n");
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
			printf("Seluruh bangunanmu mendapatkan tambahan 5 pasukan!!\n\n");
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
			printf("Jumlah pasukan di semua bangunan musuh berkurang 10!!\n\n");
			break;
		}
	}

}

boolean IsSkill6(Player P, TabBangunan T) {
	/* Mengecek apakah kondisi untuk Skill6 terpenuhi */
	int i;
	Bangunan tmpB;
	boolean cek;

	i=GetFirstIdx(T);
	cek = true;
	while(cek && i<=GetLastIdx(T)) {
		tmpB = TabElmt(T,i);
		if(Pemilik(tmpB) == Kode(P) && Lvl(tmpB) != 4) cek = false;
		i++;
	}
	return cek;
}

boolean isGameOver(Player PEnemy){
	/* Mengecek apakah game sudah berakhir dan dimenangkan salah satu pemain */
	return (NbElmt(L(PEnemy)) == 0);
}

void TakeTurn(Player *PCurrent, Player *PEnemy, TabBangunan *T, MATRIKS Peta, Graph G, boolean Load){
	/* Melakukan satu giliran PCurrent */
	int idx;
	int idx2;
	int i;
	boolean mayUndo;
	boolean is_cont;
	Stack S;
	Bangunan tmpB;

	if(!Load){
		// Jika dari load tidak ada inisiasi turn ini
		xTurn(*PCurrent) = false;
		ignoreP(*PCurrent) = false;
		isCrit(*PCurrent) = false;
		UpdatePasukan(T, *PCurrent);
		ResetAttackMove(T);
		// counter shield berkurang per giliran
		if(cShield(*PCurrent) > 0){
			cShield(*PCurrent) -= 1;
		}
	}
	
	SCreateEmpty(&S);
	is_cont = true;
	mayUndo = true;

	printf("\n");
	PrintPeta(Peta, *T);
	printf("\n");
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
	while(!IsKataEND_TURN(CKata) && !IsKataEXIT(CKata) && is_cont){

		if(IsKataATTACK(CKata)){
			printf("\n");
			IdxFromDaftarBangunan(*PCurrent, *T, &idx, "Daftar Bangunan", "Bangunan yang digunakan untuk menyerang");
			if(!hasAttacked(TabElmt(*T, idx))){
				if(idx != -1){
					printf("\n");
					IdxFromAdjacentBangunan(idx, *PCurrent, *T, &idx2, "Daftar bangunan yang dapat diserang", "Bangunan yang diserang", false, G);
				}
				if(idx != -1 && idx2 != -1){
					DoAttack(idx, idx2, PCurrent, PEnemy, *T, &S);
				}
			}
			else{
				printf("Bangunan telah menyerang giliran ini.\n");
			}
			getchar();
			is_cont = !isGameOver(*PEnemy);
		}
		else if(IsKataLEVEL_UP(CKata)){
			IdxFromDaftarBangunan(*PCurrent, *T, &idx, "Daftar Bangunan", "Bangunan yang akan di level up");
			DoLevelUp(idx, *T, &S, *PCurrent, *PEnemy);
			getchar();
		}
		else if(IsKataMOVE(CKata)){
			IdxFromDaftarBangunan(*PCurrent, *T, &idx, "Daftar Bangunan", "Pilih bangunan");
			if(!hasMoved(TabElmt(*T, idx))){
				if(idx != -1){
					IdxFromAdjacentBangunan(idx, *PCurrent, *T, &idx2, "Daftar bangunan terdekat", "Bangunan yang akan menerima", true, G);
				}
				if(idx != -1 && idx2 != -1){
					DoMove(idx, idx2, *T, &S, *PCurrent, *PEnemy);
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
				DoSkill(PCurrent, PEnemy, T);

				if(xTurn(*PCurrent)){
					if(!IsQFull(Q(*PEnemy))) {
						Add(&Q(*PEnemy), 5); // CRITICAL HIT ACTIVATED
						printf("Musuhmu mendapat Skill CRITICAL HIT!\n");
					} else printf("Queue musuhmu sudah penuh!");
				}
			}
		}
		else if(IsKataUNDO(CKata)){
			// Spesifikasi UNDO ada pada stackt.h
			if(mayUndo){
				if(IsSEmpty(S)){
					printf("UNDO tidak dapat dilakukan!\n");
				}
				else{
					do {
						PopBangunan(&S, &tmpB, &idx);
						if(idx != -1){
							TabElmt(*T, idx) = tmpB;
						}
					} while(idx != -1);
					// push sampai ketemu queue
					PopQ(&S, &Q(*PEnemy));
					PopQ(&S, &Q(*PCurrent));
					// selesai pop queue

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
			// printf("Fitur belum tersedia.\n");
			if(Kode(*PCurrent)==1){
				SaveFile(*PCurrent, *PEnemy, *T, Peta, G, 1);
			}
			else{
				SaveFile(*PEnemy, *PCurrent, *T, Peta, G, 2);
			}
			
		}
		else if(IsKataSTATUS(CKata)){
			printf("\n");
			PrintPeta(Peta, *T);
			printf("\n");
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
			printf("Input Anda tidak valid.\n");
		}

		if(is_cont){
			printf("\n");
			printf("ENTER COMMAND: ");
			BacaInput();
		}
	}

	if(IsKataEND_TURN(CKata)){
		if(IsSkill6(*PCurrent, *T)){
			if(!IsQFull(Q(*PCurrent))) {
				Add(&Q(*PCurrent), 6);
				printf("Kamu mendapat Skill INSTANT REINFORCEMENT!\n");	
			} else printf("Queue-mu sudah penuh!");
		}
		if(xTurn(*PCurrent)){
			TakeTurn(PCurrent, PEnemy, T, Peta, G, false);
		}
		else{
			TakeTurn(PEnemy, PCurrent, T, Peta, G, false);
		}
		
	}
	else if(IsKataEXIT(CKata)){if(!IsQFull(Q(*PEnemy)))
		printf("ByeBye!\n");
	}
	else if(!is_cont){
		printf("\n\n");
		printf("\x1b[1m");
		printf("          .------------------------------------------.\n");
		printf("          |                                          |\n");
		printf("          |           -: PLAYER "); printf("%d", Kode(*PCurrent)); printf(" WIN  :-            |\n");
		printf("          |           -: PLAYER "); printf("%d", Kode(*PEnemy)); printf(" LOSE :-            |\n");
		printf("          |                                          |\n");
		printf("          '------------------------------------------'\n");
		printf("\x1b[0m");
		printf("\n\n");
	}
}

void SavePlayer(Player Pl){
	/* Menulis info Player ke pitaout */
	/* Pitaout sudah dibuka dan belum ditutup */
	addressL P;
	int tmp;

	// List
	P = First(L(Pl));

	while(P != LNil){
		TULISANGKA(Info(P)); TULISBLANK();
		P = Next(P);
	}
	TULISANGKA(99); //DELIMITER
	TULISNL();

	// Q
	while(!IsQEmpty(Q(Pl))){
		Del(&Q(Pl), &tmp);
		TULISANGKA(tmp); TULISBLANK();
	}
	TULISANGKA(99); //DELIMITER
	TULISNL();

	// cShield, ignoreP, isCrit
	TULISANGKA(cShield(Pl)); TULISBLANK();
	TULISANGKA(ignoreP(Pl)); TULISBLANK();
	TULISANGKA(isCrit(Pl)); TULISBLANK();
	TULISANGKA(xTurn(Pl)); TULISBLANK();
	TULISNL();
}

void SaveBangunan(Bangunan B){
	/* Menulis info Bangunan ke pitaout */
	TULISANGKA(Tipe(B)); TULISBLANK();
	TULISANGKA(Pemilik(B)); TULISBLANK();
	TULISANGKA(Pasukan(B)); TULISBLANK();
	TULISANGKA(Lvl(B)); TULISBLANK();
	TULISANGKA(A(B)); TULISBLANK();
	TULISANGKA(M(B)); TULISBLANK();
	TULISANGKA(P(B)); TULISBLANK();
	TULISANGKA(Absis(Pos(B))); TULISBLANK();
	TULISANGKA(Ordinat(Pos(B))); TULISBLANK();
	TULISANGKA(hasAttacked(B)); TULISBLANK();
	TULISANGKA(hasMoved(B)); TULISBLANK();
	TULISNL();
}

void SaveFile(Player P1, Player P2, TabBangunan T, MATRIKS Peta, Graph G, int Turn){
	/* Membuat save file */
	addressL P;
	int tmp, i, j;

	// Path save
	printf("Lokasi save file: ");
	BacaInput();
	CKata.TabKata[CKata.Length+1] = 0;

	// Mulai menulis
	STARTTULIS(&CKata.TabKata[1]);

	// Player
	SavePlayer(P1);
	SavePlayer(P2);

	// Tab
	TULISANGKA(TabNbElmt(T)); TULISNL();
	for(i=GetFirstIdx(T);i<=(GetLastIdx(T));i++){
		SaveBangunan(TabElmt(T, i));
	}

	// Peta dan Graf
	TULISANGKA(NBrsEff(Peta)); TULISBLANK();
	TULISANGKA(NKolEff(Peta)); TULISBLANK();
	TULISNL();

	for(i=GetFirstIdx(T);i<=(GetLastIdx(T));i++){
		for(j=GetFirstIdx(T);j<=(GetLastIdx(T));j++){
			TULISANGKA(isConnected(G, i, j)); TULISBLANK();
		}
		TULISNL();
	}

	// Giliran
	TULISANGKA(Turn); TULISKAR('.');


    DONETULIS();
}