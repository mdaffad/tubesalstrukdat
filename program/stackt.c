/* File : stackt.c */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

#include "stackt.h"
#include "boolean.h"

typedef int infotype;
typedef int address;   /* indeks tabel */

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void SCreateEmpty (Stack *S){
	/* I.S. sembarang; */
	/* F.S. Membuat sebuah stack S yang kosong berkapasitas SMaxEl */
	/* jadi indeksnya antara 1.. SMaxEl+1 karena 0 tidak dipakai */
	/* Ciri stack kosong : TOP bernilai SNil */
	Top(*S) = SNil;
}


/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsSEmpty (Stack S){
	/* Mengirim true jika Stack kosong: lihat definisi di atas */
	return Top(S) == SNil;
}

boolean IsSFull (Stack S){
	/* Mengirim true jika tabel penampung nilai elemen stack penuh */
	return Top(S) == SMaxEl;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, infotype X){
	/* Menambahkan X sebagai elemen Stack S. */
	/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
	/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
	if(Top(*S) == SNil){
		Top(*S) = 1;
	}
	else{
		Top(*S)++;
	}
	InfoTop(*S) = X;
}


/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, infotype* X){
	/* Menghapus X dari Stack S. */
	/* I.S. S  tidak mungkin kosong */
	/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
	*X = InfoTop(*S);
	Top(*S)--;
}
