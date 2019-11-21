#include <stdio.h>
#include "arraydinpos.h"
#include "boolean.h"

void menu() {
    printf("*** ARRAYDINPOS TEST PROGRAM ***\n");
    printf("1. TabNbElmt\n");
    printf("2. MaxElement\n");
    printf("3. GetFirstIdx\n");
    printf("4. GetLastIdx\n");
    printf("5. IsIdxTabValid\n");
    printf("6. IsIdxTabEff\n");
    printf("7. IsTabEmpty\n");
    printf("8. IsTabFull\n");
    printf("*** ARRAYDINPOS TEST PROGRAM ***\n");
}

int main() {
    int input;
    TabBangunan T;
    TabBangunan T1;
    IdxType i;
    menu();
    while(1) {
        printf("\n> ");
        scanf("%d", &input);
        switch(c) {
            case 1: {
                printf("Mengirimkan banyaknya elemen efektif tabel, mengirimkan nol jika tabel kosong");
                MakeEmpty(&T);
                printf("\nTabNbElmt: %d\n", TabNbElmt(T));
                printf("\n");
                break;
            }
            case 2: {
                printf("Mengirimkan maksimum elemen yang dapat ditampung oleh tabel");
                MakeEmpty(&T);
                printf("\nMaxElement: %d\n", MaxElement(T));
                printf("\n");
                break;
            }
            case 3: {
                printf("Mengirimkan indeks elemen T pertama\n");
                MakeEmpty(&T);
                printf("\nGetFirstIdx: %d\n", GetFirstIdx(T));
                printf("\n");
                break;
            }
            case 4: {
                printf("Mengirimkan indeks elemen T terakhir\n");
                MakeEmpty(&T);
                printf("\nGetLastIdx: %d\n", GetLastIdx(T));
                printf("\n");
                break;
            }
            case 5: {
                printf("Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel, yaitu antara indeks yang terdefinisi utk container\n");
                MakeEmpty(&T);
                printf("\nIsIdxTabValid: %d\n", IsIdxTabValid(T, i));
                printf("\n");
                break;
            }
            case 6: {
                printf("Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel, yaitu antara FirstIdx(T)..LastIdx(T)\n");
                MakeEmpty(&T);
                printf("\nIsIdxTabEff: %d\n", IsIdxTabEff(T, i));
                printf("\n");
                break;
            }
            case 7: {
                printf("Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak\n");
                MakeEmpty(&T);
                printf("\nIsTabEmpty: %d\n", IsTabEmpty(T));
                printf("\nIsTabEmpty: %d\n", IsTabEmpty(T1));
                printf("\n")
            }
            case 8: {
                printf("Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak\n");
                MakeEmpty(&T);
                printf("\nIsTabFull: %d\n", IsTabFull(T));
                printf("\nIsTabFull: %d\n", IsTabFull(T1));
                printf("\n");
            }
            default: {
                printf("Not Available\n");
            }
        }
    }
    return 0;
}
