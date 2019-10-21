/* File: array.c */
/* Tanggal: 15 September 2019 */

#include <stdio.h>

#include "boolean.h"
#include "matrikskar.h"


/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M){
	/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
	/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
	/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
	NBrsEff(*M) = NB;
	NKolEff(*M) = NK;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsMatIdxValid (int i, int j){
	/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
	return (i>=BrsMin) && (i<=BrsMax) && (j>=KolMin) && (j<=KolMax);
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M){
	/* Mengirimkan indeks baris terkecil M */
	return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M){
	/* Mengirimkan indeks kolom terkecil M */
	return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M){
	/* Mengirimkan indeks baris terbesar M */
	return NBrsEff(M);
}
indeks GetLastIdxKol (MATRIKS M){
	/* Mengirimkan indeks kolom terbesar M */
	return NKolEff(M);
}
boolean IsMatIdxEff (MATRIKS M, indeks i, indeks j){
	/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
	return (i>=GetFirstIdxBrs(M)) && (i<=GetLastIdxBrs(M)) && (j>=GetFirstIdxKol(M)) && (j<=GetLastIdxKol(M));
}