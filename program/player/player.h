/* File: player.h */
/* PLAYER dalam game Avatar */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../boolean/boolean.h"
#include "../point/point.h"
#include "../arraydinpos/arraydinpos.h"
#include "../queue/queue.h"
#include "../stackt/stackt.h"
#include "../listlinier/listlinier.h"
#include "../bangunan/bangunan.h"
#include "../matrikskar/matrikskar.h"
#include "../mesinkata/mesinkata.h"
#include "../skill/skill.h"
#include "../graf/graf.h"
#include "../pcolor/pcolor.h"

// DEFINISI ADT BANGUNAN
typedef struct {
	int Kode;
	List L;
	Queue Q;
	int counterShield;
	boolean isIgnorePertahanan;
	boolean isCritical;
} Player;

#define Kode(P) (P).Kode
#define L(P) (P).L
#define Q(P) (P).Q
#define cShield(P) (P).counterShield
#define ignoreP(P) (P).isIgnorePertahanan
#define isCrit(P) (P).isCritical

void MakePlayer(Player *P, int Kode);
/* Konstruktor untuk Player */

void AddIdxBangunan(Player *P, int Idx);
/* Menambahkan index bangunan pada tab ke list milik player */

void DelIdxBangunan(Player *P, int Idx);
/* Membuang index bangunan pada tab dalam list milik player */

void UpdateLBangunan(Player *P, TabBangunan T);
/* Mengupdate list bangunan milik player sesuai bangunan pada tabel */

void UpdatePasukan(TabBangunan *T, Player P);
/* Mengupdate pasukan milik player P pada awal giliran */

void ResetAttackMove(TabBangunan *T);
/* Me-reset semua hasAttacked dan hasMoved pada awal giliran */

void IdxFromDaftarBangunan(Player P, TabBangunan T, int *idx, char *PesanDaftar, char *PesanInput);
/* Memberikan pilihan bangunan dari setiap bangunan dalam list */

void IdxFromAdjacentBangunan(int indeksInput, Player P, TabBangunan T, int *idx, char *PesanDaftar, char *PesanInput, boolean self, Graph G);
/* 	Memberikan pilihan bangunan yang terhubung dengan bangunan ke-indeksInput dalam list
	Jika self=true, bangunan milik sendiri, jika false milik 0 atau player lawan */

void DoLevelUp(int idx, TabBangunan T, Stack *S, Player PCurrent, Player PEnemy);
/* Melakukan level up pada bangunan ke idx dalam tabel */

void TransferPemilik(int idxB, Player *PCurrent, Player *PEnemy, TabBangunan T);
/* Memindahkan bangunan ke idxB pada tabel menjadi milik PCurrent */

void DoAttack(int idxB1, int idxB2, Player *PCurrent, Player *PEnemy, TabBangunan T, Stack *S);
/* Bangunan ke-idxB1 menyerang bangunan ke-idxB2 dalam tabel */

void DoMove(int idxB1, int idxB2, TabBangunan T, Stack *S, Player PCurrent, Player PEnemy);
/* Pasukan pada bangunan ke-idxB1 berpindah ke bangunan ke-idxB2 dalam tabel */

void DoSkill(Player *PCurrent, Player *PEnemy, TabBangunan *T, boolean *ExtraTurn);
/* Menggunakan skill terdepan pada Queue milik PCurrent */

boolean IsSkill6(Player P, TabBangunan T);
/* Mengecek apakah kondisi untuk Skill6 terpenuhi */

boolean isGameOver(Player PEnemy);
/* Mengecek apakah game sudah berakhir dan dimenangkan salah satu pemain */

void TakeTurn(Player *PCurrent, Player *PEnemy, TabBangunan *T, MATRIKS Peta, Graph G);
/* Melakukan satu giliran PCurrent */

#endif