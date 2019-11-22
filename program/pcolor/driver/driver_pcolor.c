/**
Filename: pcolor_driver.c (driver of pcolor.h)
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 17/10/2019
**/

#include <stdio.h>
#include "../pcolor.h"

int main() {
    print_red('R');
    print_green('G');
    print_magenta('M');
    print_cyan('C');
    print_yellow('Y');
    print_blue('B');
    printf("\n");
    return 0;
}
