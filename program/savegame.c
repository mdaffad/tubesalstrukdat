#include <stdio.h>
#include <stdlib.h>

int main() {
   int num;
   FILE *fptr;
   fptr = fopen("C:\\program.txt","w"); // Path untuk write filenya bisa diganti
   if(fptr == NULL) {
      printf("Error!"); 
      exit(1);
   }
   printf("Enter num: ");
   scanf("%d",&num);
   fprintf(fptr,"%d",num);
   fclose(fptr);
   return 0;
}

// KODE MASIH RANGKANYA SAJA, MASIH PERLU DIUBAH SESUAI DENGAN ADT NYA