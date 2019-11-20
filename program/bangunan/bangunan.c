/* File: bangunan.c */
/* bangunan dalam game Avatar */

#include "../boolean/boolean.h"
#include "../point/point.h"
#include "../bangunan/bangunan.h"
#include "../pcolor/pcolor.h"
#include <stdio.h>

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */

void MakeBangunan(Bangunan *B, int Tipe, int X, int Y){
	/* I.S. B sembarang, Tipe bernilai [1,4] */
	/* F.S. Membuat bangunan yang bertipe Tipe dan memiliki level 1 */

	Tipe(*B) = Tipe;
	Pemilik(*B) = 0;

	switch(Tipe(*B)){
		case 1: {
			// CASTLE (C)
			Pasukan(*B) = 40;
			break;
		}
		case 2: {
			// TOWER (T)
			Pasukan(*B) = 30;
			break;
		}
		case 3: {
			// FORT (F)
			Pasukan(*B) = 80;
			break;
		}
		case 4: {
			// VILLAGE (V)
			Pasukan(*B) = 20;
			break;
		}
	}

	hasAttacked(*B) = false;
	hasMoved(*B) = false;
	Pos(*B) = MakePOINT(X,Y);
	UpdateToLevel(B, 1);
}

char Symbol(Bangunan B){
	/* Mengirimkan karakter simbol yang merepresentasikan bangunan B sesuai tipe:
		1: Castle (C)
		2: Tower (T)
		3: Fort (F)
		4: Village (V)
	*/

	switch(Tipe(B)){
		case 1: {
			return 'C';
			break;
		}
		case 2: {
			return 'T';
			break;
		}
		case 3: {
			return 'F';
			break;
		}
		case 4: {
			return 'V';
			break;
		}
	}
}

void PrintSymbolColor(Bangunan B){
	/* Mencetak nama bangunan B sesuai tipe dgn warna:
		1: Castle (C)
		2: Tower (T)
		3: Fort (F)
		4: Village (V)
	*/

	switch(Tipe(B)){
		case 1: {
			// CASTLE (C)
			if(Pemilik(B)==1){
				print_blue('C');
			}
			else if(Pemilik(B)==2){
				print_red('C');
			}
			else{
				printf("C");
			}
			break;
		}
		case 2: {
			// TOWER (T)
			if(Pemilik(B)==1){
				print_blue('T');
			}
			else if(Pemilik(B)==2){
				print_red('T');
			}
			else{
				printf("T");
			}
			break;
		}
		case 3: {
			// FORT (F)
			if(Pemilik(B)==1){
				print_blue('F');
			}
			else if(Pemilik(B)==2){
				print_red('F');
			}
			else{
				printf("F");	
			}
			break;
		}
		case 4: {
			// VILLAGE (V)
			if(Pemilik(B)==1){
				print_blue('V');
			}
			else if(Pemilik(B)==2){
				print_red('V');
			}
			else{
				printf("V");
			}
			break;
		}
	}
}


void PrintNama(Bangunan B){
	/* Mencetak nama bangunan B sesuai tipe:
		1: Castle (C)
		2: Tower (T)
		3: Fort (F)
		4: Village (V)
	*/

	switch(Tipe(B)){
		case 1: {
			// CASTLE (C)
			printf("Castle");
			break;
		}
		case 2: {
			// TOWER (T)
			printf("Tower");
			break;
		}
		case 3: {
			// FORT (F)
			printf("Fort");
			break;
		}
		case 4: {
			// VILLAGE (V)
			printf("Village");
			break;
		}
	}
}

int CharToTipe(char c){
	/* Mengirim tipe karakter sesuai tipe:
		1: Castle (C)
		2: Tower (T)
		3: Fort (F)
		4: Village (V)
	*/
	switch(c){
		case 'C': {
			return 1;
			break;
		}
		case 'T': {
			return 2;
			break;
		}
		case 'F': {
			return 3;
			break;
		}
		case 'V': {
			return 4;
			break;
		}
	}
}

Bangunan BUndef(){
	/* Mengirimkan nilai bangunan undef dengan spesifikasi semua atribut bernilai -1 */
	Bangunan B;
	Tipe(B) = -1;
	Pemilik(B) = -1;
	Pasukan(B) = -1;
	Lvl(B) = -1;
	A(B) = -1;
	M(B) = -1;
	P(B) = false;
	Pos(B) = MakePOINT(-1,-1);
	hasAttacked(B) = false;
	hasMoved(B) = false;
	return B;
}

boolean IsBUndef(Bangunan B){
	/* Mengirimkan true jika bangunan B adalah BUndef */
	boolean isUndef;

	isUndef = Tipe(B) == -1;
	isUndef &= Pemilik(B) == -1;
	isUndef &= Pasukan(B) == -1;
	isUndef &= Lvl(B) == -1;
	isUndef &= A(B) == -1;
	isUndef &= M(B) == -1;
	isUndef &= P(B) == false;
	isUndef &= PointEQ(Pos(B), MakePOINT(-1,-1));
	isUndef &= hasAttacked(B) == false;
	isUndef &= hasMoved(B) == false;

	return isUndef;
}


void UpdateToLevel(Bangunan *B, int Lvl){
	/* I.S. B bisa saja belum terdefinisi sepenuhnya, Tipe B terdefinisi [1,4], Lvl bernilai [1,4] */
	/* F.S. Mengupdate bangunan menjadi level Lvl sesuai spesifikasi */

	Lvl(*B) = Lvl;
	switch(Tipe(*B)){
		case 1: {
			// CASTLE (C)
			switch(Lvl){
				case 1: {
					A(*B) = 10;
					M(*B) = 40;
					P(*B) = false;
					break;
				}
				case 2: {
					A(*B) = 15;
					M(*B) = 60;
					P(*B) = false;
					break;
				}
				case 3: {
					A(*B) = 20;
					M(*B) = 80;
					P(*B) = false;
					break;
				}
				case 4: {
					A(*B) = 25;
					M(*B) = 100;
					P(*B) = false;
					break;
				}
			}
			break;
		}
		case 2: {
			// TOWER (T)
			switch(Lvl){
				case 1: {
					A(*B) = 5;
					M(*B) = 20;
					P(*B) = true;
					break;
				}
				case 2: {
					A(*B) = 10;
					M(*B) = 30;
					P(*B) = true;
					break;
				}
				case 3: {
					A(*B) = 20;
					M(*B) = 40;
					P(*B) = true;
					break;
				}
				case 4: {
					A(*B) = 30;
					M(*B) = 50;
					P(*B) = true;
					break;
				}
			}
			break;
		}
		case 3: {
			// FORT (F)
			switch(Lvl){
				case 1: {
					A(*B) = 10;
					M(*B) = 20;
					P(*B) = false;
					break;
				}
				case 2: {
					A(*B) = 20;
					M(*B) = 40;
					P(*B) = false;
					break;
				}
				case 3: {
					A(*B) = 30;
					M(*B) = 60;
					P(*B) = true;
					break;
				}
				case 4: {
					A(*B) = 40;
					M(*B) = 80;
					P(*B) = true;
					break;
				}
			}
			break;
		}
		case 4: {
			// VILLAGE (V)
			switch(Lvl){
				case 1: {
					A(*B) = 5;
					M(*B) = 20;
					P(*B) = false;
					break;
				}
				case 2: {
					A(*B) = 10;
					M(*B) = 30;
					P(*B) = false;
					break;
				}
				case 3: {
					A(*B) = 15;
					M(*B) = 40;
					P(*B) = false;
					break;
				}
				case 4: {
					A(*B) = 20;
					M(*B) = 50;
					P(*B) = false;
					break;
				}
			}
			break;
		}
	}
}

boolean CheckLevelUp(Bangunan B){
	/* Mengembalikan apakah level bangunan B dapat dinaikkan
		dengan spesifikasi pasukan pada bangunan B harus dapat berkurang sebesar M/2. */
	return (Pasukan(B) >= M(B)/2 && Lvl(B) < 4);
}

void LevelUp(Bangunan *B){
	/* Menaikkan level bangunan B
		pasukan pada bangunan B berkurang sebesar M/2. */
	UpdateToLevel(B, Lvl(*B)+1);
	Pasukan(*B) -= M(*B)/2;
}

void PrintBangunan(Bangunan B){
	/* I.S. B terdefinisi */
	/* F.S. Atribut B terprint di layar */
	printf("Tipe: %c\n", Symbol(B));
	printf("Pemilik: %d\n", Pemilik(B));
	printf("Pasukan: %d\n", Pasukan(B));
	printf("Level: %d\n", Lvl(B));
	printf("A: %d\n", A(B));
	printf("M: %d\n", M(B));
	P(B) ? printf("P: yes\n") : printf("P: no\n");
	printf("Pos: "); TulisPOINT(Pos(B)); printf("\n");
	hasAttacked(B) ? printf("hasAttacked: yes\n") : printf("hasAttacked: no\n");
	hasMoved(B) ? printf("hasMoved: yes\n") : printf("hasMoved: no\n");
}
	
	
