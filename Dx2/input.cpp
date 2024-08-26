#include"input.h"

//マクロ定義
#define NUM_KEY_MAX (256)//キーの最大数

//グローバル変数
XINPUT_STATE g_joyKeyState;//ジョイパッドのプレス情報
LPDIRECTINPUT8 g_pInput = NULL;//DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//入力デバイス（キーボード）へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];//キーボードのプレス情報
BYTE g_oldKeyState[NUM_KEY_MAX];//キーボードのトリガー情報

//キーボードの初期化処理
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput,
		NULL
	)))
	{
		return E_FAIL;
	}

	//入力デバイス（キーボード）の生成
	if (FAILED(g_pInput->CreateDevice(
		GUID_SysKeyboard,
		&g_pDevKeyboard,
		NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(
		hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)
	)))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//キーボードの終了処理
void UninitKeyboard(void)
{
	//入力デバイス（キーボード）の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();

		g_pDevKeyboard->Release();

		g_pDevKeyboard = NULL;
	}

	//Directinputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();

		g_pInput = NULL;
	}
}
//キーボードの更新処理
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力情報
	int nCntKey;

	//ひとつ前のキーボードプレス情報を保存	
	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_oldKeyState[nCntKey] = g_aKeyState[nCntKey];
	}

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}
//キーボードのプレス情報を取得
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//キーボードのトリガー処理
bool Trigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_oldKeyState[nKey] & 0x80))
	{
		Trigger = false;
	}
	
	return Trigger;
}

bool KeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_oldKeyState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}

	return Trigger;
}

bool KeyboardRepeat(int nKey)
{
	bool Trigger = false;
	if (g_oldKeyState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}

	return Trigger;
}
//ジョイパッドの初期化処理
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//Xinputのステートを設定（有効にする）
	XInputEnable(true);

	return S_OK;
}
//ジョイパッドの終了処理
void UninitJoypad(void)
{
	//XInputのステートを設定（無効にする）
	XInputEnable(false);
}
//ジョイパッドの更新処理
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//ジョイパッドの入力情報

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joyKeyState=joykeyState;//ジョイパッドのプレス情報を保存
	}
}
//ジョイパッドのプレス情報を取得
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}