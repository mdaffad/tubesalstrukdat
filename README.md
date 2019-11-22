# tubesalstrukdat
Tugas Besar Algoritma Struktur Data (IF2120) ITB 2019

## compile
kalo di windows sabi pake git bash:
```sh
gcc */*.c main.c -o main
```
## drivers
untuk driver tolong ditempatkan di folder ./program/adt/driver dan dinamakan driver_adt.c.
misalnya ./program/graf/driver/driver_graf.c.
cara compile driver, masuk dulu ke ./program/adt, lalu
```sh
gcc ../arraydinpos/*.c ../bangunan/*.c ../graf/*.c ../listlinier/*.c ../matrikskar/*.c ../mesinkar/*.c ../mesinkata/*.c ../pcolor/*.c ../player/*.c ../point/*.c ../queue/*.c ../skill/*.c ../stackt/*.c ./driver/*.c -o drive
```
## kalo warnanya jelek
buka cmd:
```sh
reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1
```
