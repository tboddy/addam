#define BG_I 480
#define BG_FADE50_I BG_I + 4
#define BG_FADE25_I BG_FADE50_I + 1
#define BG_FADE75_I BG_FADE25_I + 1
#define BG_SIZE_T 2


//////////
// draw //
//////////

#define FLOOR_TILES 13
#define BG_TILES 22
#define OUT_TILES 26

void drawBgShadows(){
	for(u8 y = 0; y < BG_TILES; y++){
		for(u8 x = 0; x < BG_TILES; x++){
			if((x == 0 && y == 0) ||
				(x == BG_TILES - 1 && y == 0) ||
				(x == 0 && y == BG_TILES - 1) ||
				(x == BG_TILES - 1 && y == BG_TILES - 1))
				VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE75_I), x + GAME_X_T + 2, y + GAME_Y_T + 2);
			else if((y == 0 || y == BG_TILES - 1 || x == 0 || x == BG_TILES - 1) ||
				((x == 1 || x == BG_TILES - 2) && (y < 8 || y >= BG_TILES - 8)) ||
				((x == 2 || x == BG_TILES - 3) && (y < 6 || y >= BG_TILES - 6)) ||
				((x == 3 || x == BG_TILES - 4) && (y < 4 || y >= BG_TILES - 4)) ||
				((x < 6 || x >= BG_TILES - 6) && (y < 3 || y >= BG_TILES - 3)) ||
				((x < 8 || x >= BG_TILES - 8) && (y < 2 || y >= BG_TILES - 2)))
				VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE50_I), x + GAME_X_T + 2, y + GAME_Y_T + 2);
			else if((y < 5 || y >= BG_TILES - 5 || x < 5 | x >= BG_TILES - 5) ||
				((x == 5 || x == BG_TILES - 6) && (y < 9 || y >= BG_TILES - 9)) ||
				((x == 6 || x == BG_TILES - 7) && (y < 7 || y >= BG_TILES - 7)) ||
				((x < 9 || x >= BG_TILES - 9) && (y < 6 || y >= BG_TILES - 6))
				)
				VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE25_I), x + GAME_X_T + 2, y + GAME_Y_T + 2);
		}
	}
}

static void drawBg(){
	for(u8 y = 0; y < OUT_TILES; y++){
		for(u8 x = 0; x < OUT_TILES; x++){
			if(y % 2 == 0 && x % 2 == 0)
				VDP_fillTileMapRectInc(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_I), x + GAME_X_T, y + GAME_Y_T, BG_SIZE_T, BG_SIZE_T);
			if(y == 0 || x == 0 || x == OUT_TILES - 1 || y == OUT_TILES - 1)
				VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE75_I), x + GAME_X_T, y + GAME_Y_T);
			if(y == 1 || x == 1 || x == OUT_TILES - 2 || y == OUT_TILES - 2)
				VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_FADE50_I), x + GAME_X_T, y + GAME_Y_T);
		}
	}
	drawBgShadows();
}


////////////
// extern //
////////////

void updateBackground(){
	
}

void loadBackground(){
	VDP_loadTileSet(bgFloor.tileset, BG_I, DMA);
	VDP_loadTileSet(bgFade50.tileset, BG_FADE50_I, DMA);
	VDP_loadTileSet(bgFade25.tileset, BG_FADE25_I, DMA);
	VDP_loadTileSet(bgFade75.tileset, BG_FADE75_I, DMA);
	drawBg();
}