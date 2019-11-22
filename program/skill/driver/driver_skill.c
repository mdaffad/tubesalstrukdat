#include <stdio.h>
#include "../skill.h"


int main() {
    int input;
    printf("input kode skill: ");
    scanf("%d", &input);
    PrintSkillName(input);
    printf("\n");
    return 0;
}