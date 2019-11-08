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
	boolean hasAttacked; /* bernilai true/false menyatakan apakah bangunan sudah ATTACK atau belum pada 1 giliran, direset setiap awal turn */
	boolean hasMoved; /* bernilai true/false menyatakan apakah bangunan sudah MOVE atau belum pada 1 giliran, direset setiap awal turn */

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
#define hasAttacked(B) (B).hasAttacked
#define hasMoved(B) (B).hasMoved


/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void MakeBangunan(Bangunan *B, int Tipe, int X, int Y);
	/* I.S. B sembarang, Tipe bernilai [1,4] */
	/* F.S. Membuat bangunan yang bertipe Tipe dan memiliki level 1, memiliki jumlah pasukan awal sesuai spesifikasi */

char Symbol(Bangunan B);
	/* Mengirimkan karakter simbol yang merepresentasikan bangunan B sesuai tipe:
		1: Castle (C)
		2: Tower (T)
		3: Fort (F)
		4: Village (V)
	*/

void PrintSymbolColor(Bangunan B);
	/* Mencetak nama bangunan B sesuai tipe dgn warna:
		1: Castle (C)
		2: Tower (T)
		3: Fort (F)
		4: Village (V)
	*/

void PrintNama(Bangunan B);
	/* Mencetak nama bangunan B sesuai tipe:
		1: Castle (C)
		2: Tower (T)
		3: Fort (F)
		4: Village (V)
	*/

int CharToTipe(char c);
	/* Mengirim tipe karakter sesuai tipe:
		1: Castle (C)
		2: Tower (T)
		3: Fort (F)
		4: Village (V)
	*/

Bangunan BUndef();
	/* Mengirimkan nilai bangunan undef dengan spesifikasi semua atribut bernilai -1 */

boolean IsBUndef(Bangunan B);
	/* Mengirimkan true jika bangunan B adalah BUndef */

void UpdateToLevel(Bangunan *B, int Lvl);
	/* I.S. B bisa sembarang, Lvl bernilai [1,4] */
	/* F.S. Mengupdate bangunan menjadi level Lvl sesuai spesifikasi */

boolean CheckLevelUp(Bangunan B);
	/* Mengembalikan apakah level bangunan B dapat dinaikkan
		dengan spesifikasi pasukan pada bangunan B harus dapat berkurang sebesar M/2. */

void LevelUp(Bangunan *B);
	/* Menaikkan level bangunan B
		pasukan pada bangunan B berkurang sebesar M/2. */

void PrintBangunan(Bangunan B);
	/* I.S. B terdefinisi */
	/* F.S. Atribut B terprint di layar */

#endif