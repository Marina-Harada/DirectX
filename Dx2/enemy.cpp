//************************************
//
//２Ｄゲーム制作
//Author:Marina Harada
//
//************************************
#include"enemy.h"
#include"bullet.h"
#include"explosion.h"

//マクロ定義
#define NUM_ENEMY (4)//敵の種類

//グローバル宣言
int g_nNumEnemy = 1;//敵の総数
LPDIRECT3DTEXTURE9 g_pTextureEnemy[NUM_ENEMY] = {}; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL; //頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];//敵の情報
//int g_nCounterAnimEnemy; //アニメーションカウンター
//int g_nPatternAnimEnemy; //アニメーションパターンNo.
//D3DXVECTOR3 g_posEnemy; //位置
//D3DXVECTOR3 g_moveEnemy; //移動量
//D3DXVECTOR3 g_rotEnemy;//向き
//float g_fLengthEnemy;//対角線の長さ
//float g_fAngleEnemy;//対角線の角度
//bool g_texture;//テクスチャ反転

//敵の初期化処理
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\sleep.png",
		&g_pTextureEnemy[0]
	);

	//g_posEnemy = D3DXVECTOR3(300.0f,100.0f,0.0f); //位置を初期化する
	//g_moveEnemy= D3DXVECTOR3(0.0f,0.0f,0.0f); //移動量を初期化する
	//g_rotEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化する
	//g_aEnemy[nCntEnemy].nLife = 100;
	//g_nNumEnemy = 0;

	////対角線の長さを算出する
	//g_fLengthEnemy = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT)/2.0f;

	////対角線の角度を算出する
	//g_fAngleEnemy = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 8, //確保するバッファのサイズ、*数は必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(460.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(460.0f, 360.0f, 0.0f);
	
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}
//敵の終了処理
void UninitEnemy(void)
{
	//テクスチャの破棄
	if (g_pTextureEnemy[NUM_ENEMY])
	{
		g_pTextureEnemy[NUM_ENEMY]->Release();

		g_pTextureEnemy[NUM_ENEMY] = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();

		g_pVtxBuffEnemy = NULL;
	}

}
//敵の更新処理
void UpdateEnemy(void)
{
	int nCntEnemy;

	//使用されている敵が弾を発射する処理
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点情報へのポインタ
		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();
	}
}
//敵の描画処理
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	int nCntEnemy;

    //デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffEnemy,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(nCntEnemy=0; nCntEnemy< MAX_ENEMY; nCntEnemy++)
	{
		if(g_aEnemy[nCntEnemy].bUse == true)
		//敵が使用されている
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureEnemy[nCntEnemy]);

		//プレイヤーの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,//プリミティブの種類
			0*nCntEnemy,//描画する最初の頂点インデックス
			2//プリミティブ（プレイヤー）の数
		);
	}
}
//敵の設定処理
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//敵が使用されていない
			//敵の情報を設定
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = NUM_ENEMY;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nLife = 30;
			g_aEnemy[nCntEnemy].bUse = true;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 100.0f, g_aEnemy[nCntEnemy].pos.y - 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 100.0f, g_aEnemy[nCntEnemy].pos.y - 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 100.0f, g_aEnemy[nCntEnemy].pos.y + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 100.0f, g_aEnemy[nCntEnemy].pos.y + 100.0f, 0.0f);

			g_nNumEnemy++;//敵の総数カウントアップ

			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

}
//敵の取得
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}
//敵のヒット処理
void HitEnemy(int nCntEnemy, int nDamage)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//敵の体力0になった時
	if (g_aEnemy[nCntEnemy].nLife<=0)
	{
		//爆発の設定
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		g_nNumEnemy--;//敵の総数カウントダウン

		if (g_nNumEnemy <= 0)
		{
			//モード設定（リザルト画面に移行）
			SetMode(MODE_RESULT);
		}

		g_aEnemy[nCntEnemy].bUse = false;
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;

		g_aEnemy[nCntEnemy].nCounterState = 5;//ダメージ状態意を保つ時間の設定

		pVtx += 4 * nCntEnemy;//頂点バッファを一気に動かせる

		//ポリゴンをダメージ色に設定
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 0);

	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}