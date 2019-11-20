/* File: player.h */
/* PLAYER dalam game Avatar */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "boolean.h"
#include "point.h"
#include "arraydinpos.h"
#include "queue.h"
#include "stackt.h"
#include "listlinier.h"
#include "bangunan.h"
#include "matrikskar.h"
#include "mesinkata.h"
#include "skill.h"
#include "graf.h"
#include "pcolor.h"

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

void DoLevelUp(int idx, TabBangunan T, Stack *S);

void TakeTurn(Player *PCurrent, Player *PEnemy, TabBangunan *T, MATRIKS Peta);

#endif