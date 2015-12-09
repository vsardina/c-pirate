/*
Name:          Ronni Sardina
Date:          11-19-2013
Cite Sources:  none
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "finalfunc.h"
#include "gfx4.h"
#define XSIZE 500
#define YSIZE 400
#define XMID 250
#define YMID 200
#define CANNONBALLWEIGHT 10
#define CANNONWEIGHT 1000
#define SHIPWEIGHT 10000
#define CANNONPRICE 2000
#define CANNONBALLPRICE 10
/*
typedef struct PirateShip_t
{
	double windSpeed, weight, shipSpeed;
	int gold, life, hp, level, cannons, cannonballs;
	char FlagColor[10];
	char Location[15];
	char Action[20];
} PirateShip;
typedef struct Attack_t
{
	int enemyShipLvl, enemyGold, enemyLife, enemyHP, enemyCannons, enemyCannonballs, damageToEnemy, hit, enemyHit, damageToMe;
	char EnemyLocation[10];
	char EnemyFlagColor[10];
	char Attack[20];
	bool win;
} AttackStats;*/
//FUNCTIONS
void rest(PirateShip *myShip)
{
	printf("YOU HAVE RESTED AND REPAIRED ALL DAMAGE TO YOUR SHIP.\n");
	myShip->life = myShip->hp;
}

void printEnemy(AttackStats *attack)
{
	printf("Enemy Ship Lvl : %d\n", attack->enemyShipLvl);
	printf("Enemy Location : %s\n", attack->EnemyLocation);
	printf("Enemy Flag Color : %s\n", attack->EnemyFlagColor);
}

void attackWave(PirateShip *myShip, AttackStats *attack)
{
	time_t t;
	srand(time(&t));
	char Answer[20];
	int d = 0;			//distance from user game
	//Your attack on the enemy
	if (myShip->cannonballs <= 0)
	{
		printf("YOU HAVE NO CANNONBALLS. GO BUY THEM AT THE PORT\n");
	}
	else
	{
		d = playerShot(attack);
		if (myShip->cannonballs >= myShip->cannons)
		{
			if (d <= 5)
			{
				attack->hit = myShip->cannons;
			}
			else if (d <= 10)
			{
				attack->hit = myShip->cannons - 1;
			}
			else if (d <= 20)
			{
				attack->hit = myShip->cannons - 2;
			}
			else if (d <= 40)
			{
				attack->hit = myShip->cannons - 3;
			}
			else if (d <= 80)
			{
				attack->hit = myShip->cannons - 4;
			}
			else if (d <= 160)
			{
				attack->hit = myShip->cannons - 5;	
			}
			else if (d <= 185)
			{
				attack->hit = myShip->cannons - 6;	
			}
			attack->damageToEnemy = attack->hit * 10;
			attack->enemyLife -= attack->damageToEnemy;
			myShip->cannonballs -= myShip->cannons;
		}
		else	//if 0<cannonballs<cannons
		{
			if (d <= 10)
			{
				attack->hit = myShip->cannonballs;
			}
			else if (d <= 20)
			{
				attack->hit = myShip->cannonballs - 1;
			}
			else if (d <= 40)
			{
				attack->hit = myShip->cannonballs - 2;
			}
			else if (d <= 80)
			{
				attack->hit = myShip->cannonballs - 3;
			}
			else if (d <= 160)
			{
				attack->hit = myShip->cannonballs - 4;
			}
			else if (d <= 320)
			{
				attack->hit = myShip->cannonballs - 5;	
			}
			else
			{
				attack->hit = myShip->cannonballs - 6;	
			}
			attack->damageToEnemy = attack->hit * 10;
			attack->enemyLife -= attack->damageToEnemy;
			myShip->cannonballs = 0;
		} 
		
	}
	/*
	if (myShip->cannonballs >= myShip->cannons)
	{
		attack->hit = rand() % myShip->cannons +1;
		attack->damageToEnemy = attack->hit * 10;
		attack->enemyLife -= attack->damageToEnemy;
		myShip->cannonballs -= myShip->cannons;
	}
	else if (myShip->cannonballs > 0)
	{
		attack->hit = rand() % myShip->cannonballs +1;
		attack->damageToEnemy = attack->hit * 10;
		attack->enemyLife -= attack->damageToEnemy;
		myShip->cannonballs = 0;
	}
	else
	{
		printf("YOU HAVE NO CANNONBALLS. GO BUY THEM AT THE PORT\n");
	}*/
	//enemy attack on you
	if (attack->enemyCannonballs >= attack->enemyCannons)
	{
		attack->enemyHit = rand() % attack->enemyCannons + 1;
		attack->damageToMe = attack->enemyHit * 10;
		myShip->life -= attack->damageToMe;
		attack->enemyCannonballs -= attack->enemyCannons;
	}
	else if (attack->enemyCannonballs > 0)
	{
		attack->hit = rand() % attack->enemyCannonballs;
		attack->damageToMe = attack->enemyHit * 10;
		myShip->life -= attack->damageToMe;
		attack->enemyCannonballs = 0;
	}
	else //enemy has no ammo
	{
		attack->enemyLife = 0;
	}

	//print results of attack
	printf("Life : %d/%d\n", myShip->life, myShip->hp);
	printf("Cannonballs left : %d\n", myShip->cannonballs);
	printf("Enemy Life : %d/%d\n", attack->enemyLife, attack->enemyHP);

	if (myShip->life >= .25 * myShip->hp && attack->enemyLife >= .25 * attack->enemyHP)
	{
		printf("BOTH SHIPS ARE STILL SAILING. ATTACK AGAIN? (yes or no)\n");
		scanf("%s", Answer);
		if (!strcmp(Answer, "yes"))
		{
			attackWave(myShip, attack);
		}
		else
		{
			printf("YOU ARE BACK AT PORT\n");
			strcpy(myShip->Location, "PORT");
		}
	
	}
	else if (myShip->life > attack->enemyLife && myShip->life > 0 || myShip->life >= .25 * myShip->hp && attack->enemyLife < .25 * attack->enemyHP)
	{
		printf("YOU SUCCESSFULLY LOOTED THE ENEMY SHIP, GAINED %d GOLD, AND ARE BACK AT PORT\n", attack->enemyGold);
		myShip->gold += attack->enemyGold;
		myShip->hp += attack->enemyHP * .1;
		strcpy(myShip->Location, "PORT");
		printShipStatus(myShip);
	}
	else 
	{
		printf("YOUR SHIP HAS BEEN BOARDED. HALF OF YOUR GOLD HAS BEEN PILLAGED. BACK TO PORT AND BETTER LUCK NEXT TIME.\n");
		myShip->gold -= .5 * myShip->gold;
		strcpy(myShip->Location, "PORT");
		printShipStatus(myShip);
	}
}
double shipSpeed(PirateShip *myShip)
{
	myShip->weight = SHIPWEIGHT + (myShip->cannons * CANNONWEIGHT) + (myShip->cannonballs * CANNONBALLWEIGHT);
	printf("Input Wind Speed in Knots --> \n");
	scanf("%d", myShip->shipSpeed);
	//buoyancy = xxxxxxx
	//shipspeed = shipspeed -=buoyancy
	return myShip->shipSpeed;
}

void attackShip(PirateShip *myShip, AttackStats *attack)
{
	time_t t;
	srand(time(&t));
	char Attack[20];
	if (!strcmp(myShip->Location, "SEA"))
	{
		attack->enemyShipLvl = rand() % 3 +1;
	
		if (attack->enemyShipLvl == 1)
		{
			strcpy(attack->EnemyFlagColor, "yellow");
			strcpy(attack->EnemyLocation, "SEA");
			attack->enemyGold = rand() % 1001;
			attack->enemyLife = rand() % 91 + 10;
			attack->enemyHP = attack->enemyLife;
			attack->enemyCannons = rand() % 4 + 1;
			attack->enemyCannonballs = rand() % 30 + 1;
		}
		else if (attack->enemyShipLvl == 2)
		{
			strcpy(attack->EnemyFlagColor, "red");
			strcpy(attack->EnemyLocation, "SEA");
			attack->enemyGold = rand() % 4000 + 1001;
			attack->enemyLife = rand() % 200+ 101;
			attack->enemyHP = attack->enemyLife;
			attack->enemyCannons = rand() % 4 + 4;
			attack->enemyCannonballs = rand() % 40 + 31;
		}
		else	//if enemy ship lvl == 0
		{
			strcpy(attack->EnemyFlagColor, "blue");
			strcpy(attack->EnemyLocation, "SEA");
			attack->enemyGold = rand() % 10000 + 5001;
			attack->enemyLife = rand() % 200+ 301;
			attack->enemyHP = attack->enemyLife;
			attack->enemyCannons = rand() % 5 + 8;
			attack->enemyCannonballs = rand() % 50 + 71;
		}
		printEnemy(attack);
		printf("Attack? (yes or no) : \n");
		scanf("%s", Attack);
		if (!strcmp(Attack, "yes"))
		{
			attackWave(myShip, attack);	//recursion
		}
		else
		{
			printf("YOU ARE AT SEA\n");
			strcpy(myShip->Location, "SEA");
		}
	
	
	}
	else
	{
		printf("YOU ARE NOT AT SEA\n");
	}
	//find and attack random 0-500hp
	//win = get gold random amount between x and x, x% of defeated ships hp depending on ship level 1,2,3
	//chance of winning varies random between x and x for levels 1,2,3
	//level 1 = 10-100hp, 0-3 cannons, 0 - 1000 gold, holds 0-30 cannonballs
	//level 2 = 101-300hp, 4-7 cannons, 1001 - 5000 gold, holds 31-70 cannonballs
	//level 3 = 301-500hp, 8-12 cannons, 5001 - 15,000 gold, holds 71 - 120 cannonballs
}

void goToPort(PirateShip *myShip)
{
	strcpy(myShip->Location, "PORT");
	printf("YOU ARE AT PORT\n");
}
void goToSea (PirateShip *myShip)
{
	strcpy(myShip->Location, "SEA");
	printf("YOU ARE AT SEA\n");
}

void buyCannons(PirateShip *myShip, int number)
{
	if (!strcmp(myShip->Location, "PORT"))
	{
		if (number * CANNONPRICE < myShip->gold)
		{
			myShip->gold -= (number * CANNONPRICE);
			myShip->cannons += number;
			printf("YOU HAVE BOUGHT %d CANNONS\n", number);
		}
		else
		{
			printf("YOU DO NOT HAVE ENOUGH GOLD. GO ATTACK SOME SHIPS.\n");
		}
	}
	else
	{
		printf("YOU ARE NOT AT PORT\n");
	}
}
void buyCannonballs(PirateShip *myShip, int number)
{
	if (!strcmp(myShip->Location, "PORT"))
	{
		if (number * CANNONBALLPRICE < myShip->gold)
		{
			myShip->gold -= (number * CANNONBALLPRICE);
			myShip->cannonballs += number;
			printf("YOU HAVE BOUGHT %d CANNONBALLS\n", number);
		}
		else
		{
			printf("YOU DO NOT HAVE ENOUGH GOLD. GO ATTACK SOME SHIPS.\n");
		}
	}
	else
	{
		printf("YOU ARE NOT AT PORT\n");
	}
}

void printShipStatus(PirateShip *myShip)
{
	printf("Location : %s\n", myShip->Location);
	printf("Flag Color : %s\n", myShip->FlagColor);
	printf("Life : %d/%d\n", myShip->life, myShip->hp);
	if (!strcmp(myShip->Location, "SEA"))
	{
		printf("Ship Speed : %d\n", myShip->shipSpeed);
		printf("Total Ship Weight : %d\n", myShip->weight);
	}
	printf("# of Cannons : %d\n", myShip->cannons);
	printf("# of Cannonballs : %d\n", myShip->cannonballs);
	printf("Gold Pieces : %d\n", myShip->gold);
	//fix level
	
	if (myShip->hp <= 100 || myShip->cannons <= 3)
	{
		myShip->level = 1;
	}
	else if (myShip->hp > 300 && myShip->cannons > 7)
	{
		myShip->level = 3;
	}
	else
	{
		myShip->level = 2;
	}
	printf("Ship Level : %d\n", myShip->level);
}

void pirateLife(PirateShip *myShip, AttackStats *attack)
{
	gfx_open(XSIZE, YSIZE, "Target Window");
	gfx_clear;
	while(1)
	{
		int number = 0;
		printf("=======================================\n");
		if (myShip->cannonballs <= 0 && myShip->gold < 10)
		{
			printf("YOU ARE POOR AND DO NOT HAVE THE SUPPLIES TO ATTACK. YOUR CREW COMMITS MUTINY AND YOU WALK THE PLANK.\n");
			strcpy(myShip->Action, "end");
		}
		else if (myShip->hp >= 300 && myShip->gold > 10000)
		{
			printf("YOU ARE A SUCCESSFUL PLUNDERING PIRATE! ENJOY YOUR INFAMY IN YOUR PALACE IN THE CARRIBBEAN.\n");
			strcpy(myShip->Action, "end");
		}
		else
		{
			printf("What Would You Like To Do? \ngotoport\ngotosea\nbuycannons\nbuycannonballs\nattackships\nshipstats\nrest\nend\n");
			printf("=======================================\n");
			scanf("%s", myShip->Action);
		}
		if (!strcmp(myShip->Action, "gotoport"))
		{
			goToPort(myShip);
		}
		else if (!strcmp(myShip->Action, "gotosea"))
		{
			goToSea(myShip);
		}
		else if (!strcmp(myShip->Action, "buycannons"))
		{
			printf("Cannon Price : %d\n", CANNONPRICE);
			printf("Input # of Cannons : \n");
			scanf("%d", &number);
			buyCannons(myShip, number);
		}
		else if (!strcmp(myShip->Action, "buycannonballs"))
		{
			printf("Cannonball Price : %d\n", CANNONBALLPRICE);
			printf("Input # of Cannonballs : \n");
			scanf("%d", &number);
			buyCannonballs(myShip, number);
		}
		else if (!strcmp(myShip->Action, "attackships"))
		{
			attackShip(myShip, attack);
		}
		else if (!strcmp(myShip->Action, "shipstats"))
		{
			printShipStatus(myShip);
		}
		else if (!strcmp(myShip->Action, "rest"))
		{
			rest(myShip);
		}
		else if (!strcmp(myShip->Action, "end"))
		{
			printf("YOUR PIRATE LIFE HAS ENDED\n");
			printShipStatus(myShip);
			break;
		}
		else
		{
			printf("PLEASE TYPE A VALID RESPONSE\n");
		}
	}
}
void printStart(PirateShip *myShip)
{
	printf("WELCOME TO THE PIRATE LIFE!\n");
	printShipStatus(myShip);
}
int playerShot(AttackStats *attack)
{
	time_t t;
	srand(time(&t));
	int r = 30;					//radius
	int x = 50, y = YMID;		//starting coordinates
	int d = 0;		//distance from center target
	double dx = 0.;		//change in coordinates
	char c;
	double deltat = 10000;
	//Open screen
	//gfx_open(XSIZE, YSIZE, "Target Window");
	//gfx_clear;
	//gfx_clear_color(213, 47, 94);
	drawEnemy(attack);
	
	//change crosshair target speed
	if(attack->enemyShipLvl == 1)		//level 1 enemy
	{
		dx = 1;
	}
	else if (attack->enemyShipLvl == 2)		//level 2 enemy
	{
		dx = 2;
	}
	else		//level 3 enemy
	{
		dx = 3;
	}
	
	while (1)
	{
		gfx_clear();
		//gfx_clear_color(213, 47, 94);
		drawEnemy(attack);
		//draw white target circle
		gfx_color(255, 255, 255);
		gfx_circle(XMID, YMID, r);
		//draw moving green crosshair circle
		gfx_color(82, 199, 104);
		gfx_point(x, y);
		gfx_circle(x, y, r);
		gfx_flush();
		usleep(deltat);
		
		//if crosshairs hits edge of screen reverse direction
		if (x >= XSIZE - r || x <= r)
		{
			dx = dx * -1;
		}
		//change center of crosshairs
		x += dx;
		
		if (gfx_event_waiting())
		{
			c = gfx_wait();
			if (c == 1)
			{
				d = abs(x-XMID);
				return d;
				break;
			}
		}
	}	
}
void drawEnemy(AttackStats *attack)
{
	XPoint base[4];
	XPoint sail[3];
	base[0].x = XMID - 70;
	base[0].y = YMID - 20;
	base[1].x = XMID + 70;
	base[1].y = YMID - 20;
	base[2].x = XMID + 40;
	base[2].y = YMID + 20;
	base[3].x = XMID - 40;
	base[3].y = YMID + 20;
	
	sail[0].x = XMID;
	sail[0].y = YMID - 100;
	sail[1].x = XMID + 70;
	sail[1].y = YMID - 25;
	sail[2].x = XMID - 40;
	sail[2].y = YMID - 25;
	
	
	gfx_color(17, 0, 127);							//ocean blue
	gfx_fill_rectangle(0, YSIZE/2, XSIZE, YSIZE/2);
	gfx_color(74, 64, 25);							//wood brown
	gfx_fill_polygon(base, 4);
	if(!strcmp(attack->EnemyFlagColor, "yellow"))
	{
		gfx_color(255, 255, 102);	//yellow flag
	}
	else if(!strcmp(attack->EnemyFlagColor, "red"))
	{
		gfx_color(204, 0, 0);	//red flag
	}
	else		//blue flag
	{
		gfx_color(32, 106, 255);
	}
	gfx_fill_polygon(sail, 3);
}
//default constructor: shipweight = 100, cannons = 1, cannonballs = 10, flagcolor = black
//normal constructor
//copy constructor
//calculate speed and weight: 
	//weight = shipweight + cannonweight + cannonballsweight
	//shipspeed = wind(mph) 
	//Force = mass(kg) * velocity
	//acceleration = change in velocity / time
	//mass = density * volume

	//wind speed = speed of the boat
	//weight = subtracts from buovancy (the water level rises)
	//default buoyancy = 2ft water level
	//higher water level subtracts from speed

//lower anchor
	//shipspeed = 0, regardless of wind

//attack other ships 
	//int life
	//int gold
	//int level
	//cannot have anchor down
	//find and attack random 0-500hp
	//win = get gold random amount between x and x, x% of defeated ships hp depending on ship level 1,2,3
	//chance of winning varies random between x and x for levels 1,2,3
	//level 1 = 10-100hp, 0-3 cannons, 0 - 1000 gold, holds 0-12 cannonballs
	//level 2 = 101-300hp, 4-7 cannons, 1001 - 5000 gold, holds 13-28 cannonballs
	//level 3 = 301-500hp, 8-12 cannons, 5001 - 15,000 gold, holds 29 - 48 cannonballs
	//shooting cannon(round 1)
		//your attack cannons have random x-x % hitting target
		//each shot -= cannonball
		//successful shot = 10 points damage
		//print ship status
	//if you sustain 75% damage you lose, minus x% of winning ships gold amount of gold looted, minus x% of winning ships xp depending on ships level
	//other ships have same rates
	//raise white flag truce fight ends no more attacks
	//one helper method (input win ship, input loss ship)
//ship status
	//life
	//gold
	//cannons
	//cannonballs
	//weight
	//speed or at anchor
//go to port
//buy cannons
//repair ship

