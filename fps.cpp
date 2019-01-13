///����������������������������������������
//fps.cpp
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########

#include "fps.h"

///########## �O���[�o���ϐ��̐錾�Ə����� ##########

//FPS�\���̂̕ϐ�
MY_FPS MyFPS;

///########## �v���g�^�C�v�錾 ##########

//��ʍX�V�̎������擾����֐�
BOOL MY_FPS_UPDATE(VOID);

//�w�肵��FPS�ɂȂ�悤�ɑ҂֐�
VOID MY_FPS_WAIT(VOID);

//FPS�̒l��\������֐�
VOID MY_FPS_DRAW(HDC hdc);

///########## �w�肵��FPS�ɂȂ�悤�ɑ҂֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_FPS_WAIT(VOID)
{
	//���݂̎������~���b�Ŏ擾
	DWORD now_tm = GetTickCount();

	//1�t���[���ڂ�����ۂɂ����������Ԃ��v�Z
	DWORD keika_tm = now_tm - MyFPS.fps_sta_tm;

	//�҂ׂ����� = ������ׂ����� - ���ۂɂ�����������;
	DWORD wait_tm = (MyFPS.fps_count * 1000 / MyFPS.fps_disp) - (keika_tm);

	//�҂ׂ����Ԃ��������ꍇ
	if (wait_tm > 0 && wait_tm < 2000)
	{
		//�~���b���A�����𒆒f����
		Sleep(wait_tm);
	}

	return;
}

///########## ��ʍX�V�̎������擾����֐� ##########
//���@���F�Ȃ�
//�߂�l�FTRUE �F����I�� / FALSE�F�ُ�I��
BOOL MY_FPS_UPDATE(VOID)
{
	//1�t���[���ڂȂ玞�����L��
	if (MyFPS.fps_count == 0)
	{
		//Windows���N�����Ă��猻�݂܂ł̎������~���b�Ŏ擾
		MyFPS.fps_sta_tm = GetTickCount();
	}

	//60�t���[���ڂȂ畽�ς��v�Z����
	if (MyFPS.fps_count == MyFPS.fps_ave)
	{
		//Windows���N�����Ă��猻�݂܂ł̎������~���b�Ŏ擾
		MyFPS.fps_end_tm = GetTickCount();

		//���ϓI��FPS�l���v�Z
		MyFPS.fps_Draw
			= 1000.0f / ((MyFPS.fps_end_tm - MyFPS.fps_sta_tm) / MyFPS.fps_ave);

		//����FPS�v�Z�̏���
		MyFPS.fps_sta_tm = MyFPS.fps_end_tm;

		//�J�E���g������
		MyFPS.fps_count = 0;

	}
	MyFPS.fps_count++;

	return true;
}

///########## FPS�̒l��\������֐� ##########
//���@���F�f�o�C�X�R���e�L�X�g�̃n���h��
//���@���F�Ȃ�
VOID MY_FPS_DRAW(HDC hdc)
{
	//FPS�l�𐮌`���邽�߂̕ϐ�
	CHAR strfpsChr[64];
	size_t wLen = 0;
	errno_t err = 0;

	//FPS�l�𐮌`
	sprintf(strfpsChr, "FPS�F%2.1lf", MyFPS.fps_Draw);

	//FPS�l��\�����邽�߂̕ϐ�
	TCHAR StrfpsTch[64];

	//���P�[���w��
	setlocale(LC_ALL, "japanese");

	//��������}���`�o�C�g�������烏�C�h�����ɕϊ�
	err = mbstowcs_s(
		&wLen,				//�ϊ����ꂽ������
		StrfpsTch,			//�ϊ����ꂽ���C�h����
		strlen(strfpsChr),	//�ϊ����镶����
		strfpsChr,			//�ϊ�����}���`�o�C�g����
		_TRUNCATE			//�o�b�t�@�Ɏ��܂邾���̕�����܂ŕϊ�
	);

	SetBkMode(hdc, TRANSPARENT);			//�w�i�F�͏㏑�����Ȃ�
	SetTextColor(hdc, RGB(0, 0, 0));		//�����F
	SetBkColor(hdc, RGB(255, 255, 255));	//�w�i�F

	//FPS��`��
	TextOut(hdc, 0, 0, StrfpsTch, lstrlen(StrfpsTch));
}