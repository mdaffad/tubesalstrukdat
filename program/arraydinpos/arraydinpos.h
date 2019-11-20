/* MODUL TABEL INTEGER */
/* Berisi definisi dan semua primitif pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi III : dengan banyaknya elemen didefinisikan secara implisit,
   memori tabel dinamik */

#ifndef ARRAYDINPOS_H
#define ARRAYDINPOS_H

#include "../boolean/boolean.h"
#include "../bangunan/bangunan.h"

/*  Kamus Umum */
#define IdxMin 1
/* Indeks minimum array */
#define IdxUndef -999
/* Indeks tak terdefinisi*/

/* BUndef() digunakan sebagai nilai tak terdefinisi */

/* Definisi elemen dan koleksi objek */
typedef int IdxType; /* type indeks */
typedef Bangunan ElType;  /* type elemen tabel */
typedef struct
{
  ElType *TI; /* memori tempat penyimpan elemen (container) */
  int TabMaxEl;  /* ukuran elemen */
} TabBangunan;
/* Indeks yang digunakan [IdxMin..TabMaxEl] */
/* Jika T adalah TabBangunan, cara deklarasi dan akses: */
/* Deklarasi : T : TabBangunan */
/* Maka cara akses:
   T.TI    untuk mengakses seluruh nilai elemen tabel
   T.TI[i] untuk mengakses elemen ke-i */
/* Definisi :
  Tabel kosong: semua elemen bernilai ValUndef
  Definisi elemen pertama : T.TI[i] dengan i=1
  Definisi elemen terakhir yang terdefinisi: T.TI[i] dengan i terbesar
                                             sehingga T.TI[i] != ValUndef */

/* ********** SELEKTOR ********** */
#define TI(T) (T).TI
#define TabElmt(T, i) (T).TI[(i)]
#define TabMaxEl(T) (T).TabMaxEl

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty(TabBangunan *T, int TabMaxEl);
/* I.S. T sembarang, TabMaxEl > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas TabMaxEl + 1 */
/* Proses: Inisialisasi semua elemen tabel T dengan ValUndef */

void TabDealokasi(TabBangunan *T);
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, TabMaxEl(T)=0; Neff(T)=0 */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int TabNbElmt(TabBangunan T);
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
int MaxElement(TabBangunan T);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */
IdxType GetFirstIdx(TabBangunan T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
IdxType GetLastIdx(TabBangunan T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

/* ********** Test Indeks yang valid ********** */
boolean IsIdxTabValid(TabBangunan T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean IsIdxTabEff(TabBangunan T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsTabEmpty(TabBangunan T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
boolean IsTabFull(TabBangunan T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

void PrintArrayBangunan(TabBangunan T);
/* Mencetak isi bangunan dalam TabBangunan T */

#endif
