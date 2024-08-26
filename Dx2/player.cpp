//************************************
//
//�Q�c�Q�[������
//Author:Marina Harada
//
//************************************
#include"main.h"
#include"player.h"
#include"input.h"
#include"bullet.h"

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL; //���_�o�b�t�@�ւ̃|�C���^
Player g_player;//�v���C���[�̏��
float g_fLengthPlayer;//�Ίp���̒���
float g_fAnglePlayer;//�Ίp���̊p�x
bool g_texture;//�e�N�X�`�����]

//�v���C���[�̏���������
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\sleep2.png",
		&g_pTexturePlayer
	);

	g_player.pos = D3DXVECTOR3(600.0f,400.0f,0.0f); //�ʒu������������
	g_player.move= D3DXVECTOR3(0.0f,0.0f,0.0f); //�ړ��ʂ�����������
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����������������

	//�Ίp���̒������Z�o����
	g_fLengthPlayer = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT)/2.0f;

	//�Ίp���̊p�x���Z�o����
	g_fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 8, //�m�ۂ���o�b�t�@�̃T�C�Y�A*���͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[4].pos.x = g_player.pos.x + sinf(g_player.rot.z+ (-D3DX_PI + g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[4].pos.y = g_player.pos.y + cosf(g_player.rot.z+ (-D3DX_PI + g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[4].pos.z = 0.0f;

	pVtx[5].pos.x = g_player.pos.x + sinf(g_player.rot.z+ (D3DX_PI - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[5].pos.y = g_player.pos.y + cosf(g_player.rot.z+ (D3DX_PI - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[5].pos.z = 0.0f;

	pVtx[6].pos.x = g_player.pos.x + sinf(g_player.rot.z+ (0.0f - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[6].pos.y = g_player.pos.y + cosf(g_player.rot.z+ (0.0f - g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[6].pos.z = 0.0f;

	pVtx[7].pos.x = g_player.pos.x + sinf(g_player.rot.z+ (0.0f + g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[7].pos.y = g_player.pos.y + cosf(g_player.rot.z+ (0.0f + g_fAnglePlayer))* g_fLengthPlayer;
	pVtx[7].pos.z = 0.0f;
	
	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}
//�v���C���[�̏I������
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer)
	{
		g_pTexturePlayer->Release();

		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();

		g_pVtxBuffPlayer = NULL;
	}

}
//�v���C���[�̍X�V����
void UpdatePlayer(void)
{
	//���_���W�̍X�V
    //���_���ւ̃|�C���^
	VERTEX_2D* pVtx=0;

	//���n
	if (GetKeyboardPress(DIK_A)==true)
	{

		//����
		if (GetKeyboardPress(DIK_W) == true)
		{
			//W�L�[�������ꂽ
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 0.5f;

			g_player.move.x += sinf(-D3DX_PI * 0.75f) * 0.5f;

			//�e�N�X�`�����]
			g_texture = true;

		}
		//����
		else if (GetKeyboardPress(DIK_S) == true)
		{
			//S�L�[�������ꂽ
			g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.5f;

			g_player.move.x += sinf(-D3DX_PI * 0.25f) * 0.5f;

			//�e�N�X�`�����]
			g_texture = true;

		}
		//��
		else
		{
			//A�L�[�������ꂽ
			g_player.move.x -= 0.5f;

			//�e�N�X�`�����]
			g_texture = true;

		}
	}
	//�E�n
	else if (GetKeyboardPress(DIK_D) == true)
	{
		//�E��
		if (GetKeyboardPress(DIK_W) == true)
		{
			//W�L�[�������ꂽ
			g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.5f;

			//D�L�[�������ꂽ
			g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.5f;

			//�e�N�X�`�����]
			g_texture = true;

		}
		//�E��
		else if (GetKeyboardPress(DIK_S) == true)
		{
			//S�L�[�������ꂽ
			g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.5f;

			//D�L�[�������ꂽ
			g_player.move.x += sinf(D3DX_PI * 0.25f) * 0.5f;

			//�e�N�X�`�����]
			g_texture = true;

		}
		//�E
		else
		{
			//D�L�[�������ꂽ
			g_player.move.x += 0.5f;

			//�e�N�X�`�����]
			g_texture = false;
		}
	}
	//��
	else if (GetKeyboardPress(DIK_W) == true)
	{

		//W�L�[�������ꂽ
		g_player.move.y -= 0.5f;

		//�e�N�X�`�����]
		g_texture = true;

	}
	//��
	else if (GetKeyboardPress(DIK_S) == true)
	{

		//S�L�[�������ꂽ
		g_player.move.y += 0.5f;

		//�e�N�X�`�����]
		g_texture = true;

	}
	//��]
	if (GetKeyboardPress(DIK_Q) == true)
	{

		//Q�L�[�������ꂽ
		g_player.rot.z += 0.2f;

	}
	else if (GetKeyboardPress(DIK_E) == true)
	{

		//E�L�[�������ꂽ
		g_player.rot.z -= 0.2f;

	}
	//�g��E�k��
	if (GetKeyboardPress(DIK_P) == true)
	{

		//P�L�[�������ꂽ
		g_fLengthPlayer += 0.5f;

	}
	else if (GetKeyboardPress(DIK_O) == true)
	{

		//O�L�[�������ꂽ
		g_fLengthPlayer -= 0.5f;

	}
	//�S���Z�b�g
	if (GetKeyboardPress(DIK_R) == true)
	{

		//R�L�[�������ꂽ
		g_player.pos = D3DXVECTOR3(600.0f, 400.0f, 0.0f); //�ʒu������������
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ړ��ʂ�����������
		g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����������������

	}
	//SPACE�L�[�������ꂽ
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		//�e�̐ݒ�
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * 10.0f, cosf(g_player.rot.z + D3DX_PI) * 10.0f, 0.0f),0, BULLETTYPE_PLAYER);
	}

	//�W���C�p�b�h�ł̐ݒ�
	if (GetJoypadPress(JOYKEY_A) == true)
	{
		//��L�[�������ꂽ
		g_player.pos.y -= 1.0f;
	}
	else if (GetJoypadPress(JOYKEY_B) == true)
	{
		//���L�[�������ꂽ
		g_player.pos.y += 1.0f;
	}
	else if (GetJoypadPress(JOYKEY_Y) == true)
	{
		//�E�L�[�������ꂽ
		g_player.pos.x += 1.0f;
	}
	else if (GetJoypadPress(JOYKEY_X) == true)
	{
		//���L�[�������ꂽ
		g_player.pos.x -= 1.0f;
	}
	//else if (GetJoypadPress(JOYKEY_A) == true)
	//{
	//	//A�L�[�������ꂽ
	//}
	//else if (GetJoypadPress(JOYKEY_B) == true)
	//{
	//	//B�L�[�������ꂽ
	//}
	//else if (GetJoypadPress(JOYKEY_Y) == true)
	//{
	//	//Y�L�[�������ꂽ
	//}
	//else if (GetJoypadPress(JOYKEY_X) == true)
	//{
	//	//X�L�[�������ꂽ
	//}
	//else if (GetJoypadPress(JOYKEY_LB) == true)
	//{
	//	//LB�L�[�������ꂽ
	//}
	//else if (GetJoypadPress(JOYKEY_RB) == true)
	//{
	//	//RB�L�[�������ꂽ
	//}
	//else if (GetJoypadPress(JOYKEY_LT) == true)
	//{
	//	//LT�L�[�������ꂽ
	//}
	//else if (GetJoypadPress(JOYKEY_RT) == true)
	//{
	//	//RT�L�[�������ꂽ
	//}
	//else if (GetJoypadPress(JOYKEY_LSTICK) == true)
	//{
	//	//LSTICK�L�[�������ꂽ
	//}
	//else if (GetJoypadPress(JOYKEY_RSTICK) == true)
	//{
	//	//RSTICK�L�[�������ꂽ
	//}
	//else if (GetJoypadPress(JOYKEY_BACK) == true)
	//{
	//	//BACK�L�[�������ꂽ
	//}
	//else if (GetJoypadPress(JOYKEY_START) == true)
	//{
	//	//STATE�L�[�������ꂽ
	//}

	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//�ړ��ʂ��X�V�i����������j
	g_player.move.x += (0.0f - g_player.move.x) * 0.03f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.03f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[4].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[4].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[4].pos.z = 0.0f;

	pVtx[5].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[5].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[5].pos.z = 0.0f;

	pVtx[6].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[6].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[6].pos.z = 0.0f;

	pVtx[7].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[7].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[7].pos.z = 0.0f;

	//�v���C���[�̃_���[�W�J��
	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;

			//���_���ւ̃|�C���^
			VERTEX_2D* pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[�̐ݒ�
			pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPlayer->Unlock();
			
		}
		break;

	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{
			//���[�h�ݒ�i���U���g��ʈڍs�j
			SetMode(MODE_RESULT);

			return;
		}
		break;
	}
}
//�v���C���[�̕`�揈��
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

    //�f�o�C�X�̎擾
	pDevice = GetDevice();

	//if (g_player.bDisp == true)
	//{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(
			0,
			g_pVtxBuffPlayer,
			0,
			sizeof(VERTEX_2D)
		);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
			4,//�`�悷��ŏ��̒��_�C���f�b�N�X
			2//�v���~�e�B�u�i�v���C���[�j�̐�
		);
	//}
}
//�v���C���[�̎擾
Player* GetPlayer(void)
{
	return &g_player;//�v���C���[�̏���Ԃ�
}
//�v���C���[�̃q�b�g����
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;

	//�v���C���[�̗̑͂��Ȃ��Ȃ���
	if (g_player.nLife<=0)
	{
		g_player.bDisp = false;

		g_player.state = PLAYERSTATE_DEATH;

		g_player.nCounterState = 60;
	}
	else
	{
		g_player.nCounterState = PLAYERSTATE_DAMAGE;

		g_player.nCounterState = 5;

		//���_���ւ̃|�C���^
		VERTEX_2D* pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[4].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[5].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[6].col = D3DCOLOR_RGBA(255, 0, 0, 0);
		pVtx[7].col = D3DCOLOR_RGBA(255, 0, 0, 0);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();

	}
}












////���_���W�̐ݒ�
//pVtx[4].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y - 150.0f, 0.0f);
//pVtx[5].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y - 150.0f, 0.0f);
//pVtx[6].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y + 150.0f, 0.0f);
//pVtx[7].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y + 150.0f, 0.0f);

//int g_nCounterAnimPlayer; //�A�j���[�V�����J�E���^�[
//int g_nPatternAnimPlayer; //�A�j���[�V�����p�^�[��No.


	//g_nCounterAnimPlayer++; //�J�E���^�[�����Z

	//if ((g_nCounterAnimPlayer%5 == 0))
	//{//��莞�Ԍo�߂���

	//	g_nCounterAnimPlayer = 0;

	//	//�p�^�[��No.���X�V����
	//	g_nPatternAnimPlayer=(g_nPatternAnimPlayer+1)%10;

	//	//�e�N�X�`�����]
	//	if (g_texture == true)
	//	{
	//		//�e�N�X�`�����W�̐ݒ�
	//		pVtx[4].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, 0.5f * (g_nPatternAnimPlayer / 5));
	//		pVtx[5].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f + 0.2f, 0.5f * (g_nPatternAnimPlayer / 5));
	//		pVtx[6].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, 0.5f * (g_nPatternAnimPlayer / 5) + 0.5f);
	//		pVtx[7].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f + 0.2f, 0.5f * (g_nPatternAnimPlayer / 5) + 0.5f);

	//	}
	//	else if (g_texture == false)
	//	{
	//		//�e�N�X�`�����W�̐ݒ�
	//		pVtx[4].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f + 0.2f, 0.5f * (g_nPatternAnimPlayer / 5));
	//		pVtx[5].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, 0.5f * (g_nPatternAnimPlayer / 5));
	//		pVtx[6].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f + 0.2f, 0.5f * (g_nPatternAnimPlayer / 5) + 0.5f);
	//		pVtx[7].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, 0.5f * (g_nPatternAnimPlayer / 5) + 0.5f);

	//	}

	//	//���_�o�b�t�@���A�����b�N����
	//	g_pVtxBuffPlayer->Unlock();

	//}

	//g_nCounterAnimPlayer = 0; //�J�E���^�[������������
	//g_nPatternAnimPlayer = 0; //�p�^�[��No.������������
