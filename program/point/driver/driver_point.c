#include <stdio.h>
#include "../point.h"
#include "../../boolean/boolean.h"

int main() {
    POINT P1, P2;

    printf("Point 1: ");
    BacaPOINT(&P1);
    printf("Point 2: ");
    BacaPOINT(&P2);

    printf("\n");
    printf("PointEQ : %d\n", PointEQ(P1, P2));
    printf("PointNEQ : %d\n", PointNEQ(P1, P2));

    printf("\n");
    printf("P1: "); TulisPOINT(P1); printf("\n");
    printf("P2: "); TulisPOINT(P2); printf("\n");


    return 0;
}