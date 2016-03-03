#include "WindowManager.h"

//�R���X�g���N�^
WindowManager::WindowManager()
{
	m_window = NULL;
}

//�f�X�g���N�^
WindowManager::~WindowManager()
{

}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�E�B���h�E���쐬����
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
	printf("�E�B���h�E�i%d �~ %d�j�̐������J�n���܂�... ", WINDOW_WIDTH, WINDOW_HEIGHT);
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
	m_Width = p_Width;
	m_Height = p_Height;
}