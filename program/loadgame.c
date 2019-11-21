#include <stdio.h>
#include <stdlib.h>

int main()
{
   int num;
   FILE *fptr;
   if ((fptr = fopen("./program.txt","r")) == NULL) { // Menggunakan path relative, bisa juga diganti menjadi path tertentu
       printf("Error opening file!");
       // Program ada jika file pointernya mengembalikan NULL.
       exit(1);
   }
   fscanf(fptr,"%d", &num);
   printf("Value of n=%d", num); // Jangan lupa dihapus karena hanya untuk tes output program.txt nya
   fclose(fptr); 
   return 0;
}
