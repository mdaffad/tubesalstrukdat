/* File: mesinkata.c */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#include "boolean.h"
#include "mesinkar.h"
#include "mesinkata.h"

#include <stdio.h>

boolean EndKata;
Kata CKata;

void IgnoreBlank(){
	/* Mengabaikan satu atau beberapa BLANK
	   I.S. : CC sembarang
	   F.S. : CC ≠ BLANK atau CC = MARK */
	while(CC == BLANK || CC == BLANK2){
		ADV();
	}
}

void STARTKATA(){
	/* I.S. : CC sembarang
	   F.S. : EndKata = true, dan CC = MARK;
	          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
	          CC karakter pertama sesudah karakter terakhir kata */
	START();
	IgnoreBlank();
	if(CC == MARK){
		EndKata = true;
	}
	else{
		EndKata = false;
		SalinKata();
	}

}

void ADVKATA(){
	/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
	   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
	          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
	          Jika CC = MARK, EndKata = true.
	   Proses : Akuisisi kata menggunakan procedure SalinKata */
	IgnoreBlank();
	if(CC == MARK){
		EndKata = true;
	}
	else{
		SalinKata();
		IgnoreBlank();
	}
}

void SalinKata(){
	/* Mengakuisisi kata, menyimpan dalam CKata
	   I.S. : CC adalah karakter pertama dari kata
	   F.S. : CKata berisi kata yang sudah diakuisisi;
	          CC = BLANK atau CC = MARK;
	          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
	          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
	
	int i=1;
	do {
		CKata.TabKata[i] = CC;
		ADV();
		i++;
	} while((CC != MARK) && (CC != BLANK) && (CC != BLANK2) && (i <= NMax));
	CKata.Length = i-1;
}

int CharToInt(char c){
	/* Mengirimkan angka dari karakter, c bernilai ['0'..'9'] */

	return c - '0';
}

int BacaAngka(){
	/* Membaca angka selanjutnya */
	
	int i;
	int sum;

	sum = 0;
	for(int i=1; i<=CKata.Length; i++){
		sum = (10*sum) + CharToInt(CKata.TabKata[i]);
	}
	ADVKATA();
	return sum;
}

char BacaHuruf(){
	/* Membaca karakter selanjutnya */

	char c;

	c = CKata.TabKata[1];
	ADVKATA();
	return c;
}

void BacaInput(){
	int i=1;
	/* Membaca input */

	do {
		ADVInput();
		CKata.TabKata[i] = CC;
		i++;
	} while((CC != EOI) && (i <= NMax));
	CKata.Length = i-2;
}

boolean IsKataSama(Kata K1, Kata K2){
	boolean sama;
	int i;

	if(K1.Length != K2.Length){
		return false;
	}
	else{
		sama = true;
		i=1;

		while(sama && i<=K1.Length){
			sama = (K1.TabKata[i] == K2.TabKata[i]);
			i++;
		}

		return sama;
	}
}

boolean IsKataATTACK(Kata K){
	Kata KataATTACK;
	KataATTACK.Length = 6;
	KataATTACK.TabKata[1] = 'A';
	KataATTACK.TabKata[2] = 'T';
	KataATTACK.TabKata[3] = 'T';
	KataATTACK.TabKata[4] = 'A';
	KataATTACK.TabKata[5] = 'C';
	KataATTACK.TabKata[6] = 'K';

	return IsKataSama(K, KataATTACK);
}

boolean IsKataLEVEL_UP(Kata K){
	Kata KataLEVEL_UP;
	KataLEVEL_UP.Length = 8;
	KataLEVEL_UP.TabKata[1] = 'L';
	KataLEVEL_UP.TabKata[2] = 'E';
	KataLEVEL_UP.TabKata[3] = 'V';
	KataLEVEL_UP.TabKata[4] = 'E';
	KataLEVEL_UP.TabKata[5] = 'L';
	KataLEVEL_UP.TabKata[6] = '_';
	KataLEVEL_UP.TabKata[7] = 'U';
	KataLEVEL_UP.TabKata[8] = 'P';

	return IsKataSama(K, KataLEVEL_UP);
}

boolean IsKataSKILL(Kata K){
	Kata KataSKILL;
	KataSKILL.Length = 5;
	KataSKILL.TabKata[1] = 'S';
	KataSKILL.TabKata[2] = 'K';
	KataSKILL.TabKata[3] = 'I';
	KataSKILL.TabKata[4] = 'L';
	KataSKILL.TabKata[5] = 'L';

	return IsKataSama(K, KataSKILL);
}

boolean IsKataUNDO(Kata K){
	Kata KataUNDO;
	KataUNDO.Length = 4;
	KataUNDO.TabKata[1] = 'U';
	KataUNDO.TabKata[2] = 'N';
	KataUNDO.TabKata[3] = 'D';
	KataUNDO.TabKata[4] = 'O';

	return IsKataSama(K, KataUNDO);
}


boolean IsKataEND_TURN(Kata K){
	Kata KataEND_TURN;
	KataEND_TURN.Length = 8;
	KataEND_TURN.TabKata[1] = 'E';
	KataEND_TURN.TabKata[2] = 'N';
	KataEND_TURN.TabKata[3] = 'D';
	KataEND_TURN.TabKata[4] = '_';
	KataEND_TURN.TabKata[5] = 'T';
	KataEND_TURN.TabKata[6] = 'U';
	KataEND_TURN.TabKata[7] = 'R';
	KataEND_TURN.TabKata[8] = 'N';

	return IsKataSama(K, KataEND_TURN);
}

boolean IsKataSAVE(Kata K){
	Kata KataSAVE;
	KataSAVE.Length = 4;
	KataSAVE.TabKata[1] = 'S';
	KataSAVE.TabKata[2] = 'A';
	KataSAVE.TabKata[3] = 'V';
	KataSAVE.TabKata[4] = 'E';

	return IsKataSama(K, KataSAVE);
}

boolean IsKataMOVE(Kata K){
	Kata KataMOVE;
	KataMOVE.Length = 4;
	KataMOVE.TabKata[1] = 'M';
	KataMOVE.TabKata[2] = 'O';
	KataMOVE.TabKata[3] = 'V';
	KataMOVE.TabKata[4] = 'E';

	return IsKataSama(K, KataMOVE);
}

boolean IsKataEXIT(Kata K){
	Kata KataEXIT;
	KataEXIT.Length = 4;
	KataEXIT.TabKata[1] = 'E';
	KataEXIT.TabKata[2] = 'X';
	KataEXIT.TabKata[3] = 'I';
	KataEXIT.TabKata[4] = 'T';

	return IsKataSama(K, KataEXIT);
}


boolean IsKataSTATUS(Kata K){
	Kata KataSTATUS;
	KataSTATUS.Length = 6;
	KataSTATUS.TabKata[1] = 'S';
	KataSTATUS.TabKata[2] = 'T';
	KataSTATUS.TabKata[3] = 'A';
	KataSTATUS.TabKata[4] = 'T';
	KataSTATUS.TabKata[5] = 'U';
	KataSTATUS.TabKata[6] = 'S';

	return IsKataSama(K, KataSTATUS);
}
