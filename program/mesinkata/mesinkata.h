/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "../boolean/boolean.h"
#include "../mesinkar/mesinkar.h"

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

void STARTKATA(char* path);
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
/* Menentukan apakah kedua kata sama, mengirimkan true jika kedua kata sama, false jika tidak */

boolean IsKataATTACK(Kata K);
/* Menentukan apakah kata yang diinput sama dengan kata 'ATTACK', mengirimkan true jika kedua kata sama, false jika tidak */

boolean IsKataLEVEL_UP(Kata K);
/* Menentukan apakah kata yang diinput sama dengan kata 'LEVEL_UP', mengirimkan true jika kedua kata sama, false jika tidak */

boolean IsKataSKILL(Kata K);
/* Menentukan apakah kata yang diinput sama dengan kata 'SKILL', mengirimkan true jika kedua kata sama, false jika tidak */

boolean IsKataUNDO(Kata K);
/* Menentukan apakah kata yang diinput sama dengan kata 'UNDO', mengirimkan true jika kedua kata sama, false jika tidak */

boolean IsKataEND_TURN(Kata K);
/* Menentukan apakah kata yang diinput sama dengan kata 'END_TURN', mengirimkan true jika kedua kata sama, false jika tidak */

boolean IsKataSAVE(Kata K);
/* Menentukan apakah kata yang diinput sama dengan kata 'SAVE', mengirimkan true jika kedua kata sama, false jika tidak */

boolean IsKataMOVE(Kata K);
/* Menentukan apakah kata yang diinput sama dengan kata 'MOVE', mengirimkan true jika kedua kata sama, false jika tidak */

boolean IsKataEXIT(Kata K);
/* Menentukan apakah kata yang diinput sama dengan kata 'EXIT', mengirimkan true jika kedua kata sama, false jika tidak */

boolean IsKataSTATUS(Kata K);
/* Menentukan apakah kata yang diinput sama dengan kata 'STATUS', mengirimkan true jika kedua kata sama, false jika tidak */

#endif
