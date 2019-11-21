#include <stdio.h>
#include "bangunan.h"

void menu(){
    printf("*** BANGUNAN TEST PROGRAM ***\n");
    printf("1. Symbol\n");
    printf("2. CharToTipe\n");
    printf("3. BUndef\n");
    printf("4. IsBUndef\n");
    printf("5. CheckLevelUp\n");
    printf("*** BANGUNAN TEST PROGRAM ***\n");
}

int main() {
    int input;
    int Tipe;
    int X;
    int Y;
    char c;
    Bangunan B;
    IdxType i;
    menu();
    while(1) {
        printf("\n> ");
        scanf("%d", &input);
        switch(c) {
            case 1: {
                printf("Mengirimkan karakter simbol yang merepresentasikan bangunan B sesuai tipe:\n
                1: Castle (C)\n
		        2: Tower (T)\n
		        3: Fort (F)\n
		        4: Village (V)\n");
                scanf("%d", &Tipe);
                scanf("%d", &X);
                scanf("%d", &Y);
                MakeBangunan(&B, Tipe, X, Y);
                printf("\n Symbol: %c\n", Symbol(B));
                printf("\n");
                break;
            }
            case 2: {
                printf("Mengirim tipe karakter sesuai tipe:\n
		        1: Castle (C)\n
		        2: Tower (T)\n
		        3: Fort (F)\n
		        4: Village (V)\n");
                scanf("%c", &c);
                printf("\nCharToTipe: %c\n", CharToTipe(c));
                printf("\n");
                break;
            }
            case 3: {
                printf("Mengirimkan nilai bangunan undef dengan spesifikasi semua atribut bernilai -1\n");
                scanf("%d", &Tipe);
                scanf("%d", &X);
                scanf("%d", &Y);
                MakeBangunan(&B, Tipe, X, Y);
                printf("\nBUndef: %d\n", BUndef());
                printf("\n");
                break;
            }
            case 4: {
                printf("Mengirimkan true jika bangunan B adalah BUndef\n");
                scanf("%d", &Tipe);
                scanf("%d", &X);
                scanf("%d", &Y);
                MakeBangunan(&B, Tipe, X, Y);
                printf("\nIsBUndef: %d\n", IsBUndef(B));
                printf("\n");
                break;
            }
            case 5: {
                printf("Mengembalikan apakah level bangunan B dapat dinaikkan\n");
                scanf("%d", &Tipe);
                scanf("%d", &X);
                scanf("%d", &Y);
                MakeBangunan(&B, Tipe, X, Y);
                printf("\nCheckLevelUp: %d\n", CheckLevelUp(B));
                printf("\n");
                break;
            }
            default: {
                printf("Not Available\n");
            }
        }
    }
    return 0;
}
