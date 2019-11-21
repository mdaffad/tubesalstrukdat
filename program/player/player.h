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
} Player;

#define Kode(P) (P).Kode
#define L(P) (P).L
#define Q(P) (P).Q

void MakePlayer(Player *P, int Kode);

void AddIdxBangunan(Player *P, int Idx);

void DelIdxBangunan(Player *P, int Idx);

void UpdatePasukan(TabBangunan *T, Player P);

void IdxFromDaftarBangunan(Player P, TabBangunan T, int *idx, char *PesanDaftar, char *PesanInput);

void DoLevelUp(int idx, TabBangunan T, Stack *S, Player PCurrent, Player PEnemy);

void TakeTurn(Player *PCurrent, Player *PEnemy, TabBangunan *T, MATRIKS Peta, Graph G);

#endif