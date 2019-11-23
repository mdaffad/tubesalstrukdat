#include <stdio.h>
#include "../../bangunan/bangunan.h"
#include "../../arraydinpos/arraydinpos.h"
#include "../../boolean/boolean.h"

void menu(){
    printf("*** BANGUNAN TEST PROGRAM ***\n");
    printf("1. Symbol\n");
    printf("2. CharToTipe\n");
    printf("3. PrintBangunan\n");
    printf("4. IsBUndef\n");
    printf("5. CheckLevelUp\n");
    printf("6. LevelUp -> PrintBangunan\n");
    printf("7. UpdateToLevel -> PrintBangunan\n");
    printf("8. PrintNama\n");
    printf("9. PrintSymbolColor\n");
    printf("*** BANGUNAN TEST PROGRAM ***\n");
}

int main() {
    int input;
    int Tipe;
    int X;
    int Y;
    char c;
    int Lvl;
    Bangunan B;
    IdxType i;
    menu();
    while(1) {
        printf("\n> ");
        scanf("%d", &c);
        switch(c) {
            case 1: {
                printf("Mengirimkan karakter simbol yang merepresentasikan bangunan B sesuai tipe:\n1: Castle (C)\n2: Tower (T)\n3: Fort (F)\n4: Village (V)\n");
                scanf("%d", &Tipe);
                scanf("%d", &X);
                scanf("%d", &Y);
                MakeBangunan(&B, Tipe, X, Y);
                printf("\n Symbol: %c\n", Symbol(B));
                printf("\n");
                break;
            }
            case 2: {
                printf("Mengirim tipe karakter sesuai tipe:\n1: Castle (C)\n2: Tower (T)\n3: Fort (F)\n4: Village (V)\n");
                scanf("%c", &c);
                printf("\nCharToTipe: %c\n", CharToTipe(c));
                printf("\n");
                break;
            }
            case 3: {
                printf("Atribut B terprint di layar\n");
                scanf("%d", &Tipe);
                scanf("%d", &X);
                scanf("%d", &Y);
                MakeBangunan(&B, Tipe, X, Y);
                PrintBangunan(B);
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
            case 6: {
                printf("Menaikkan level bangunan B, pasukan pada bangunan B berkurang sebesar M/2, lalu mencetak atribut bangunan B ke layar.");
                scanf("%d", &Tipe);
                scanf("%d", &X);
                scanf("%d", &Y);
                MakeBangunan(&B, Tipe, X, Y);
                LevelUp(&B);
                PrintBangunan(B);
                printf("\n");
                break;
            }
            case 7: {
                printf("Mengupdate bangunan menjadi level Lvl sesuai spesifikasi, lalu mencetak atribut bangunan B ke layar\n");
                scanf("%d", &Tipe);
                scanf("%d", &X);
                scanf("%d", &Y);
                scanf("%d", &Lvl);
                MakeBangunan(&B, Tipe, X, Y);
                UpdateToLevel(&B, Lvl);
                PrintBangunan(B);
                printf("\n");
                break;
            }
            case 8: {
                printf("Mencetak nama bangunan B sesuai tipe:\n1: Castle (C)\n2: Tower (T)\n3: Fort (F)\n4: Village (V)\n");
                scanf("%d", &Tipe);
                scanf("%d", &X);
                scanf("%d", &Y);
                MakeBangunan(&B, Tipe, X, Y);
                PrintNama(B);
                break;
            }
            case 9: {
                printf("Mencetak nama bangunan B sesuai tipe dgn warna:\n1: Castle (C)\n2: Tower (T)\n3: Fort (F)\n4: Village (V)\n");
                scanf("%d", &Tipe);
                scanf("%d", &X);
                scanf("%d", &Y);
                MakeBangunan(&B, Tipe, X, Y);
                PrintSymbolColor(B);
                break;
            }
            default: {
                printf("Not Available\n");
                break;
            }
        }
    }
    return 0;
}
