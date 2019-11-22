#include <stdio.h>
#include "../mesinkar.h"

int main() {
    char c;
    int K;

    START("./test.txt");
    do{
        printf("%c", CC);
        ADV();
    } while(CC !=MARK);

    STARTTULIS("./out.txt");
    TULISKAR('a');
    TULISBLANK();
    TULISKAR('b');
    TULISNL();
    TULISANGKA(1);
    TULISBLANK();
    TULISANGKA(2);
    TULISNL();

    return 0;
}