//************************************
//
//�Q�c�Q�[������
//Author:Marina Harada
//
//************************************
#include"enemy.h"
#include"bullet.h"
#include"explosion.h"

//�}�N����`
#define NUM_ENEMY (4)//�G�̎��

//�O���[�o���錾
int g_nNumEnemy = 1;//�G�̑���
LPDIRECT3DTEXTURE9 g_pTextureEnemy[NUM_ENEMY] = {}; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL; //���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];//�G�̏��
//int g_nCounterAnimEnemy; //�A�j���[�V�����J�E���^�[
//int g_nPatternAnimEnemy; //�A�j���[�V�����p�^�[��No.
//D3DXVECTOR3 g_posEnemy; //�ʒu
//D3DXVECTOR3 g_moveEnemy; //�ړ���
//D3DXVECTOR3 g_rotEnemy;//����
//float g_fLengthEnemy;//�Ίp���̒���
//float g_fAngleEnemy;//�Ίp���̊p�x
//bool g_texture;//�e�N�X�`�����]

//�G�̏���������
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\sleep.png",
		&g_pTextureEnemy[0]
	);

	//g_posEnemy = D3DXVECTOR3(300.0f,100.0f,0.0f); //�ʒu������������
	//g_moveEnemy= D3DXVECTOR3(0.0f,0.0f,0.0f); //�ړ��ʂ�����������
	//g_rotEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����������������
	//g_aEnemy[nCntEnemy].nLife = 100;
	//g_nNumEnemy = 0;

	////�Ίp���̒������Z�o����
	//g_fLengthEnemy = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT)/2.0f;

	////�Ίp���̊p�x���Z�o����
	//g_fAngleEnemy = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 8, //�m�ۂ���o�b�t�@�̃T�C�Y�A*���͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(460.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(460.0f, 360.0f, 0.0f);
	
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}
//�G�̏I������
void UninitEnemy(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEnemy[NUM_ENEMY])
	{
		g_pTextureEnemy[NUM_ENEMY]->Release();

		g_pTextureEnemy[NUM_ENEMY] = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();

		g_pVtxBuffEnemy = NULL;
	}

}
//�G�̍X�V����
void UpdateEnemy(void)
{
	int nCntEnemy;

	//�g�p����Ă���G���e�𔭎˂��鏈��
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���ւ̃|�C���^
		VERTEX_2D* pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();
	}
}
//�G�̕`�揈��
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	int nCntEnemy;

    //�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffEnemy,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(nCntEnemy=0; nCntEnemy< MAX_ENEMY; nCntEnemy++)
	{
		if(g_aEnemy[nCntEnemy].bUse == true)
		//�G���g�p����Ă���
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureEnemy[nCntEnemy]);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
			0*nCntEnemy,//�`�悷��ŏ��̒��_�C���f�b�N�X
			2//�v���~�e�B�u�i�v���C���[�j�̐�
		);
	}
}
//�G�̐ݒ菈��
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//�G���g�p����Ă��Ȃ�
			//�G�̏���ݒ�
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = NUM_ENEMY;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nLife = 30;
			g_aEnemy[nCntEnemy].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 100.0f, g_aEnemy[nCntEnemy].pos.y - 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 100.0f, g_aEnemy[nCntEnemy].pos.y - 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 100.0f, g_aEnemy[nCntEnemy].pos.y + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 100.0f, g_aEnemy[nCntEnemy].pos.y + 100.0f, 0.0f);

			g_nNumEnemy++;//�G�̑����J�E���g�A�b�v

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

}
//�G�̎擾
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}
//�G�̃q�b�g����
void HitEnemy(int nCntEnemy, int nDamage)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�G�̗̑�0�ɂȂ�����
	if (g_aEnemy[nCntEnemy].nLife<=0)
	{
		//�����̐ݒ�
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		g_nNumEnemy--;//�G�̑����J�E���g�_�E��

		if (g_nNumEnemy <= 0)
		{
			//���[�h�ݒ�i���U���g��ʂɈڍs�j
			SetMode(MODE_RESULT);
		}

		g_aEnemy[nCntEnemy].bUse = false;
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;

		g_aEnemy[nCntEnemy].nCounterState = 5;//�_���[�W��Ԉӂ�ۂ��Ԃ̐ݒ�

		pVtx += 4 * nCntEnemy;//���_�o�b�t�@����C�ɓ�������

		//�|���S�����_���[�W�F�ɐݒ�
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 0);

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}