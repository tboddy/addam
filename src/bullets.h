s16 killBulletsClock = 0;

#define BULLET_DIST_CHECK FIX32(0.5)
#define BULLET_GRAZE_CHECK FIX32(12)
#define BULLET_OFF 4
#define BULLET_OFF_BIG 8
#define BULLET_OFF_HUGE 16
#define BULLET_DIST FIX32(4)
#define BULLET_DIST_BIG FIX32(8)
#define BULLET_DIST_HUGE FIX32(16)
#define BULLET_DIST_PLAYER FIX32(24)

#define BULLET_BOUND_BOSS_X FIX16(16)
#define BULLET_BOUND_BOSS_Y FIX16(48)
#define BULLET_BOUND_BOSS_W FIX16(320 - 16)
#define BULLET_BOUND_BOSS_H FIX16(224 - 40)


// lifecycle

void spawnBullet(struct bulletSpawner spawner, void(*updater)){
	if(spawner.player || (!spawner.player && !player.recovering)){
		s16 i = -1;
		for(s16 j = 0; j < BULLET_COUNT; j++) if(!bullets[j].active && i == -1) i = j;
		if(i > -1 && (spawner.player || (player.invincibleClock < INVINCIBLE_LIMIT))){
			bullets[i].active = TRUE;
			bullets[i].pos.x = spawner.x;
			bullets[i].pos.y = spawner.y;
			bullets[i].speed = spawner.speed;
			bullets[i].angle = spawner.angle;
			bullets[i].player = spawner.player;
			if(bullets[i].player) playerBulletCount++;
			bulletCount++;
			bullets[i].clock = 0;
			bullets[i].big = spawner.big;
			bullets[i].huge = spawner.huge;
			for(u8 j = 0; j < COUNT_INT; j++){
				bullets[i].bools[j] = spawner.bools[j];
				bullets[i].ints[j] = spawner.ints[j];
				bullets[i].fixes[j] = spawner.fixes[j];
			}
			if(spawner.vel.x || spawner.vel.y){
				bullets[i].vel.x = spawner.vel.x;
				bullets[i].vel.y = spawner.vel.y;
			} else {
				bullets[i].vel.x = fix16Mul(cosFix16(spawner.angle), spawner.speed);
				bullets[i].vel.y = fix16Mul(sinFix16(spawner.angle), spawner.speed);
			}
			bullets[i].updater = updater;
			bullets[i].dist = FIX32(bullets[i].player ? (BULLET_OFF_BIG + 4) : (bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF)) - 2);
			bullets[i].image = SPR_addSprite(spawner.image,
				fix16ToInt(bullets[i].pos.x) - (bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF)) + GAME_X,
				fix16ToInt(bullets[i].pos.y) - (bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF)) + GAME_Y,
				TILE_ATTR(gameOver ? PAL1 : PAL0, 0, spawner.yFlip, spawner.xFlip));
			if(spawner.anim) SPR_setAnim(bullets[i].image, spawner.anim);
			bullets[i].anim = spawner.anim;
			SPR_setDepth(bullets[i].image, spawner.player ? 7 : (spawner.top ? 3 : 4));
		}
	}
}

void killBullet(s16 i, bool explode){
	SPR_releaseSprite(bullets[i].image);
	if(bullets[i].player) playerBulletCount--;
	bulletCount--;
	bullets[i].active = FALSE;
	if(explode){
		spawnExplosion(bullets[i].pos.x, bullets[i].pos.y, bullets[i].player ? 3 : bullets[i].anim, FALSE);
		// if(!isAttract) XGM_startPlayPCM(SFX_EXPLOSION_1, 15, SOUND_PCM_CH2);
	}
}

void updateBulletVel(s16 i){
	bullets[i].vel.x = fix16Mul(cosFix16(bullets[i].angle), bullets[i].speed);
	bullets[i].vel.y = fix16Mul(sinFix16(bullets[i].angle), bullets[i].speed);
}


// collision

fix16 bulletModX = FIX16(152 * 2 + 8);
fix16 bulletModY = FIX16(92 * 2 + 8);
fix32 bulletDist, eBulletDist;

static void collideBulletWithEnemy(s16 i){
	for(s16 j = 0; j < ENEMY_COUNT; j++){
		if(enemies[j].active){
			bulletDist = getApproximatedDistance(
				fix16ToFix32((bullets[i].pos.x - enemies[j].pos.x)),
				fix16ToFix32((bullets[i].pos.y - enemies[j].pos.y)));
			if(bulletDist <= bullets[i].dist){
				if(!isAttract) XGM_startPlayPCM(SFX_EXPLOSION_1, 15, SOUND_PCM_CH3);
				killBullet(i, TRUE);
				enemies[j].health--;
				if(enemies[j].health <= 0){
					if(!isAttract) XGM_startPlayPCM(SFX_EXPLOSION_2, 15, SOUND_PCM_CH3);
					if(!enemies[j].boss && isLunatic){
						struct bulletSpawner spawner = {
							.x = enemies[j].pos.x,
							.y = enemies[j].pos.y,
							.image = &smallBullet,
							.anim = 4
						};
						spawner.vel = hone(enemies[j].pos, player.pos, FIX16(2 + (random() % 2 < 1 ? 0.5 : 0)), 0);
						spawnBullet(spawner, EMPTY);
					}
					killEnemy(j);
					enemies[j].active = FALSE;
					SPR_releaseSprite(enemies[j].image);
				} else {
					score += enemies[j].boss ? 64 : 16;
				}
			}
		}
	}
}

fix32 pBulletDist;
#define PLAYER_COL_OFF FIX16(24)
static void collideBulletWithPlayer(s16 i){
	if(bullets[i].pos.y >= (player.pos.y - PLAYER_COL_OFF) && bullets[i].pos.y <= (player.pos.y + PLAYER_COL_OFF) &&
		bullets[i].pos.x >= (player.pos.x - PLAYER_COL_OFF) && bullets[i].pos.x <= (player.pos.x + PLAYER_COL_OFF)){
		pBulletDist = getApproximatedDistance(
			fix16ToFix32((player.pos.x - bullets[i].pos.x)),
			fix16ToFix32((player.pos.y - bullets[i].pos.y)));
		if(pBulletDist <= (player.flipping ? (bullets[i].dist - 3) : bullets[i].dist)){
			player.hit = TRUE;
			killBullets = TRUE;
			spawnExplosion(bullets[i].pos.x, bullets[i].pos.y, bullets[i].anim, TRUE);
		}
	}
}

#define BULLET_BOUND_X FIX16(16)
#define BULLET_BOUND_W GAME_W_F - BULLET_BOUND_X

#define BULLET_BOUND_Y FIX16(16)
#define BULLET_BOUND_H GAME_H_F - BULLET_BOUND_Y

#define BULLET_FLIP_X_CHECK FIX16(GAME_W / 2)
#define BULLET_FLIP_Y_CHECK FIX16(GAME_H / 2)

static void reflectBullet(s16 i){
	if(bullets[i].pos.x <= (BULLET_BOUND_X + FIX16(bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF))) ||
		bullets[i].pos.x >= (BULLET_BOUND_W - FIX16(bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF)))){
		bullets[i].vel.x *= -1;
		if(bullets[i].pos.x < BULLET_FLIP_Y_CHECK) SPR_setHFlip(bullets[i].image, FALSE);
		else if(bullets[i].pos.x > BULLET_FLIP_Y_CHECK) SPR_setHFlip(bullets[i].image, TRUE);
	}
	if(bullets[i].pos.y <= (BULLET_BOUND_Y + FIX16(bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF))) ||
		bullets[i].pos.y >= (BULLET_BOUND_H - FIX16(bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF)))){
		bullets[i].vel.y *= -1;
		if(bullets[i].pos.y < BULLET_FLIP_Y_CHECK) SPR_setVFlip(bullets[i].image, FALSE);
		else if(bullets[i].pos.y > BULLET_FLIP_Y_CHECK) SPR_setVFlip(bullets[i].image, TRUE);
	}
}

static void collideBullet(s16 i){
	if(bullets[i].pos.x <= (BULLET_BOUND_X + FIX16(bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF))) ||
		bullets[i].pos.x >= (BULLET_BOUND_W - FIX16(bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF))) ||
		bullets[i].pos.y <= (BULLET_BOUND_Y + FIX16(bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF))) ||
		bullets[i].pos.y >= (BULLET_BOUND_H - FIX16(bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF)))){
		if(bullets[i].player){
			reflectBullet(i);
		} else killBullet(i, TRUE);
	}
	if(bullets[i].active && bullets[i].player) {
		collideBulletWithEnemy(i);
	} else if(bullets[i].active && !player.recovering && !isAttract && !gameOver) collideBulletWithPlayer(i);
}


// loop

static void drawBullet(s16 i){
	SPR_setPosition(bullets[i].image,
		fix16ToInt(bullets[i].pos.x) - (bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF)) + GAME_X,
		fix16ToInt(bullets[i].pos.y) - (bullets[i].huge ? BULLET_OFF_HUGE : (bullets[i].big ? BULLET_OFF_BIG : BULLET_OFF)) + GAME_Y);
}

static void updateBullet(s16 i){
	bullets[i].pos.x += bullets[i].vel.x;
	bullets[i].pos.y += bullets[i].vel.y;
	bullets[i].posTile.x = fix16ToInt(bullets[i].pos.x / 8);
	bullets[i].posTile.y = fix16ToInt(bullets[i].pos.y / 8);
	if(bullets[i].clock > 0) bullets[i].updater(i);
	if(bullets[i].active){
		collideBullet(i);
		drawBullet(i);
		bullets[i].clock++;
	}
}

void updateBullets(){
	if(killBullets){
		if(killBulletsClock == 0) killBulletsClock = KILL_BULLET_TIME;
		for(s16 i = 0; i < BULLET_COUNT; i++) if(bullets[i].active && !bullets[i].player){
			killBullet(i, FALSE);
		}
		killBulletsClock--;
		if(killBulletsClock <= 0)
			killBullets = FALSE;
	}
	for(s16 i = 0; i < BULLET_COUNT; i++) if(bullets[i].active) updateBullet(i);
}