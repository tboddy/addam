// Addaṁ

#include <genesis.h>
#include <resources.h>

#include "global.h"
#include "explosions.h"
#include "bullets.h"
#include "enemies.h"
#include "background.h"
#include "player.h"
#include "stage.h"
#include "chrome.h"
#include "start.h"

static void loadInternals(){
	JOY_init();
	JOY_setEventHandler(&updateControls);
	SPR_init();
	VDP_loadFont(font.tileset, DMA);
	PAL_setPalette(PAL0, playerKoakuma.palette->data, DMA);
	PAL_setPalette(PAL1, shadow.palette->data, CPU);
	PAL_setPalette(PAL2, font.palette->data, DMA);
	VDP_setTextPriority(1);
	VDP_setTextPalette(PAL2);
	XGM_setPCM(SFX_START_GAME, sfxStartGame, sizeof(sfxStartGame));
	XGM_setPCM(SFX_BULLET_1, sfxBullet1, sizeof(sfxBullet1));
	XGM_setPCM(SFX_BULLET_2, sfxBullet2, sizeof(sfxBullet2));
	XGM_setPCM(SFX_BULLET_3, sfxBullet3, sizeof(sfxBullet3));
	XGM_setPCM(SFX_PLAYER_SHOT, sfxPlayerShot, sizeof(sfxPlayerShot));
	XGM_setPCM(SFX_TREASURE, sfxTreasure, sizeof(sfxTreasure));
	XGM_setPCM(SFX_EXPLOSION_1, sfxExplosion1, sizeof(sfxExplosion1));
	XGM_setPCM(SFX_EXPLOSION_2, sfxExplosion2, sizeof(sfxExplosion2));
	XGM_setPCM(SFX_BEAT_LEVEL, sfxBeatLevel, sizeof(sfxBeatLevel));
	XGM_setPCM(SFX_GAME_OVER, sfxGameOver, sizeof(sfxGameOver));
	XGM_setPCM(SFX_BEAT_GAME, sfxBeatGame, sizeof(sfxBeatGame));
	XGM_setPCM(SFX_PLAYER_HIT, sfxPlayerHit, sizeof(sfxPlayerHit));
}

void loadGame(){
	started = TRUE;
	loadPlayer();
	loadChrome();
	loadBackground();
	loadStage();
}

s16 gameOverClock;

static void updateGame(){
	if(!paused){
		if(clock % 2 == 0){
			updatePlayer();
			updateStage();
			updateEnemies();
		} else {
			updateBullets();
			updateExplosions();
			updateBackground();
		}
		updateChrome();
	}
	if(ctrl.start && !pausing && !gameOver && player.clock >= 60){
		paused = paused ? FALSE : TRUE;
		pausing = TRUE;
		if(xgm2Active)
			paused ? XGM2_pause() : XGM2_resume();
		else
			paused ? XGM_pausePlay() : XGM_resumePlay();
		paused ? showPause() : clearPause();
	} else if(!ctrl.start && pausing) pausing = FALSE;
	if(gameOver){
		if((gameOverClock >= 120 && (ctrl.a || ctrl.b || ctrl.c || ctrl.start)) ||
			(gameOverClock >= 900)){
			SPR_reset();
			VDP_clearTileMapRect(BG_B, 0, 0, 40, 38);
			VDP_clearTileMapRect(BG_A, 0, 0, 40, 38);
			SYS_hardReset();
		}
		gameOverClock++;
	}
}

int main(){
	loadInternals();
	// loadGame();
	loadStart();
	while(1){
		started ? updateGame() : updateStart();
		clock++;
		if(clock >= CLOCK_LIMIT) clock = 600;
		SPR_update();
		SYS_doVBlankProcess();
	}
	return(0);
}