/*------------------------------------------------------------------------------------------
 *�@���v���O����������
 *	OpenGLES�̕׋����n�߂悤�Ƃ���l�����̃v���W�F�N�g�ł��B
 *�@�܂����n�߂ŉ����ł��܂��񂪁i�Œ���̓���m�F�����ł��܂���j�A
 *	����A�s����ȒP�ɐݒ�ł���悤�ɂ�����A�}�E�X�ł̑���ȂǗl�X�ȋ@�\��񋟂��Ă����\��ł��B
 *------------------------------------------------------------------------------------------*/

#include <Main.hpp>

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

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@���_�E�t���O�����g�V�F�[�_�[�������N���AShaderProgram���쐬����
*	����
*	�@vertex_shader_file	�F[I/ ]�@�o�[�e�b�N�X�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
*	�@fragment_shader_file	�F[I/ ]�@�t���O�����g�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
*	�߂�l
*	�@�����N�ς݂̃v���O����
*-------------------------------------------------------------------------------*/
GLuint Shader_CreateProgram(const char* vertex_shader_file, const char* fragment_shader_file)
{

	//�t�@�C������\�[�X��ǂݍ��ށi�uShader�v�t�H���_�Ɋi�[����Ă���K�v������܂��j
	char vertex_shader_source[SHADER_STRING_ALL_MAX] = { 0 };		//���_�V�F�[�_
	Shader_FileLoad(vertex_shader_file, vertex_shader_source, SHADER_STRING_ALL_MAX);
	char fragment_shader_source[SHADER_STRING_ALL_MAX] = { 0 };	//�t���O�����g�V�F�[�_
	Shader_FileLoad(fragment_shader_file, fragment_shader_source, SHADER_STRING_ALL_MAX);

	//�\�[�X���A�b�v���[�h����
	const GLuint vertex_shader = Shader_SourceLoad(vertex_shader_source, GL_VERTEX_SHADER);			//���_�V�F�[�_
	const GLuint fragment_shader = Shader_SourceLoad(fragment_shader_source, GL_FRAGMENT_SHADER);	//�t���O�����g�V�F�[�_

	//Program�̐���
	const GLuint program = glCreateProgram();
	assert(GL_NO_ERROR == glGetError());
	assert(program != 0);

	glAttachShader(program, vertex_shader);		// �o�[�e�b�N�X�V�F�[�_�[�ƃv���O�������֘A�t����
	glAttachShader(program, fragment_shader);	// �t���O�����g�V�F�[�_�[�ƃv���O�������֘A�t����
	assert(GL_NO_ERROR == glGetError());

	// �R���p�C�����s��
	glLinkProgram(program);

	// �����N�G���[���`�F�b�N����
	GLint linkSuccess = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
	if (GL_FALSE == linkSuccess) {
		// �G���[����������
		GLint infoLen = 0;
		// �G���[���b�Z�[�W���擾
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			GLchar *message = (GLchar*)calloc(infoLen, sizeof(GLchar));
			glGetProgramInfoLog(program, infoLen, NULL, message);
			printf("%s", message);
			free((void*)message);
		}
	}
	assert(linkSuccess == GL_TRUE);

	// �����N�ς݂̂��߁A�X�̃V�F�[�_�[�I�u�W�F�N�g�̉���t���O�𗧂Ă�
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// �����N�ς݂̃v���O������Ԃ�
	return program;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�V�F�[�_�[�t�@�C���̓ǂݍ��݂��s��
*	����
*	�@shader_file_name	�F[I/ ]�@�e�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
*	�@shader_source		�F[ /O]�@�e�V�F�[�_�[�̃\�[�X
*	�@source_size		�F[I/ ]�@�V�F�[�_�[�̑S���̍ő啶����
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void Shader_FileLoad(const char* shader_file_name, char* shader_source, int source_size)
{

	FILE *fp;		//�t�@�C���|�C���^�錾
	char String_Line[SHADER_STRING_LINE_MAX] = { 0 };		//1�s�̓ǂݍ��ݍő吔

	char shader_dir_file_name[SHADER_FILE_NAME_MAX] = "..\\Shader\\";

	strcat_s(shader_dir_file_name, shader_file_name);

	//�t�@�C���̃I�[�v��
	assert(0 == fopen_s(&fp, shader_dir_file_name, "r"));

	//�t�@�C���̓ǂݍ���
	while (fgets(String_Line, sizeof(String_Line), fp) != NULL)
	{
		//1�s�Óǂݍ��ނ̂ŕ����������
		assert(0 == strcat_s(shader_source, source_size, String_Line));
	}

	//�t�@�C���N���[�Y
	fclose(fp);
}


/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�V�F�[�_�[�\�[�X�̓ǂݍ��݂��s��
*	����
*	�@shader_source		�F[I/ ]�@�e�V�F�[�_�[�̃\�[�X�f�[�^
*	�@gl_xxxx_shader	�F[I/ ]�@�쐬����V�F�[�_�[�I�u�W�F�N�g�i�o�[�e�b�N�X or �t���O�����g�j
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
GLint Shader_SourceLoad(const char* shader_source, const GLuint gl_xxxx_shader)
{

	const GLint shader = glCreateShader(gl_xxxx_shader);
	assert(GL_NO_ERROR == glGetError());

	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);

	// �R���p�C���G���[���`�F�b�N����
	GLint compileSuccess = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
	if (GL_FALSE == compileSuccess) {
		// �G���[����������
		GLint infoLen = 0;
		// �G���[���b�Z�[�W���擾
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			GLchar *message = (GLchar*)calloc(infoLen, sizeof(GLchar));
			glGetShaderInfoLog(shader, infoLen, NULL, message);
			if (GL_VERTEX_SHADER == gl_xxxx_shader)
			{
				printf("GL_VERTEX_SHADER ERROR\n");
			}
			else
			{
				printf("GL_FRAGMENT_SHADER ERROR\n");
			}
			printf("%s", message);
			free((void*)message);
		}
	}

	// �R���p�C�����s���Ă����炱���Ńv���O�������~����
	assert(GL_TRUE == compileSuccess);

	return shader;
}