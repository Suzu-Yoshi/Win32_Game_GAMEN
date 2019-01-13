///����������������������������������������
//main.h
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <windows.h>

///########## �}�N����` ##########

//�G���[���b�Z�[�W
#define ERR_MSG_TITLE			TEXT("WINDOW_ERROR")

#define ERR_MSG_NO_WIN_CLASS	TEXT("�E�B���h�E�N���X��\
�o�^�ł��܂���ł���\n�v���O�������I�����܂�")

#define ERR_MSG_NO_WIN_CREATE	TEXT("�E�B���h�E\
���쐬�ł��܂���ł���\n�v���O�������I�����܂�")

//�����ō쐬����E�B���h�E�N���X�̖��O
#define MY_WIN_CLASS	"MY_WIN_CLASS"

//�E�B���h�E�̃T�C�Y��ύX�ł��Ȃ�����
#define WS_STATIC_WINDOW	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

//�E�B���h�E�̃^�C�g�����Ȃ���
#define WS_NOT_TITLE WS_POPUP | WS_BORDER

//�Q�[���E�B���h�E�̏ꏊ��傫����ݒ�
#define GAME_LEFT		0		//���̈ʒu
#define GAME_TOP		0		//�c�̈ʒu
#define GAME_RIGHT		400		//��
#define GAME_BOTTOM		400		//����
#define GAME_POS_X		  0		//�����X���W
#define GAME_POS_Y		  0		//�����Y���W

//�Q�[���̃^�C�g��
#define GAME_TITLE			"GAME_TITLE"

///########## �񋓌^ ##########

//�E�B���h�E�̕\����ύX
enum WIN_MODE {
	WIN_RESZ_OK,	//0�F�E�B���h�E�T�C�Y�̕ύX���ł���
	WIN_RESZ_NG,	//1�F�E�B���h�E�T�C�Y�̕ύX���ł��Ȃ�
	WIN_NO_TITLE	//2�F�E�B���h�E�̃^�C�g�����Ȃ���
};

///########## �\���� ##########

//����E�B���h�E�\����
struct MY_STRUCT_GAME_WINDOW
{
	HWND		hwnd;			//�E�B���h�E�n���h��(�X�̃E�B���h�E������)
	WNDCLASS	winc;			//�E�B���h�E�N���X���Ǘ�
	MSG			msg;			//���b�Z�[�W��ێ�
	RECT		win_size;		//�E�B���h�E�̑S�̂̏ꏊ�Ƒ傫����
	RECT		win_rect_win;	//�E�C���h�E�̈�	
	RECT		win_rect_cli;	//�N���C�A���g�̈�
	int			win_mode;		//�E�B���h�E�̕\����ݒ�
	HBITMAP		hbmp_double;	//������ޯ̧�ݸޗp
	HDC			hdc_double;		//������ޯ̧�ݸޗp
	POINT		point_Mouse;	//�}�E�X�̍��W
};

///########## ���O�̍Ē�` ##########
typedef MY_STRUCT_GAME_WINDOW	MY_WIN;

///��������������������������������������������������������
#pragma once	//��d�C���N���[�h�̖h�~
///��������������������������������������������������������

///########## �O���[�o���ϐ��̐錾�Ə����� ##########

///���������� �{�̂�main.cpp ����������

//����E�B���h�E�\���̂̕ϐ�
extern MY_WIN MyWin;

///���������� �{�̂�main.cpp ����������

///########## �O�� �֐� �Q�Ƃ̐錾 ##########

///���������� �{�̂�main.cpp ����������

//�E�B���h�E�v���V�[�W��
extern LRESULT CALLBACK MY_WndProc(HWND, UINT, WPARAM, LPARAM);

//�E�B���h�E�𐶐�����
extern BOOL MY_CreateWindowClass(HINSTANCE);

//�����̃E�B���h�E�N���X���쐬�A�o�^����֐�
extern BOOL MY_CreateWindow(HINSTANCE);

//�N���C�A���g�̈��ݒ肷��
extern VOID MY_SetClientSize(VOID);

//�_�u���o�b�t�@�����O�̐ݒ������
extern VOID MY_SetDoubleBufferring(VOID);

///���������� �{�̂�main.cpp ����������
