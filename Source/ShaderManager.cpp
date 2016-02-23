#include "ShaderManager.h"

//�R���X�g���N�^
ShaderManager::ShaderManager()
{
	m_ProgramObject = -1;
	memset(m_vertex_shader_file, 0, sizeof(m_vertex_shader_file));
	memset(m_fragment_shader_file, 0, sizeof(m_fragment_shader_file));
}

//�f�X�g���N�^
ShaderManager::~ShaderManager()
{
	//�v���O�����I�u�W�F�N�g���폜����
	glDeleteProgram(m_ProgramObject);
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�o�[�e�b�N�X�E�t���O�����g�V�F�[�_�[�̃\�[�X���w�肳�ꂽ�t�@�C������ǂݍ��݁A
*	�@�R���p�C���y�у����N���āA�v���O�����I�u�W�F�N�g���쐬����
*	����
*	�@p_vertex_shader_file		�F[I/ ]�@�o�[�e�b�N�X�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
*	�@p_fragment_shader_file	�F[I/ ]�@�t���O�����g�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::CreateShaderProgram(const char* p_vertex_shader_file, const char* p_fragment_shader_file)
{
	//�ǂݍ��ރV�F�[�_�[�����L��
	strcat_s(m_vertex_shader_file, sizeof(m_vertex_shader_file), p_vertex_shader_file);
	strcat_s(m_fragment_shader_file, sizeof(m_fragment_shader_file), p_vertex_shader_file);

	//�t�@�C������o�[�e�b�N�X�\�[�X��ǂݍ��ށi�uShader�v�t�H���_�Ɋi�[����Ă���K�v������܂��j
	char vertex_shader_source[SHADER_STRING_ALL_MAX] = { 0 };		//���_�V�F�[�_
	Shader_FileLoad(p_vertex_shader_file, vertex_shader_source, SHADER_STRING_ALL_MAX);
	//�\�[�X���A�b�v���[�h����
	const GLuint vertex_shader = Shader_SourceLoad(vertex_shader_source, GL_VERTEX_SHADER);			//���_�V�F�[�_

	//�t�@�C������t���O�����g�\�[�X��ǂݍ��ށi�uShader�v�t�H���_�Ɋi�[����Ă���K�v������܂��j
	char fragment_shader_source[SHADER_STRING_ALL_MAX] = { 0 };		//�t���O�����g�V�F�[�_
	Shader_FileLoad(p_fragment_shader_file, fragment_shader_source, SHADER_STRING_ALL_MAX);
	//�\�[�X���A�b�v���[�h����
	const GLuint fragment_shader = Shader_SourceLoad(fragment_shader_source, GL_FRAGMENT_SHADER);	//�t���O�����g�V�F�[�_


	//�v���O�����I�u�W�F�N�g�̐���
	const GLuint ProgramObject = glCreateProgram();
	if (GL_NO_ERROR != glGetError() || 0 == ProgramObject)
	{
		ERROR_MESSAGE("�v���O�����I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B");
	}

	glAttachShader(ProgramObject, vertex_shader);		// �o�[�e�b�N�X�V�F�[�_�[�ƃv���O�������֘A�t����
	glAttachShader(ProgramObject, fragment_shader);	// �t���O�����g�V�F�[�_�[�ƃv���O�������֘A�t����
	if (GL_NO_ERROR != glGetError())
	{
		ERROR_MESSAGE("�V�F�[�_�[�ƃV�F�[�_�[�v���O�����̊֘A�t���Ɏ��s���܂����B");
	}

	// �V�F�[�_�[�v���O�����̃����N���s��
	printf("�V�F�[�_�[�v���O�����̃����N���J�n���܂�... ");
	glLinkProgram(ProgramObject);

	// �����N�G���[���`�F�b�N����
	GLint linkSuccess = 0;
	glGetProgramiv(ProgramObject, GL_LINK_STATUS, &linkSuccess);
	if (GL_FALSE == linkSuccess) {
		// �G���[����������
		GLint infoLen = 0;
		// �G���[���b�Z�[�W���擾
		glGetProgramiv(ProgramObject, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			GLchar *message = (GLchar*)calloc(infoLen, sizeof(GLchar));
			glGetProgramInfoLog(ProgramObject, infoLen, NULL, message);

			//�G���[���b�Z�[�W�\��
			printf("\n\n�����N�G���[�̏��͈ȉ��ł��B\n");
			printf("%s", message);
			free((void*)message);
		}
	}
	if (GL_TRUE != linkSuccess)
	{
		ERROR_MESSAGE("�V�F�[�_�[�v���O�����̃����N�Ɏ��s���܂����B");
	}
	printf("����\n");

	// �����N�ς݂̂��߁A�X�̃V�F�[�_�[�I�u�W�F�N�g�̉���t���O�𗧂Ă�
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	//�����N�ς݂̃v���O�������L������
	m_ProgramObject = ProgramObject;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Attribute�ϐ��̃��P�[�V����ID�𐶐��i�ق� glGetAttribLocation �Ɠ����ł��j
*	�@������₷���悤�Ɉ��������Ȃ������̂ƁA�G���[�Ǘ����ꌳ�������_���Ⴄ�݂̂ł��B
*	����
*	�@p_attribute_name			�F[I/ ]�@�V�F�[�_�[�Ŏg�p����Attribute�ϐ��̖��O
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
GLint ShaderManager::GetAttribLocation(const GLchar* p_attribute_name)
{
	printf("�V�F�[�_�[�u%s�v�p��\n", m_vertex_shader_file);
	printf("�A�g���r���[�g�ϐ��u%s�v�̃��P�[�V����ID�̐������J�n���܂�... ", p_attribute_name);

	GLint AttribLocationID = glGetAttribLocation(m_ProgramObject, p_attribute_name);

	if (AttribLocationID < 0)
	{
		ERROR_MESSAGE("Attribute�ϐ��̃��P�[�V����ID�𐶐��Ɏ��s���܂����B");
	}
	printf("����\n");

	return AttribLocationID;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Uniform�ϐ��̃��P�[�V����ID�𐶐��i�ق� glGetUniformLocation �Ɠ����ł��j
*	�@������₷���悤�Ɉ��������Ȃ������̂ƁA�G���[�Ǘ����ꌳ�������_���Ⴄ�݂̂ł��B
*	����
*	�@p_uniform_name			�F[I/ ]�@�V�F�[�_�[�Ŏg�p����Uniform�ϐ��̖��O
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
GLint ShaderManager::GetUniformLocation(const GLchar* p_uniform_name)
{
	printf("�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n", m_vertex_shader_file, m_fragment_shader_file);
	printf("���j�z�[���ϐ��u%s�v�̃��P�[�V����ID�̐������J�n���܂�... ", p_uniform_name);

	GLint UniformLocationID = glGetUniformLocation(m_ProgramObject, p_uniform_name);

	if (UniformLocationID < 0)
	{
		ERROR_MESSAGE("Uniform�ϐ��̃��P�[�V����ID�𐶐��Ɏ��s���܂����B");
	}
	printf("����\n");

	return UniformLocationID;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�V�F�[�_�[�v���O�����̗��p���J�n����i�ق� glUseProgram �Ɠ����ł��j
*	�@������₷���悤�Ɉ��������Ȃ������̂ƁA�G���[�Ǘ����ꌳ�������_���Ⴄ�݂̂ł��B
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::UseProgram(void)
{
	// �V�F�[�_�[�v���O�����̗��p���J�n����
	glUseProgram(m_ProgramObject);

	if (GL_NO_ERROR != glGetError())
	{
		printf("�V�F�[�_�[�u%s�v�y�сu%s�v�p�̏����ŃG���[���������܂����B\n", m_vertex_shader_file, m_fragment_shader_file);
		ERROR_MESSAGE("�V�F�[�_�[�v���O�����̗��p�Ɏ��s���܂����B");
	}
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�V�F�[�_�[�t�@�C���̓ǂݍ��݂��s��
*	����
*	�@p_shader_file_name	�F[I/ ]�@�e�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
*	�@p_shader_source		�F[ /O]�@�e�V�F�[�_�[�̃\�[�X
*	�@source_size			�F[I/ ]�@�V�F�[�_�[�̑S���̍ő啶����
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::Shader_FileLoad(const char* p_shader_file_name, char* p_shader_source, const int p_source_size)
{

	FILE *fp;		//�t�@�C���|�C���^�錾
	char String_Line[SHADER_STRING_LINE_MAX] = { 0 };		//1�s�̓ǂݍ��ݍő吔

	char shader_dir_file_name[SHADER_FILE_NAME_MAX] = "..\\Shader\\";

	strcat_s(shader_dir_file_name, p_shader_file_name);

	//�t�@�C���̃I�[�v��
	printf("�u%s�v�V�F�[�_�[�t�@�C���̓ǂݍ��݂��J�n���܂�... ", p_shader_file_name);
	if (0 != fopen_s(&fp, shader_dir_file_name, "r"))
	{
		ERROR_MESSAGE("�V�F�[�_�[�t�@�C���̃I�[�v���Ɏ��s���܂���");
	}

	//�t�@�C���̓ǂݍ���
	while (fgets(String_Line, sizeof(String_Line), fp) != NULL)
	{
		//1�s�Óǂݍ��ނ̂ŕ����������
		if (0 != strcat_s(p_shader_source, p_source_size, String_Line))
		{
			ERROR_MESSAGE("�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B");
		}
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	printf("����\n");
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
GLint ShaderManager::Shader_SourceLoad(const char* p_shader_source, const GLuint p_gl_xxxx_shader)
{

	//�V�F�[�_�[�I�u�W�F�N�g�̐���
	const GLint shader = glCreateShader(p_gl_xxxx_shader);
	if (GL_NO_ERROR != glGetError())
	{
		ERROR_MESSAGE("�V�F�[�_�[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���");
	}

	//�\�[�X�v���O������ǂݍ���
	glShaderSource(shader, 1, &p_shader_source, NULL);

	//�V�F�[�_�[�̃R���p�C�����J�n
	printf("�V�F�[�_�[�̃R���p�C�����J�n���܂�... ");
	glCompileShader(shader);

	// �R���p�C���G���[���`�F�b�N����
	GLint compileSuccess = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
	if (GL_FALSE == compileSuccess)
	{
		// �G���[����������
		GLint infoLen = 0;
		// �G���[���b�Z�[�W���擾
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			GLchar *message = (GLchar*)calloc(infoLen, sizeof(GLchar));
			glGetShaderInfoLog(shader, infoLen, NULL, message);

			//�G���[���b�Z�[�W�\��
			printf("\n\n�R���p�C���G���[�̏��͈ȉ��ł��B\n");
			printf("%s", message);
			free((void*)message);
		}
	}

	// �R���p�C�����s���Ă����炱���Ńv���O�������~����
	if (GL_TRUE != compileSuccess)
	{
		ERROR_MESSAGE("�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B");
	}

	printf("����\n");
	
	return shader;
}