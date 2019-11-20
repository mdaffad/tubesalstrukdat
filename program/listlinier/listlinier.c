/* File : listlinier.c */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi addressL dengan pointer */
/* infotype adalah integer */

#include "../listlinier/listlinier.h"
#include "../boolean/boolean.h"
#include "../arraydinpos/arraydinpos.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsLEmpty (List L){
	/* Mengirim true jika list kosong */
	return First(L) == LNil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void LCreateEmpty (List *L){
	/* I.S. sembarang             */
	/* F.S. Terbentuk list kosong */
	First(*L) = LNil;
}

/****************** Manajemen Memori ******************/
addressL Alokasi (infotype X){
	/* Mengirimkan addressL hasil alokasi sebuah elemen */
	/* Jika alokasi berhasil, maka addressL tidak LNil, dan misalnya */
	/* menghasilkan P, maka Info(P)=X, Next(P)=LNil */
	/* Jika alokasi gagal, mengirimkan LNil */
	addressL P;

	P = (addressL) malloc (sizeof (ElmtList));
	if (P != LNil) {
		Info(P) = X;
		Next(P) = LNil;
		return P;
	}
	else{
		return LNil;
	}
}

void Dealokasi (addressL *P){
	/* I.S. P terdefinisi */
	/* F.S. P dikembalikan ke sistem */
	/* Melakukan dealokasi/pengembalian addressL P */	
	free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressL Search (List L, infotype X){
	/* Mencari apakah ada elemen list dengan Info(P)= X */
	/* Jika ada, mengirimkan addressL elemen tersebut. */
	/* Jika tidak ada, mengirimkan LNil */
	addressL P;
	boolean found;

	P = First(L);
	found = false;
	while(!found && P!=LNil){
		if(Info(P) == X){
			found = true;
		}
		else{
			P = Next(P);
		}
	}
	return P;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X){
	/* I.S. L mungkin kosong */
	/* F.S. Melakukan alokasi sebuah elemen dan */
	/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */

	addressL P;

	P = Alokasi(X);
	if(P != LNil){
		InsertFirst(L, P);
	}
}

void InsVLast (List *L, infotype X){
	/* I.S. L mungkin kosong */
	/* F.S. Melakukan alokasi sebuah elemen dan */
	/* menambahkan elemen list di akhir: elemen terakhir yang baru */
	/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
	addressL P;
	P = Alokasi(X);

	if(P != LNil){
		InsertLast(L, P);
	}
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X){
	/* I.S. List L tidak kosong  */
	/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
	/*      dan alamat elemen pertama di-dealokasi */
	addressL P;

	DelFirst(L, &P);
	*X = Info(P);
	Dealokasi(&P);
}

void DelVLast (List *L, infotype *X){
	/* I.S. list tidak kosong */
	/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
	/*      dan alamat elemen terakhir di-dealokasi */
	addressL P;

	DelLast(L, &P);
	*X = Info(P);
	Dealokasi(&P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, addressL P){
	/* I.S. Sembarang, P sudah dialokasi  */
	/* F.S. Menambahkan elemen ber-addressL P sebagai elemen pertama */
	Next(P)=First(*L);
	First(*L)=P;
}

void InsertAfter (List *L, addressL P, addressL Prec){
	/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
	/*      P sudah dialokasi  */
	/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

	Next(P) = Next(Prec);
	Next(Prec) = P;
}


void InsertLast (List *L, addressL P){
	/* I.S. Sembarang, P sudah dialokasi  */
	/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
	addressL Last;

	Next(P) = LNil;
	Last = First(*L);

	if(IsLEmpty(*L)){
		First(*L)=P;
	}
	else{
		while(Next(Last) != LNil){
			Last = Next(Last);
		}
		Next(Last) = P;
	}
	
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, addressL *P){
	/* I.S. List tidak kosong */
	/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
	/*      Elemen list berkurang satu (mungkin menjadi kosong) */
	/* First element yg baru adalah suksesor elemen pertama yang lama */
	*P = First(*L);
	First(*L) = Next(First(*L));
	Next(*P) = LNil;
}

void DelP (List *L, infotype X){
	/* I.S. Sembarang */
	/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
	/* Maka P dihapus dari list dan di-dealokasi */
	/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
	/* maka yang dihapus hanya elemen pertama dengan Info = X */
	/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
	/* List mungkin menjadi kosong karena penghapusan */
	
	addressL P, Prec;
	boolean found;

	P = First(*L);
	Prec = LNil;
	found = false;

	while(!found && P!=LNil){
		if(Info(P) == X){
			found = true;
		}
		else{
			Prec = P;
			P = Next(P);
		}
	}

	if(found){
		if(Prec != LNil){
			DelAfter(L,&P,Prec);
		}
		else{
			if(Next(P) != LNil){
				DelFirst(L, &P);
			}
			else{
				P=LNil;
			}
		}
		Dealokasi(&P);
	}

}

void DelLast (List *L, addressL *P){
	/* I.S. List tidak kosong */
	/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
	/*      Elemen list berkurang satu (mungkin menjadi kosong) */
	/* Last element baru adalah predesesor elemen terakhir yg lama, */
	/* jika ada */
	addressL Last, PrecLast;

	Last = First(*L);
	PrecLast = LNil;

	while(Next(Last) != LNil){
		PrecLast = Last;
		Last = Next(Last);
	}

	*P = Last;
	if(PrecLast == LNil){
		First(*L) = LNil;
	}
	else{
		Next(PrecLast) = LNil;
	}
}

void DelAfter (List *L, addressL *Pdel, addressL Prec){
	/* I.S. List tidak kosong. Prec adalah anggota list  */
	/* F.S. Menghapus Next(Prec): */
	/*      Pdel adalah alamat elemen list yang dihapus  */
	*Pdel = Next(Prec);
	if(*Pdel != LNil){
		Next(Prec) = Next(*Pdel);
	}
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L){
	/* I.S. List mungkin kosong */
	/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
	/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
	/* Jika list kosong : menulis [] */
	/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

	addressL P;
	boolean FirstPrint;

	printf("[");
	P = First(L);
	FirstPrint = true;

	while(P != LNil){
		if(FirstPrint){
			printf("%d", Info(P));
			FirstPrint = false;
		}
		else{
			printf(",%d", Info(P));
		}

		P = Next(P);
	}
	printf("]");
}

int NbElmt (List L){
	/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

	int sum;
	addressL P;

	sum = 0;
	P = First(L);
	while(P != LNil){
		sum++;
		P = Next(P);
	}
	return sum;
}

/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
infotype Max (List L){
	/* Mengirimkan nilai Info(P) yang maksimum */

	infotype max;
	addressL P;

	P = First(L);
	max = Info(P);
	while(P != LNil){
		if(max < Info(P)){
			max = Info(P);
		}
		P = Next(P);
	}

	return max;
}

/****************** PROSES TERHADAP LIST ******************/
void Konkat1 (List *L1, List *L2, List *L3){
	/* I.S. L1 dan L2 sembarang */
	/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
	/* Konkatenasi dua buah list : L1 dan L2    */
	/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
	/* dan L1 serta L2 menjadi list kosong.*/
	/* Tidak ada alokasi/dealokasi pada prosedur ini */

	addressL Last;

	Last = First(*L1);

	if(IsLEmpty(*L1)){
		First(*L1)=First(*L2);
	}
	else{
		while(Next(Last) != LNil){
			Last = Next(Last);
		}
		Next(Last) = First(*L2);
	}

	First(*L3) = First(*L1);
	First(*L1) = LNil;
	First(*L2) = LNil;
}

void PrintListBangunan(List L, TabBangunan T){
	/* Mencetak bangunan-bangunan pada TabBangunan yang indeksnya ada pada List L */
	addressL P;
	int i;
	Bangunan tmp;

	P = First(L);
	i = 1;
	while(P != LNil){
		tmp = TabElmt(T, Info(P));
		// printf("%d. ", Info(P));
		printf("%d. ", i);

		PrintNama(tmp);
		printf(" ");

		TulisPOINT(Pos(tmp));

		printf(" %d lv. %d\n", Pasukan(tmp), Lvl(tmp));

		P = Next(P);
		i++;
	}
}

infotype GetAtIdx(List L, int N){
	/* Mengirimkan indeks pada TabBangunan yang ada pada node ke N list */
	addressL P;
	int i;

	P = First(L);
	i = 1;

	while(i < N){
		P = Next(P);
		i++;
	}

	return Info(P);

}