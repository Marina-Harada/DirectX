#include"title.h"
#include"input.h"
#include"sound.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL; //頂点バッファへのポインタ

//タイトル画面の初期化処理
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\title000.png",
		&g_pTextureTitle
	);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 8, //確保するバッファのサイズ、*数は必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	g_pVtxBuffTitle->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM);
}
//タイトル画面の終了処理
void UninitTitle(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTextureTitle)
	{
		g_pTextureTitle->Release();

		g_pTextureTitle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();

		g_pVtxBuffTitle = NULL;
	}

}
//タイトル画面の更新処理
void UpdateTitle(void)
{
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		//決定キー（ENTERキー）が押された
		//モード設定（ゲーム画面に移行）
		SetMode(MODE_GAME);
	}
}
//タイトル画面の描画
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

    //デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffTitle,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);

	//プレイヤーの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,//描画する最初の頂点インデックス
		2//プリミティブ（プレイヤー）の数
	);

}