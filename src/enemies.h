#include "enemytypes.h"

void spawnEnemy(u8 type){
	s16 i = -1;
	for(s16 j = 0; j < ENEMY_COUNT; j++) if(!enemies[j].active && i == -1) i = j;
	if(i > -1){
		enemies[i].active = TRUE;
		enemies[i].angle = random() % 1024;
		enemies[i].pos.x = FIX16(GAME_W / 2) + cosFix16(enemies[i].angle) * 16;
		enemies[i].pos.y = FIX16(GAME_W / 2) + sinFix16(enemies[i].angle) * 16;
		// enemies[i].pos.x = FIX16(GAME_W / 2) - FIX16(16) + FIX16(random() % 32);
		// enemies[i].pos.y = FIX16(GAME_H / 2) - FIX16(16) + FIX16(random() % 32);
		enemies[i].clock = 0;
		enemies[i].boss = FALSE;
		enemies[i].type = type;
		for(u8 j = 0; j < COUNT_INT; j++){
			enemies[i].bools[j] = 0;
			enemies[i].ints[j] = 0;
			enemies[i].fixes[j] = 0;
		}
		switch(enemies[i].type){

			case 1: spawnEnemyOne(i); break;
			case 2: spawnEnemyTwo(i); break;

			case 3: spawnBossOne(i); break;

			case 4: spawnEnemyThree(i); break;
			case 5: spawnEnemyFour(i); break;
			case 6: spawnEnemyFive(i); break;
			case 7: spawnEnemySix(i); break;

			case 8: spawnBossTwo(i); break;

			case 9: spawnEnemySeven(i); break;

			case 11: spawnBossThree(i); break;

			case 17: spawnBossFour(i); break;
			case 20: spawnBossFive(i); break;
			case 23: spawnBossSix(i); break;
			case 25: spawnBossFinal(i); break;
		}
		if(enemies[i].boss){
			enemies[i].speed = FIX16(0.25);
			enemies[i].pos.x = FIX16(GAME_W / 2);
			enemies[i].pos.y = FIX16(GAME_H / 2);
			enemies[i].angle = 256 * (random() % 4) + 128;
		}
		SPR_setDepth(enemies[i].image, 6);
		SPR_setAnim(enemies[i].image, enemies[i].anim);
		SPR_setHFlip(enemies[i].image, random() % 2 < 1);
		enemies[i].vel.x = fix16Mul(cosFix16(enemies[i].angle), enemies[i].speed);
		enemies[i].vel.y = fix16Mul(sinFix16(enemies[i].angle), enemies[i].speed);
		spawnExplosion(enemies[i].pos.x, enemies[i].pos.y, enemies[i].boss ? 3 : enemies[i].anim, TRUE);
	}
}

#define ENEMY_BOUND_X FIX16(24)
#define ENEMY_BOUND_W GAME_W_F - ENEMY_BOUND_X

#define ENEMY_BOUND_Y FIX16(24)
#define ENEMY_BOUND_H GAME_H_F - ENEMY_BOUND_Y

#define BOSS_BOUND_X FIX16(88)
#define BOSS_BOUND_W GAME_W_F - BOSS_BOUND_X

#define BOSS_BOUND_Y FIX16(96)
#define BOSS_BOUND_H GAME_H_F - BOSS_BOUND_Y

// enemies[i].boss


static void reflectEnemy(s16 i){
	if(enemies[i].pos.x <= ((enemies[i].boss ? BOSS_BOUND_X : ENEMY_BOUND_X) + enemies[i].off.x) ||
		enemies[i].pos.x >= ((enemies[i].boss ? BOSS_BOUND_W : ENEMY_BOUND_W) - enemies[i].off.x))
		enemies[i].vel.x *= -1;
	if(enemies[i].pos.y <= ((enemies[i].boss ? BOSS_BOUND_Y : ENEMY_BOUND_Y) + enemies[i].off.y) ||
		enemies[i].pos.y >= ((enemies[i].boss ? BOSS_BOUND_H : ENEMY_BOUND_H) - enemies[i].off.y))
		enemies[i].vel.y *= -1;
}

static void collideEnemy(s16 i){
	if(enemies[i].pos.x <= ((enemies[i].boss ? BOSS_BOUND_X : ENEMY_BOUND_X) + enemies[i].off.x) ||
		enemies[i].pos.x >= ((enemies[i].boss ? BOSS_BOUND_W : ENEMY_BOUND_W) - enemies[i].off.x) ||
		enemies[i].pos.y <= ((enemies[i].boss ? BOSS_BOUND_Y : ENEMY_BOUND_Y) + enemies[i].off.y) ||
		enemies[i].pos.y >= ((enemies[i].boss ? BOSS_BOUND_H : ENEMY_BOUND_H) - enemies[i].off.y)){
			reflectEnemy(i);
	}
}

static void drawEnemy(s16 i){
	if(gameOver && !enemies[i].bools[7]){
		enemies[i].bools[7] = TRUE;
		SPR_setPalette(enemies[i].image, PAL1);
	}
	SPR_setPosition(enemies[i].image,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y);
}

static void updateEnemy(s16 i){
	enemyCount++;

	if(enemies[i].boss && enemies[i].clock > 0){
		if(enemies[i].clock % 240 == 0){
			enemies[i].vel.x *= 0.75;
			enemies[i].vel.y *= 0.75;
		} else if(enemies[i].clock % 240 == 120){
			enemies[i].vel.x *= 1.5;
			enemies[i].vel.y *= 1.5;
		}
	}

	enemies[i].pos.x += enemies[i].vel.x;
	enemies[i].pos.y += enemies[i].vel.y;
	enemies[i].posTile.x = fix16ToInt(enemies[i].pos.x / 8);
	enemies[i].posTile.y = fix16ToInt(enemies[i].pos.y / 8);
	if(enemies[i].clock > 0){
		switch(enemies[i].type){

			case 1: updateEnemyOne(i); break;
			case 2: updateEnemyTwo(i); break;
			case 3: updateBossOne(i); break;
			case 4: updateEnemyThree(i); break;
			case 5: updateEnemyFour(i); break;
			case 6: updateEnemyFive(i); break;
			case 7: updateEnemySix(i); break;
			case 8: updateBossTwo(i); break;
			case 9: updateEnemySeven(i); break;

			case 11: updateBossThree(i); break;

			case 17: updateBossFour(i); break;
			case 20: updateBossFive(i); break;
			case 23: updateBossSix(i); break;
			case 25: updateBossFinal(i); break;

		}
	}

	if(enemies[i].boss && enemies[i].clock >= 60 && enemies[i].clock % 4 == 3 && isLunatic){
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = 4,
			.speed = FIX16(2 + (random() % 2 < 1 ? 0.5 : 0)),
			.angle = random() % 1024
		};
		spawnBullet(spawner, EMPTY);
	}

	collideEnemy(i);
	drawEnemy(i);
	enemies[i].clock++;
}

void updateEnemies(){
	enemyCount = 0;
	// if(killEnemies)
	// 	for(s16 i = 0; i < ENEMY_COUNT; i++) if(enemies[i].active)
	// 		killBullet(i, FALSE);
	for(s16 i = 0; i < ENEMY_COUNT; i++){
		if(enemies[i].active){
			updateEnemy(i);
			if(killEnemies){
				enemies[i].active = FALSE;
				SPR_releaseSprite(enemies[i].image);
			}
		}
	}
	if(killEnemies) killEnemies = FALSE;
}