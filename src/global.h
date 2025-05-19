#define WIN_W_T 40
#define WIN_H_T 28

#define GAME_X_T 2
#define GAME_Y_T 1

#define GAME_X GAME_X_T * 8
#define GAME_Y GAME_Y_T * 8

#define GAME_W_T 26
#define GAME_H_T 26

#define GAME_W GAME_W_T * 8
#define GAME_H GAME_H_T * 8

#define GAME_W_F FIX16(GAME_W)
#define GAME_H_F FIX16(GAME_H)


#define NORM 0.707

s16 emptyI, clock, currentStage, currentLevel, timeLeft, attractClock;
bool clearedLevels[24];
bool clearedStages[6];
void EMPTY(s16 i){emptyI = i;}

#define CLOCK_LIMIT 32000
#define COUNT_INT 8
#define ATTRACT_LIMIT 2100

#define SFX_MENU_SELECT 64
#define SFX_MENU_CHOOSE 65
#define SFX_START_GAME 66
#define SFX_TREASURE 68

#define SFX_PLAYER_SHOT 67
#define SFX_BULLET_1 69
#define SFX_BULLET_2 70
#define SFX_BULLET_3 71

#define SFX_EXPLOSION_1 73
#define SFX_EXPLOSION_2 74
#define SFX_EXPLOSION_3 75

#define SFX_BEAT_LEVEL 78

#define SFX_PLAYER_HIT 79

#define SFX_GAME_OVER 80
#define SFX_BEAT_GAME 81

#define FIRST_ROTATING_BULLET 3

bool gameOver, isAttract, paused, started, unlocked, wonGame, pausing,
	isLunatic, isClassic, xgm2Active;
s32 score, highScore, highLunaticScore, highClassicScore;
fix32 enemyKillDist;
s16 enemyKillBonus, progress;

s16 wallHealth[4];

Vect2D_s16 mapPos;
s16 stageClock;

u8 currentAttract;

u32 ATTRACT_SRAM = 0x0000;
u32 SCORE_SRAM = 0x0033;
u32 LUNATIC_SCORE_SRAM = 0x1133;
u32 tempHighScore, tempLunaticHighScore;
u8 tempAttract;

void getHighScore(){
	SRAM_enable();
	tempHighScore = SRAM_readLong(SCORE_SRAM);
	if(tempHighScore > 0 && tempHighScore < 1000000) highScore = tempHighScore;
	tempLunaticHighScore = SRAM_readLong(LUNATIC_SCORE_SRAM);
	if(tempLunaticHighScore > 0 && tempLunaticHighScore < 1000000) highLunaticScore = tempLunaticHighScore;
	SRAM_disable();
}

static void saveHighScore(){
	SRAM_enable();
	if(isLunatic){
		SRAM_writeLong(LUNATIC_SCORE_SRAM, highLunaticScore);
	} else {
		SRAM_writeLong(SCORE_SRAM, highScore);
	}
	SRAM_disable();
}
void getAttract(){
	SRAM_enable();
	tempAttract = SRAM_readByte(ATTRACT_SRAM);
	if(tempAttract == 0 || tempAttract == 1) currentAttract = tempAttract;
	SRAM_disable();
}
static void saveAttract(){
	SRAM_enable();
	SRAM_writeByte(ATTRACT_SRAM, currentAttract);
	SRAM_disable();
}

// controls

struct controls {
	bool left, right, up, down, a, b, c, start;
};
struct controls ctrl;

void updateControls(u16 joy, u16 changed, u16 state){
	if(changed){}
	if(joy == JOY_1){
		ctrl.left = (state & BUTTON_LEFT);
		ctrl.right = (state & BUTTON_RIGHT);
		ctrl.up = (state & BUTTON_UP);
		ctrl.down = (state & BUTTON_DOWN);
		ctrl.a = (state & BUTTON_A);
		ctrl.b = (state & BUTTON_B);
		ctrl.c = (state & BUTTON_C);
		ctrl.start = (state & BUTTON_START);
	}
}


// player

#define INVINCIBLE_LIMIT 120

struct playerStruct {
	bool movingLeft, movingUp, flipping, sideFlipped, startedFlip, canFlip,
		recovering, hit;
	Vect2D_s16 posTile;
	Vect2D_f16 pos, vel;
	Sprite* image;
	u8 currentWall;
	fix16 jumpSpeed;
	s16 invincibleClock, shotClock, lives, angle, shotAngle, moveClock, health;
	u32 clock;
};
struct playerStruct player;


// bullets

#define KILL_BULLET_TIME 15
#define BULLET_COUNT 72
bool killBullets;
s16 playerBulletCount, bulletCount;

struct bulletSpawner {
	fix16 x, y, speed;
	Vect2D_f16 vel;
	s16 angle, anim;
	SpriteDefinition* image;
	bool big, player, huge, top, hFlip, vFlip;
	bool bools[COUNT_INT];
	s16 ints[COUNT_INT];
	fix16 fixes[COUNT_INT];
};
struct bullet {
	bool active, player, big, huge, hFlip, vFlip;
	Vect2D_s16 posTile;
	fix16 speed;
	Vect2D_f16 pos, vel;
	s16 angle, clock, anim, frame;
	fix32 dist;
	Sprite* image;
	void (*updater)(s16);
	bool bools[COUNT_INT];
	s16 ints[COUNT_INT];
	fix16 fixes[COUNT_INT];
};
struct bullet bullets[BULLET_COUNT];


// enemies

s16 bossHealth, bossMax;
bool bossActive;
#define ENEMY_COUNT 16
bool killEnemies;
s16 enemyCount;
struct enemy {
	bool active, boss;
	Vect2D_s16 posTile, off;
	fix16 speed;
	Vect2D_f16 pos, vel;
	s16 angle, clock, health;
	Sprite* image;
	u8 type, anim;
	void (*updater)(s16);
	bool bools[COUNT_INT];
	s16 ints[COUNT_INT];
	fix16 fixes[COUNT_INT];
};
struct enemy enemies[ENEMY_COUNT];


// explosions

#define EXPLOSION_COUNT 4
bool killExplosions;

struct explosion {
	bool active, big;
	Vect2D_f16 pos;
	Sprite* image;
	s16 clock, frame;
};
struct explosion explosions[EXPLOSION_COUNT];


// hone
fix16 hMod;
Vect2D_f16 hPos, velPos, velPos2;
Vect2D_f16 hone(Vect2D_f16 pos, Vect2D_f16 target, fix16 speed, s16 lerp){
	hPos.x = target.x;
	hPos.y = target.y;
	if(lerp > 0){
		hPos.x = hPos.x - FIX16(lerp) + FIX16(random() % (lerp * 2));
		hPos.y = hPos.y - FIX16(lerp) + FIX16(random() % (lerp * 2));
	}
	hMod = fix32ToFix16(getApproximatedDistance(
		fix16ToFix32(pos.x) - fix16ToFix32(hPos.x),
		fix16ToFix32(pos.y) - fix16ToFix32(hPos.y)));
	hPos.x = fix16Mul(fix16Div(hPos.x - pos.x, hMod), speed);
	hPos.y = fix16Mul(fix16Div(hPos.y - pos.y, hMod), speed);
	return hPos;
}

#define PI_MOD 2.84444444444

#define PI_F FIX16(3.14159265358 * PI_MOD)
#define PI_F_2 FIX16(1.57079632679 * PI_MOD)
#define PI_F_4 FIX16(0.78539816339 * PI_MOD)

fix16 arctan(fix16 x) {
	return fix16Mul(PI_F_4, x) - fix16Mul(fix16Mul(x, (abs(x) - 1)), (FIX16(0.245) + fix16Mul(FIX16(0.066), abs(x))));
}
fix16 arctan2(fix16 y, fix16 x) {
	return x >= 0 ?
		(y >= 0 ? (y < x ? arctan(fix16Div(y, x)) : PI_F_2 - arctan(fix16Div(x, y))) : (-y < x ? arctan(fix16Div(y, x)) : -PI_F_2 - arctan(fix16Div(x, y)))) :
		(y >= 0 ? (y < -x ? arctan(fix16Div(y, x)) + PI_F : PI_F_2 - arctan(fix16Div(x, y))) : (-y < -x ? arctan(fix16Div(y, x)) - PI_F : -PI_F_2 - arctan(fix16Div(x, y))));
}
s16 arcAngle;
s16 honeAngle(fix16 x1, fix16 x2, fix16 y1, fix16 y2){
	arcAngle = arctan2(y2 - y1, x2 - x1);
	if(arcAngle >= 128) arcAngle -= 32;
	if(arcAngle >= 384) arcAngle -= 32;
	if(arcAngle < 0){
		arcAngle = 1024 + arcAngle;
		if(arcAngle < 896) arcAngle += 32;
		if(arcAngle < 640) arcAngle += 32;
	}
	return arcAngle;
}

void bulletSfx(u8 i){
	if(!killBullets && !isAttract && !gameOver) XGM_startPlayPCM(i == 0 ? SFX_BULLET_1 : SFX_BULLET_2, 15, SOUND_PCM_CH3);
}