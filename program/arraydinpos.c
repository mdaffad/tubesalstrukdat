/* File: arraydin.c */
/* Tanggal: 12 September 2019 */
/* Steve Bezalel I. G. / 13518018 */

#include <stdio.h>
#include <stdlib.h>

#include "boolean.h"
#include "bangunan.h"
#include "arraydinpos.h"


/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty(TabBangunan *T, int TabMaxEl){
  /* I.S. T sembarang, TabMaxEl > 0 */
  /* F.S. Terbentuk tabel T kosong dengan kapasitas TabMaxEl + 1 */
  /* Proses: Inisialisasi semua elemen tabel T dengan ValUndef */
  TI(*T) = (ElType*)malloc((TabMaxEl+1)*sizeof(ElType));
  TabMaxEl(*T) = TabMaxEl;
  for(int i=IdxMin; i<=TabMaxEl; i++){
    TabElmt(*T, i) = BUndef();
  }
}

void TabDealokasi(TabBangunan *T){
  /* I.S. T terdefinisi; */
  /* F.S. TI(T) dikembalikan ke system, TabMaxEl(T)=0; Neff(T)=0 */
  for(int i=IdxMin; i<=TabMaxEl(*T); i++){
    TabElmt(*T, i) = BUndef();
  }
  free(TI(*T));
  TabMaxEl(*T) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int TabNbElmt(TabBangunan T){
  /* Mengirimkan banyaknya elemen efektif tabel */
  /* Mengirimkan nol jika tabel kosong */
  IdxType i;
  int Nb;
  Nb = 0;
  i = IdxMin;
  while(!IsBUndef(TabElmt(T, i))&&(i<=TabMaxEl(T))){
    Nb++;
    i++;
  }
  return Nb;
}

/* *** Daya tampung container *** */
int MaxElement(TabBangunan T){
  /* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
  return TabMaxEl(T);
}

/* *** Selektor INDEKS *** */
IdxType GetFirstIdx(TabBangunan T){
  /* Prekondisi : Tabel T tidak kosong */
  /* Mengirimkan indeks elemen T pertama */
  return(IdxMin);
}

IdxType GetLastIdx(TabBangunan T){
  /* Prekondisi : Tabel T tidak kosong */
  /* Mengirimkan indeks elemen T terakhir */
  return TabNbElmt(T)-IdxMin+1;
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxTabValid(TabBangunan T, IdxType i){
  /* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
  /* yaitu antara indeks yang terdefinisi utk container*/
  return (i<=MaxElement(T)) && (i>=IdxMin);
}

boolean IsIdxTabEff(TabBangunan T, IdxType i){
  /* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
  /* yaitu antara FirstIdx(T)..LastIdx(T) */
  return (i<=GetLastIdx(T)) && (i>=GetFirstIdx(T));
}


/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsTabEmpty(TabBangunan T){
  /* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
  return (TabNbElmt(T)==0);
}
/* *** Test tabel penuh *** */
boolean IsTabFull(TabBangunan T){
  /* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
  return (TabNbElmt(T)==MaxElement(T));
}

void PrintArrayBangunan(TabBangunan T){
  /* Mencetak isi bangunan dalam TabBangunan T */
  IdxType i;

  for(i=GetFirstIdx(T);i<=(GetLastIdx(T));i++){
    printf("INDEX: %d\n", i);
    PrintBangunan(TabElmt(T, i));
    if(i<(GetLastIdx(T))){
      printf("\n");
    }
  }
}