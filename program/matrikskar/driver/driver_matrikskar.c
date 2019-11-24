#include <stdio.h>
#include "../matrikskar.h"
#include "../../boolean/boolean.h"

int main()
{
    MATRIKS M;
    printf("CreateEmpty (20,20)\n");
    MakeMATRIKS (20, 20, &M);
    printf("IsMatIdxValid (25,25) : %d\n",IsMatIdxValid (25, 25));
    printf("IsMatIdxEff (5,5) : %d\n",IsMatIdxEff(M,5,5));

    printf("GetFirstIdxBrs : %d\n",GetFirstIdxBrs(M));
    printf("GetFirstIdxKol : %d\n",GetLastIdxKol(M));
    printf("GetLastIdxBrs : %d\n",GetFirstIdxBrs(M));
    printf("GetLastIdxKol : %d\n",GetLastIdxKol(M));
    

    Bangunan A;
    Bangunan B;
    Bangunan C;
    Bangunan D;

    

    MakeBangunan(&A, 1, 1, 4);
    MakeBangunan(&B, 2, 20, 5);
    MakeBangunan(&C, 3, 10, 1);
    MakeBangunan(&D, 4, 12, 15);

    TabBangunan T;
    MakeEmpty(&T,4);
    TabElmt(T,1) = A;
    TabElmt(T,2) = B;
    TabElmt(T,3) = C;
    TabElmt(T,4) = D;


    FillPeta(&M, T);
    PrintPeta(M,T);



    return 0;
}