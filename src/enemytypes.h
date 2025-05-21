// boss suicide

bool keyOne, keyTwo, keyThree, keyFour, keyFive, keySix;

s32 tempScore;
void killEnemy(s16 i){
	if(enemies[i].boss){
		clearBossHud();
		tempScore = 10000;
		killBullets = TRUE;
		switch(enemies[i].type){
			case 3: keyOne = TRUE; break;
			case 8: keyTwo = TRUE; tempScore + 1000; break;
			case 11: keyThree = TRUE; tempScore + 1000 * 2; break;
			case 17: keyFour = TRUE; tempScore + 1000 * 3; break;
			case 20: keyFive = TRUE; tempScore + 1000 * 4; break;
			case 23: keySix = TRUE; tempScore + 1000 * 5; break;
			case 25:
				tempScore + 1000 * 6;
				gameOver = TRUE;
				wonGame = TRUE;
				break;
		}
		unlocked = TRUE;
		loadWalls();
		XGM_stopPlay();
	} else {
		tempScore = 500;
		if(timeLeft == 0) tempScore *= 2;
	}
	score += tempScore;
}

static void setEnemySpeed(s16 i){
	enemies[i].speed = FIX16(isLunatic ? 2.5 : 2) + FIX16((random() % 2 < 1) ? 0.5 : 0);
}


// stages

static void spawnEnemyOne(s16 i){
	enemies[i].health = 2;
	enemies[i].off.x = 8;
	enemies[i].off.y = 8;
	enemies[i].anim = 0;
	enemies[i].image = SPR_addSprite(&enemyFairy,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	setEnemySpeed(i);
}
static void updateEnemyOne(s16 i){}

static void spawnEnemyTwo(s16 i){
	enemies[i].health = 2;
	enemies[i].off.x = 8;
	enemies[i].off.y = 8;
	enemies[i].anim = 1;
	enemies[i].image = SPR_addSprite(&enemyFairy,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	setEnemySpeed(i);
}
static void updateEnemyTwo(s16 i){
	if(enemies[i].clock % 120 == 0 && enemies[i].clock > 0){
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = 2,
			.speed = FIX16(3)
		};
		spawner.angle = honeAngle(enemies[i].pos.x, player.pos.x, enemies[i].pos.y, player.pos.y);
		spawnBullet(spawner, EMPTY);
		bulletSfx(1);
	} else if(enemies[i].clock % 120 == 30){
		bulletSfx(2);
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = 0,
			.speed = FIX16(2),
			.angle = random() % 205,
		};
		for(u8 j = 0; j < (isLunatic ? 5 : 3); j++){
			spawnBullet(spawner, EMPTY);
			spawner.angle += isLunatic ? 205 : 341;
		}
	}
}

static void spawnEnemyThree(s16 i){
	enemies[i].health = 2;
	enemies[i].off.x = 8;
	enemies[i].off.y = 8;
	enemies[i].anim = 2;
	enemies[i].image = SPR_addSprite(&enemyFairy,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	setEnemySpeed(i);
	enemies[i].ints[5] = (random() % 30) + 30;
	enemies[i].ints[6] = enemies[i].ints[5] + 1;
}
static void updateEnemyThree(s16 i){
	if(enemies[i].clock % 60 == enemies[i].ints[5] || enemies[i].clock % 60 == enemies[i].ints[6]){
		if(enemies[i].clock % 60 == enemies[i].ints[5]){
			enemies[i].ints[0] = random() % 1024;
			bulletSfx(1);
		}
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = 0,
			.speed = FIX16(2),
			.angle = enemies[i].ints[0]
		};
		for(u8 j = 0; j < 4; j++){
			spawnBullet(spawner, EMPTY);
			spawner.angle += 128;
		}
		enemies[i].ints[0] += 512;
	}
}

static void spawnEnemyFour(s16 i){
	enemies[i].health = 2;
	enemies[i].off.x = 8;
	enemies[i].off.y = 8;
	enemies[i].anim = 0;
	enemies[i].image = SPR_addSprite(&enemyFairy,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	setEnemySpeed(i);
}
static void updateEnemyFour(s16 i){
	if(enemies[i].clock % 40 >= 20 && enemies[i].clock % 4 == 0){
		if(enemies[i].clock % 9 == 0){
			bulletSfx(2);
		}
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.angle = honeAngle(enemies[i].pos.x, player.pos.x, enemies[i].pos.y, player.pos.y) - (enemies[i].clock % 40 == 20 ? 0 : (40 + (random() % 80))),
			.speed = FIX16(2 + (enemies[i].clock % 8 == 0 ? 0 : 1)),
			.anim = enemies[i].clock % 8 == 4 ? 2 : 0
		};
		spawnBullet(spawner, EMPTY);
	}
}

static void spawnEnemyFive(s16 i){
	enemies[i].health = 2;
	enemies[i].off.x = 8;
	enemies[i].off.y = 8;
	enemies[i].anim = 1;
	enemies[i].image = SPR_addSprite(&enemyFairy,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	setEnemySpeed(i);
}
static void updateEnemyFive(s16 i){
	if(enemies[i].clock % 40 >= 25 && enemies[i].clock % 5 == 0){
		if(enemies[i].clock % 40 == 25)  enemies[i].fixes[0] = 0;
		if(enemies[i].clock % 10 == 5) bulletSfx(1);
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = 4,
			.speed = FIX16(3) - enemies[i].fixes[0],
			.angle = honeAngle(enemies[i].pos.x, player.pos.x, enemies[i].pos.y, player.pos.y)
		};
		spawnBullet(spawner, EMPTY);
		enemies[i].fixes[0] += FIX16(0.2);
	}
}

static void spawnEnemySix(s16 i){
	enemies[i].health = 2;
	enemies[i].off.x = 8;
	enemies[i].off.y = 8;
	enemies[i].anim = 2;
	enemies[i].image = SPR_addSprite(&enemyFairy,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	setEnemySpeed(i);
}
static void updateEnemySix(s16 i){
	if(enemies[i].clock % 40 >= 24){
		if(enemies[i].clock % 40 == 24 || enemies[i].clock % 40 == 32) bulletSfx(2);
		if(enemies[i].clock % 40 == 24){
			enemies[i].ints[0] = random() % 1024;
			enemies[i].fixes[0] = FIX16(3);
		}
		if(enemies[i].clock % 40 == 32){
			enemies[i].ints[0] += 64;
			enemies[i].fixes[0] = FIX16(2);
		}
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.speed = enemies[i].fixes[0],
			.angle = enemies[i].ints[0],
			.anim = 0
		};
		spawnBullet(spawner, EMPTY);
		enemies[i].ints[0] += 128;
	}
}

static void spawnEnemySeven(s16 i){
	enemies[i].health = 3;
	enemies[i].off.x = 8;
	enemies[i].off.y = 8;
	enemies[i].anim = 0;
	enemies[i].image = SPR_addSprite(&enemyFairy,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	setEnemySpeed(i);
}
static void updateEnemySeven(s16 i){
	if((enemies[i].clock % 40 == 10) || (enemies[i].clock % 40 == 20) || (enemies[i].clock % 40 == 30)){
		bulletSfx(2);
		if(enemies[i].clock % 40 == 10){
			enemies[i].ints[0] = random() % 1024;
			enemies[i].fixes[0] = FIX16(3);
		} else if(enemies[i].clock % 40 == 20 || enemies[i].clock % 40 == 30){
			enemies[i].ints[0] += 64;
			enemies[i].fixes[0] -= FIX16(0.5);
		}
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = enemies[i].clock % 40 == 20 ? 4 : 1,
			.speed = enemies[i].fixes[0],
			.angle = enemies[i].ints[0]
		};
		// big true
		for(u8 j = 0; j < 5; j++){
			spawnBullet(spawner, EMPTY);
			spawner.angle += 205;
		}
	}
}




// lily from touhou 7
static void spawnBossOne(s16 i){
	// if(!isAttract) XGM_startPlay(&bgmBoss1);
	if(isAttract) enemies[i].angle = 768 - 64;
	enemies[i].health = 15;
	enemies[i].off.x = 16;
	enemies[i].off.y = 16;
	enemies[i].anim = 0;
	enemies[i].boss = TRUE;
	enemies[i].image = SPR_addSprite(&enemyBoss,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	bossMax = enemies[i].health;
	bossHealth = enemies[i].health;
	loadBossHud();
}

static void updateBossOne(s16 i){
	bossHealth = enemies[i].health;
	if(enemies[i].clock % 300 < 200){
		if(enemies[i].clock % 60 == 20 || enemies[i].clock % 60 == 30 || enemies[i].clock % 60 == 40){
			if(enemies[i].clock % 60 == 20){
				enemies[i].ints[0] == random() % 1024;
				enemies[i].fixes[0] = enemies[i].pos.x;
				enemies[i].fixes[1] = enemies[i].pos.y;
			}
			struct bulletSpawner spawner = {
				.x = enemies[i].fixes[0],
				.y = enemies[i].fixes[1],
				.anim = 0,
				.speed = FIX16(4),
				.angle = enemies[i].ints[0]
			};
			void updater(u8 j){
				if(bullets[j].clock % 3 == 0 && bullets[j].clock > 0 && bullets[j].speed >= FIX16(2.5)){
					bullets[j].speed -= FIX16(0.5);
					updateBulletVel(j);
				}
			}
			for(u8 j = 0; j < 8; j++){
				spawnBullet(spawner, updater);
				spawner.angle += 128;
			}
		} else if(enemies[i].clock % 60 >= 50){
			if(enemies[i].clock % 60 == 50){
				enemies[i].fixes[0] = enemies[i].pos.x;
				enemies[i].fixes[1] = enemies[i].pos.y;
			}
			struct bulletSpawner spawner = {
				.x = enemies[i].pos.x,
				.y = enemies[i].pos.y,
				.anim = 5,
				.speed = FIX16(2.5),
				.angle = random() % 1024
			};
			void updater(u8 j){
				if(bullets[j].clock == 15){
					bullets[j].angle = honeAngle(bullets[j].pos.x, player.pos.x, bullets[j].pos.y, player.pos.y);
					updateBulletVel(j);
				}
			}
			spawnBullet(spawner, updater);
		}
	} else if(enemies[i].clock % 3 == 0 && enemies[i].clock % 300 >= 220 && enemies[i].clock % 300 < 280){
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = 2,
			.speed = FIX16(enemies[i].clock % 6 == 0 ? 2 : 3),
			.angle = random() % 1024
		};
		spawnBullet(spawner, EMPTY);
	}
}

// cirno from touhou 7
static void spawnBossTwo(s16 i){
	if(!isAttract) XGM_startPlay(&bgmBoss1);
	enemies[i].health = 20;
	enemies[i].off.x = 16;
	enemies[i].off.y = 16;
	enemies[i].anim = 1;
	enemies[i].boss = TRUE;
	enemies[i].image = SPR_addSprite(&enemyBoss,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	bossMax = enemies[i].health;
	bossHealth = enemies[i].health;
	loadBossHud();
}
static void updateBossTwo(s16 i){
	bossHealth = enemies[i].health;
	if(enemies[i].clock % 10 == 0 && enemies[i].clock % 90 < 70 && enemies[i].clock % 90 >= 10){
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = 2,
		};
		// big true
		if(enemies[i].clock % 20 == 0){
			bulletSfx(1);
			spawner.speed = FIX16(2);
			spawner.angle = honeAngle(enemies[i].pos.x, player.pos.x, enemies[i].pos.y, player.pos.y);
		} else {
			spawner.speed = FIX16(1.5);
			spawner.angle = honeAngle(enemies[i].pos.x, player.pos.x, enemies[i].pos.y, player.pos.y) - 32 + (random() % 64);
		}
		spawnBullet(spawner, EMPTY);
	}
	if(enemies[i].clock % 50 >= 30 && enemies[i].clock % 2 == 0){
		if(enemies[i].clock % 50 == 30){
			enemies[i].ints[0] = random() % 1024;
			enemies[i].ints[1] = enemies[i].ints[0] + 384;
		}
		if(enemies[i].clock % 10 == 4){
			bulletSfx(2);
		}
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = 5,
			.speed = FIX16(4),
			.angle = enemies[i].clock % 4 == 0 ? enemies[i].ints[0] : enemies[i].ints[1]
		};
		// big true
		spawner.bools[0] = enemies[i].clock % 2 == 0;
		void updater(s16 j){
			if(bullets[j].clock == 5){
				bullets[j].vel.x = 0;
				bullets[j].vel.y = 0;
			} else if(bullets[j].clock == 15){
				bullets[j].speed = FIX16(0.5);
				bullets[j].angle += bullets[j].bools[0] ? 256 : -256;
				updateBulletVel(j);
			} else if(bullets[j].clock > 15 && bullets[j].clock % 5 == 0 && bullets[j].speed < FIX16(4)){
				bullets[j].speed += FIX16(0.5);
				updateBulletVel(j);
			}
		}
		spawnBullet(spawner, updater);
		enemies[i].ints[0] += 64;
		enemies[i].ints[1] -= 64;
	}
}


// eternity from touhou 16, normal spell
static void spawnBossThree(s16 i){
	if(!isAttract) XGM_startPlay(&bgmBoss1);
	enemies[i].health = 25;
	enemies[i].off.x = 16;
	enemies[i].off.y = 16;
	enemies[i].anim = 2;
	enemies[i].boss = TRUE;
	enemies[i].image = SPR_addSprite(&enemyBoss,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	bossMax = enemies[i].health;
	bossHealth = enemies[i].health;
	loadBossHud();
}
static void updateBossThree(s16 i){
	bossHealth = enemies[i].health;
	if(enemies[i].clock % 240 < 180){

		if((enemies[i].clock % 60 >= 30 && enemies[i].clock % 60 < 34) ||
			(enemies[i].clock % 60 >= 35 && enemies[i].clock % 60 < 39) ||
			(enemies[i].clock % 60 >= 40 && enemies[i].clock % 60 < 44)){
			if(enemies[i].clock % 60 == 30 || enemies[i].clock % 60 == 35 || enemies[i].clock % 60 == 40)
				bulletSfx(1);
			if(enemies[i].clock % 60 == 30){
				enemies[i].ints[0] = random() % 1024;
				enemies[i].fixes[0] = 0;
				enemies[i].fixes[1] = enemies[i].pos.x;
				enemies[i].fixes[2] = enemies[i].pos.y;
			} else if(enemies[i].clock % 60 == 35 || enemies[i].clock % 60 == 40){
				enemies[i].fixes[0] += FIX16(1);
			}
			struct bulletSpawner spawner = {
				.x = enemies[i].fixes[1],
				.y = enemies[i].fixes[2],
				.anim = 0,
				.speed = FIX16(3.5) - enemies[i].fixes[0],
				.angle = enemies[i].ints[0]
			};
			// big true
			spawnBullet(spawner, EMPTY);
			enemies[i].ints[0] += 256;
		}

		if(enemies[i].clock % 60 >= 0 && enemies[i].clock >= 60 && enemies[i].clock % 60 < 30){
			if(enemies[i].clock % 60 == 0){
				enemies[i].fixes[1] = enemies[i].pos.x;
				enemies[i].fixes[2] = enemies[i].pos.y;
				enemies[i].ints[2] = random() % 1024;
			}
			if(enemies[i].clock % 15 == 0) bulletSfx(2);
			if(enemies[i].clock % 240 < 120 && enemies[i].clock % 3 == 0){
				struct bulletSpawner spawner = {
					.x = enemies[i].fixes[1],
					.y = enemies[i].fixes[2],
					.anim = 1,
					.speed = FIX16(2),
					.angle = enemies[i].ints[2]
				};
				// big true
				spawner.bools[0] = enemies[i].clock % 6 == 0;
				void updater(s16 j){
					if(!bullets[j].bools[1] && bullets[j].clock % 5 == 0){
						bullets[j].angle += bullets[j].bools[0] ? 64 : -64;
						bullets[j].speed -= FIX16(0.5);
						updateBulletVel(j);
						if(bullets[j].speed <= 0){
							bullets[j].bools[1] = TRUE;
						}
					} else if(bullets[j].bools[1] && bullets[j].clock == 25){
						bullets[j].speed = FIX16(2) + FIX16(bullets[j].bools[0] ? 1 : 0);
						updateBulletVel(j);
					}
				}
				spawnBullet(spawner, updater);
				enemies[i].ints[2] += 158;
			} else if(enemies[i].clock % 240 >= 120 && enemies[i].clock % 2 == 0) {
					struct bulletSpawner spawner = {
						.x = enemies[i].fixes[1],
						.y = enemies[i].fixes[2],
						.anim = 1,
						.speed = FIX16(2.5),
						.angle = enemies[i].ints[2]
					};
					// big true
					spawnBullet(spawner, EMPTY);
					enemies[i].ints[2] += 158;

			}
		}

	}
}


// sunny from gfw, spell 1
static void spawnBossFour(s16 i){
	if(!isAttract) XGM_startPlay(&bgmBoss1);
	enemies[i].health = 30;
	enemies[i].off.x = 16;
	enemies[i].off.y = 16;
	enemies[i].anim = 3;
	enemies[i].boss = TRUE;
	enemies[i].image = SPR_addSprite(&enemyBoss,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	bossMax = enemies[i].health;
	bossHealth = enemies[i].health;
	loadBossHud();
}
static void updateBossFour(s16 i){
	bossHealth = enemies[i].health;
	if(enemies[i].clock % 120 >= 30 && enemies[i].clock % 2 == 0){
		if(enemies[i].clock % 120 == 30){
			enemies[i].ints[0] = random() % 1024;
			enemies[i].ints[1] = enemies[i].ints[0];
		}
		if(enemies[i].clock % 10 == 0) bulletSfx(enemies[i].clock % 120 >= 60 ? 2 : 1);
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = 5,
			.speed = FIX16(enemies[i].clock % 4 == 0 ? 2.5 : 3),
			.angle = enemies[i].ints[0]
		};
		spawner.angle = spawner.angle % 1024;
		spawnBullet(spawner, EMPTY);
		enemies[i].ints[0] += 210;
		if(enemies[i].clock % 120 >= 60 && enemies[i].clock % 4 == 0){
			spawner.anim = 1;
			spawner.speed = FIX16(2);
			spawner.angle = enemies[i].ints[1];
			spawnBullet(spawner, EMPTY);
			enemies[i].ints[1] += 137;
		}
	}
}


// luna from gfw, spells 2, 3
static void spawnBossFive(s16 i){
	if(!isAttract) XGM_startPlay(&bgmBoss1);
	enemies[i].health = 35;
	enemies[i].off.x = 16;
	enemies[i].off.y = 16;
	enemies[i].anim = 4;
	enemies[i].boss = TRUE;
	enemies[i].image = SPR_addSprite(&enemyBoss,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	bossMax = enemies[i].health;
	bossHealth = enemies[i].health;
	loadBossHud();
}
static void updateBossFive(s16 i){
	bossHealth = enemies[i].health;
	if(enemies[i].clock % 60 >= 21 && enemies[i].clock % 3 == 0){
		if(enemies[i].clock % 9 == 0) bulletSfx(1);
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = enemies[i].clock % 6 == 0 ? 1 : 2,
			.speed = FIX16(enemies[i].clock % 6 == 0 ? 2 : 3),
			.angle = random() % 1024
		};
		spawnBullet(spawner, EMPTY);
		if(enemies[i].clock >= 60){
			if(enemies[i].clock % 60 == 21){
				enemies[i].ints[1] = random() % 1024;
			}
			spawner.speed = FIX16(3);
			spawner.angle = enemies[i].ints[1];
			spawner.x += fix16Mul(cosFix16(spawner.angle), FIX16(8));
			spawner.y += fix16Mul(sinFix16(spawner.angle), FIX16(8));
			if(enemies[i].clock  % 6 == 0){
				spawner.big = FALSE;
				spawner.huge = TRUE;
			}
			spawnBullet(spawner, EMPTY);
			enemies[i].ints[1] += 633;
		}
	}
}


// star from gfw, spells 2, 3
static void spawnBossSix(s16 i){
	if(!isAttract) XGM_startPlay(&bgmBoss2);
	enemies[i].health = 40;
	enemies[i].off.x = 16;
	enemies[i].off.y = 16;
	enemies[i].anim = 6;
	enemies[i].boss = TRUE;
	enemies[i].image = SPR_addSprite(&enemyBoss,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	bossMax = enemies[i].health;
	bossHealth = enemies[i].health;
	loadBossHud();
}
static void updateBossSix(s16 i){
	bossHealth = enemies[i].health;
	if(enemies[i].clock % 60 >= 30 && enemies[i].clock % 60 < 34){
		if(enemies[i].clock % 60 == 30) bulletSfx(1);
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = 2,
			.speed = FIX16(enemies[i].clock % 2 == 0 ? 3 : 2),
			.angle = random() % 512
		};
		// huge true
		void updater(s16 j){
			if(bullets[j].clock == 25){
				bullets[j].vel.x = 0;
				bullets[j].vel.y = 0;
			} else if(bullets[j].clock >= 20 && bullets[j].clock % 10 == 0){
				if(bullets[j].clock == 50) killBullet(j, TRUE);
				else {
					bulletSfx(2);
					struct bulletSpawner spawner = {
						.x = bullets[j].pos.x,
						.y = bullets[j].pos.y,
						.anim = 4,
						.speed = FIX16(bullets[j].clock % 20 == 0 ? 3 : 4),
						.angle = honeAngle(bullets[j].pos.x, player.pos.x, bullets[j].pos.y, player.pos.y) - 40 + (random() % 80)
					};
					spawnBullet(spawner, EMPTY);
				}
			}
		}
		for(u8 j = 0; j < 2; j++){
			spawnBullet(spawner, updater);
			spawner.angle += 512;
		}
	}
}


// clownpiece from touhou 15, non, spells 2, 3
static void spawnBossFinal(s16 i){
	if(!isAttract) XGM_startPlay(&bgmBoss2);
	enemies[i].health = 45;
	enemies[i].off.x = 16;
	enemies[i].off.y = 16;
	enemies[i].anim = 6;
	enemies[i].boss = TRUE;
	enemies[i].image = SPR_addSprite(&enemyBoss,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off.x + GAME_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off.y + GAME_Y,
		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	bossMax = enemies[i].health;
	bossHealth = enemies[i].health;
	loadBossHud();
}
static void updateBossFinal(s16 i){
	bossHealth = enemies[i].health;
	if(enemies[i].clock % 120 >= 30 && enemies[i].clock % 2 == 0){
		if(enemies[i].clock % 120 == 30){
			enemies[i].ints[0] = random() % 1024;
		}
		if(enemies[i].clock % 4 == 0) bulletSfx(1);
		struct bulletSpawner spawner = {
			.x = enemies[i].pos.x,
			.y = enemies[i].pos.y,
			.anim = 1,
			.speed = FIX16(3),
			.angle = enemies[i].ints[0]
		};
		// big true
		if(enemies[i].clock % 6 == 0 && enemies[i].clock > 0){
			spawner.anim = 0;
			spawner.bools[5] = TRUE;
			spawner.x += fix16Mul(cosFix16(spawner.angle), FIX16(8));
			spawner.y += fix16Mul(sinFix16(spawner.angle), FIX16(8));
		}
		void updater(s16 j){
			if(!bullets[j].bools[0]){
				if(bullets[j].pos.x <= FIX16((bullets[j].bools[5] ? 38 : 28)) || bullets[j].pos.x >= FIX16(GAME_W - (bullets[j].bools[5] ? 38 : 28))){
					bullets[j].vel.x *= -1;
					bullets[j].vel.x *= 0.75;
					bullets[j].vel.y *= 0.75;
					bullets[j].bools[0] = TRUE;
					SPR_setAnim(bullets[j].image, 0);
				}
				if(bullets[j].pos.y <= FIX16((bullets[j].bools[5] ? 38 : 28)) || bullets[j].pos.y >= FIX16(GAME_H - (bullets[j].bools[5] ? 38 : 28))){
					bullets[j].vel.y *= -1;
					bullets[j].vel.x *= 0.75;
					bullets[j].vel.y *= 0.75;
					bullets[j].bools[0] = TRUE;
					SPR_setAnim(bullets[j].image, 0);
				}
			}
		}
		spawnBullet(spawner, updater);
		enemies[i].ints[0] += 158;
	}
}
