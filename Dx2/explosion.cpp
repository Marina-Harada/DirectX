#include"explosion.h"

//マクロ定義
#define MAX_EXPLOSION (128)//爆発の最大数

//爆発構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXCOLOR col;//色
	int nCounterAnim;//アニメーションカウンター
	int nPatternAnim;//アニメーションパターンNo.
	bool bUse;//使用しているかどうか
}Explosion;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL; //頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];//爆発の情報

//爆発の初期化処理
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion
	);

	//爆発の情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION, //確保するバッファのサイズ、*数は必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(300.0f, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(350.0f, 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(300.0f, 150.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(350.0f, 150.0f, 0.0f);

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
	g_pVtxBuffExplosion->Unlock();

}
//爆発の終了処理
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion!=NULL)
	{
		g_pTextureExplosion->Release();

		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();

		g_pVtxBuffExplosion = NULL;
	}

}
//爆発の更新処理
void UpdateExplosion(void)
{
	int nCntExplosion;

    //頂点情報へのポインタ
	VERTEX_2D* pVtx = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//爆発の使用されている
			g_aExplosion[nCntExplosion].nCounterAnim++; //カウンターを加算

			if (g_aExplosion[nCntExplosion].nCounterAnim >= 8)
			{
				//一定時間経過した
				g_aExplosion[nCntExplosion].nPatternAnim = 0;

				//使用していない状態にする
				g_aExplosion[nCntExplosion].bUse = false;
			}

			if((g_aExplosion[nCntExplosion].nCounterAnim%5)==0)
			{
				//テクスチャ座補油の更新
				g_aExplosion[nCntExplosion].nCounterAnim = 0;

				//パターンNo.を更新する
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 10;

				//頂点座標の設定
				pVtx[0].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f)+0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f)+0.125f, 1.0f);

			}

			pVtx += 4;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}
//爆発の描画処理
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	int nCntExplosion;

    //デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffExplosion,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//爆発が使用されている
			//ポリゴンの描画
			pDevice->SetTexture(0, g_pTextureExplosion);
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,
				nCntExplosion *4,
				2
			);
		}
	}
}
//爆発の設定処理
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	//頂点情報へのポインタ
	VERTEX_2D* pVtx = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			//爆発が使用されていない
			g_aExplosion[nCntExplosion].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 20.0f, g_aExplosion[nCntExplosion].pos.y - 20.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 20.0f, g_aExplosion[nCntExplosion].pos.y - 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 20.0f, g_aExplosion[nCntExplosion].pos.y + 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 20.0f, g_aExplosion[nCntExplosion].pos.y + 20.0f, 0.0f);

			//テクスチャの設定
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 1.0f);

			//g_aExplosion[nCntExplosion].move = move;
			//g_aExplosion[nCntExplosion].nLife = 100;
			g_aExplosion[nCntExplosion].bUse = true;//使用している状態にする

			break;//ここでfor文を抜ける
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();

}