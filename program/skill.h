/* File : skill.h */
/* skill dalam game Avatar */

#ifndef skill_H
#define skill_H

#include "boolean.h"
#include "point.h"
#include "arraydinpos.h"
#include "queue.h"
#include "stackt.h"
#include "listlinier.h"
#include "skill.h"
#include "bangunan.h"
#include "matrikskar.h"
#include "mesinkata.h"
#include "graf.h"
#include "pcolor.h"
#include "player.h"


// DEFINISI ADT SKILL
// implementasi dgn int sbg kode skill

// DESKRIPSI TIAP SKILL
/*
	Skill 1:
		Nama: Instant Upgrade
		Desc: Seluruh bangunan yang dimiliki pemain akan naik 1 level.
		Kond: Pemain tidak akan mendapat skill ini selain dari daftar skill awal.

	Skill 2:
		Nama: Shield (BONUS)
		Desc: Seluruh bangunan yang dimiliki oleh pemain akan memiliki pertahanan selama 2
			turn lawan . Apabila skill ini digunakan 2 kali berturut-turut, durasi tidak akan
			bertambah, namun menjadi nilai maksimum.
		Kond: Pemain mendapat skill ini jika setelah sebuah lawan menyerang, bangunan pemain
			berkurang 1 menjadi sisa 2.

	Skill 3:
		Nama: Extra Turn
		Desc: Setelah giliran pengaktifan skill ini berakhir, pemain selanjutnya tetap pemain 
			yang sama.
		Kond: Pemain mendapat skill ini jika Fort pemain tersebut direbut lawan.

	Skill 4:
		Nama: Attack Up (BONUS)
		Desc: Pada giliran ini, setelah skill ini diaktifkan, pertahanan bangunan musuh (termasuk
			Shield) tidak akan mempengaruhi penyerangan.
		Kond: Pemain mendapat skill ini jika pemain baru saja menyerang Tower lawan dan
			jumlah towernya menjadi 3.
	Skill 5:
		Nama: Critical Hit (BONUS)
		Desc: Pada giliran ini, setelah skill diaktifkan, jumlah pasukan pada bangunan yang
			melakukan serangan tepat selanjutnya (hanya berlaku 1 serangan) hanya
			berkurang ½ dari jumlah seharusnya efektif sebanyak 2 kali lipat pasukan . Skill ini
			akan menonaktifkan Shield maupun pertahanan bangunan, seperti Attack Up.
		Kond: Pemain mendapat skill ini jika lawan baru saja mengaktifkan skill Extra Turn.
	Skill 6:
		Nama: Instant Reinforcement
		Desc: Seluruh bangunan mendapatkan tambahan 5 pasukan.
		Kond: Pemain mendapat skill ini di akhir gilirannya bila semua bangunan yang ia miliki
			memiliki level 4.
	Skill 7:
		Nama: Barrage
			Desc: Jumlah pasukan pada seluruh bangunan musuh akan berkurang sebanyak 10 pasukan.
		Kond: Pemain mendapat skill ini jika lawan baru saja bertambah bangunannya menjadi 10 bangunan. */

void PrintSkillName(int S);

#endif