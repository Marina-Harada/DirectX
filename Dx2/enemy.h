#ifndef _ENEMY_H_ //このマクロ定義がされていなかったら
#define _ENEMY_H_ //２重インクルード防止のマクロ定義

#include"main.h"

//マクロ定義
#define MAX_ENEMY (128)//敵の最大数

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,//通常状態
	ENEMYSTATE_DAMAGE,//ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE;

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;//位置
	int nType;//種類
	ENEMYSTATE state;//状態
	int nCounterState;//状態管理カウンター
	int nLife;//体力
	bool bUse;//使用しているか
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
Enemy* GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif