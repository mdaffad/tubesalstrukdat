/* File: mesinkar.h */
/* Definisi Mesin Karakter */

#ifndef __MESIN_KAR_H_
#define __MESIN_KAR_H_

#include "../boolean/boolean.h"

#define MARK '.'
/* State Mesin */
extern char CC;
extern boolean EOP;

void START(char* path);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca, path pita pada parameter.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita
          Jika CC != MARK maka EOP akan padam (false)
          Jika CC = MARK maka EOP akan menyala (true) */

void STARTTULIS(char* path);
/* Membuka pitaout karakter pada path */

void TULISKAR(char c);
/* Menulis c pada pitaout */

void TULISANGKA(int d);
/* Menulis d pada pitaout */

void TULISBLANK();
/* Menulis spasi pada pitaout */

void TULISNL();
/* Menulis newline pada pitaout */

void DONETULIS();
/* Selesai menulis pitaout */

void ADV();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK
          Jika  CC = MARK maka EOP akan menyala (true) */

void ADVInput();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela =
          CC, CC != EOI
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK.
          Jika  CC = MARK maka EOP akan menyala (true) */

#endif
