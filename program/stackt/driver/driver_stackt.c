#include <stdio.h>
#include "../stackt.h"
#include "../../boolean/boolean.h"

#include <stdlib.h>

int main(){
	Stack S;
    infostack X;
    infostack Y;


    SCreateEmpty(&S);

    
    
    // // define dummy infostack X
    // // void MakeBangunan(Bangunan *B, int Tipe, int X, int Y);

    // Bangunan B;
    // MakeBangunan(&B, 1, 2, 0);




	SCreateEmpty(&S);
	printf("isSEmpty? : %d\n", IsSEmpty(S));
    MakeBangunan(&B(X), 1, 1, 1);
    Idx(X) = 1;
    QCreateEmpty(&Qu(Y), 5);
    MakeBangunan(&B(Y), 1, 1, 1);
    Idx(X) = 2;
    QCreateEmpty(&Qu(Y), 5);



	printf("Push 1, ");
	Push(&S, X);
    printf("Push 2 (199x), ");
    for(int i = 1; i <=199; i++)
    {
        Push(&S, Y);
    }
    printf("\n");
    printf("isFull? : %d\n", IsSFull(S));
    
    infostack dummy;
    Pop(&S, &dummy);
    printf("indeks stack Pop : %d\n", Idx(dummy));
    PushUndef(&S);
    Pop(&S, &dummy);
    printf("indeks stack Pop Undef : %d\n", Idx(dummy));

    Bangunan Z;
    PushBangunan(&S, Z, 3);
    PopBangunan(&S, &Z,&Idx(dummy));
    printf("Tipe PopBangunan : %d\n", Tipe(Z));

    PushQ (&S, Qu(Y));
    PopQ (&S, &Qu(dummy));
    printf("PopQ in Qu? : %d\n", IsQEmpty(Qu(dummy)));

    return 0;
}