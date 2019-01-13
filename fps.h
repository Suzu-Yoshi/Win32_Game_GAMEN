///����������������������������������������
//fps.h
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <windows.h>

///########## �}�N����` ##########

//FPS�p�̃^�C�}�[ID
#define TIMER_ID_FPS	100

#define FPS_CALC_AVE	60.0f
#define FPS_DISP		60

///########## �\���� ##########

//FPS�̃p�����[�^�\����
struct MY_STRUCT_FPS
{
	float		fps_Show;				//�\������FPS
	DWORD		fps_sta_tm;				//0�t���[���ڂ̊J�n����
	DWORD		fps_end_tm;				//�ݒ肵���t���[���̏I������
	DWORD		fps_count;				//�t���[���̃J�E���g
	float		fps_ave = FPS_CALC_AVE;	//FPS���v�Z���邽�߂̕��σT���v����
	int			fps_disp = FPS_DISP;	//FPS�̒l
};

///########## ���O�̍Ē�` ##########

typedef MY_STRUCT_FPS	MY_FPS;

///��������������������������������������������������������
#pragma once	//��d�C���N���[�h�̖h�~
///��������������������������������������������������������

///########## �O���[�o���ϐ� �Q�Ƃ̐錾 ##########

///���������� �{�̂�fps.cpp ����������

//FPS�\���̂̕ϐ�
extern MY_FPS MyFPS;

///���������� �{�̂�fps.cpp ����������

///########## �O�� �֐� �Q�Ƃ̐錾 ##########

///���������� �{�̂�fps.cpp ����������

//��ʍX�V�̎������擾����֐�
extern BOOL MY_FPS_UPDATE(VOID);

//�w�肵��FPS�ɂȂ�悤�ɑ҂֐�
extern VOID MY_FPS_WAIT(VOID);

///���������� �{�̂�fps.cpp ����������