#include"bullet.h"
#include"explosion.h"
#include"enemy.h"
#include"player.h"

//マクロ定義
#define MAX_BULLET (128)//弾の最大数

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	int nLife;//寿命
	BULLETTYPE type;//種類
	bool bUse;//使用しているかどうか
}Bullet;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL; //頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];

//弾の初期化処理
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet
	);

	//弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BULLET, //確保するバッファのサイズ、*数は必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

}
//弾の終了処理
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet)
	{
		g_pTextureBullet->Release();

		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();

		g_pVtxBuffBullet = NULL;
	}

}
//弾の更新処理
void UpdateBullet(void)
{
	int nCntBullet;
    //頂点情報へのポインタ
	VERTEX_2D* pVtx = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//弾の使用されている
			Enemy* pEnemy;//敵へのポインタ
			int nCntEnemy;

			//敵の取得
			pEnemy = GetEnemy();

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pEnemy++)
			{
				if (pEnemy->bUse == true)
				{
					//敵が使用されている
					if (g_aBullet[nCntBullet].pos.x>=pEnemy->pos.x&&g_aBullet[nCntBullet].pos.x<=pEnemy->pos.x&& g_aBullet[nCntBullet].pos.y>=pEnemy->pos.y&& g_aBullet[nCntBullet].pos.y<=pEnemy->pos.y)
					{
						if (g_aBullet[nCntBullet].pos >= pEnemy->pos)//敵と弾が当たった
						{
							//敵のヒット処理
							HitEnemy(nCntBullet, 1);

							g_aBullet[nCntBullet].bUse = false;//使用していない状態にする

							//プレイヤーの弾
							Enemy* pEnemy = GetEnemy();

							//爆発の設定
							SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

							pEnemy->bUse = false;//敵を使用していない状態にする

							g_aBullet[nCntBullet].bUse = false;//弾を使用していない状態にする
						}
						else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
						{
							//敵の弾
							Player* pPlayer = GetPlayer();
						}
					}
				}
			}

			//弾の位置の更新
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 50.0f, g_aBullet[nCntBullet].pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 50.0f, g_aBullet[nCntBullet].pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 50.0f, g_aBullet[nCntBullet].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 50.0f, g_aBullet[nCntBullet].pos.y + 50.0f, 0.0f);

			//弾の位置が画面外に出た
			if (0>=g_aBullet[nCntBullet].pos.x>=SCREEN_HEIGHT|| 0 >= g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT)
			{
				g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
			}
			//寿命のカウントダウン
			//寿命が尽きた
			if (g_aBullet[nCntBullet].nLife==0)
			{
				//爆発の設定
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
			}
		}

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

}
//弾の描画処理
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	int nCntBullet;

    //デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffBullet,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//弾が使用されている
			//ポリゴンの描画
			pDevice->SetTexture(0, g_pTextureBullet);
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,
				nCntBullet *4,
				2
			);
		}
	}
}
//弾の設定処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet;
	//頂点情報へのポインタ
	VERTEX_2D* pVtx = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			//弾が使用されていない
			g_aBullet[nCntBullet].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 50.0f, g_aBullet[nCntBullet].pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 50.0f, g_aBullet[nCntBullet].pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 50.0f, g_aBullet[nCntBullet].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 50.0f, g_aBullet[nCntBullet].pos.y + 50.0f, 0.0f);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].bUse = true;//使用している状態にする
			break;//ここでfor文を抜ける
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

}