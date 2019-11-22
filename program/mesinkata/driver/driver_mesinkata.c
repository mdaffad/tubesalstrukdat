#include <stdio.h>
#include "../mesinkata.h"
#include "../../boolean/boolean.h"

/* Driver ini juga merupakan driver untuk mesinkar */

int main() {
    char c;
    int K;

    printf("Ketikkan satu digit angka (akan dibaca dgn pembacaan char) : ");
    scanf("%c", &c);
    getchar();
    printf("\nCharToInt: %d\n\n", CharToInt(c));

    STARTKATA("./test.txt");
    printf("isikan test.txt dengan 1 huruf lalu 1 angka\n");

    c = BacaHuruf();
    K = BacaAngka();
    printf("BacaHuruf: %c\n", c);
    printf("BacaAngka: %d\n", K);
    printf("Pembacaan kata: ");

    BacaInput();
    printf("IsKataATTACK: %d\n", IsKataATTACK(CKata));
    printf("IsKataLEVEL_UP: %d\n", IsKataLEVEL_UP(CKata));
    printf("IsKataSKILL: %d\n", IsKataSKILL(CKata));
    printf("IsKataUNDO: %d\n", IsKataUNDO(CKata));
    printf("IsKataEND_TURN: %d\n", IsKataEND_TURN(CKata));
    printf("IsKataSAVE: %d\n", IsKataSAVE(CKata));
    printf("IsKataMOVE: %d\n", IsKataMOVE(CKata));
    printf("IsKataEXIT: %d\n", IsKataEXIT(CKata));
    printf("IsKataSTATUS: %d\n", IsKataSTATUS(CKata));

    return 0;
}