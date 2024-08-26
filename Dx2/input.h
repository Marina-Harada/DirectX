#ifndef _INPUT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _INPUT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

//�L�[�̎��
typedef enum
{
	JOYKEY_UP = 0,//�\���L�[�i��j
	JOYKEY_UNDER = 1,//�\���L�[�i���j
	JOYKEY_LEFT = 2,//�\���L�[�i�E�j
	JOYKEY_RIGHT = 3,//�\���L�[�i���j
	JOYKEY_A = 4,//A�L�[
	JOYKEY_B = 5,//B�L�[
	JOYKEY_X = 6,//X�L�[
	JOYKEY_Y = 7,//Y�L�[
	JOYKEY_LB = 8,//LB�L�[
	JOYKEY_RB = 9,//RB�L�[
	JOYKEY_RT = 10,//LT�L�[
	JOYKEY_LT = 11,//RT�L�[
	JOYKEY_LSTICK = 12,//LStick�L�[
	JOYKEY_RSTICK = 13,//RStick�L�[
	JOYKEY_BACK = 14,//Back�L�[
	JOYKEY_START= 15,//State�L�[
}JOYKEY;

//�v���g�^�C�v�錾
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