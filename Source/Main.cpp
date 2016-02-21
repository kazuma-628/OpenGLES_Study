/*------------------------------------------------------------------------------------------
 *�@���v���O����������
 *	OpenGLES�̕׋����n�߂悤�Ƃ���l�����̃v���W�F�N�g�ł��B
 *�@�܂����n�߂ŉ����ł��܂��񂪁i�Œ���̓���m�F�����ł��܂���j�A
 *	����A�s����ȒP�ɐݒ�ł���悤�ɂ�����A�}�E�X�ł̑���ȂǗl�X�ȋ@�\��񋟂��Ă����\��ł��B
 *
 *	�ϐ����ɂ���
 *	�E�u p_ �v�Ŏn�܂���̂͊֐��̈����i�p�����[�^�[�j��\���Ă��܂��B
 *	�E�u m_ �v�Ŏn�܂���̂̓N���X�̕ϐ��i�����o�j��\���Ă��܂��B
 *
 *	DEBUG�p�̃��b�Z�[�W�����ɂ���
 *	�EERROR_MESSAGE("�����Ƀe�L�X�g���L�q���܂�");	//���s�s�\�ȃG���[�����������ꍇ�A���b�Z�[�W�{�b�N�X��\�����܂�
	�Eprintf("�����Ƀe�L�X�g���L�q���܂�");			//���s�s�\�ȃG���[�ȊO��printf�ŕ��ʂɕ\�����Ă�������
 *------------------------------------------------------------------------------------------*/

#include "Main.h"
#include "ShaderCreateProgram.h"

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
	GLFWwindow *const window = OpenGLES_init();

	//Main�V�F�[�_�[�p�̃I�u�W�F�N�g����
	ShaderManager *MainShader = new ShaderManager;

	//�V�F�[�_�[�̓ǂݍ��݂��s��
	//�uShader�v�t�H���_�Ɋi�[����Ă���K�v������܂��B
	MainShader->CreateShaderProgram("Main.vert", "Main.frag");
	
	GLint attr_pos = MainShader->GetAttribLocation("attr_pos");

	GLint attr_color = MainShader->GetAttribLocation("attr_color");

	// �V�F�[�_�[�v���O�����̗��p���J�n����
	glUseProgram(MainShader->GetShaderProgram());
	if (GL_NO_ERROR != glGetError())
	{
		ERROR_MESSAGE("�V�F�[�_�[�v���O�����̗��p�Ɏ��s���܂����B");
	}

	//�V�F�[�_�[�̕ϐ���L����
	glEnableVertexAttribArray(attr_pos);
	glEnableVertexAttribArray(attr_color);


	// ��ʒ����֕`�悷��
	const GLfloat position[] =
	{
		// v0
		-0.5f, 0.5f,
		// v1
		0.5f, 0.5f,
		// v2
		0.5f, -0.5f,
		// v3
		-0.5, -0.5
	};

	// ���_�J���[��ݒ肷��
	const GLubyte color[] =
	{
		// v0 rgb
		200, 200, 200,
		// v1 rgb
		200, 0, 0,
		// v2 rgb
		0, 200, 0,
		// v3 rgb
		0, 0, 200
	};



	//�w�i�F�w��
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	int count = 0;
	//�E�B���h�E���J���Ă���Ԃ̓��[�v
	while (glfwWindowShouldClose(window) == GL_FALSE)
	{
		//�F������
		glClear(GL_COLOR_BUFFER_BIT);

		//�r���[�|�[�g��ݒ肷��
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		//�ϐ���]��
		glVertexAttribPointer(attr_pos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
		glVertexAttribPointer(attr_color, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, color);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		//�`�揈��
		glfwSwapBuffers(window);

		//�C�x���g���o��
		glfwPollEvents();
	}

	//�I������
	delete MainShader;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@OpenGL�̏��������s��
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�E�B���h�E�n���h��
*-------------------------------------------------------------------------------*/
GLFWwindow *const OpenGLES_init()
{

	// GLFW�������ƃG���[�`�F�b�N
	printf("GLFW�̏��������J�n���܂�... ");
	if(GL_TRUE != glfwInit())
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

	//�E�B���h�E����
	//�����ŃE�B���h�E�T�C�Y���w�肵�Ă��܂��B�T�C�Y��ύX�������ꍇ��Define�l��ύX���Ă��������B
	printf("�E�B���h�E�i%d �~ %d�j�̐������J�n���܂�... ", WINDOW_WIDTH, WINDOW_HEIGHT);
	GLFWwindow *const window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLES_Study", NULL, NULL);
	
	//�E�B���h�E�������ł��Ă��邩�`�F�b�N
	if(NULL == window)
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

	// GLEW������������
	printf("GLEW�̏��������J�n���܂�... ");
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		ERROR_MESSAGE("GLEW�̏������Ɏ��s���܂����B");
	}
	printf("����\n");

	// �J���[�o�b�t�@�̓���ւ��^�C�~���O�i�ʏ��1����́j
	glfwSwapInterval(1);

	return window;
}