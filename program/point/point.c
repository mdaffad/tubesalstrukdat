/* File: point.c */
/* Tanggal: 27 Agustus 2019 */

#include <stdio.h>

#include "../boolean/boolean.h"
#include "../point/point.h"

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y){
	/* Membentuk sebuah POINT dari komponen-komponennya */
	POINT P;
	Absis(P) = X;
	Ordinat(P) = Y;
	return P;
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPOINT (POINT * P){
	/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
	   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
	/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
	/* Contoh: 1 2
	   akan membentuk POINT <1,2> */
	/* I.S. Sembarang */
	/* F.S. P terdefinisi */

	int X, Y;
	scanf("%d %d", &X, &Y);
	(*P) = MakePOINT(X, Y);
}

void TulisPOINT (POINT P){
	/* Nilai P ditulis ke layar dengan format "(X,Y)"
	   tanpa spasi, enter, atau karakter lain di depan, belakang,
	   atau di antaranya
	   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
	*/
	/* I.S. P terdefinisi */
	/* F.S. P tertulis di layar dengan format "(X,Y)" */

	printf("(%d,%d)", Absis(P), Ordinat(P));

}



/* *** Kelompok operasi relasional terhadap POINT *** */
boolean PointEQ (POINT P1, POINT P2){
	/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
	return ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2)));
}

boolean PointNEQ (POINT P1, POINT P2){
	/* Mengirimkan true jika P1 tidak sama dengan P2 */
	return ((Absis(P1) != Absis(P2)) || (Ordinat(P1) != Ordinat(P2)));
}
