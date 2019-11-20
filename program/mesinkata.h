/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "boolean.h"
#include "mesinkar.h"

#define NMax 50
#define BLANK ' '
#define BLANK2 '\n'
#define EOI '\n'
// end of input

typedef struct {
  char TabKata[NMax+1]; /* container penyimpan kata, indeks yang dipakai [1..NMax] */
    int Length;
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;

void IgnoreBlank();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATA();
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKata();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

int CharToInt(char c);
/* Mengirimkan angka dari karakter, c bernilai ['0'..'9'] */

int BacaAngka();
/* Membaca angka selanjutnya */

char BacaHuruf();
/* Membaca karakter selanjutnya */

void BacaInput();
/* Membaca input */

boolean IsKataSama(Kata K1, Kata K2);

boolean IsKataATTACK(Kata K);

boolean IsKataLEVEL_UP(Kata K);

boolean IsKataSKILL(Kata K);

boolean IsKataUNDO(Kata K);

boolean IsKataEND_TURN(Kata K);

boolean IsKataSAVE(Kata K);

boolean IsKataMOVE(Kata K);

boolean IsKataEXIT(Kata K);

boolean IsKataSTATUS(Kata K);

#endif