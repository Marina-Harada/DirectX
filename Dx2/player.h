#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//�o����ԁi�_�Łj
	PLAYERSTATE_NORMAL,//�ʏ���
	PLAYERSTATE_DAMAGE,//�_���[�W���
	PLAYERSTATE_DEATH,//���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	PLAYERSTATE state;//�v���C���[�̏��
	int nCounterState;//��ԊǗ��J�E���^�[
	int nLife;//�̗�
	bool bDisp;//�\�����邩���Ȃ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDamage);

#endif
