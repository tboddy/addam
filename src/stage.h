#define WALL_TOP_I 768
#define WALL_BOTTOM_I WALL_TOP_I + 4
#define WALL_LEFT_I WALL_BOTTOM_I + 4
#define WALL_RIGHT_I WALL_LEFT_I + 4

#define WALL_TOP_LEFT_I WALL_RIGHT_I + 4
#define WALL_TOP_RIGHT_I WALL_TOP_LEFT_I + 4
#define WALL_BOTTOM_LEFT_I WALL_TOP_RIGHT_I + 4
#define WALL_BOTTOM_RIGHT_I WALL_BOTTOM_LEFT_I + 4

// #define TORCH_TOP1_I WALL_BOTTOM_RIGHT_I + 4
// #define TORCH_TOP2_I TORCH_TOP1_I + 4
// #define OPEN_LEFT_I TORCH_TOP2_I + 4
// #define OPEN_RIGHT_I OPEN_LEFT_I + 4

// #define OPEN_TOP_LEFT_I OPEN_RIGHT_I + 4
// #define OPEN_TOP_RIGHT_I OPEN_TOP_LEFT_I + 4
// #define OPEN_BOTTOM_LEFT_I OPEN_TOP_RIGHT_I + 4
// #define OPEN_BOTTOM_RIGHT_I OPEN_BOTTOM_LEFT_I + 4

#define DOOR_X_I WALL_BOTTOM_RIGHT_I + 4
#define DOOR_Y_I DOOR_X_I + 4

#define LOCK_X_I DOOR_Y_I + 4
#define LOCK_Y_I LOCK_X_I + 4

#define WALL_W GAME_W_T / 2
#define WALL_H GAME_H_T / 2 - 2
#define WALL_X GAME_X_T
#define WALL_Y GAME_Y_T

#define WALL_SIZE 2

s16 introTime;
#define INTRO_LIMIT 120

bool clearedRooms[25];

void loadWalls(){
	bossActive = FALSE;
	switch(mapPos.y){
		case 0:
			switch(mapPos.x){
				case 0:
					currentStage = 1;
					wallHealth[0] = 2;
					wallHealth[1] = 2;
					wallHealth[2] = 1;
					wallHealth[3] = 1;
					break;
				case 1:
					currentStage = 2;
					wallHealth[0] = keyOne ? 2 : 3;  // 1ST KEY DOOR
					wallHealth[1] = 2;
					wallHealth[2] = 2;
					wallHealth[3] = 1;
					break;
				case 2:
					currentStage = 5;
					wallHealth[0] = 2;
					wallHealth[1] = 2;
					wallHealth[2] = 2;
					wallHealth[3] = 1;
					break;
				case 3:
					currentStage = 6;
					wallHealth[0] = 1;
					wallHealth[1] = 2;
					wallHealth[2] = 2;
					wallHealth[3] = 1;
					break;

				case 4: // 6TH BOSS
					currentStage = 23;
					wallHealth[0] = 1;
					wallHealth[1] = 2;
					wallHealth[2] = 1;
					wallHealth[3] = 1;
					break;


			}
			break;

		case 1:
			switch(mapPos.x){

				case 0:
					currentStage = 3;
					wallHealth[0] = 2;
					wallHealth[1] = 1;
					wallHealth[2] = 1;
					wallHealth[3] = 2;
					break;
				case 1: // 1ST BOSS
					currentStage = 4;
					wallHealth[0] = 1;
					wallHealth[1] = 1;
					wallHealth[2] = 2;
					wallHealth[3] = 2;
					break;

				case 2:
					currentStage = 7;
					wallHealth[0] = 2;
					wallHealth[1] = keyTwo ? 2 : 3; // 2ND KEY DOOR
					wallHealth[2] = 1;
					wallHealth[3] = 2;
					break;
				case 3: // 2ND BOSS
					currentStage = 8;
					wallHealth[0] = 1;
					wallHealth[1] = 1;
					wallHealth[2] = 2;
					wallHealth[3] = 2;
					break;

				case 4:
					currentStage = 22;
					wallHealth[0] = 1;
					wallHealth[1] = 2;
					wallHealth[2] = 1;
					wallHealth[3] = 2;
					break;

			}
			break;

		case 2:
			switch(mapPos.x){
				case 0:
					currentStage = 13;
					wallHealth[0] = 2;
					wallHealth[1] = 2;
					wallHealth[2] = 1;
					wallHealth[3] = 1;
					break;
				case 1:
					currentStage = 12;
					wallHealth[0] = 2;
					wallHealth[1] = 1;
					wallHealth[2] = 2;
					wallHealth[3] = 1;
					break;
				case 2:
					currentStage = 9;
					wallHealth[0] = 2;
					wallHealth[1] = 1;
					wallHealth[2] = keyThree ? 2 : 3; // 3RD KEY DOOR
					wallHealth[3] = 2;
					break;
				case 3:
					currentStage = 10;
					wallHealth[0] = keyFive ? 2 : 3; // 5TH KEY DOOR
					wallHealth[1] = 2;
					wallHealth[2] = 2;
					wallHealth[3] = 1;
					break;
				case 4:
					currentStage = 21;
					wallHealth[0] = 1;
					wallHealth[1] = 2;
					wallHealth[2] = 2;
					wallHealth[3] = 2;
					break;
			}
			break;

		case 3:
			switch(mapPos.x){
				case 0:
					currentStage = 14;
					wallHealth[0] = 2;
					wallHealth[1] = 1;
					wallHealth[2] = 1;
					wallHealth[3] = 2;
					break;
				case 1:
					currentStage = 15;
					wallHealth[0] = 1;
					wallHealth[1] = 2;
					wallHealth[2] = 2;
					wallHealth[3] = 1;
					break;
				case 2:
					currentStage = 18;
					wallHealth[0] = 2;
					wallHealth[1] = 2;
					wallHealth[2] = 1;
					wallHealth[3] = 1;
					break;
				case 3: // 3RD BOSS
					currentStage = 11;
					wallHealth[0] = 1;
					wallHealth[1] = 1;
					wallHealth[2] = keyFour ? 2 : 3; // 4TH KEY DOOR
					wallHealth[3] = 2;
					break;
				case 4:
					currentStage = 24;
					wallHealth[0] = 1;
					wallHealth[1] = keySix ? 2 : 3; // 6TH KEY DOOR
					wallHealth[2] = 1;
					wallHealth[3] = 2;
					break;
			}
			break;

		case 4:
			switch(mapPos.x){
				case 0: // 4TH BOSS
					currentStage = 17;
					wallHealth[0] = 2;
					wallHealth[1] = 1;
					wallHealth[2] = 1;
					wallHealth[3] = 1;
					break;
				case 1:
					currentStage = 16;
					wallHealth[0] = 1;
					wallHealth[1] = 1;
					wallHealth[2] = 2;
					wallHealth[3] = 2;
					break;
				case 2:
					currentStage = 19;
					wallHealth[0] = 2;
					wallHealth[1] = 1;
					wallHealth[2] = 1;
					wallHealth[3] = 2;
					break;
				case 3: // 5TH BOSS
					currentStage = 20;
					wallHealth[0] = 1;
					wallHealth[1] = 1;
					wallHealth[2] = 2;
					wallHealth[3] = 1;
					break;
				case 4: // FINAL BOSS
					currentStage = 25;
					wallHealth[0] = 1;
					wallHealth[1] = 1;
					wallHealth[2] = 1;
					wallHealth[3] = 2;
					break;
			}
			break;

	}
	if(clearedRooms[currentStage]) unlocked = TRUE;
	if(unlocked){
		for(u8 i = 0; i < 4; i++){
			if(wallHealth[i] == 2){
				wallHealth[i] = 0;
			}
		}
		if(!clearedRooms[currentStage]){
			clearedRooms[currentStage] = TRUE;
			progress += 4;
		}
	// } else timeLeft = currentStage == 1 ? 60 : (120 + currentStage * 1);
	} else timeLeft = currentStage == 1 ? 200 : (400 + currentStage * 15);
	if(unlocked) timeLeft = 0;
	for(u8 x = 0; x < WALL_W; x++){
		VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0,
			(x == WALL_W - 1 ? WALL_TOP_RIGHT_I : (x == 0 ? WALL_TOP_LEFT_I : WALL_TOP_I))), WALL_X + x * 2, WALL_Y, WALL_SIZE, WALL_SIZE);
		VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0,
			(x == WALL_W - 1 ? WALL_BOTTOM_RIGHT_I : (x == 0 ? WALL_BOTTOM_LEFT_I : WALL_BOTTOM_I))),
			WALL_X + x * 2, WALL_Y + GAME_H_T - 2, WALL_SIZE, WALL_SIZE);
		if(x > 4 && x < WALL_W - 5){

			// top wall hole
			if(wallHealth[3] == 0){
				VDP_clearTileMapRect(BG_A, WALL_X + x * 2, WALL_Y, WALL_SIZE, WALL_SIZE);
				VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE75_I), WALL_X + x * 2, WALL_Y, WALL_SIZE, WALL_SIZE - 1);
				VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE50_I), WALL_X + x * 2, WALL_Y + 1, WALL_SIZE, WALL_SIZE - 1);
			} else if(wallHealth[3] == 2)
				VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, DOOR_X_I), WALL_X + x * 2, WALL_Y, WALL_SIZE, WALL_SIZE);
			else if(wallHealth[3] == 3)
				VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, LOCK_X_I), WALL_X + x * 2, WALL_Y, WALL_SIZE, WALL_SIZE);

			// bottom wall hole
			if(wallHealth[1] == 0){
				VDP_clearTileMapRect(BG_A, WALL_X + x * 2, WALL_Y + GAME_H_T - 2, WALL_SIZE, WALL_SIZE);
				VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE50_I), WALL_X + x * 2, WALL_Y + GAME_H_T - 2, WALL_SIZE, WALL_SIZE - 1);
				VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE75_I), WALL_X + x * 2, WALL_Y + GAME_H_T - 1, WALL_SIZE, WALL_SIZE - 1);
			}
			else if(wallHealth[1] == 2)
				VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, DOOR_X_I), WALL_X + x * 2, WALL_Y + GAME_H_T - 2, WALL_SIZE, WALL_SIZE);
 			else if(wallHealth[1] == 3)
				VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, LOCK_X_I), WALL_X + x * 2, WALL_Y + GAME_H_T - 2, WALL_SIZE, WALL_SIZE);

		}
	}
	for(u8 y = 0; y < WALL_H; y++){
		VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, WALL_LEFT_I), WALL_X, WALL_Y + 2 + y * 2, WALL_SIZE, WALL_SIZE);
		VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, WALL_RIGHT_I), WALL_X + GAME_W_T - 2, WALL_Y + 2 + y * 2, WALL_SIZE, WALL_SIZE);
		if(y > 3 && y < WALL_H - 4){

			// left wall hole
			if(wallHealth[2] == 0){
				VDP_clearTileMapRect(BG_A, WALL_X, WALL_Y + 2 + y * 2, WALL_SIZE, WALL_SIZE);
				VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE75_I), WALL_X, WALL_Y + 2 + y * 2, WALL_SIZE - 1, WALL_SIZE);
				VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE50_I), WALL_X + 1, WALL_Y + 2 + y * 2, WALL_SIZE - 1, WALL_SIZE);
			} else if(wallHealth[2] == 2)
				VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, DOOR_Y_I), WALL_X, WALL_Y + 2 + y * 2, WALL_SIZE, WALL_SIZE);
			else if(wallHealth[2] == 3)
				VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, LOCK_Y_I), WALL_X, WALL_Y + 2 + y * 2, WALL_SIZE, WALL_SIZE);

			// // right wall hole
			if(wallHealth[0] == 0){
				VDP_clearTileMapRect(BG_A, WALL_X + GAME_W_T - 2, WALL_Y + 2 + y * 2, WALL_SIZE, WALL_SIZE);
				VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE50_I), WALL_X + GAME_W_T - 2, WALL_Y + 2 + y * 2, WALL_SIZE - 1, WALL_SIZE);
				VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE75_I), WALL_X + GAME_W_T - 1, WALL_Y + 2 + y * 2, WALL_SIZE - 1, WALL_SIZE);
			} else if(wallHealth[0] == 2)
				VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, DOOR_Y_I), WALL_X + GAME_W_T - 2, WALL_Y + 2 + y * 2, WALL_SIZE, WALL_SIZE);
			else if(wallHealth[0] == 3)
				VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, LOCK_Y_I), WALL_X + GAME_W_T - 2, WALL_Y + 2 + y * 2, WALL_SIZE, WALL_SIZE);

		}
	}
}

#define PLAYER_CHANGE_OFF FIX16(32)

#define MAP_SIZE 5

void changeLevels(s16 door){
	if(!XGM_isPlaying() && !isAttract){
		if(currentStage == 4){
			XGM_startPlay(&bgm2);
		} else if(currentStage == 8){
			XGM_startPlay(&bgm3);
		} else if(currentStage == 11){
			XGM_startPlay(&bgm4);
		} else if(currentStage == 17){
			XGM_startPlay(&bgm5);
		} else if(currentStage == 20 || currentStage == 23){
			XGM_startPlay(&bgm6);
		}
	}
	unlocked = FALSE;
	stageClock = -1;
	// VDP_clearTileMapRect(BG_A, GAME_X_T, GAME_Y_T, GAME_W_T, GAME_H_T);
	switch(door){
		case 0:
			mapPos.x++;
			player.pos.x = PLAYER_CHANGE_OFF;
			player.currentWall = 2;
			break;
		case 1:
			mapPos.y++;
			player.pos.y = PLAYER_CHANGE_OFF;
			player.currentWall = 3;
			break;
		case 2:
			mapPos.x--;
			player.pos.x = GAME_W_F - PLAYER_CHANGE_OFF;
			player.currentWall = 0;
			break;
		case 3:
			mapPos.y--;
			player.pos.y = GAME_H_F - PLAYER_CHANGE_OFF;
			player.currentWall = 1;
			break;
	}
	loadWalls();
	killEnemies = TRUE;
	killBullets = TRUE;
	player.flipping = TRUE;
	player.sideFlipped = FALSE;
	player.jumpSpeed = 0;
	player.startedFlip = TRUE;
	player.canFlip = FALSE;
}

void loadStage(){
	VDP_loadTileSet(wallTop.tileset, WALL_TOP_I, DMA);
	VDP_loadTileSet(wallBottom.tileset, WALL_BOTTOM_I, DMA);
	VDP_loadTileSet(wallLeft.tileset, WALL_LEFT_I, DMA);
	VDP_loadTileSet(wallRight.tileset, WALL_RIGHT_I, DMA);
	VDP_loadTileSet(wallTopLeft.tileset, WALL_TOP_LEFT_I, DMA);
	VDP_loadTileSet(wallTopRight.tileset, WALL_TOP_RIGHT_I, DMA);
	VDP_loadTileSet(wallBottomLeft.tileset, WALL_BOTTOM_LEFT_I, DMA);
	VDP_loadTileSet(wallBottomRight.tileset, WALL_BOTTOM_RIGHT_I, DMA);

	// VDP_loadTileSet(bgTorchTop1.tileset, TORCH_TOP1_I, DMA);
	// VDP_loadTileSet(bgTorchTop2.tileset, TORCH_TOP2_I, DMA);

	// VDP_loadTileSet(openTop.tileset,TORCH_I, DMA);
	// VDP_loadTileSet(openBottom.tileset, OPEN_BOTTOM_I, DMA);
	// VDP_loadTileSet(openLeft.tileset, OPEN_LEFT_I, DMA);
	// VDP_loadTileSet(openRight.tileset, OPEN_RIGHT_I, DMA);
	// VDP_loadTileSet(openTopLeft.tileset, OPEN_TOP_LEFT_I, DMA);
	// VDP_loadTileSet(openTopRight.tileset, OPEN_TOP_RIGHT_I, DMA);
	// VDP_loadTileSet(openBottomLeft.tileset, OPEN_BOTTOM_LEFT_I, DMA);
	// VDP_loadTileSet(openBottomRight.tileset, OPEN_BOTTOM_RIGHT_I, DMA);

	VDP_loadTileSet(doorX.tileset, DOOR_X_I, DMA);
	VDP_loadTileSet(doorY.tileset, DOOR_Y_I, DMA);
	VDP_loadTileSet(lockX.tileset, LOCK_X_I, DMA);
	VDP_loadTileSet(lockY.tileset, LOCK_Y_I, DMA);
	if(isAttract){
		getAttract();
		switch(currentAttract){
			case 0:
				mapPos.x = 3;
				mapPos.y = 4;
				break;
			case 1:
				mapPos.x = 0;
				mapPos.y = 4;
				break;
		}
		currentAttract++;
		if(currentAttract > 1) currentAttract = 0;
		saveAttract();
		loadWalls();
	} else {
		currentStage = 1;
		loadWalls();
		VDP_drawText("wait FOR DOORS", 8, 11);
		VDP_drawText("  TO open UP  ", 8, 12);
		VDP_drawText("GET THE bosses", 8, 15);
		VDP_drawText("TO unlock DOOR", 8, 16);
		introTime = INTRO_LIMIT;
		XGM_startPlay(&bgm1);
	}
}


static void stageOne(){
	if(stageClock == 0) XGM_stopPlay();
	else if(stageClock == 40) spawnEnemy(25);
	// if(enemyCount < 3 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20) spawnEnemy(1);
}
static void stageTwo(){
	if(enemyCount < 3 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20) spawnEnemy(2);
}
static void stageThree(){
	if(enemyCount < 4 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20) spawnEnemy(2);
}
static void stageFour(){
	if(stageClock == 0) XGM_stopPlay();
	else if(stageClock == 40) spawnEnemy(3);
}

static void stageFive(){
	if(enemyCount < 2 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20) spawnEnemy(4);
}
static void stageSix(){
	if(enemyCount < 3 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(4);
		spawnEnemy(1);
	}
}
static void stageSeven(){
	if(enemyCount < 4 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(4);
		spawnEnemy(1);
	}
}
static void stageEight(){
	if(stageClock == 0) XGM_stopPlay();
	else if(stageClock == 40) spawnEnemy(8);
}

static void stageNine(){
	if(enemyCount < 2 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(5);
		spawnEnemy(2);
	}
}
static void stageTen(){
	if(enemyCount < 3 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(5);
		spawnEnemy(2);
	}
}
static void stageEleven(){
	if(stageClock == 0) XGM_stopPlay();
	else if(stageClock == 40) spawnEnemy(11);
}


static void stageTwelve(){
	if(enemyCount < 3 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(5);
		spawnEnemy(2);
	}
}
static void stageThirteen(){
	if(enemyCount < 3 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(6);
		spawnEnemy(2);
	}
}
static void stageFourteen(){
	if(enemyCount < 4 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(6);
		spawnEnemy(2);
	}
}
static void stageFifteen(){
	if(enemyCount < 4 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(6);
		spawnEnemy(2);
		spawnEnemy(2);
	}
}
static void stageSixteen(){
	if(enemyCount < 4 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(6);
		spawnEnemy(2);
		spawnEnemy(2);
		spawnEnemy(1);
	}
}
static void stageSeventeen(){
	if(stageClock == 0) XGM_stopPlay();
	else if(stageClock == 40) spawnEnemy(17);
}


static void stageEighteen(){
	if(enemyCount < 4 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(6);
		spawnEnemy(2);
		spawnEnemy(2);
	}
}
static void stageNineteen(){
	if(enemyCount < 4 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(6);
		spawnEnemy(2);
		spawnEnemy(2);
		spawnEnemy(1);
	}
}
static void stageTwenty(){
	if(stageClock == 0) XGM_stopPlay();
	else if(stageClock == 40) spawnEnemy(20);
}


static void stageTwentyOne(){
	if(enemyCount < 2 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20) spawnEnemy(7);
}
static void stageTwentyTwo(){
	if(enemyCount < 2 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(7);
		spawnEnemy(2);
	}
}
static void stageTwentyThree(){
	if(stageClock == 0) XGM_stopPlay();
	else if(stageClock == 40) spawnEnemy(23);
}


static void stageTwentyFour(){
	if(enemyCount < 3 && stageClock % 20 == 0 && timeLeft > 0 && stageClock > 20){
		spawnEnemy(9);
		spawnEnemy(2);
		spawnEnemy(2);
	}
}
static void stageTwentyFive(){
	if(stageClock == 0) XGM_stopPlay();
	else if(stageClock == 40) spawnEnemy(25);
}


void updateStage(){
	if(stageClock == 0){
		loadTimeHud();
	} if(!clearedRooms[currentStage]){
		switch(currentStage){
			// case 1: stageTwentyFive(); break;
			case 1: stageOne(); break;
			case 2: stageTwo(); break;
			case 3: stageThree(); break;
			case 4: stageFour(); break; // boss one
			case 5: stageFive(); break;
			case 6: stageSix(); break;
			case 7: stageSeven(); break;
			case 8: stageEight(); break; // boss two
			case 9: stageNine(); break;
			case 10: stageTen(); break;
			case 11: stageEleven(); break; // boss three
			case 12: stageTwelve(); break;
			case 13: stageThirteen(); break;
			case 14: stageFourteen(); break;
			case 15: stageFifteen(); break;
			case 16: stageSixteen(); break;
			case 17: stageSeventeen(); break; // boss four
			case 18: stageEighteen(); break;
			case 19: stageNineteen(); break;
			case 20: stageTwenty(); break; // boss five
			case 21: stageTwentyOne(); break;
			case 22: stageTwentyTwo(); break;
			case 23: stageTwentyThree(); break; // boss six
			case 24: stageTwentyFour(); break;
			case 25: stageTwentyFive(); break; // final boss
		}
	}
	if(stageClock < CLOCK_LIMIT) stageClock++;
	if(!bossActive){
		if(timeLeft > 0 && !paused){
			if(timeLeft <= 110 && timeLeft % 10 == 0){
				if(timeLeft % 20 == 10) showUnlocking();
				else clearUnlocking();
			}
			timeLeft--;
		} else if(timeLeft <= 0 && !unlocked){
			clearUnlocking();
			unlocked = TRUE;
			loadWalls();
		}
	}
	if(introTime > 0){
		introTime--;
		if(introTime <= 0){
			VDP_clearText(8, 11, 14);
			VDP_clearText(8, 12, 14);
			VDP_clearText(8, 15, 14);
			VDP_clearText(8, 16, 14);
			drawBgShadows();
		}
	}
	if(attractClock > 0){
		attractClock--;
		if(attractClock <= 0){
			VDP_clearTileMapRect(BG_B, 0, 0, 40, 38);
			VDP_clearTileMapRect(BG_A, 0, 0, 40, 38);
			SYS_hardReset();
		}
	}
}