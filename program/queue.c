/* File : queue.c */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#include "boolean.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/* ********* Prototype ********* */
boolean IsQEmpty (Queue Q){
	/* Mengirim true jika Q kosong: lihat definisi di atas */
	return Head(Q)==QNil && Tail(Q)==QNil;	
}

boolean IsQFull (Queue Q){
	/* Mengirim true jika tabel penampung elemen Q sudah penuh */
	/* yaitu mengandung elemen sebanyak QMaxEl */
	return (((Tail(Q)-Head(Q) + QMaxEl(Q)) % QMaxEl(Q)) + 1 == QMaxEl(Q));
}

int QNBElmt (Queue Q){
	/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
	if(IsQEmpty(Q)){
		return 0;
	}
	else{
		return ((Tail(Q)-Head(Q) + QMaxEl(Q)) % QMaxEl(Q)) + 1;
	}
}


/* *** Kreator *** */
void QCreateEmpty (Queue * Q, int Max){
	/* I.S. sembarang */
	/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
	/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
	/* atau : jika alokasi gagal, Q kosong dg QMaxEl=0 */
	/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
	(*Q).T = (int*) malloc ((Max+1) * sizeof(infotype));
	if (!(*Q).T){
		QMaxEl(*Q) = 0;
	}
	else{
		QMaxEl(*Q) = Max;
	}
	Head(*Q) = QNil;
	Tail(*Q) = QNil;
}

/* *** Destruktor *** */
void QDeAlokasi(Queue * Q){
	/* Proses: Mengembalikan memori Q */
	/* I.S. Q pernah dialokasi */
	/* F.S. Q menjadi tidak terdefinisi lagi, QMaxEl(Q) diset 0 */
	free((*Q).T);
	QMaxEl(*Q) = 0;
}

/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotype X){
	/* Proses: Menambahkan X pada Q dengan aturan FIFO */
	/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
	/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
	if(IsQEmpty(*Q)){
		Head(*Q) = 1;
		Tail(*Q) = 1;
	}
	else{
		Tail(*Q) = ((Tail(*Q) + QMaxEl(*Q)) % QMaxEl(*Q)) + 1;
	}
	InfoTail(*Q) = X;
}

void Del (Queue * Q, infotype * X){
	/* Proses: Menghapus X pada Q dengan aturan FIFO */
	/* I.S. Q tidak mungkin kosong */
	/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
	        Q mungkin kosong */
	*X = InfoHead(*Q);
	if(QNBElmt(*Q)==1){
		Head(*Q) = QNil;
		Tail(*Q) = QNil;
	}
	else{
		Head(*Q) = ((Head(*Q) + QMaxEl(*Q)) % QMaxEl(*Q)) + 1;	
	}
	
}
