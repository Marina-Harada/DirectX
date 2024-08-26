#ifndef _INPUT_H_ //このマクロ定義がされていなかったら
#define _INPUT_H_ //２重インクルード防止のマクロ定義

#include"main.h"

//キーの種類
typedef enum
{
	JOYKEY_UP = 0,//十字キー（上）
	JOYKEY_UNDER = 1,//十字キー（下）
	JOYKEY_LEFT = 2,//十字キー（右）
	JOYKEY_RIGHT = 3,//十字キー（左）
	JOYKEY_A = 4,//Aキー
	JOYKEY_B = 5,//Bキー
	JOYKEY_X = 6,//Xキー
	JOYKEY_Y = 7,//Yキー
	JOYKEY_LB = 8,//LBキー
	JOYKEY_RB = 9,//RBキー
	JOYKEY_RT = 10,//LTキー
	JOYKEY_LT = 11,//RTキー
	JOYKEY_LSTICK = 12,//LStickキー
	JOYKEY_RSTICK = 13,//RStickキー
	JOYKEY_BACK = 14,//Backキー
	JOYKEY_START= 15,//Stateキー
}JOYKEY;

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool Trigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);

HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);

#endif