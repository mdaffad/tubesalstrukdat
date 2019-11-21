#include <stdio.h>
#include "skill.h"
#include "boolean.h"

void menu() {
    printf("*** SKILL TEST PROGRAM ***\n");
    printf("PrintSkillName\n")
    printf("*** SKILL TEST PROGRAM ***\n");
}

int main() {
    int input;
    menu();
    while(1) {
        printf("Prosedur untuk menampilkan nama skill sesuai dengan inputannya\n");
        scanf("%d", &input);
        PrintSkillName(input);
        break;
    }
    return 0;
}