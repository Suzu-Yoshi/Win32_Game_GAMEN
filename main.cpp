///����������������������������������������
//main.cpp
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########
#include "main.h"
#include "fps.h"
#include "winproc.h"

///########## ���C�u�����ǂݍ��� ##########

///########## �}�N����` ##########

///########## �񋓌^ ##########

///########## �\���� ##########

///########## ���O�̍Ē�` ##########

///########## �O���[�o���ϐ��̐錾�Ə����� ##########

//����E�B���h�E�\���̂̕ϐ�
MY_WIN MyWin;

///########## �v���g�^�C�v�錾 ##########

//�E�B���h�E�𐶐�����
BOOL MY_CreateWindowClass(HINSTANCE);

//�����̃E�B���h�E�N���X���쐬�A�o�^����֐�
BOOL MY_CreateWindow(HINSTANCE);

//�N���C�A���g�̈��ݒ肷��
VOID MY_SetClientSize(VOID);

//�_�u���o�b�t�@�����O�̐ݒ������
VOID MY_SetDoubleBufferring(VOID);

///########## ���C���֐� ##########
//���@���F�A�v���P�[�V�����̃C���X�^���X�n���h��
//���@���F�A�v���P�[�V�����̑O�̃C���X�^���X�n���h��(Win32�͏��NULL)
//���@���F�R�}���h���C�������̕�����
//���@���F�E�B���h�E�̕\�����
//�߂�l�F���b�Z�[�W��wParam
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdShow)
{

	//�I���`�F�b�N
	BOOL CheckError;

	//�����̃E�B���h�E�N���X���쐬�A�o�^����֐�
	CheckError = FALSE;		//�`�F�b�N������
	CheckError = MY_CreateWindowClass(hInstance);

	//�o�^���ł��Ȃ�������v���O�������I������
	if (CheckError == FALSE) { return -1; }

	//�E�B���h�E�𐶐�����(�T�C�Y�ύX�Ȃ�)
	MyWin.win_mode = (int)WIN_RESZ_NG;	//�E�B���h�E�\�����[�h��ݒ�
	CheckError = FALSE;					//�`�F�b�N������
	CheckError = MY_CreateWindow(hInstance);

	//�E�B���h�E����������Ȃ�������v���O�������I������
	if (MyWin.hwnd == NULL) { return -1; }

	//�N���C�A���g�̈���Đݒ肷��
	MY_SetClientSize();

	//�_�u���o�b�t�@�����O�̐ݒ������
	MY_SetDoubleBufferring();

	//�E�B���h�E��\��
	ShowWindow(MyWin.hwnd, SW_SHOW);

	/*
	//�E�B���h�E�N���X��o�^�ł��Ȃ������Ƃ�
	if (!RegisterClass(&MyWin.winc))
	{
		//���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, ERR_MSG_NO_WIN_CLASS, ERR_MSG_TITLE, MB_OK);

		return FALSE;
	}*/

	//�������[�v
	while (true)
	{
		//���b�Z�[�W���u���b�Z�[�W�L���[�v�ɂ��邩���f����
		if (PeekMessage(&MyWin.msg, NULL, 0, 0, PM_REMOVE))
		{
			//���b�Z�[�W���u���b�Z�[�W�L���[�v�ɂ���Ƃ�

			//����{�^�����������Ƃ��͖������[�v���甲����
			if (MyWin.msg.message == WM_QUIT)
			{
				break;
			}

			//���z�L�[�R�[�h�����ۂ̕����ɕϊ�����
			TranslateMessage(&MyWin.msg);

			//���b�Z�[�W���E�B���h�E�v���V�[�W���ɑ���
			DispatchMessage(&MyWin.msg);
		}
		else
		{
			//���b�Z�[�W���u���b�Z�[�W�L���[�v�ɂȂ��Ƃ�

			//���Ԏ擾
			MY_FPS_UPDATE();

			//WM_PAINT�𔭐�
			InvalidateRect(MyWin.hwnd, NULL, FALSE);

			//�w�肵��FPS�ɂȂ�悤�ɑ҂�
			MY_FPS_WAIT();
		}
	}

	return (int)MyWin.msg.wParam;
}

///########## �����̃E�B���h�E�N���X���쐬�A�o�^����֐� ##########
//���@���F���C���֐��̃C���X�^���X�n���h��
//�߂�l�FTRUE �F����I�� / FALSE�F�ُ�I��
BOOL MY_CreateWindowClass(HINSTANCE hInstance)
{
	//�u���V���쐬
	HBRUSH brush;

	//�u���V�̐F��ݒ�
	brush = CreateSolidBrush(RGB(255, 255, 255));

	//�E�B���h�E�N���X�̐ݒ�͂�������
	MyWin.winc.style = CS_HREDRAW | CS_VREDRAW;
	MyWin.winc.lpfnWndProc = MY_WndProc;			//����̃E�B���h�E�v���V�[�W��
	MyWin.winc.cbClsExtra = 0;
	MyWin.winc.cbWndExtra = 0;
	MyWin.winc.hInstance = hInstance;				//���C���֐��̃C���X�^���X�n���h��
	MyWin.winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	MyWin.winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	MyWin.winc.hbrBackground = brush;				//�u���V�̐F��ݒ�
	MyWin.winc.lpszMenuName = NULL;
	MyWin.winc.lpszClassName = TEXT(MY_WIN_CLASS);	//����̃E�B���h�E�N���X�̖��O

	//�u���V���폜
	DeleteObject(brush);

	//�E�B���h�E�N���X��o�^�ł��Ȃ������Ƃ�
	if (!RegisterClass(&MyWin.winc))
	{
		//���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, ERR_MSG_NO_WIN_CLASS, ERR_MSG_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

///########## �E�B���h�E�𐶐�����֐� ##########
//���@���F���C���֐��̃C���X�^���X�n���h��
//�߂�l�FTRUE �F����I�� / FALSE�F�ُ�I��
BOOL MY_CreateWindow(HINSTANCE hInstance)
{
	switch (MyWin.win_mode)
	{
	case WIN_RESZ_OK:
		//�E�B���h�E�̃T�C�Y�ύX���ł���

		//�E�B���h�E���쐬����
		MyWin.hwnd = CreateWindow(
			TEXT(MY_WIN_CLASS),
			TEXT(GAME_TITLE),
			WS_OVERLAPPEDWINDOW,
			GAME_LEFT,
			GAME_TOP,
			GAME_RIGHT,
			GAME_BOTTOM,
			NULL,
			NULL,
			hInstance,
			NULL);
		break;

	case WIN_RESZ_NG:
		//�E�B���h�E�̃T�C�Y�ύX���ł��Ȃ�

		//�E�B���h�E���쐬����
		MyWin.hwnd = CreateWindow(
			TEXT(MY_WIN_CLASS),
			TEXT(GAME_TITLE),
			WS_STATIC_WINDOW,
			GAME_LEFT,
			GAME_TOP,
			GAME_RIGHT,
			GAME_BOTTOM,
			NULL,
			NULL,
			hInstance,
			NULL);
		break;

	case WIN_NO_TITLE:
		//�E�B���h�E�̃^�C�g����\�����Ȃ�

		//�E�B���h�E���쐬����
		MyWin.hwnd = CreateWindow(
			TEXT(MY_WIN_CLASS),
			TEXT(GAME_TITLE),
			WS_NOT_TITLE,
			GAME_LEFT,
			GAME_TOP,
			GAME_RIGHT,
			GAME_BOTTOM,
			NULL,
			NULL,
			hInstance,
			NULL);
		break;
	}

	//�E�B���h�E����������Ȃ������Ƃ�
	if (MyWin.hwnd == NULL)
	{
		//���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, ERR_MSG_NO_WIN_CREATE, ERR_MSG_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

///########## �N���C�A���g�̈�̐ݒ������֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_SetClientSize(VOID)
{
	//��ʂ̕\���̈�𒲐�����\����
	RECT rect_set;

	//�ŏ��̃N���C�A���g�̗̈��ݒ�
	rect_set.top = GAME_TOP;
	rect_set.left = GAME_LEFT;
	rect_set.bottom = GAME_BOTTOM;
	rect_set.right = GAME_RIGHT;

	//�f�X�N�g�b�v�̑傫�����擾����\����
	RECT Desktop_rect;

	//�f�X�N�g�b�v�̃��[�N�G���A�̈���擾
	SystemParametersInfo(SPI_GETWORKAREA, 0, &Desktop_rect, 0);

	//�E�B���h�E����ʒ����ɕ\������Ƃ��g�p
	int Client_width_half;
	int Client_height_half;
	int Desktop_width_half;
	int Desktop_height_half;

	//�E�B���h�E�̈���擾
	GetWindowRect(MyWin.hwnd, &MyWin.win_rect_win);

	//�N���C�A���g�̈���擾
	GetClientRect(MyWin.hwnd, &MyWin.win_rect_cli);

	//�N���C�A���g�̈�̕����C��
	rect_set.right += (
		(MyWin.win_rect_win.right - MyWin.win_rect_win.left)	// (�E�C���h�E  �̉��T�C�Y) 
		- (MyWin.win_rect_cli.right - MyWin.win_rect_cli.left)	//-(�N���C�A���g�̉��T�C�Y)
		);

	//�N���C�A���g�̈�̍������C��
	rect_set.bottom += (
		(MyWin.win_rect_win.bottom - MyWin.win_rect_win.top)	// (�E�C���h�E  �̏c�T�C�Y)
		- (MyWin.win_rect_cli.bottom - MyWin.win_rect_cli.top)	//-(�N���C�A���g�̏c�T�C�Y)
		);

	//�E�B���h�E����ʒ����ɕ\��

	//�f�X�N�g�b�v�̈�̕��̔����̒l���擾
	Desktop_width_half = (Desktop_rect.right - Desktop_rect.left) / 2;
	//�f�X�N�g�b�v�̈�̍����̔����̒l���擾
	Desktop_height_half = (Desktop_rect.bottom - Desktop_rect.top) / 2;

	//�N���C�A���g�̈�̕��̔����̒l���擾
	Client_width_half = (rect_set.right - rect_set.left) / 2;
	//�N���C�A���g�̈�̍����̔����̒l���擾
	Client_height_half = (rect_set.bottom - rect_set.top) / 2;

	//�f�X�N�g�b�v�̒���(��)���v�Z
	rect_set.left = Desktop_width_half - Client_width_half;
	//�f�X�N�g�b�v�̒���(�c)���v�Z
	rect_set.top = Desktop_height_half - Client_height_half;

	//�N���C�A���g�̈�̏ꏊ�ƃT�C�Y���Đݒ�
	SetWindowPos(
		MyWin.hwnd,				//�E�B���h�E�n���h��
		HWND_TOP,				//�E�B���h�E��O�̖ʂɂ���
		rect_set.left,			//�E�B���h�E��X���W
		rect_set.top,			//�E�B���h�E��Y���W
		rect_set.right,			//�E�B���h�E�̕�
		rect_set.bottom,		//�E�B���h�E�̍���
		SWP_SHOWWINDOW);		//�E�B���h�E��\��

	//���������E�B���h�E�̈���擾
	GetWindowRect(MyWin.hwnd, &MyWin.win_rect_win);

	//���������N���C�A���g�̈���擾
	GetClientRect(MyWin.hwnd, &MyWin.win_rect_cli);

	return;
}

///########## �_�u���o�b�t�@�����O�̐ݒ������֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_SetDoubleBufferring(VOID)
{
	// �E�C���h�E�̃f�o�C�X�R���e�L�X�g�̃n���h�����擾
	HDC hdc = GetDC(MyWin.hwnd);

	//�������̒��Ƀf�o�C�X�R���e�L�X�g�̃n���h�����쐬
	MyWin.hdc_double = CreateCompatibleDC(hdc);

	//�������̒��ɉ摜���쐬
	MyWin.hbmp_double = CreateCompatibleBitmap(
		hdc,
		MyWin.win_rect_cli.right,
		MyWin.win_rect_cli.bottom);

	//�f�o�C�X�R���e�L�X�g�ɉ摜��ݒ�
	SelectObject(MyWin.hdc_double, MyWin.hbmp_double);

	return;
}