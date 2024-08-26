#ifndef _ENEMY_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ENEMY_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

//�}�N����`
#define MAX_ENEMY (128)//�G�̍ő吔

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,//�ʏ���
	ENEMYSTATE_DAMAGE,//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	int nType;//���
	ENEMYSTATE state;//���
	int nCounterState;//��ԊǗ��J�E���^�[
	int nLife;//�̗�
	bool bUse;//�g�p���Ă��邩
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
Enemy* GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif