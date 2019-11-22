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

    return 0;
}