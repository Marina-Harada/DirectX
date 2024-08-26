//************************************
//
//２Ｄゲーム制作
//Author:Marina Harada
//
//************************************
#include"main.h"
#include"player.h"
#include"input.h"
#include"bullet.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL; //頂点バッファへのポインタ
Player g_player;//プレイヤーの情報
float g_fLengthPlayer;//対角線の長さ
float g_fAnglePlayer;//対角線の角度
bool g_texture;//テクスチャ反転

//プレイヤーの初期化処理
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\sleep2.png",
		&g_pTexturePlayer
	);

	g_player.pos = D3DXVECTOR3(600.0f,400.0f,0.0f); //位置を初期化する
	g_player.move= D3DXVECTOR3(0.0f,0.0f,0.0f); //移動量を初期化する
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化する

	//対角線の長さを算出する
	g_fLengthPlayer = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT)/2.0f;

	//対角線の角度を算出する
	g_fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 8, //確保するバッファのサイズ、*数は必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[4].pos.x = g_player.pos.x + sinf(g_player.rot.z+ (-D3DX_PI + g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[4].pos.y = g_player.pos.y + cosf(g_player.rot.z+ (-D3DX_PI + g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[4].pos.z = 0.0f;

	pVtx[5].pos.x = g_player.pos.x + sinf(g_player.rot.z+ (D3DX_PI - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[5].pos.y = g_player.pos.y + cosf(g_player.rot.z+ (D3DX_PI - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[5].pos.z = 0.0f;

	pVtx[6].pos.x = g_player.pos.x + sinf(g_player.rot.z+ (0.0f - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[6].pos.y = g_player.pos.y + cosf(g_player.rot.z+ (0.0f - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[6].pos.z = 0.0f;

	pVtx[7].pos.x = g_player.pos.x + sinf(g_player.rot.z+ (0.0f + g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[7].pos.y = g_player.pos.y + cosf(g_player.rot.z+ (0.0f + g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[7].pos.z = 0.0f;
	
	//rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}
//プレイヤーの終了処理
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer)
	{
		g_pTexturePlayer->Release();

		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();

		g_pVtxBuffPlayer = NULL;
	}

}
//プレイヤーの更新処理
void UpdatePlayer(void)
{
	//頂点座標の更新
    //頂点情報へのポインタ
	VERTEX_2D* pVtx=0;

	//左系
	if (GetKeyboardPress(DIK_A)==true)
	{

		//左上
		if (GetKeyboardPress(DIK_W) == true)
		{
			//Wキーが押された
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 0.5f;

			g_player.move.x += sinf(-D3DX_PI * 0.75f) * 0.5f;

			//テクスチャ反転
			g_texture = true;

		}
		//左下
		else if (GetKeyboardPress(DIK_S) == true)
		{
			//Sキーが押された
			g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.5f;

			g_player.move.x += sinf(-D3DX_PI * 0.25f) * 0.5f;

			//テクスチャ反転
			g_texture = true;

		}
		//左
		else
		{
			//Aキーが押された
			g_player.move.x -= 0.5f;

			//テクスチャ反転
			g_texture = true;

		}
	}
	//右系
	else if (GetKeyboardPress(DIK_D) == true)
	{
		//右上
		if (GetKeyboardPress(DIK_W) == true)
		{
			//Wキーが押された
			g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.5f;

			//Dキーが押された
			g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.5f;

			//テクスチャ反転
			g_texture = true;

		}
		//右下
		else if (GetKeyboardPress(DIK_S) == true)
		{
			//Sキーが押された
			g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.5f;

			//Dキーが押された
			g_player.move.x += sinf(D3DX_PI * 0.25f) * 0.5f;

			//テクスチャ反転
			g_texture = true;

		}
		//右
		else
		{
			//Dキーが押された
			g_player.move.x += 0.5f;

			//テクスチャ反転
			g_texture = false;
		}
	}
	//上
	else if (GetKeyboardPress(DIK_W) == true)
	{

		//Wキーが押された
		g_player.move.y -= 0.5f;

		//テクスチャ反転
		g_texture = true;

	}
	//下
	else if (GetKeyboardPress(DIK_S) == true)
	{

		//Sキーが押された
		g_player.move.y += 0.5f;

		//テクスチャ反転
		g_texture = true;

	}
	//回転
	if (GetKeyboardPress(DIK_Q) == true)
	{

		//Qキーが押された
		g_player.rot.z += 0.2f;

	}
	else if (GetKeyboardPress(DIK_E) == true)
	{

		//Eキーが押された
		g_player.rot.z -= 0.2f;

	}
	//拡大・縮小
	if (GetKeyboardPress(DIK_P) == true)
	{

		//Pキーが押された
		g_fLengthPlayer += 0.5f;

	}
	else if (GetKeyboardPress(DIK_O) == true)
	{

		//Oキーが押された
		g_fLengthPlayer -= 0.5f;

	}
	//全リセット
	if (GetKeyboardPress(DIK_R) == true)
	{

		//Rキーが押された
		g_player.pos = D3DXVECTOR3(600.0f, 400.0f, 0.0f); //位置を初期化する
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量を初期化する
		g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化する

	}
	//SPACEキーが押された
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		//弾の設定
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * 10.0f, cosf(g_player.rot.z + D3DX_PI) * 10.0f, 0.0f),0, BULLETTYPE_PLAYER);
	}

	//ジョイパッド版の設定
	if (GetJoypadPress(JOYKEY_A) == true)
	{
		//上キーが押された
		g_player.pos.y -= 1.0f;
	}
	else if (GetJoypadPress(JOYKEY_B) == true)
	{
		//下キーが押された
		g_player.pos.y += 1.0f;
	}
	else if (GetJoypadPress(JOYKEY_Y) == true)
	{
		//右キーが押された
		g_player.pos.x += 1.0f;
	}
	else if (GetJoypadPress(JOYKEY_X) == true)
	{
		//左キーが押された
		g_player.pos.x -= 1.0f;
	}
	//else if (GetJoypadPress(JOYKEY_A) == true)
	//{
	//	//Aキーが押された
	//}
	//else if (GetJoypadPress(JOYKEY_B) == true)
	//{
	//	//Bキーが押された
	//}
	//else if (GetJoypadPress(JOYKEY_Y) == true)
	//{
	//	//Yキーが押された
	//}
	//else if (GetJoypadPress(JOYKEY_X) == true)
	//{
	//	//Xキーが押された
	//}
	//else if (GetJoypadPress(JOYKEY_LB) == true)
	//{
	//	//LBキーが押された
	//}
	//else if (GetJoypadPress(JOYKEY_RB) == true)
	//{
	//	//RBキーが押された
	//}
	//else if (GetJoypadPress(JOYKEY_LT) == true)
	//{
	//	//LTキーが押された
	//}
	//else if (GetJoypadPress(JOYKEY_RT) == true)
	//{
	//	//RTキーが押された
	//}
	//else if (GetJoypadPress(JOYKEY_LSTICK) == true)
	//{
	//	//LSTICKキーが押された
	//}
	//else if (GetJoypadPress(JOYKEY_RSTICK) == true)
	//{
	//	//RSTICKキーが押された
	//}
	//else if (GetJoypadPress(JOYKEY_BACK) == true)
	//{
	//	//BACKキーが押された
	//}
	//else if (GetJoypadPress(JOYKEY_START) == true)
	//{
	//	//STATEキーが押された
	//}

	//位置を更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//移動量を更新（減衰させる）
	g_player.move.x += (0.0f - g_player.move.x) * 0.03f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.03f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[4].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[4].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[4].pos.z = 0.0f;

	pVtx[5].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[5].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[5].pos.z = 0.0f;

	pVtx[6].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[6].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[6].pos.z = 0.0f;

	pVtx[7].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[7].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[7].pos.z = 0.0f;

	//プレイヤーのダメージ遷移
	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;

			//頂点情報へのポインタ
			VERTEX_2D* pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラーの設定
			pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//頂点バッファをアンロックする
			g_pVtxBuffPlayer->Unlock();
			
		}
		break;

	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{
			//モード設定（リザルト画面移行）
			SetMode(MODE_RESULT);

			return;
		}
		break;
	}
}
//プレイヤーの描画処理
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

    //デバイスの取得
	pDevice = GetDevice();

	//if (g_player.bDisp == true)
	//{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(
			0,
			g_pVtxBuffPlayer,
			0,
			sizeof(VERTEX_2D)
		);

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		//プレイヤーの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,//プリミティブの種類
			4,//描画する最初の頂点インデックス
			2//プリミティブ（プレイヤー）の数
		);
	//}
}
//プレイヤーの取得
Player* GetPlayer(void)
{
	return &g_player;//プレイヤーの情報を返す
}
//プレイヤーのヒット処理
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;

	//プレイヤーの体力がなくなった
	if (g_player.nLife<=0)
	{
		g_player.bDisp = false;

		g_player.state = PLAYERSTATE_DEATH;

		g_player.nCounterState = 60;
	}
	else
	{
		g_player.nCounterState = PLAYERSTATE_DAMAGE;

		g_player.nCounterState = 5;

		//頂点情報へのポインタ
		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[4].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[5].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[6].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[7].col = D3DCOLOR_RGBA(255, 0, 0, 0);

		//頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();

	}
}












////頂点座標の設定
//pVtx[4].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y - 150.0f, 0.0f);
//pVtx[5].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y - 150.0f, 0.0f);
//pVtx[6].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y + 150.0f, 0.0f);
//pVtx[7].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y + 150.0f, 0.0f);

//int g_nCounterAnimPlayer; //アニメーションカウンター
//int g_nPatternAnimPlayer; //アニメーションパターンNo.


	//g_nCounterAnimPlayer++; //カウンターを加算

	//if ((g_nCounterAnimPlayer%5 == 0))
	//{//一定時間経過した

	//	g_nCounterAnimPlayer = 0;

	//	//パターンNo.を更新する
	//	g_nPatternAnimPlayer=(g_nPatternAnimPlayer+1)%10;

	//	//テクスチャ反転
	//	if (g_texture == true)
	//	{
	//		//テクスチャ座標の設定
	//		pVtx[4].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, 0.5f * (g_nPatternAnimPlayer / 5));
	//		pVtx[5].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f + 0.2f, 0.5f * (g_nPatternAnimPlayer / 5));
	//		pVtx[6].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, 0.5f * (g_nPatternAnimPlayer / 5) + 0.5f);
	//		pVtx[7].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f + 0.2f, 0.5f * (g_nPatternAnimPlayer / 5) + 0.5f);

	//	}
	//	else if (g_texture == false)
	//	{
	//		//テクスチャ座標の設定
	//		pVtx[4].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f + 0.2f, 0.5f * (g_nPatternAnimPlayer / 5));
	//		pVtx[5].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, 0.5f * (g_nPatternAnimPlayer / 5));
	//		pVtx[6].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f + 0.2f, 0.5f * (g_nPatternAnimPlayer / 5) + 0.5f);
	//		pVtx[7].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, 0.5f * (g_nPatternAnimPlayer / 5) + 0.5f);

	//	}

	//	//頂点バッファをアンロックする
	//	g_pVtxBuffPlayer->Unlock();

	//}

	//g_nCounterAnimPlayer = 0; //カウンターを初期化する
	//g_nPatternAnimPlayer = 0; //パターンNo.を初期化する
