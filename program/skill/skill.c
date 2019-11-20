/* File: skill.c */
/* skill dalam game Avatar */

#include "../boolean/boolean.h"
#include "../point/point.h"
#include "../arraydinpos/arraydinpos.h"
#include "../queue/queue.h"
#include "../stackt/stackt.h"
#include "../listlinier/listlinier.h"
#include "../skill/skill.h"
#include "../bangunan/bangunan.h"
#include "../matrikskar/matrikskar.h"
#include "../mesinkata/mesinkata.h"
#include "../graf/graf.h"
#include "../pcolor/pcolor.h"
#include "../player/player.h"
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