/* File : graf.c */
/* graf dlm game avatar */

#include "../boolean/boolean.h"
#include "../graf/graf.h"
#include <stdlib.h>
#include <stdio.h>

/* *** Konstruktor *** */
void CreateGraph(infograph X, Graph* G){
	/* I.S. Sembarang ; F.S. Terbentuk Graph dengan satu simpul dengan Id=X */
	adrNode P;

	FirstG(*G) = Nil;
	InsertNode(G, X, &P);
}


/* *** Manajemen Memory List Simpul (Leader) *** */
adrNode AlokNodeGraph (infograph X){
	/*	Mengembalikan address hasil alokasi Simpul X .
	Jika alokasi berhasil, maka address tidak Nil, misalnya
	menghasilkan P, maka Id X, 
	Trail(P)=Nil,
	dan NextG(P)=Nil. Jika alokasi
	gagal, mengembalikan Nil. */
	adrNode P;

	P = (adrNode) malloc (sizeof(NodeGraph));
	if(P != Nil){
		Id(P) = X;
		Trail(P) = Nil;
		NextG(P) = Nil;
	}

    return P;
}

void DeAlokNodeGraph (adrNode P){
	/* I.S. P terdefinisi F.S. P dikembalikan ke sistem */
    free(P);
}

adrSuccNode AlokSuccNode(adrNode Pn){
	/* 	Mengembalikan address hasil alokasi.
	Jika alokasi berhasil, maka address tidak Nil, misalnya
	menghasilkan Pt, maka Succ (Pt)=Pn dan NextG(Pt)=Nil. 
	Jika alokasi gagal, mengembalikan Nil. */
	adrSuccNode P;

   	P = (adrSuccNode) malloc(sizeof(SuccNode));
    if(P != Nil){
	    NextG(P) = Nil;
	    Succ(P) = Pn;
    }
	return P;
}

void DealokSuccNode (adrSuccNode P){
	/* I.S. P terdefinisi F.S. P dikembalikan ke sistem */
    free(P);
}


adrNode SearchNode (Graph G, infograph X){
	/*	Mengembalikan address simpul dengan Id=X jika sudah ada pada graph G, Nil jika belum */
	adrNode P;

	P = FirstG(G);
	while(P != Nil){
		if(Id(P) == X){
			return P;
		}
		P = NextG(P);
	}

    return P;
}

adrSuccNode SearchEdge (Graph G, infograph prec, infograph succ){
	/* 	Mengembalikan address trailer yang menyimpan info busur (prec,succ)
	jika sudah ada pada graph G, Nil jika belum */
	adrNode Pn;
	adrSuccNode P;

    Pn = SearchNode(G, prec);
	if(Pn == Nil){
		// Tidak ada node prec
		return Nil;
	}

	P = Trail(Pn);
	// ada prec, mencari (prec, succ)
    while(P != Nil){
		if(Id(Succ(P)) == succ){
			return P;
		}
		P = NextG(P);
	}

	return P;
}

void InsertNode (Graph* G, infograph X, adrNode* Pn){
	/*	Menambahkan simpul X ke dalam graph, jika alokasi X berhasil.
	I.S. G terdefinisi, X terdefinisi dan belum ada pada G.
	F.S. Jika alokasi berhasil, X menjadi elemen
	terakhir G, Pn berisi address simpul X. Jika alokasi gagal, G tetap, Pn berisi Nil */
	adrNode P;

    *Pn = AlokNodeGraph(X);

	P = FirstG(*G);
	if(P == Nil){
		// kasus graf kosong
		FirstG(*G) = *Pn;
	}

	else {
		// alokasi ke elemen terakhir
		while(NextG(P) != Nil){
			P = NextG(P);
		}
		NextG(P) = *Pn;
	}
}

void InsertEdge (Graph* G, infograph prec, infograph succ){
	/* 	Menambahkan busur dari prec menuju succ ke dalam G 
	I.S. G, prec, succ terdefinisi.
	F.S. Jika belum ada busur (prec,succ) di G, maka tambahkan busur
		(prec,succ) ke G. Jika simpul prec/succ belum ada pada G,
		tambahkan simpul tersebut dahulu. Jika sudah ada busur (prec,succ)
		di G, maka G tetap. */
	adrNode Pprec;
	adrNode Psucc;
	adrSuccNode P;

    if (SearchEdge(*G, prec, succ) == Nil){
		Pprec = SearchNode(*G, prec);
		Psucc = SearchNode(*G, succ);

		if(Pprec == Nil){
			InsertNode(G, prec, &Pprec);
		}
		if(Psucc == Nil){
			InsertNode(G, succ, &Psucc);
		}

		P = Trail(Pprec);

		if(P == Nil){
			Trail(Pprec) = AlokSuccNode(Psucc);
		}
		else {
			while(NextG(P) != Nil){
				P = NextG(P);
			}
			NextG(P) = AlokSuccNode(Psucc);
		}
	}
	// else Edge sudah ada
	
}

/* *** Lain-Lain *** */

void Connect(Graph *G, infograph N1, infograph N2){
	/* Menyambungkan N1 dan N2 */
	InsertEdge(G, N1, N2);
	InsertEdge(G, N2, N1);
}

boolean isConnected (Graph G, infograph N1, infograph N2){
	/* Mengembalikan apakah N1 dan N2 terhubung */
	return (SearchEdge(G, N1, N2) != Nil) && (SearchEdge(G, N2, N1) != Nil);
}
