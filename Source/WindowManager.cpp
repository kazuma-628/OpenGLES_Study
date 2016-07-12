#include "WindowManager.h"

/////////////////////////////////////////////
//static�ϐ��̎��̂��`

Size WindowManager::m_WindowSize;			//�}�E�X�{�^���̏��

//�R���X�g���N�^
WindowManager::WindowManager()
{
	m_window = NULL;
	memset(&m_WindowSize, 0, sizeof(m_WindowSize));
}

//�f�X�g���N�^
WindowManager::~WindowManager()
{
	glfwDestroyWindow(m_window);
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�E�B���h�E���쐬����
*	�@�� �E�B���h�E�𕡐��������邱�Ƃɂ͂܂��Ή����Ă��Ȃ��̂Œ��� ��
*	����
*	�@p_Width	�F[I/ ]�@�E�B���h�E�̕�
*	�@p_Height	�F[I/ ]�@�E�B���h�E�̍���
*	�@p_Title	�F[I/ ]�@�E�B���h�E�̖��O�i�E�B���h�E�����^�X�N�o�[�ɕ\�������j
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void WindowManager::CreateNewWindow(const int p_Width, const int p_Height, const char* p_Title)
{

	//////////////////////////////////////////////////////
	//	GLFW������

	// GLFW�������ƃG���[�`�F�b�N
	printf("GLFW�̏��������J�n���܂�... ");
	if (GL_TRUE != glfwInit())
	{
		ERROR_MESSAGE("GLFW�̏������Ɏ��s���܂���");
	}
	printf("����\n");

	//�v���O�����I�����̏�����o�^����iGLFW�̏I������������j
	atexit(glfwTerminate);

	//OpenGL�̃o�[�W�����y�уv���t�@�C���w��
	//OpenGLES3.0���w�肵�����Ƃ��낾���ANSIGHT�i�f�o�b�J�c�[���j���g�p���邽�߂ɁAGLES3.0�ɑΉ�����GL4.3���w�肷��
	//�o�[�W��������ύX�������Ƃ��́uglfwWindowHint�v�Ō�������΂킩��Ǝv���܂��B
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


	//////////////////////////////////////////////////////
	//	�E�B���h�E����

	//�����ŃE�B���h�E�T�C�Y���w�肵�Ă��܂��B�T�C�Y��ύX�������ꍇ��Define�l��ύX���Ă��������B
	printf("�E�B���h�E�i%d �~ %d�j�̐������J�n���܂�... ", p_Width, p_Height);
	GLFWwindow *const window = glfwCreateWindow(p_Width, p_Height, p_Title, NULL, NULL);

	//�E�B���h�E�������ł��Ă��邩�`�F�b�N
	if (NULL == window)
	{
		ERROR_MESSAGE("�E�B���h�E�����Ɏ��s���܂����B\n"\
			"�O���t�B�b�N��OpenGLES�ɑΉ����Ă��Ȃ��\��������܂��B\n"\
			"�O���t�B�b�N�h���C�o���ŐV�ɂ��Ă݂Ă��������B\n"\
			"����ł��_���ȏꍇ�́A�c�O�Ȃ��炨�g���̊��ł͎g�p���邱�Ƃ��ł��܂���B\n"\
			"�ݒ�ł́AOpenGLES3.0�ɑΉ�����OpenGL4.3��ݒ肵�Ă��܂��B\n"\
			"���g���̊����Ή����Ă��邩�l�b�g�ȂǂŒ��ׂĂ݂Ă��������B");
	}
	printf("����\n");

	// �쐬�����E�B���h�E��OpenGL�̏����Ώۂɂ���
	glfwMakeContextCurrent(window);

	// �J���[�o�b�t�@�̓���ւ��^�C�~���O�i�ʏ��1����́j
	glfwSwapInterval(1);

	//////////////////////////////////////////////////////
	//	�E�B���h�E�T�C�Y���ω��������p�̃R�[���o�b�N��o�^

	glfwSetWindowSizeCallback(window, WindowManager::WindowSizeCallback);

	//////////////////////////////////////////////////////
	//	GLEW������

	// GLEW������������
	printf("GLEW�̏��������J�n���܂�... ");
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		ERROR_MESSAGE("GLEW�̏������Ɏ��s���܂����B");
	}
	printf("����\n");
	
	//////////////////////////////////////////////////////
	//	������������ۑ�

	//���������E�B���h�E�n���h����ۑ�
	m_window = window;

	//�����������̃E�B���h�E�̕�������ۑ�
	m_WindowSize.Width = p_Width;
	m_WindowSize.Height = p_Height;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�E�B���h�E�ɕ`�悷��i�t�����g�o�b�t�@ / �o�b�N�o�b�t�@ ���ʁj
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void WindowManager::DrawingOnWindow(void)
{
	glfwSwapBuffers(m_window);
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�E�B���h�E�T�C�Y���ω��������ɃR�[���o�b�N�����֐�
*	����
*	�@p_window	�F[I/ ]�@�E�B���h�E�n���h��
*	�@p_Width	�F[I/ ]�@�E�B���h�E�̕�
*	�@p_Height	�F[I/ ]�@�E�B���h�E�̍���
*	�@�ڍׂ͉��LURL�Q�Ƃ̂���
*	�@http://www.glfw.org/docs/latest/group__window.html#gaaca1c2715759d03da9834eac19323d4a
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void WindowManager::WindowSizeCallback(GLFWwindow* p_window, int p_Width, int p_Height)
{
	//�����������̃E�B���h�E�̕�������ۑ�
	m_WindowSize.Width = p_Width;
	m_WindowSize.Height = p_Height;
}