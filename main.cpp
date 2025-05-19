//==================================================================
//
//C++��DirectX [main.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "main.h"
#include "manager.h"

//================================================
//�O���[�o���ϐ�
//================================================

//================================================
//���C���֐�
//================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	CManager* pManager = NULL;

	DWORD dwCurrentTime;							//���ݎ���
	DWORD dwExecLastTime;							//�Ō�ɏ�����������

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),							//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,									//�E�B���h�E�̃X�^�C��
		WindowProc,									//�E�B���h�E�v���V�[�W��
		0,											//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,											//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,									//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),				//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),					//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),					//�N���C�A���g�̈�̔w�i�F
		NULL,										//���j���[�o�[
		CLASS_NAME,									//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)				//�t�@�C���̃A�C�R��
	};

	HWND hWnd;//�E�B���h�E�n���h��(���ʎq)
	MSG msg;//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//��ʃT�C�Y�̍\����

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,						//�g���E�B���h�E�X�^�C��
		CLASS_NAME,									//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,								//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,						//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,								//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,								//�E�B���h�E�̍���Y���W
		(rect.right - rect.top),					//�E�B���h�E�̕�
		(rect.bottom - rect.top),					//�E�B���h�E�̍���
		NULL,										//�e�E�B���h�E�̃n���h��
		NULL,										//���j���[�n���h���܂��͏��E�B���h�EID
		hInstance,									//�C���X�^���X�n���h��
		NULL);										//�E�B���h�E�쐬�f�[�^

	//�}�l�[�W���̐���
	pManager = new CManager;

	//�}�l�[�W���̏���������
	pManager->Init(hWnd, TRUE);

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;								//����������
	dwExecLastTime = timeGetTime();					//���ݎ������擾(�ۑ�)

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);						//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);								//�N���C�A���g�̈���X�V


	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				TranslateMessage(&msg);				//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);				//�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;		//�����J�n�̎���[���ݎ���]��ۑ�
				//�X�V����
				pManager->Update();

				//�`�揈��
				pManager->Draw();
			}
		}
	}

	//�}�l�[�W���̔j��
	if (pManager != NULL)
	{
		//�}�l�[�W���̏I������
		pManager->Uninit();

		delete pManager;

		pManager = NULL;
	}

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:								//�E�B���h�E�j���̃��b�Z�[�W
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:								//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:								//[Esc]�L�[�������ꂽ
			//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//�K��̏�����Ԃ�
}