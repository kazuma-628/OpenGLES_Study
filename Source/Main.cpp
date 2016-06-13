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
	//////////////////////////////////////////////////////
	//	�e�I�u�W�F�N�g����

	//���C���`��p�̃I�u�W�F�N�g����
	MainDraw *m_MainDraw = new MainDraw;

	//Key�Ǘ��p�̃I�u�W�F�N�g����
	DeviceManager *m_DeviceManager = new DeviceManager;

	//�E�B���h�E�Ǘ��p�̃I�u�W�F�N�g����
	WindowManager *m_WindowManager = new WindowManager;

	//���f���f�[�^�Ǘ��p�̃I�u�W�F�N�g����
	ModelData *m_ModelData = new ModelData;


	//////////////////////////////////////////////////////
	//	�e�I�u�W�F�N�g������ �y�� ����
	
	//�E�C���h�E���쐬
	//�� �E�B���h�E�𕡐��������邱�Ƃɂ͂܂��Ή����Ă��Ȃ��̂Œ��� ��
	m_WindowManager->CreateNewWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLES_Study");
	//�쐬�����E�B���h�E�n���h�����擾
	GLFWwindow* const window = m_WindowManager->GetWindow();

	//�L�[�Ǘ��p�̃I�u�W�F�N�g�������i�}�E�X��L�[�{�[�h����̃R�[���o�b�N�Ȃǂ�o�^�j
	//���̊֐��R�[���̑O�ɃE�B���h�E����������Ă���K�v������
	//�� �E�B���h�E�𕡐��������āA���ꂼ��Key�Ǘ����邱�Ƃ͂܂��Ή����Ă��Ȃ��̂Œ��� ��
	m_DeviceManager->Initialize(window);

	//���C���`�揀��
	m_MainDraw->Prepare();

	//////////////////////////////////////////////////////
	//	���C�����[�v

	//�E�B���h�E���J���Ă���Ԃ̓��[�v
	while (GL_FALSE == m_WindowManager->GetWindowShouldClose())
	{
		//�C�x���g���o���i�}�E�X��ԂȂǂ̃C�x���g���擾�j
		glfwPollEvents();

		//���C���`��J�n
		m_MainDraw->Drawing(m_WindowManager, m_DeviceManager, m_ModelData);

		//GL�G���[�`�F�b�N
		if (GL_NO_ERROR != GL_GET_ERROR())
		{
			ERROR_MESSAGE("�v���O�������̂ǂ�����GL�֘A�̃G���[���������܂����B\n������ǋ����Ă�������");
		}
	}

	//////////////////////////////////////////////////////
	//	���������I�u�W�F�N�g�̔j��

	//�I������
	delete m_MainDraw;
	delete m_DeviceManager;
	delete m_WindowManager;
	delete m_ModelData;
}