/*------------------------------------------------------------------------------------------
*�@���v���O����������
*	OpenGLES�̕׋����n�߂悤�Ƃ���l�����̃v���W�F�N�g�ł��B
*�@�܂����n�߂ł��܂�o���邱�Ƃ�����܂��񂪁A���֗��ɂȂ�悤�l�X�ȋ@�\��񋟂��Ă����\��ł��B
*
*	�֐��ɂ���
*�@�uShaderManager�v�N���X�́A��{�I��OpenGLES�̃R�}���h�������ƊȒP�Ɏg����悤�ɂ������́i�⏕�֐��j�ł��B
*�@�V�F�[�_�[�\�[�X�̓ǂݍ��݂�G���[�����A�v���O�����I�u�W�F�N�g�̏�ԊǗ��Ȃǂ��ꌳ�����ĕ�����₷�����܂����B
*�@�ugl�R�}���h�v���́ugl�v����������̂��⏕�֐����ƂȂ��Ă���ꍇ�������̂ł��B�iglUseProgram �� UseProgram �Ȃǁj
*	�����ACreateShaderProgram�͕ʂŁA���ł��낢�돈�����Ă��܂��B�������܂�̏������قƂ�ǂȂ̂ŋC�ɂ��Ȃ��Ă悢�ł��B
*�@�Ƃ肠�����A�t�@�C�������w�肵����A��������v���O�����I�u�W�F�N�g���쐬���Ă����񂾂Ȓ��x�Ŗ�肠��܂���B
*
*	�ϐ����ɂ���
*	�E�u p_ �v�Ŏn�܂���̂͊֐��̈����i�p�����[�^�[�j��\���Ă��܂��B
*	�E�u m_ �v�Ŏn�܂���̂̓N���X�̕ϐ��i�����o�j��\���Ă��܂��B�imain�֐��͓��ʂɃN���X�łȂ��Ă��t�^���Ă܂��j
*
*	����ɂ���
*	�@�E�N���b�N �y�� ���N���b�N �y�� �X�N���[���̑���ɑΉ����Ă��܂��B
*	�@�T���v���v���O�����ł́A�u�E�N���b�N = �ړ��A���N���b�N = ��]�A�X�N���[�� = �g��A�X�y�[�X = �����ʒu�v�ƂȂ��Ă��܂��B
*
*	DEBUG�p�̃��b�Z�[�W�����ɂ���
*	�EERROR_MESSAGE("�����Ƀe�L�X�g���L�q���܂�");	//���s�s�\�ȃG���[�����������ꍇ�͂��̃}�N�����g�p���邱�ƂŃ��b�Z�[�W�{�b�N�X��\���ł��܂�
*	�Eprintf("�����Ƀe�L�X�g���L�q���܂�");			//���s�s�\�ȃG���[�ȊO��printf�ŕ��ʂɕ\�����Ă�������
*------------------------------------------------------------------------------------------*/

#include "Main.h"

typedef struct
{
	Vec2 OldPosition;				//�y1�C�x���g�O�z�}�E�X�̃J�[�\�����W
	Vec2 OldScrollAmount;			//�y1�C�x���g�O�z�X�N���[���̍��v�ʁA������Ԃ�[x:0�i��[���E]�X�N���[���j][y:0�i�c[�㉺]�X�N���[���j]�ŁA
									//�@�X�N���[�������������l���~�ρi���Z/���Z�j����Ă���
}TmpGlobalData;

static TmpGlobalData TmpGlobal = { 0 };

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@���C���G���g���[�|�C���g
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void main(void)
{
	//////////////////////////////////////////////////////
	//	�e�I�u�W�F�N�g����

	//�E�B���h�E�Ǘ��p�̃I�u�W�F�N�g����
	WindowManager *m_WindowManager = new WindowManager;

	//�f�o�C�X�Ǘ��p�̃I�u�W�F�N�g����
	DeviceManager *m_DeviceManager = new DeviceManager;

	//���\�[�X�Ǘ��p�̃I�u�W�F�N�g����
	//�����̃I�u�W�F�N�g�𒼐ڑ��삷�邱�Ƃ͂Ȃ����A
	//�@�R���X�g���N�^�ƃf�X�g���N�^�𖾎��I�ɃR�[�������邽�߂ɐ�������
	ResourceManager *m_ResourceManager = new ResourceManager;

	//���f���f�[�^�Ǘ��p�̃I�u�W�F�N�g����
	//�����̃I�u�W�F�N�g�𒼐ڑ��삷�邱�Ƃ͂Ȃ����A
	//�@�R���X�g���N�^�ƃf�X�g���N�^�𖾎��I�ɃR�[�������邽�߂ɐ�������
	ModelManager *m_ModelManager = new ModelManager;

	//�O���[�o���f�[�^����
	GlobalData m_Global = { 0 };

	//////////////////////////////////////////////////////
	//	�e�V�F�[�_�[�I�u�W�F�N�g����

	//���C���`��p�̃I�u�W�F�N�g����
	MainDraw *m_MainDraw = new MainDraw;

	//////////////////////////////////////////////////////
	//	�e�I�u�W�F�N�g������ �y�� ����
	
	//�E�C���h�E���쐬
	//�� �E�B���h�E�𕡐��������邱�Ƃɂ͂܂��Ή����Ă��Ȃ��̂Œ��� ��
	m_WindowManager->CreateNewWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLES_Study");
	//�쐬�����E�B���h�E�n���h�����擾
	GLFWwindow* const window = m_WindowManager->GetWindow();

	//�f�o�C�X�Ǘ��p�̃I�u�W�F�N�g�������i�}�E�X��L�[�{�[�h����̃R�[���o�b�N�Ȃǂ�o�^�j
	//���̊֐��R�[���̑O�ɃE�B���h�E����������Ă���K�v������
	//�� �E�B���h�E�𕡐��������āA���ꂼ��Key�Ǘ����邱�Ƃ͂܂��Ή����Ă��Ȃ��̂Œ��� ��
	m_DeviceManager->Initialize(window);

	//���C���`�揀��
	m_MainDraw->Prepare();

	//////////////////////////////////////////////////////
	//	�`�惁�C�����[�v

	//�E�B���h�E���J���Ă���Ԃ̓��[�v
	while (GL_FALSE == m_WindowManager->GetWindowShouldClose())
	{
		//�C�x���g���o���i�}�E�X��ԂȂǂ̃C�x���g���擾�j
		glfwPollEvents();

		//�`��ɕK�v�Ȋe�����ݒ�/�X�V
		SetVarietyOfInformation(m_WindowManager, m_DeviceManager, &m_Global);

		//���C���`��J�n
		m_MainDraw->Drawing(&m_Global);

		//�`�攽�f����
		m_WindowManager->DrawingOnWindow();

		//GL�G���[�`�F�b�N
		if (GL_NO_ERROR != GL_GET_ERROR())
		{
			ERROR_MESSAGE("�v���O�������̂ǂ�����GL�֘A�̃G���[���������܂����B\n������ǋ����Ă�������\n");
		}
	}

	//////////////////////////////////////////////////////
	//	���������I�u�W�F�N�g�̔j��

	//�I������
	delete m_MainDraw;
	delete m_WindowManager;
	delete m_DeviceManager;
	delete m_ResourceManager;
	delete m_ModelManager;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�`��ɕK�v�Ȋe�����ݒ�/�X�V����
*	����
*	�@p_WindowManager		�F[I/ ]�@�E�B���h�E�Ǘ��I�u�W�F�N�g
*	�@p_DeviceManager		�F[I/ ]�@�f�o�C�X�Ǘ��I�u�W�F�N�g
*	�@p_Global				�F[ /O]�@�O���[�o���f�[�^
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void SetVarietyOfInformation(WindowManager *p_WindowManager, DeviceManager *p_DeviceManager, GlobalData *p_Global)
{
	//�E�B���h�E�T�C�Y�̎擾
	Size const WindowSize = p_WindowManager->GetWindowSize();
	//�}�E�X�̏����擾
	MouseInfo MouseButton = p_DeviceManager->GetMouseInfo();
	//�L�[�i�L�[�{�[�h�j�̏����擾
	KeyInfo KeyBoard = p_DeviceManager->GetKeyInfo();

	////////////////////////////////////
	// ���C���ƂȂ郂�f���r���[�}�g���N�X�̍쐬�i�匳�̃}�g���N�X�f�[�^�j

	//�I�u�W�F�N�g���ړ������邽�߂̍s��
	Matrix ModelView;

	//3D��Ԃɂ��邽�߂̍s��
	Matrix Projection;

	///////////////////////////////////
	// �I�u�W�F�N�g�ړ��֌W�̏���

	//�X�y�[�X�ŏ����ʒu�ɖ߂�
	if (true == KeyBoard.Change.Key_SPACE)
	{
		memset(&p_Global->Translate, 0, sizeof(p_Global->Translate));
		memset(&p_Global->Rotate, 0, sizeof(p_Global->Rotate));
	}

	//���s�ړ��p�̕ϐ��Ƀ}�E�X���̍��W��������
	if (GLFW_PRESS == MouseButton.Left.State)
	{
		p_Global->Translate.x += MouseButton.Position.x - TmpGlobal.OldPosition.x;
		p_Global->Translate.y += MouseButton.Position.y - TmpGlobal.OldPosition.y;
	}
	//�X�N���[���̓{�^����������Ă��Ȃ��Ă��K������
	p_Global->Translate.z += MouseButton.ScrollAmount.y - TmpGlobal.OldScrollAmount.y;

	//��]�p�̕ϐ��Ƀ}�E�X���̍��W��������
	//�{���ł����360�x��]������ϐ������������������ǂ����A�T���v���Ȃ̂Ŋ���
	if (GLFW_PRESS == MouseButton.Right.State)
	{
		p_Global->Rotate.x += MouseButton.Position.x - TmpGlobal.OldPosition.x;
		p_Global->Rotate.y += MouseButton.Position.y - TmpGlobal.OldPosition.y;
	}

	//�X�ɃL�[�{�[�h�̏���������
	if (GLFW_PRESS == KeyBoard.Change.Key_W)
	{
		p_Global->Translate.y += 1.0f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_S)
	{
		p_Global->Translate.y -= 1.0f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_A)
	{
		p_Global->Translate.x += 1.0f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_D)
	{
		p_Global->Translate.x -= 1.0f;
	}

	//�J�����̉f��ʒu�Ɉړ�������
	ModelView.Translate(0.0, 0.0, -35.0f);
	//�}�E�X�ł̃I�u�W�F�N�g�̈ړ�
	ModelView.Translate(p_Global->Translate.x / 6.0f, -p_Global->Translate.y / 6.0f, p_Global->Translate.z);

	//�}�E�X�ł̃I�u�W�F�N�g�̉�]
	ModelView.Rotate(-p_Global->Rotate.y / 2.0f, 1.0f, 0.0f, 0.0f);
	ModelView.Rotate(-p_Global->Rotate.x / 2.0f, 0.0f, 1.0f, 0.0f);

	//�������e�s��Ŏg�p����l���O���[�o���̈�ɕۑ�
	p_Global->NearClip = 1.0f;
	p_Global->FarClip = 200.0f;
	//�������e�s���K�p����
	Projection.Perspective(-1.0f, 1.0f, -1.0f, 1.0f, p_Global->NearClip, p_Global->FarClip);

	///////////////////////////////////
	// �e�����ۑ�

	//�e��s���ۑ�����
	p_Global->ModelViewMatrix = ModelView.GetMatrix();
	p_Global->ProjectionMatrix = Projection.GetMatrix();

	//�E�B���h�E�T�C�Y��ۑ�
	p_Global->WindowSize.Width = WindowSize.Width;
	p_Global->WindowSize.Height = WindowSize.Height;

	//1�C�x���g�O�̏���ۑ�����
	TmpGlobal.OldPosition.x = MouseButton.Position.x;
	TmpGlobal.OldPosition.y = MouseButton.Position.y;
	TmpGlobal.OldScrollAmount.x = MouseButton.ScrollAmount.x;
	TmpGlobal.OldScrollAmount.y = MouseButton.ScrollAmount.y;
}


