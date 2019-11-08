/* File: skill.c */
/* skill dalam game Avatar */

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
#include <stdio.h>

void PrintSkillName(int S){
	switch(S){
		case 1: {
			// IU
			printf("Instant Upgrade");
			break;
		}
		case 2: {
			// SHIELD
			printf("Shield");
			break;
		}
		case 3: {
			// EXTRA TURN
			printf("Extra Turn");
			break;
		}
		case 4: {
			// ATTACK UP
			printf("Attack Up");
			break;
		}
		case 5: {
			// ATTACK UP
			printf("Critical Hit");
			break;
		}
		case 6: {
			// INSTANT REINFORCEMENT
			printf("Instant Reinforcement");
			break;
		}
		case 7: {
			// BARRAGE
			printf("Barrage");
			break;
		}
	}
}