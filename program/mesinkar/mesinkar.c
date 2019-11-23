/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "../mesinkar/mesinkar.h"
#include <stdio.h>

char CC;
boolean EOP;

static FILE * pita;
static FILE * pitaout;
static int retval;

void START(char* path) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca, path pita pada parameter.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    pita = fopen(path,"r"); 
    ADV();
}

void STARTTULIS(char* path){
  /* Membuka pitaout karakter pada path */
  pitaout = fopen(path,"w+");
}

void TULISKAR(char c){
  /* Menulis c pada pitaout */
  fprintf(pitaout, "%c", c);
}

void TULISANGKA(int d){
  /* Menulis d pada pitaout */
  fprintf(pitaout, "%d", d);
}

void TULISBLANK(){
  /* Menulis spasi pada pitaout */
  fprintf(pitaout, " ");
}

void DONETULIS(){
  /* Selesai menulis pitaout */
  fclose(pitaout);
}

void TULISNL(){
  /* Menulis newline pada pita */
  fprintf(pitaout, "\n");
}

void ADV() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela =
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK.
          Jika  CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    retval = fscanf(pita,"%c",&CC);
    EOP = (CC == MARK);
    if (EOP) {
       fclose(pita);
    }
}


void ADVInput() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela =
          CC, CC != EOI
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK.
          Jika  CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    retval = scanf("%c",&CC);
}