// start

#define START_W 40
#define START_H 28
#define START_I 1

#define TRANS_TIME 260
// #define TRANS_TIME 220

s16 startClock;

static void updateTransition(s16 startTime, bool last){
	if(startClock >= startTime && startClock < startTime + TRANS_TIME){
		switch(startClock - startTime){
			case 0: VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, START_I), 0, 0, START_W, START_H); break;
			case 5: VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, START_I + 1), 0, 0, START_W, START_H); break;
			case 10: VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, START_I + 2), 0, 0, START_W, START_H); break;
			case 15: VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, START_I + 3), 0, 0, START_W, START_H); break;
			case 20: VDP_clearTileMapRect(BG_A, 0, 0, START_W, START_H); break;
			case TRANS_TIME - 20: if(!last){
				XGM_startPlay(&bgmStart);
				VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, START_I + 3), 0, 0, START_W, START_H);
				} break;
			case TRANS_TIME - 15: if(!last) VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, START_I + 2), 0, 0, START_W, START_H); break;
			case TRANS_TIME - 10: if(!last) VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, START_I + 1), 0, 0, START_W, START_H); break;
			case TRANS_TIME - 5: if(!last) VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, START_I), 0, 0, START_W, START_H); break;
		}
	}
}


static void drawStartSega(){
	VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, START_I), 0, 0, START_W, START_H);
	VDP_drawImageEx(BG_B, &startSplash1, TILE_ATTR_FULL(PAL0, 0, 0, 0, START_I + 8), 5, 8, 0, DMA);
}

Sprite *bgSprite;

// events

static void loadGameFromStart(){
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	XGM_stopPlay();
	setRandomSeed(startClock);
	VDP_clearTileMapRect(BG_A, 0, 0, START_W, START_H);
	VDP_clearTileMapRect(BG_B, 0, 0, START_W, START_H);
	loadGame();
}


static void loadAttractFromStart(){
	isLunatic = TRUE;
	isAttract = TRUE;
	attractClock = 720;
	loadGameFromStart();
}


// bg

#define START_BG_X 9
#define START_BG_Y 3

static void drawStartBg(){
	VDP_clearTileMapRect(BG_B, 0, 0, START_W, START_H);
	VDP_drawImageEx(BG_B, &startBigBg, TILE_ATTR_FULL(PAL1, 0, 0, 0, START_I + 8 + 162), 0, 0, 0, DMA);
}


// menu

char startLivesStr[2];
char hiScoreStr[11];
char lunaticHiScoreStr[11];
char classicHiScoreStr[11];
s16 highScoreLength, lunaticHighScoreLength, classicHighScoreLength;

#define LOGO_X 3
#define LOGO_Y 5
#define MENU_X 6
#define MENU_Y 16

static void drawStartMenu(){
	highScoreLength = 1;
	if(highScore >= 10) highScoreLength++;
	if(highScore >= 100) highScoreLength++;
	if(highScore >= 1000) highScoreLength++;
	if(highScore >= 10000) highScoreLength++;
	if(highScore >= 100000) highScoreLength++;
	if(highScore >= 1000000) highScoreLength++;
	if(highScore >= 10000000) highScoreLength++;
	if(highScore >= 100000000) highScoreLength++;
	if(highScore >= 1000000000) highScoreLength++;
	if(highScore >= 10000000000) highScoreLength++;

	lunaticHighScoreLength = 1;
	if(highLunaticScore >= 10) lunaticHighScoreLength++;
	if(highLunaticScore >= 100) lunaticHighScoreLength++;
	if(highLunaticScore >= 1000) lunaticHighScoreLength++;
	if(highLunaticScore >= 10000) lunaticHighScoreLength++;
	if(highLunaticScore >= 100000) lunaticHighScoreLength++;
	if(highLunaticScore >= 1000000) lunaticHighScoreLength++;
	if(highLunaticScore >= 10000000) lunaticHighScoreLength++;
	if(highLunaticScore >= 100000000) lunaticHighScoreLength++;
	if(highLunaticScore >= 1000000000) lunaticHighScoreLength++;
	if(highLunaticScore >= 10000000000) lunaticHighScoreLength++;

	// classicHighScoreLength = 1;

	uintToStr(highScore, hiScoreStr, highScoreLength);

	uintToStr(highLunaticScore, lunaticHiScoreStr, lunaticHighScoreLength);

	// uintToStr(highClassicScore, classicHiScoreStr, classicHighScoreLength);

	VDP_drawImageEx(BG_A, &startLogo, TILE_ATTR_FULL(PAL0, 0, 0, 0, START_I + 8), LOGO_X, LOGO_Y, 0, DMA);

	VDP_drawText("+", MENU_X - 1, MENU_Y);

	VDP_drawText("NORMAL GAME", MENU_X, MENU_Y);
	VDP_drawText("HI:", MENU_X, MENU_Y + 1);
	VDP_drawText(hiScoreStr, MENU_X + 3, MENU_Y + 1);

	VDP_drawText("LUNATIC GAME", MENU_X, MENU_Y + 3);
	VDP_drawText("HI:", MENU_X, MENU_Y + 4);
	VDP_drawText(lunaticHiScoreStr, MENU_X + 3, MENU_Y + 4);
	// VDP_drawText(lunaticHiScoreStr, MENU_X + 1, MENU_Y + 4);

	// VDP_drawText("CLASSIC MODE", MENU_X, MENU_Y + 6);
	// VDP_drawText(classicHiScoreStr, MENU_X + 1, MENU_Y + 7);

	VDP_drawText("   11.2024  T.BODDY, KASHA, MOLLYCO   ", 1, 26);

}

s8 currentMenu;
bool movingMenu, changingMenu;

s16 startTime;

static void updateStartMenu(){

	if(startTime == 0 && (ctrl.up || ctrl.down) && !movingMenu){
		movingMenu = TRUE;
		if(ctrl.up) currentMenu--;
		else if(ctrl.down) currentMenu++;
		if(currentMenu < 0) currentMenu = 1;
		else if(currentMenu > 1) currentMenu = 0;
		switch(currentMenu){
			case 0:
				VDP_clearText(MENU_X - 1, MENU_Y + 3, 1);
				VDP_clearText(MENU_X - 1, MENU_Y + 6, 1);
				VDP_drawText("+", MENU_X - 1, MENU_Y);
				break;
			case 1:
				VDP_clearText(MENU_X - 1, MENU_Y, 1);
				VDP_clearText(MENU_X - 1, MENU_Y + 6, 1);
				VDP_drawText("+", MENU_X - 1, MENU_Y + 3);
				break;
			case 2:
				VDP_clearText(MENU_X - 1, MENU_Y, 1);
				VDP_clearText(MENU_X - 1, MENU_Y + 3, 1);
				VDP_drawText("+", MENU_X - 1, MENU_Y + 6);
				break;
		}
	} else if(startTime == 0 && !ctrl.up && !ctrl.down && movingMenu){
		movingMenu = FALSE;
	}

	if(startTime == 0 && (ctrl.start || ctrl.a || ctrl.b || ctrl.c)){
		startTime = 30;
		XGM_startPlayPCM(SFX_START_GAME, 1, SOUND_PCM_CH2);
	}

	if(startTime > 0){
		startTime--;
		if(startTime <= 0){
			if(currentMenu == 0) isLunatic = FALSE;
			else if(currentMenu == 1) isLunatic = TRUE;
			// else if(currentMenu == 2) isClassic = TRUE;
			loadGameFromStart();
		}
	}
}


// loop

void loadStart(){
	getHighScore();
	VDP_loadTileSet(startFade1.tileset, START_I, DMA);
	VDP_loadTileSet(startFade2.tileset, START_I + 1, DMA);
	VDP_loadTileSet(startFade3.tileset, START_I + 2, DMA);
	VDP_loadTileSet(startFade4.tileset, START_I + 3, DMA);
	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
	// drawStartSega();
	// isLunatic = TRUE;
	loadGameFromStart();
	// loadAttractFromStart();
}

void updateStart(){
	updateTransition(0, FALSE);
	updateTransition(TRANS_TIME, TRUE);
	if(startClock == TRANS_TIME) drawStartBg();
	else if(startClock >= TRANS_TIME + 40) {
		if(startClock == TRANS_TIME + 40) drawStartMenu();
		updateStartMenu();
	}
	if(startClock >= ((ATTRACT_LIMIT * 1.5) + TRANS_TIME + 40)) loadAttractFromStart();
	if(startClock < CLOCK_LIMIT) startClock++;
}





	// for(u8 i = 0; i < LOGO_H; i++){
	// 	logoDir[i] = i % 2 == 0;
	// 	logoMod[i] = ((random() % 4) + 4) * 4;
	// }

// #define LOGO_MOD 10
// #define LOGO_LIMIT LOGO_H * LOGO_MOD

// s16 logoMod[LOGO_H];
// bool logoDir[LOGO_H];
// #define LOGO_LIMIT 1



		// VDP_setHorizontalScrollLine(BG_A, LOGO_SCROLL_Y, logoScroll, LOGO_H, DMA_QUEUE);

		// if(startClock % 2 == 0){
		// 	for(u8 i = 0; i < LOGO_H; i++){
		// 		if(startClock % LOGO_H == i) logoScroll[i] = 2;
		// 		else if(i > 0 && startClock % LOGO_H == i + 1) logoScroll[i] = 1;
		// 		else if(i < LOGO_H - 1 && startClock % LOGO_H == i - 1) logoScroll[i] = 1;
		// 		else logoScroll[i] = 0;
		// 	}
		// }

		// for(u8 i = 0; i < LOGO_H; i++){
		// 	if(startClock % logoMod[i] == 0){
		// 		if(logoDir[i]){
		// 			logoScroll[i]++;
		// 			if(logoScroll[i] >= LOGO_LIMIT) logoDir[i] = FALSE;
		// 		} else {
		// 			logoScroll[i]--;
		// 			if(logoScroll[i] <= 0) logoDir[i] = TRUE;
		// 		}
		// 	}
		// }



// #define LOGO_H 72
// #define LOGO_SCROLL_Y LOGO_Y * 8
// s16 logoScroll[LOGO_H];
// #define LOGO_LIMIT LOGO_H * 8
// #define LOGO_START LOGO_H * 4