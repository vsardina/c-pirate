
#ifndef FINALFUNC_H
#define FINALFUNC_H

typedef struct PirateShip_t
{
	double windSpeed, weight, shipSpeed;
	int gold, life, hp, level, cannons, cannonballs;
	char FlagColor[10];
	char Location[10];
	char Action[20];
} PirateShip;
typedef struct AttackStats_t
{
	int enemyShipLvl, enemyGold, enemyLife, enemyHP, enemyCannons, enemyCannonballs, damageToEnemy, hit, enemyHit, damageToMe;
	char EnemyLocation[10];
	char EnemyFlagColor[10];
	char Attack[20];
	bool win;
} AttackStats;
void rest(PirateShip *myShip);
void printShipStatus(PirateShip *myShip);
void printEnemy(AttackStats *attack);
void attackWave(PirateShip *myShip, AttackStats *attack);
double shipSpeed(PirateShip *myShip);
void attackShip(PirateShip *myShip, AttackStats *attack);
void goToPort(PirateShip *myShip);
void goToSea(PirateShip *myShip);
void buyCannons(PirateShip *myShip, int number);
void buyCannonballs(PirateShip *myShip, int number);
void pirateLife(PirateShip *myShip, AttackStats *attack);
void printStart(PirateShip *myShip);
void drawEnemy(AttackStats *attack);
int playerShot(AttackStats *attack);

#endif
