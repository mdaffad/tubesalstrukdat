/* File : bangunan.h */
/* bangunan dalam game Avatar */

#ifndef bangunan_H
#define bangunan_H

#include "boolean.h"
#include "point.h"

// DEFINISI ADT BANGUNAN
typedef struct {
	int Tipe;		/* tipe bangunan, bernilai [1,4] =
						1: Castle (C)
						2: Tower (T)
						3: Fort (F)
						4: Village (V)
						-1: UNDEF
					*/
	int Pemilik;	/* kepemilikan, bernilai [0,2] =
						0: tidak dimiliki siapapun
						1: dimiliki pemain 1
						2: dimiliki pemain 2
						-1: UNDEF
					*/
	int Pasukan;	/* jumlah pasukan dalam bangunan */
	int Lvl; 		/* level, bernilai [1,4] = level bangunan */
	int A; 			/* nilai penambahan pasukan = jumlah pasukan pada bangunan setiap gliran bertambah sebanyak A */
	int M;			/* nilai maksimum penambahan pasukan = jika pasukan >= M, penambahan pasukan sebanyak A tidak dilakukan */
	boolean P;		/* pertahanan, bernilai true/false = apakah bangunan memiliki pertahanan, bangunan yg memiliki pertahanan ... (baca di spek) */
	POINT Pos;		/* posisi = posisi bangunan */

} Bangunan;


// SELEKTOR
#define Tipe(B) (B).Tipe
#define Pemilik(B) (B).Pemilik
#define Pasukan(B) (B).Pasukan
#define Lvl(B) (B).Lvl
#define A(B) (B).A
#define M(B) (B).M
#define P(B) (B).P
#define Pos(B) (B).Pos


/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void MakeBangunan(Bangunan *B, int Tipe, int X, int Y);
	/* I.S. B sembarang, Tipe bernilai [1,4] */
	/* F.S. Membuat bangunan yang bertipe Tipe dan memiliki level 1, memiliki jumlah pasukan awal sesuai spesifikasi */

void UpdateToLevel(Bangunan *B, int Lvl);
	/* I.S. B bisa sembarang, Lvl bernilai [1,4] */
	/* F.S. Mengupdate bangunan menjadi level Lvl sesuai spesifikasi */

char Symbol(Bangunan B);
	/* Mengirimkan karakter simbol yang merepresentasikan bangunan B sesuai tipe:
		1: Castle (C)
		2: Tower (T)
		3: Fort (F)
		4: Village (V)
	*/

Bangunan BUndef();
	/* Mengirimkan nilai bangunan undef dengan spesifikasi semua atribut bernilai -1 */

boolean IsBUndef(Bangunan B);
	/* Mengirimkan true jika bangunan B adalah BUndef */

void PrintBangunan(Bangunan B);
	/* I.S. B terdefinisi */
	/* F.S. Atribut B terprint di layar */

#endif