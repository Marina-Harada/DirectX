#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//出現状態（点滅）
	PLAYERSTATE_NORMAL,//通常状態
	PLAYERSTATE_DAMAGE,//ダメージ状態
	PLAYERSTATE_DEATH,//死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤーの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	PLAYERSTATE state;//プレイヤーの状態
	int nCounterState;//状態管理カウンター
	int nLife;//体力
	bool bDisp;//表示するかしないか
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDamage);

#endif
