/*------------------------------------------------------------------------------------------
*�@���v���O����������
*	OpenGLES�̕׋����n�߂悤�Ƃ���l�����̃v���W�F�N�g�ł��B
*�@�܂����n�߂ŉ����ł��܂��񂪁i�Œ���̓���m�F�����ł��܂���j�A
*	����A�s����ȒP�ɐݒ�ł���悤�ɂ�����A�}�E�X�ł̑���ȂǗl�X�ȋ@�\��񋟂��Ă����\��ł��B
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
*	DEBUG�p�̃��b�Z�[�W�����ɂ���
*	�EERROR_MESSAGE("�����Ƀe�L�X�g���L�q���܂�");	//���s�s�\�ȃG���[�����������ꍇ�A���b�Z�[�W�{�b�N�X��\�����܂�
*	�Eprintf("�����Ƀe�L�X�g���L�q���܂�");			//���s�s�\�ȃG���[�ȊO��printf�ŕ��ʂɕ\�����Ă�������
*------------------------------------------------------------------------------------------*/

#include "Main.h"

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
	//OpenGL�̏����� �� �E�B���h�E�n���h���̎擾
	/*
	GLFWwindow *const m_window = OpenGLES_init();
	GLFWwindow *const m_window2 = OpenGLES_init();
	GLFWwindow *const m_window3 = OpenGLES_init();
	*/

	//////////////////////////////////////////////////////
	//	�e�I�u�W�F�N�g����

	//���C���`��p�̃I�u�W�F�N�g����
	MainDraw *m_MainDraw = new MainDraw;

	//Key�Ǘ��p�̃I�u�W�F�N�g����
	KeyManager *m_KeyManager = new KeyManager;

	//�E�B���h�E�Ǘ��p�̃I�u�W�F�N�g����
	WindowManager *m_WindowManager = new WindowManager;


	//////////////////////////////////////////////////////
	//	�e�I�u�W�F�N�g������
	
	//�L�[�Ǘ��p�̃I�u�W�F�N�g�������i�}�E�X��L�[�{�[�h����̃R�[���o�b�N�Ȃǂ�o�^�j
	m_KeyManager->Initialize();

	//�E�C���h�E���쐬
	m_WindowManager->CreateNewWindow();

	//���C���`�揀��
	m_MainDraw->Prepare();

	//////////////////////////////////////////////////////
	//	���C�����[�v

	//�쐬�����E�B���h�E�n���h�����擾
	GLFWwindow* const Window = m_WindowManager->GetWindow();

	//�E�B���h�E���J���Ă���Ԃ̓��[�v
	while (glfwWindowShouldClose(Window) == GL_FALSE)
	{
		//�C�x���g���o���i�}�E�X��ԂȂǂ̃C�x���g���擾�j
		glfwPollEvents();

		//���C���`��J�n
		m_MainDraw->Drawing(Window);
	}

	//////////////////////////////////////////////////////
	//	���������I�u�W�F�N�g�̔j��

	//�I������
	delete m_MainDraw;
	delete m_KeyManager;
	delete m_WindowManager;
}