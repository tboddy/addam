#define EXPLOSION_OFF 16
#define EXPLOSION_OFF_BIG 32

// lifecycle

void spawnExplosion(fix16 x, fix16 y, s16 anim, bool big){
	// s16 i = -1;
	// for(s16 j = 0; j < EXPLOSION_COUNT; j++) if(!explosions[j].active && i == -1) i = j;
	// // if(i == -1) i = 0;
	// if(i > -1){
	// 	explosions[i].active = TRUE;
	// 	explosions[i].pos.x = fix16ToInt(x);
	// 	explosions[i].pos.y = fix16ToInt(y);
	// 	if(explosions[i].pos.x % 2 == 1) explosions[i].pos.x -= 1;
	// 	if(explosions[i].pos.y % 2 == 1) explosions[i].pos.y -= 1;
	// 	explosions[i].big = big;
	// 	explosions[i].image = SPR_addSprite(explosions[i].big ? &allExplosionsBig : &allExplosions,
	// 		explosions[i].pos.x - (explosions[i].big ? EXPLOSION_OFF_BIG : EXPLOSION_OFF) + GAME_X,
	// 		explosions[i].pos.y - (explosions[i].big ? EXPLOSION_OFF_BIG : EXPLOSION_OFF) + GAME_Y,
	// 		TILE_ATTR(gameOver ? PAL1 : PAL0, 0, FALSE, FALSE));
	// 	SPR_setAnim(explosions[i].image, anim);
	// 	explosions[i].frame = 0;
	// 	explosions[i].clock = 0;
	// }
}

static void killExplosion(s16 i){
	explosions[i].active = FALSE;
	SPR_releaseSprite(explosions[i].image);
}

// loop

static void drawExplosion(s16 i){
	SPR_setPosition(explosions[i].image,
		explosions[i].pos.x - (explosions[i].big ? EXPLOSION_OFF_BIG : EXPLOSION_OFF) + GAME_X,
		explosions[i].pos.y - (explosions[i].big ? EXPLOSION_OFF_BIG : EXPLOSION_OFF) + GAME_Y);
}

static void updateExplosion(s16 i){
	drawExplosion(i);
	if(explosions[i].clock > 0 && explosions[i].clock % 2 == 0){
		explosions[i].frame++;
		if(explosions[i].frame >= 5) killExplosion(i);
		else SPR_setFrame(explosions[i].image, explosions[i].frame);
	}
	explosions[i].clock++;
}

void updateExplosions(){
	for(s16 i = 0; i < EXPLOSION_COUNT; i++) if(explosions[i].active) updateExplosion(i);
}