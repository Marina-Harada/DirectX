#include"game.h"
#include"player.h"
#include"background.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"enemy.h"
#include"score.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;//�Q�[���̏��
int g_nCounterGameState = 0;//��ԊǗ��J�E���^�[

//�Q�[����ʂ̏���������
void InitGame(void)
{

	//�w�i�̏���������
    InitBackground();

    //�X�R�A�̏���������
    InitScore();

    //�v���C���[�̏���������
    InitPlayer();

    //�e�̏���������
    InitBullet();

    //�����̏���������
    InitExplosion();

    //�G�t�F�N�g�̏���������
    InitEffect();

    //�G�̏���������
    InitEnemy();

    SetEnemy(D3DXVECTOR3(100.0f, 100.0f, 0.0f),0);

    g_gameState = GAMESTATE_NORMAL;
    g_nCounterGameState = 0;
}
//�Q�[����ʂ̏I������
void UninitGame(void)
{
	//�w�i�̏I������
    UninitBackground();

    //�X�R�A�̏I������
    UninitScore();

    //�v���C���[�̏I������
    UninitPlayer();

    //�e�̏I������
    UninitBullet();

    //�����̏I������
    UninitExplosion();

    //�G�̏I������
    UninitEnemy();

    //�G�t�F�N�g�̏I������
    UninitEffect();

}
//�Q�[����ʂ̍X�V����
void UpdateGame(void)
{
    //�w�i�̍X�V����
    UpdateBackground();

    //�X�R�A�̍X�V����
    UpdateScore();

    //�v���C���[�̍X�V����
    UpdatePlayer();

    //�e�̍X�V����
    UpdateBullet();

    //�����̍X�V����
    UpdateExplosion();

    //�G�̍X�V����
    UpdateEnemy();

    //�G�t�F�N�g�̍X�V����
    UpdateEffect();

    //if ()//�G�S�ŁE�v���C���[�ŁE�^�C���I�[�o�[
    //{
    //    //���[�h�ݒ�i���U���g��ʂɈڍs�j
    //    SetMode(MODE_RESULT);
    //}

    switch (g_gameState)
    {
    case GAMESTATE_NORMAL:
        break;
    case GAMESTATE_END:
        g_nCounterGameState++;
        if (g_nCounterGameState >= 60)
        {
            g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�

            //��ʁi���[�h�j�̐ݒ�
            SetMode(MODE_RESULT);
        }
        break;
    }
}
//�Q�[����ʂ̕`�揈��
void DrawGame(void)
{
    //�X�R�A�̕`�揈��
    DrawScore();

    //�v���C���[�̕`�揈��
    DrawBackground();

    //�v���C���[�̕`�揈��
    DrawPlayer();

    //�e�̕`�揈��
    DrawBullet();

    //�����̕`�揈��
    DrawExplosion();

    //�G�̕`�揈��
    DrawEnemy();

    //�G�t�F�N�g�̕`�揈��
    DrawEffect();
}
//�Q�[���̏�Ԃ̐ݒ�
void SetGameState(GAMESTATE state)
{
    g_gameState = state;

    g_nCounterGameState = 0;
}
//�Q�[���̏�Ԃ̎擾
GAMESTATE GetGameState(void)
{
    return g_gameState;
}