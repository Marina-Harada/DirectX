#include"game.h"
#include"player.h"
#include"background.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"enemy.h"
#include"score.h"

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;//ゲームの状態
int g_nCounterGameState = 0;//状態管理カウンター

//ゲーム画面の初期化処理
void InitGame(void)
{

	//背景の初期化処理
    InitBackground();

    //スコアの初期化処理
    InitScore();

    //プレイヤーの初期化処理
    InitPlayer();

    //弾の初期化処理
    InitBullet();

    //爆発の初期化処理
    InitExplosion();

    //エフェクトの初期化処理
    InitEffect();

    //敵の初期化処理
    InitEnemy();

    SetEnemy(D3DXVECTOR3(100.0f, 100.0f, 0.0f),0);

    g_gameState = GAMESTATE_NORMAL;
    g_nCounterGameState = 0;
}
//ゲーム画面の終了処理
void UninitGame(void)
{
	//背景の終了処理
    UninitBackground();

    //スコアの終了処理
    UninitScore();

    //プレイヤーの終了処理
    UninitPlayer();

    //弾の終了処理
    UninitBullet();

    //爆発の終了処理
    UninitExplosion();

    //敵の終了処理
    UninitEnemy();

    //エフェクトの終了処理
    UninitEffect();

}
//ゲーム画面の更新処理
void UpdateGame(void)
{
    //背景の更新処理
    UpdateBackground();

    //スコアの更新処理
    UpdateScore();

    //プレイヤーの更新処理
    UpdatePlayer();

    //弾の更新処理
    UpdateBullet();

    //爆発の更新処理
    UpdateExplosion();

    //敵の更新処理
    UpdateEnemy();

    //エフェクトの更新処理
    UpdateEffect();

    //if ()//敵全滅・プレイヤー滅・タイムオーバー
    //{
    //    //モード設定（リザルト画面に移行）
    //    SetMode(MODE_RESULT);
    //}

    switch (g_gameState)
    {
    case GAMESTATE_NORMAL:
        break;
    case GAMESTATE_END:
        g_nCounterGameState++;
        if (g_nCounterGameState >= 60)
        {
            g_gameState = GAMESTATE_NONE;//何もしていない状態に設定

            //画面（モード）の設定
            SetMode(MODE_RESULT);
        }
        break;
    }
}
//ゲーム画面の描画処理
void DrawGame(void)
{
    //スコアの描画処理
    DrawScore();

    //プレイヤーの描画処理
    DrawBackground();

    //プレイヤーの描画処理
    DrawPlayer();

    //弾の描画処理
    DrawBullet();

    //爆発の描画処理
    DrawExplosion();

    //敵の描画処理
    DrawEnemy();

    //エフェクトの描画処理
    DrawEffect();
}
//ゲームの状態の設定
void SetGameState(GAMESTATE state)
{
    g_gameState = state;

    g_nCounterGameState = 0;
}
//ゲームの状態の取得
GAMESTATE GetGameState(void)
{
    return g_gameState;
}