/* File : stackt.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

/* Aplikasi: untuk perintah UNDO */
/* Bangunan yang mungkin di UNDO atributnya akan disimpan dalam stack */
/* setiap gerakan yang dilakukan akan disisipkan nilai bangunan tidak terdefinisi untuk memudahkan hitungan "UNDO-nya sampai mana" */

#ifndef stackt_H
#define stackt_H

#include "bangunan.h"
#include "boolean.h"
#include "arraydinpos.h"

#define SNil 0
#define SMaxEl 200
/* SNil adalah stack dengan elemen kosong . */
/* Karena indeks dalam bhs C dimulai 0 maka tabel dg indeks 0 tidak dipakai */

typedef struct {
	Bangunan B;
	int index;
} infostack;

typedef int address;   /* indeks tabel */

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct {
  infostack T[SMaxEl+1]; /* tabel penyimpan elemen */
  address TOP;  /* alamat TOP: elemen puncak */
} Stack;
/* Definisi stack S kosong : S.TOP = SNil */
/* Elemen yang dipakai menyimpan nilai Stack T[1]..T[SMaxEl] */
/* Jika S adalah Stack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define B(X) (X).B
#define Idx(X) (X).index

#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]


/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void SCreateEmpty (Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas SMaxEl */
/* jadi indeksnya antara 1.. SMaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai SNil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsSEmpty (Stack S);
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsSFull (Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, infostack X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, infostack* X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */


/* ************ Lainnya ************ */
infostack InfoUndef();
	/* Mengirimkan nilai info undef dengan spesifikasi B(I) = BUndef() dan Idx(I) -1 */


void PushUndef(Stack * S);
/* Menambahkan BUndef dengan index -1 sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. Undef menjadi TOP yang baru,TOP bertambah 1 */
/* Aplikasi untuk batasan UNDO */

void PushBangunan (Stack * S, Bangunan B, int index);
/* Menambahkan elemen Stack S dengan infostack B(X) = B, Idx(X) = index */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

void PopBangunan (Stack * S, Bangunan *B, int *index);
/* Menghapus X dari Stack S. X adalah infostack B(X) = B, Idx(X) = index */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

#endif