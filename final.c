//level 1 = 10-100hp, 0-3 cannons, 0 - 1000 gold, holds cannonballs
//level 2 = 101-300hp, 4-7 cannons, 1001 - 5000 gold, holds cannonballs
//level 3 = 301-500hp, 8-12 cannons, 5001 - 15,000 gold, holds cannonballs		
/*struct PirateShip
{
	double windSpeed, weight, shipSpeed;
	int gold, life, hp, level, cannons, cannonballs;
	char FlagColor[10];
	char Location[10];
	char Action[20];
};
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "finalfunc.h"
/*#include "gfx4.h"
#define XSIZE 1000
#define YSIZE 800
#define XMID 500
#define YMID 400
#define CANNONBALLWEIGHT 10
#define CANNONWEIGHT 1000
#define SHIPWEIGHT 10000
#define CANNONPRICE 2000
#define CANNONBALLPRICE 10*/

int main()
{
	PirateShip BlackPearl = {0.0, 0.0, 0.0, 1001, 125, 125, 2, 4, 100, "Black", "SEA", "null"};
	AttackStats attack;
	printStart(&BlackPearl);
	pirateLife(&BlackPearl, &attack);
}
