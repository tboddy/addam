#define PLAYER_INIT_X FIX16(GAME_W / 2)
#define PLAYER_INIT_Y FIX16(GAME_H - 16 - 12)

#define PLAYER_BOUND_X FIX16(16 + 9)
#define PLAYER_BOUND_W GAME_W_F - PLAYER_BOUND_X

#define PLAYER_BOUND_Y FIX16(16 + 12)
#define PLAYER_BOUND_H GAME_H_F - PLAYER_BOUND_Y

#define PLAYER_SPEED FIX16(3)
#define PLAYER_SPEED_NORM fix16Mul(PLAYER_SPEED, FIX16(NORM))

#define PLAYER_OFF_X 12
#define PLAYER_OFF_Y 12


// movement

#define PLAYER_JUMP_MOD FIX16(0.2)

#define PLAYER_JUMP_Y_FLIP fix16Div(GAME_H_F, FIX16(2))
#define PLAYER_JUMP_Y_LIMIT FIX16(16 + 12)
#define PLAYER_JUMP_H_LIMIT PLAYER_INIT_Y

#define PLAYER_JUMP_X_FLIP fix16Div(GAME_W_F, FIX16(2))
#define PLAYER_JUMP_X_LIMIT FIX16(16 + 12)
#define PLAYER_JUMP_W_LIMIT GAME_W_F - FIX16(12 + 16)



#define WALL_CHECK_MOD FIX16(18)
#define WALL_LIMIT_MOD FIX16(4)

#define WALL_CHECK_X_BOUND PLAYER_BOUND_X + WALL_LIMIT_MOD
#define WALL_CHECK_Y_BOUND PLAYER_BOUND_Y + WALL_LIMIT_MOD
#define WALL_CHECK_W_BOUND PLAYER_BOUND_W - WALL_LIMIT_MOD
#define WALL_CHECK_H_BOUND PLAYER_BOUND_H - WALL_LIMIT_MOD

#define WALL_CHECK_LEFT_BOUND GAME_W_F / 2 - WALL_CHECK_MOD
#define WALL_CHECK_RIGHT_BOUND GAME_W_F / 2 + WALL_CHECK_MOD

#define WALL_CHECK_TOP_BOUND GAME_H_F / 2 - WALL_CHECK_MOD
#define WALL_CHECK_BOTTOM_BOUND GAME_H_F / 2 + WALL_CHECK_MOD

static void movePlayer(){

	// moving across wall
	if((ctrl.left || ctrl.right) && (player.currentWall == 1 || player.currentWall == 3)){
		player.movingLeft = ctrl.left;
		player.pos.x += ctrl.left ? -PLAYER_SPEED : PLAYER_SPEED;
		player.posTile.x = fix16ToInt(player.pos.x / 8);
		if(player.pos.x < PLAYER_BOUND_X) player.pos.x = PLAYER_BOUND_X;
		else if(player.pos.x > PLAYER_BOUND_W) player.pos.x = PLAYER_BOUND_W;
	}

	else if((ctrl.up || ctrl.down) && (player.currentWall == 0 || player.currentWall == 2)){
		player.movingUp = ctrl.up;
		player.pos.y += ctrl.up ? -PLAYER_SPEED : PLAYER_SPEED;
		player.posTile.y = fix16ToInt(player.pos.y / 8);
		if(player.pos.y < PLAYER_BOUND_Y) player.pos.y = PLAYER_BOUND_Y;
		else if(player.pos.y > PLAYER_BOUND_H) player.pos.y = PLAYER_BOUND_H;
	}

	// jumping
	if(ctrl.b && !player.flipping && !player.startedFlip){
		player.flipping = TRUE;
		player.sideFlipped = FALSE;
		player.jumpSpeed = 0;
		player.startedFlip = TRUE;
		player.canFlip = FALSE;
	}
	if(player.flipping){
		player.jumpSpeed += PLAYER_JUMP_MOD;
		switch(player.currentWall){
			case 0:
				player.pos.x -= player.jumpSpeed;
				if(player.pos.x <= PLAYER_JUMP_X_FLIP) SPR_setHFlip(player.image, FALSE);
				if(player.pos.x <= PLAYER_JUMP_X_LIMIT){
					player.flipping = FALSE;
					player.pos.x = PLAYER_JUMP_X_LIMIT;
					player.currentWall = 2;
				}
				break;
			case 1:
				player.pos.y -= player.jumpSpeed;
				if(player.pos.y <= PLAYER_JUMP_Y_FLIP) SPR_setVFlip(player.image, TRUE);
				if(player.pos.y <= PLAYER_JUMP_Y_LIMIT){
					player.flipping = FALSE;
					player.pos.y = PLAYER_JUMP_Y_LIMIT;
					player.currentWall = 3;
				}
				break;
			case 2:
				player.pos.x += player.jumpSpeed;
				if(player.pos.x >= PLAYER_JUMP_X_FLIP) SPR_setHFlip(player.image, TRUE);
				if(player.pos.x >= PLAYER_JUMP_W_LIMIT){
					player.flipping = FALSE;
					player.pos.x = PLAYER_JUMP_W_LIMIT;
					player.currentWall = 0;
				}
				break;
			case 3:
				player.pos.y += player.jumpSpeed;
				if(player.pos.y >= PLAYER_JUMP_Y_FLIP) SPR_setVFlip(player.image, FALSE);
				if(player.pos.y >= PLAYER_JUMP_H_LIMIT){
					player.flipping = FALSE;
					player.pos.y = PLAYER_JUMP_H_LIMIT;
					player.currentWall = 1;
				}
				break;
		}
		if(!ctrl.b && !player.canFlip) player.canFlip = TRUE;
		if(ctrl.b && !player.sideFlipped && player.canFlip && (ctrl.left || ctrl.right || ctrl.up || ctrl.down)){
			player.jumpSpeed = 0;
			player.sideFlipped = TRUE;
			if(ctrl.up){
				player.currentWall = 1;
				SPR_setAnim(player.image, 0);
				SPR_setVFlip(player.image, TRUE);
			} else if(ctrl.down) {
				player.currentWall = 3;
				SPR_setAnim(player.image, 0);
				SPR_setVFlip(player.image, FALSE);
			} else if(ctrl.left){
				player.currentWall = 0;
				SPR_setAnim(player.image, 1);
				SPR_setHFlip(player.image, FALSE);
			}else if(ctrl.right) {
				player.currentWall = 2;
				SPR_setAnim(player.image, 1);
				SPR_setHFlip(player.image, TRUE);
			}
		}
	} else if(!player.flipping && player.startedFlip && !ctrl.b)
		player.startedFlip = FALSE;

	if(stageClock > 0){
	// go thru right wall
		if(wallHealth[0] == 0 && player.pos.x >= WALL_CHECK_W_BOUND &&
			player.pos.y >= WALL_CHECK_TOP_BOUND &&
			player.pos.y <= WALL_CHECK_BOTTOM_BOUND){
			changeLevels(0);
		}

		// go thru bottom wall
		else if(wallHealth[1] == 0 && player.pos.y >= WALL_CHECK_H_BOUND &&
			player.pos.x >= WALL_CHECK_LEFT_BOUND &&
			player.pos.x <= WALL_CHECK_RIGHT_BOUND){
			changeLevels(1);
		}

		// left wall
		else if(wallHealth[2] == 0 && player.pos.x <= WALL_CHECK_X_BOUND &&
			player.pos.y >= WALL_CHECK_TOP_BOUND &&
			player.pos.y <= WALL_CHECK_BOTTOM_BOUND){
			changeLevels(2);
		}

		// go thru top wall
		else if(wallHealth[3] == 0 && player.pos.y <= WALL_CHECK_Y_BOUND &&
			player.pos.x >= WALL_CHECK_LEFT_BOUND &&
			player.pos.x <= WALL_CHECK_RIGHT_BOUND){
			changeLevels(3);
		}
	}

}


// shooting

bool playerBulletDir, playerBulletOffDir;
s8 playerBulletOff, attractBulletDir;
s16 lastPlayerBulletAngle;
#define PLAYER_BULLET_LIMIT 4

static void spawnPlayerBullet(){
	struct bulletSpawner spawner = {
		.x = player.pos.x,
		.y = player.pos.y,
		.image = &playerBullet,
		.big = TRUE,
		.player = TRUE,
		.speed = FIX16(15)
	};
	if(isAttract) attractBulletDir = random() % 3;
	switch(player.currentWall){
		case 0:
			if(ctrl.up){
				spawner.angle = 640;
				spawner.anim = 2;
				spawner.xFlip = TRUE;
				spawner.yFlip = TRUE;
			} else if(ctrl.down){
				spawner.angle = 384;
				spawner.anim = 2;
				spawner.xFlip = TRUE;
			} else {
				spawner.angle = 512;
				spawner.anim = 0;
				spawner.xFlip = TRUE;
			}
			break;
		case 1:
			if((!isAttract && ctrl.left) || (isAttract && attractBulletDir == 0)){
				spawner.angle = 640;
				spawner.yFlip = TRUE;
				spawner.xFlip = TRUE;
				spawner.anim = 2;
			} else if((!isAttract && ctrl.right) || (isAttract && attractBulletDir == 1)){
				spawner.angle = 896;
				spawner.anim = 2;
				spawner.yFlip = TRUE;
			} else {
				spawner.angle = 768;
				spawner.anim = 1;
				spawner.yFlip = TRUE;
			}
			break;
		case 2:
			if(ctrl.up){
				spawner.angle = 896;
				spawner.anim = 2;
				spawner.yFlip = TRUE;
			} else if(ctrl.down){
				spawner.angle = 128;
				spawner.anim = 2;
			} else {
				spawner.angle = 0;
				spawner.anim = 0;
			}
			break;
		case 3:
			if(ctrl.left){
				spawner.angle = 384;
				spawner.anim = 2;
				spawner.xFlip = TRUE;
			} else if(ctrl.right){
				spawner.angle = 128;
				spawner.anim = 2;
			} else {
				spawner.angle = 256;
				spawner.anim = 1;
			}
			break;
	}
	spawner.ints[7] = player.currentWall;
	void updater(s16 i){
		bullets[i].ints[4]++;
		if(bullets[i].ints[4] >= 26) killBullet(i, TRUE);
	}
	spawnBullet(spawner, updater);
}

#define SHOT_INTERVAL 16
s16 shotInterval;

static void shotPlayer(){
	if(player.shotClock >= SHOT_INTERVAL && (ctrl.a) && !player.flipping) player.shotClock = 0;
	if(player.shotClock == 0) spawnPlayerBullet();
	if(player.shotClock < CLOCK_LIMIT) player.shotClock++;
}


static void updatePlayerHit(){
	if(player.hit){
		if(!isAttract) XGM_startPlayPCM(SFX_PLAYER_HIT, 15, SOUND_PCM_CH2);
		player.hit = FALSE;
		player.pos.x = PLAYER_INIT_X;
		player.pos.y = PLAYER_INIT_Y;
		player.currentWall = 1;
		SPR_setAnim(player.image, 0);
		SPR_setVFlip(player.image, FALSE);

		player.health -= 15;
		if(player.health <= 0) {
			SPR_setVisibility(player.image, HIDDEN);
			gameOver = TRUE;
		} else {
			player.recovering = TRUE;
			player.invincibleClock = INVINCIBLE_LIMIT;
		}
	} else if(player.invincibleClock > 0){
		player.invincibleClock--;
		if(player.invincibleClock <= 0){
			player.recovering = FALSE;
		}
	}
}


bool animatingRecovery;
static void drawPlayer(){
	SPR_setPosition(player.image, fix16ToInt(player.pos.x) - PLAYER_OFF_X + GAME_X, fix16ToInt(player.pos.y) - PLAYER_OFF_Y + GAME_Y);
	if((player.currentWall == 1 || player.currentWall == 3) && (ctrl.left || ctrl.right))
		SPR_setHFlip(player.image, player.movingLeft);
	else if((player.currentWall == 0 || player.currentWall == 2) && (ctrl.up || ctrl.down))
		SPR_setVFlip(player.image, player.movingUp);
	if(player.recovering){
		if(!animatingRecovery) animatingRecovery = TRUE;
		if(player.invincibleClock % 30 == 0){
			SPR_setVisibility(player.image, HIDDEN);
		} else if(player.invincibleClock % 30 == 15) {
			SPR_setVisibility(player.image, VISIBLE);
		}
	} else if(!player.recovering && animatingRecovery){
		animatingRecovery = FALSE;
		SPR_setVisibility(player.image, VISIBLE);
	}

}


// attract movement
s16 attractMoveClock;
fix32 attractEnemyDist;
#define ATTRACT_CHECK_DIST FIX32(64)
#define ATTRACT_SPEED FIX16(1)

static void moveAttract(){
	s16 j = -1;
	for(s16 i = 0; i < ENEMY_COUNT; i++) if(enemies[i].active){
		if(j > -1){
			if(enemies[i].pos.y > enemies[j].pos.y) j = i;
		} else j = i;
	}
	if(j > -1){
		attractEnemyDist = getApproximatedDistance(
			fix16ToFix32((player.pos.x - enemies[j].pos.x)),
			fix16ToFix32((player.pos.y - enemies[j].pos.y)));
		if(attractEnemyDist <= ATTRACT_CHECK_DIST){
			if(enemies[j].pos.x < player.pos.x){ // left
				player.angle = 0;
			} else { // right
				player.angle = 512;
			}
			// player.angle = random() % 2 < 1 ? 0 : 512;
			if(player.pos.x < FIX16(32)){
				player.angle = 0;
			} else if(player.pos.x > (GAME_W_F - FIX16(32))){
				player.angle = 512;
			}
			player.pos.x = (player.pos.x + fix16Mul(cosFix16(player.angle), ATTRACT_SPEED));
			player.pos.y = (player.pos.y + fix16Mul(sinFix16(player.angle), ATTRACT_SPEED));
		} else if(attractMoveClock % 20 < 15) {
			if(attractMoveClock % 20 == 0){
				if(player.pos.x < FIX16(32)){
					player.angle = 0;
				} else if(player.pos.x > (GAME_W_F - FIX16(32))){
					player.angle = 512;
				}
			}
			player.pos.x = (player.pos.x + fix16Mul(cosFix16(player.angle), ATTRACT_SPEED));
			player.pos.y = (player.pos.y + fix16Mul(sinFix16(player.angle), ATTRACT_SPEED));
		}
	}

	if(player.pos.x < FIX16(8)){
		player.pos.x = FIX16(8);
		player.vel.x *= -1;
	} else if(player.pos.x > (GAME_W_F - FIX16(8))){
		player.pos.x = (GAME_W_F - FIX16(8));
		player.vel.x *= -1;
	}

	if(player.pos.y < FIX16(8)){
		player.pos.y = FIX16(8);
		player.vel.y *= -1;
	} else if(player.pos.y > (GAME_H_F - FIX16(8))){
		player.pos.y = (GAME_H_F - FIX16(8));
		player.vel.y *= -1;
	}

	attractMoveClock++;
	if(attractMoveClock >= CLOCK_LIMIT) attractMoveClock = 0;

}

static void shotAttract(){
	if(attractMoveClock > 0 && attractMoveClock % 30 == 0)
		spawnPlayerBullet();
}


void loadPlayer(){
	player.health = 100;
	player.pos.x = PLAYER_INIT_X;
	player.pos.y = PLAYER_INIT_Y;
	player.currentWall = 1;
	player.shotClock = SHOT_INTERVAL - 1;
	player.image = SPR_addSprite(&playerReimu, fix16ToInt(player.pos.x) - PLAYER_OFF_X + GAME_X, fix16ToInt(player.pos.y) - PLAYER_OFF_Y + GAME_Y, TILE_ATTR(PAL0, 0, 0, 0));
	SPR_setVisibility(player.image, HIDDEN);
}

void updatePlayer(){

	if(isAttract && player.clock >= 60){
		moveAttract();
		shotAttract();
	} else if(!isAttract && player.clock >= 10) {
		movePlayer();
		shotPlayer();
	}
	if(player.clock == 10) SPR_setVisibility(player.image, VISIBLE);

	updatePlayerHit();
	drawPlayer();
	player.clock++;
	if(isAttract && (ctrl.a || ctrl.b || ctrl.c || ctrl.start)){
		SPR_reset();
		VDP_clearTileMapRect(BG_B, 0, 0, 40, 38);
		VDP_clearTileMapRect(BG_A, 0, 0, 40, 38);
		SYS_hardReset();
	}
}