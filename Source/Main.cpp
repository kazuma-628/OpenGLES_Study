/*------------------------------------------------------------------------------------------
 *�@���v���O����������
 *	OpenGLES�̕׋����n�߂悤�Ƃ���l�����̃v���W�F�N�g�ł��B
 *�@�܂����n�߂ŉ����ł��܂��񂪁i�Œ���̓���m�F�����ł��܂���j�A
 *	����A�s����ȒP�ɐݒ�ł���悤�ɂ�����A�}�E�X�ł̑���ȂǗl�X�ȋ@�\��񋟂��Ă����\��ł��B
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

	//�V�F�[�_�[�̓ǂݍ��݂��s��
	//�uShader�v�t�H���_�Ɋi�[����Ă���K�v������܂��B
	GLint shader_program = Shader_CreateProgram("Main.vert", "Main.frag");

	GLint attr_pos = glGetAttribLocation(shader_program, "attr_pos");
	assert(attr_pos >= 0);

	GLint attr_color = glGetAttribLocation(shader_program, "attr_color");
	assert(attr_color >= 0);

	// �V�F�[�_�[�̗��p���J�n����
	glUseProgram(shader_program);
	assert(glGetError() == GL_NO_ERROR);

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
	// GLFW������
	assert(GL_TRUE == glfwInit());

	//�v���O�����I�����̏�����o�^����iGLFW�̏I������������j
	atexit(glfwTerminate);

	//OpenGL�̃o�[�W�����y�уv���t�@�C���w��
	//OpenGLES3.0���w�肵�����Ƃ��낾���ANSIGHT���g�p���邽�߂ɁAGLES3.0�ɑΉ�����GL4.3���w�肷��
	//�o�[�W��������ύX�������Ƃ��́uglfwWindowHint�v�Ō�������΂킩��Ǝv���܂��B
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//�E�B���h�E����
	GLFWwindow *const window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLES_Study", NULL, NULL);
	assert(NULL != window);

	// �쐬�����E�B���h�E��OpenGL�̏����Ώۂɂ���
	glfwMakeContextCurrent(window);

	// GLEW������������
	glewExperimental = GL_TRUE;
	assert(GLEW_OK == glewInit());

	// �J���[�o�b�t�@�̓���ւ��^�C�~���O�i�ʏ��1����́j
	glfwSwapInterval(1);

	return window;
}