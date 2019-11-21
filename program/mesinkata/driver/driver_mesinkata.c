#include <stdio.h>
#include "../mesinkata.c"
#include "../../boolean/boolean.h"

void menu() {
    printf("*** MESINKATA TEST PROGRAM ***\n");
    printf("1. ChartoInt\n");
    printf("2. BacaAngka\n");
    printf("3. BacaHuruf\n");
    printf("4. IsKataSama\n");
    printf("5. IsKataATTACK\n");
    printf("6. IsKataLEVEL_UP\n");
    printf("7. IsKataSKILL\n");
    printf("8. IsKataUNDO\n");
    printf("9. IsKataEND_TURN\n");
    printf("10. IsKataSAVE\n");
    printf("11. IsKataMOVE\n");
    printf("12. IsKataEXIT\n");
    printf("13. IsKataSTATUS\n");
    printf("*** MESINKATA TEST PROGRAM ***\n");
}

int main() {
    int input;
    char c;
    Kata K;
    Kata K1;
    Kata K2;
    menu();
    while(1) {
        printf("\n> ");
        scanf("%d", &input);
        switch(input) {
            case 1: {
                printf("Mengirimkan angka dari karakter, c bernilai ['0'..'9']\n");
                scanf("%c", &c);
                printf("\nCharToInt: %d\n", CharToInt(c));
                printf("\n");
                break;
            }
            case 2: {
                printf("Membaca angka selanjutnya\n");
                STARTKATA("./test.txt");
                printf("\nBacaAngka: %d\n", BacaAngka());
                printf("\n");
            }
            case 3: {
                printf("Membaca karakter selanjutnya\n");
                STARTKATA("./test.txt");
                printf("\nBacaHuruf: %d\n", BacaHuruf());
                printf("\n");
            }
            case 4: {
                printf("Menentukan apakah kedua kata sama, mengirimkan true jika kedua kata sama, false jika tidak\n");
                scanf("%c", &K1);
                scanf("%c", &K2);
                STARTKATA("./test.txt");
                printf("\nIsKataSama: %d\n", IsKataSama(K1, K2));
                printf("\n");
            }
            case 5: {
                printf("Menentukan apakah kata yang diinput sama dengan kata 'ATTACK', mengirimkan true jika kedua kata sama, false jika tidak\n");
                scanf("%c", &K);
                STARTKATA("./test.txt");
                printf("\nIsKataATTACK: %d\n", IsKataAttack(K));
                printf("\n");                
            }
            case 6: {
                printf("Menentukan apakah kata yang diinput sama dengan kata 'LEVEL_UP', mengirimkan true jika kedua kata sama, false jika tidak\n");
                scanf("%c", &K);
                STARTKATA("./test.txt");
                printf("\nIsKataLEVEL_UP: %d\n", IsKataLEVEL_UP(K));
                printf("\n");                
            }
            case 7: {
                printf("Menentukan apakah kata yang diinput sama dengan kata 'SKILL', mengirimkan true jika kedua kata sama, false jika tidak\n");
                scanf("%c", &K);
                STARTKATA("./test.txt");
                printf("\nIsKataSKILL: %d\n", IsKataSKILL(K));
                printf("\n");                
            }
            case 8: {
                printf("Menentukan apakah kata yang diinput sama dengan kata 'UNDO', mengirimkan true jika kedua kata sama, false jika tidak\n");
                scanf("%c", &K);
                STARTKATA("./test.txt");
                printf("\nIsKataUNDO: %d\n", IsKataUNDO(K));
                printf("\n");                
            }
            case 9: {
                printf("Menentukan apakah kata yang diinput sama dengan kata 'END_TURN', mengirimkan true jika kedua kata sama, false jika tidak\n");
                scanf("%c", &K);
                STARTKATA("./test.txt");
                printf("\nIsKataEND_TURN: %d\n", IsKataEND_TURN(K));
                printf("\n");                
            }
            case 10: {
                printf("Menentukan apakah kata yang diinput sama dengan kata 'SAVE', mengirimkan true jika kedua kata sama, false jika tidak\n");
                scanf("%c", &K);
                STARTKATA("./test.txt");
                printf("\nIsKataSAVE: %d\n", IsKataSAVE(K));
                printf("\n");
            }
            case 11: {
                printf("Menentukan apakah kata yang diinput sama dengan kata 'MOVE', mengirimkan true jika kedua kata sama, false jika tidak\n");
                scanf("%c", &K);
                STARTKATA("./test.txt");
                printf("\nIsKataMOVE: %d\n", IsKataMOVE(K));
                printf("\n");
            }
            case 12: {
                printf("Menentukan apakah kata yang diinput sama dengan kata 'EXIT', mengirimkan true jika kedua kata sama, false jika tidak\n");
                scanf("%c", &K);
                STARTKATA("./test.txt");
                printf("\nIsKataEXIT: %d\n", IsKataEXIT(K));
                printf("\n");
            }
            case 13: {
                printf("Menentukan apakah kata yang diinput sama dengan kata 'STATUS', mengirimkan true jika kedua kata sama, false jika tidak\n");
                scanf("%c", &K);
                STARTKATA("./test.txt");
                printf("\nIsKataSTATUS: %d\n", IsKataSTATUS(K));
                printf("\n");                
            }
            default: {
                printf("Not Available\n");
            }
        }
    }
    return 0;
}
