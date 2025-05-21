#define FRAME_TOP_I 8
#define FRAME_BOTTOM_I FRAME_TOP_I + 40
#define FRAME_LEFT_I FRAME_BOTTOM_I + 40
#define FRAME_RIGHT_I FRAME_LEFT_I + 52

#define GO_1_I FRAME_RIGHT_I + 312
#define GO_2_I GO_1_I + 4

///////////
// frame //
///////////

static void loadFrame(){
	// top
	VDP_fillTileMapRectInc(BG_B, TILE_ATTR_FULL(PAL1, 1, 0, 0, FRAME_TOP_I), 0, 0, WIN_W_T - 1, 1);
	// bottom
	VDP_fillTileMapRectInc(BG_B, TILE_ATTR_FULL(PAL1, 1, 0, 0, FRAME_BOTTOM_I), 0, GAME_Y_T + GAME_H_T, WIN_W_T, 1);
	// left
	VDP_fillTileMapRectInc(BG_B, TILE_ATTR_FULL(PAL1, 1, 0, 0, FRAME_LEFT_I), 0, GAME_Y_T, GAME_X_T, GAME_H_T);
	// right
	VDP_fillTileMapRectInc(BG_B, TILE_ATTR_FULL(PAL1, 1, 0, 0, FRAME_RIGHT_I), GAME_X_T + GAME_W_T, GAME_Y_T, WIN_W_T - GAME_W_T - GAME_X_T, GAME_H_T);

	// // top
	// VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, CHROME_I), 0, 0, WIN_W_T, 1);
	// VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, CHROME_I + 1), GAME_X_T, GAME_Y_T - 1, GAME_W_T, WIN_H_T - GAME_H_T - GAME_Y_T);
	// VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, CHROME_I + 3), GAME_X_T - 1, GAME_Y_T - 1);
	// VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 1, CHROME_I + 3), GAME_X_T + GAME_W_T, GAME_Y_T - 1);
	// // bottom
	// VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, CHROME_I), 0, GAME_H_T + GAME_Y_T, WIN_W_T, 1);
	// VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 1, 0, CHROME_I + 1), GAME_X_T, GAME_H_T + GAME_Y_T, GAME_W_T, 1);
	// VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 1, 0, CHROME_I + 3), GAME_X_T - 1, GAME_H_T + GAME_Y_T);
	// VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 1, 1, CHROME_I + 3), GAME_X_T + GAME_W_T, GAME_H_T + GAME_Y_T);
	// // left
	// // VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, CHROME_I), 0, GAME_Y_T, GAME_X_T, GAME_H_T);
	// VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, CHROME_I + 2), GAME_X_T - 1, GAME_Y_T, 1, GAME_H_T);
	// // right
	// VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 1, CHROME_I + 2), GAME_X_T + GAME_W_T, GAME_Y_T, 1, GAME_H_T);
	// VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 1, CHROME_I), GAME_X_T + GAME_W_T + 1, GAME_Y_T, WIN_W_T - GAME_W_T - GAME_X_T, GAME_H_T);
}


/////////
// hud //
/////////

#define HUD_X GAME_X_T + GAME_W_T + 1
#define SCORE_Y 4
#define HEALTH_Y SCORE_Y + 6
#define TIME_Y HEALTH_Y + 3
#define PROGRESS_Y 24
#define POSITION_Y TIME_Y + 3

void loadTimeHud(){
	VDP_drawText("time       ", HUD_X, TIME_Y);
}

static void loadHud(){
	VDP_drawText(isLunatic ? "LUNATIC" : "NORMAL", HUD_X, SCORE_Y - 2);

	VDP_drawText("hi score", HUD_X, SCORE_Y);
	VDP_drawText("0", HUD_X, SCORE_Y + 1);
	VDP_drawText("score", HUD_X, SCORE_Y + 3);
	VDP_drawText("0", HUD_X, SCORE_Y + 4);

	VDP_drawText("health", HUD_X, HEALTH_Y);
	// VDP_drawText("$$$$$$$$$$$", HUD_X, HEALTH_Y + 1);

	VDP_drawText("progress", HUD_X, PROGRESS_Y);
	VDP_drawText("0%", HUD_X, PROGRESS_Y + 1);

	VDP_drawText("position", HUD_X, POSITION_Y);
	VDP_drawText("X: 1", HUD_X, POSITION_Y + 1);
	VDP_drawText("Y: 1", HUD_X, POSITION_Y + 2);
}

s32 lastScore, lastHighScore;
char scoreStr[11];
char highScoreStr[11];
s16 scoreLength;

static void updateScore(){
	if(lastScore != score){
		scoreLength = 1;
		if(score >= 10) scoreLength++;
		if(score >= 100) scoreLength++;
		if(score >= 1000) scoreLength++;
		if(score >= 10000) scoreLength++;
		if(score >= 100000) scoreLength++;
		if(score >= 1000000) scoreLength++;
		if(score >= 10000000) scoreLength++;
		if(score >= 100000000) scoreLength++;
		if(score >= 1000000000) scoreLength++;
		if(score >= 10000000000) scoreLength++;
		lastScore = score;
		intToStr(score, scoreStr, scoreLength);
		VDP_drawText(scoreStr, HUD_X, SCORE_Y + 4);

		if(isLunatic){
			if(score >highLunaticScore) highLunaticScore = score;
		} else {
			if(score > highScore) highScore = score;
		}

	}
	if(lastHighScore != (isLunatic ? highLunaticScore : highScore)){
		lastHighScore = (isLunatic ? highLunaticScore : highScore);
		intToStr((isLunatic ? highLunaticScore : highScore), highScoreStr, scoreLength);
		VDP_drawText(highScoreStr, HUD_X, SCORE_Y + 1);
	}
}

char timeLeftStr[3];
s16 lastTimeLeft, timeLength;
static void updateTime(){
	if(timeLeft != lastTimeLeft){
		timeLength = 1;
		if(timeLeft >= 10) timeLength++;
		if(timeLeft >= 100) timeLength++;
		if(timeLeft == 99) VDP_clearTileMapRect(BG_A, HUD_X + 2, TIME_Y + 1, 1, 1);
		else if(timeLeft == 9) VDP_clearTileMapRect(BG_A, HUD_X + 1, TIME_Y + 1, 1, 1);
		lastTimeLeft = timeLeft;
		intToStr(timeLeft, timeLeftStr, timeLength);
		VDP_drawText(timeLeftStr, HUD_X, TIME_Y + 1);
	}
}


#define BOSS_TILE_COUNT 10
#define BOSS_TILE_PX BOSS_TILE_COUNT * 8
s16 lastBossHealth;
fix16 bossHealthW;

static void updateBossHud(){
	if(lastBossHealth != bossHealth){
		lastBossHealth = bossHealth;
		bossHealthW = fix16Div(fix16Mul(fix16Div(FIX16(bossHealth), FIX16(bossMax)), BOSS_TILE_PX), 8);
		for(s16 x = 0; x < BOSS_TILE_COUNT; x++){
			VDP_drawText(FIX16(x) < bossHealthW ? "$" : " ", x + HUD_X, TIME_Y + 1);
		}
	}
}

void loadBossHud(){
	lastBossHealth = 0;
	bossActive = TRUE;
	VDP_drawText("boss       ", HUD_X, TIME_Y);
	updateBossHud();
}

void clearBossHud(){
	VDP_drawText("           ", HUD_X, TIME_Y);
	VDP_drawText("           ", HUD_X, TIME_Y + 1);
}


s16 lastPlayerHealth;
fix16 playerHealthW;
#define PLAYER_MAX FIX16(100)
static void updatePlayerHealth(){
	if(lastPlayerHealth != player.health){
		lastPlayerHealth = player.health;
		playerHealthW = fix16Div(fix16Mul(fix16Div(FIX16(player.health), PLAYER_MAX), BOSS_TILE_PX), 8);
		for(s16 x = 0; x < BOSS_TILE_COUNT; x++){
			VDP_drawText(FIX16(x) < playerHealthW ? "$" : " ", x + HUD_X, HEALTH_Y + 1);
		}
	}
}

s16 lastProgress, progressLength;
char progressStr[2];
void updateProgress(){
	if(lastProgress != progress){
		lastProgress = progress;
		progressLength = progress >= 10 ? 2 : 1;
		intToStr(progress, progressStr, progressLength);
		VDP_drawText(progressStr, HUD_X, PROGRESS_Y + 1);
		if(progress >= 10) VDP_drawText("%", HUD_X + 2, PROGRESS_Y + 1);
	}
}


Vect2D_s16 lastMapPos;
char mapPosStr[1];
char mapPosYStr[1];
static void updateMapPos(){
	if(lastMapPos.x != mapPos.x || lastMapPos.y != mapPos.y){
		lastMapPos.x = mapPos.x;
		lastMapPos.y = mapPos.y;
		intToStr(mapPos.x + 1, mapPosStr, 1);
		VDP_drawText(mapPosStr, HUD_X + 3, POSITION_Y + 1);
		intToStr(mapPos.y + 1, mapPosStr, 1);
		VDP_drawText(mapPosStr, HUD_X + 3, POSITION_Y + 2);
	}
}

s16 gameOverClock;
bool didGameOver;
s16 gameOverY;

bool didGameOverPress;

static void updateGameOver(){
	if(!didGameOver){
		didGameOverPress = FALSE;
		XGM_stopPlay();
		didGameOver = TRUE;
		gameOverY = 13;
		if(score >= (isLunatic ? highLunaticScore : highScore)){
			gameOverY--;
			saveHighScore();
			VDP_drawText("new high score", 8, gameOverY + 3);
		}
		if(wonGame){
			XGM_startPlayPCM(SFX_BEAT_GAME, 15, SOUND_PCM_CH2);
			VDP_drawText("GAME  COMPLETE", 8, gameOverY);
		} else {
			XGM_startPlayPCM(SFX_GAME_OVER, 15, SOUND_PCM_CH2);
			VDP_drawText("GAME  OVER", 10, gameOverY);
		}
		VDP_drawText("PRESS ANY BUTTON", 7, gameOverY + 1);
	}
	if(!didGameOverPress && !ctrl.start && !ctrl.a && !ctrl.b && !ctrl.c) didGameOverPress = TRUE;
	if(gameOverClock >= 60 && (ctrl.start || ctrl.a || ctrl.b || ctrl.c) && didGameOverPress)
		SYS_hardReset();
	gameOverClock++;
}


// pause

#define PAUSE_X 12
#define PAUSE_Y 13

void showPause(){
	VDP_clearText(8, 11, 14);
	VDP_clearText(8, 12, 14);
	VDP_clearText(8, 15, 14);
	VDP_clearText(8, 16, 14);
	drawBgShadows();
	SPR_setPalette(player.image, PAL1);
	for(s16 i = 0; i < ENEMY_COUNT; i++)
		if(enemies[i].active)
			SPR_setPalette(enemies[i].image, PAL1);
	for(s16 i = 0; i < BULLET_COUNT; i++)
		if(bullets[i].active)
			SPR_setPalette(bullets[i].image, PAL1);
	for(s16 i = 0; i < EXPLOSION_COUNT; i++)
		if(explosions[i].active)
			SPR_setPalette(explosions[i].image, PAL1);
	VDP_drawText("PAUSED", PAUSE_X, PAUSE_Y);
	VDP_drawText("press  start", PAUSE_X - 3, PAUSE_Y + 1);
}

void clearPause(){
	VDP_clearTextArea(PAUSE_X - 3, PAUSE_Y, 12, 2);
	SPR_setPalette(player.image, PAL0);
	for(s16 i = 0; i < ENEMY_COUNT; i++)
		if(enemies[i].active)
			SPR_setPalette(enemies[i].image, PAL0);
	for(s16 i = 0; i < BULLET_COUNT; i++)
		if(bullets[i].active)
			SPR_setPalette(bullets[i].image, PAL0);
	for(s16 i = 0; i < EXPLOSION_COUNT; i++)
		if(explosions[i].active)
			SPR_setPalette(explosions[i].image, PAL0);
}


// unlocking indication

#define U_X_0 GAME_X_T + GAME_W_T - 1 - 3
#define U_Y_0 GAME_Y_T + (GAME_H_T / 2) - 2

#define U_X_1 GAME_X_T + (GAME_W_T / 2) - 2
#define U_Y_1 GAME_Y_T + GAME_H_T - 1 - 3

#define U_X_2 GAME_X_T + 3
#define U_Y_2 GAME_Y_T + (GAME_H_T / 2) - 2

#define U_X_3 GAME_X_T + (GAME_W_T / 2) - 2
#define U_Y_3 GAME_Y_T + 3

void showUnlocking(bool opposite){
	for(u8 i = 0; i < 4; i++){
		if(wallHealth[i] == 2){
			switch(i){
				case 0:
					VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, GO_1_I), U_X_0, U_Y_0, 1, 4);
					break;
				case 1:
					VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, GO_2_I), U_X_1, U_Y_1, 4, 1);
					break;
				case 2:
					VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, GO_1_I), U_X_2, U_Y_2, 1, 4);
					break;
				case 3:
					VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, GO_2_I), U_X_3, U_Y_3, 4, 1);
					break;
			}
		}
	}
}
void clearUnlocking(){
	for(u8 i = 0; i < 4; i++){
		if(wallHealth[i] == 2){
			switch(i){
				case 0:
					VDP_clearTextArea(U_X_0, U_Y_0, 1, 4);
					break;
				case 1:
					VDP_clearTextArea(U_X_1, U_Y_1, 4, 1);
					break;
				case 2:
					VDP_clearTextArea(U_X_2, U_Y_2, 1, 4);
					break;
				case 3:
					VDP_clearTextArea(U_X_3, U_Y_3, 4, 1);
					break;
			}
		}
	}
}


////////////
// extern //
////////////

void loadChrome(){
	VDP_loadTileSet(chromeFrameTop.tileset, FRAME_TOP_I, DMA);
	VDP_loadTileSet(chromeFrameBottom.tileset, FRAME_BOTTOM_I, DMA);
	VDP_loadTileSet(chromeFrameLeft.tileset, FRAME_LEFT_I, DMA);
	VDP_loadTileSet(chromeFrameRight.tileset, FRAME_RIGHT_I, DMA);
	VDP_loadTileSet(chromeGo1.tileset, GO_1_I, DMA);
	VDP_loadTileSet(chromeGo2.tileset, GO_2_I, DMA);

	loadFrame();
	loadHud();
}

void updateChrome(){
	updateScore();
	bossActive ? updateBossHud() : updateTime();
	updateProgress();
	updateMapPos();
	updatePlayerHealth();
	if(gameOver) updateGameOver();
	// VDP_showFPS(TRUE);
}


