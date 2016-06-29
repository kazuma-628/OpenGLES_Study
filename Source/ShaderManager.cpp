#include "ShaderManager.h"

//�R���X�g���N�^
ShaderManager::ShaderManager()
{
	m_ProgramObject = -1;
	m_UniformInfoIndex = 0;
	m_AttribInfoIndex = 0;
	memset(m_vertex_file_name, 0, sizeof(m_vertex_file_name));
	memset(m_fragment_file_name, 0, sizeof(m_fragment_file_name));
	memset(m_AttribInfo, 0, sizeof(m_AttribInfo));
	memset(m_UniformInfo, 0, sizeof(m_UniformInfo));

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
*	�@p_vertex_file_name			�F[I/ ]�@�o�[�e�b�N�X�V�F�[�_�[�̃t�@�C����
*	�@p_fragment_file_name			�F[I/ ]�@�t���O�����g�V�F�[�_�[�̃t�@�C����
*	�@p_geometry_file_name			�F[I/ ]�@�W�I���g���V�F�[�_�[�̃t�@�C�����i�g�p���Ȃ��ꍇ��NULL���w��j
*	�@p_tess_control_file_name		�F[I/ ]�@�e�b�Z���[�V�����R���g���[���V�F�[�_�[�̃t�@�C�����i�g�p���Ȃ��ꍇ��NULL���w��j
*	�@p_tess_evaluation_file_name	�F[I/ ]�@�e�b�Z���[�V�����]���V�F�[�_�[�̃t�@�C�����i�g�p���Ȃ��ꍇ��NULL���w��j
*
*	���ǂ̃t�@�C������[Shader]�t�H���_�ȍ~�̃t�@�C���p�X����͂��Ă�������
*	�@�f�B���N�g�����܂����Ƃ��́u\\�v�ŋ�؂��Ă��������B�i��uxxx\\xxx.vert�v
*
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::CreateShaderProgram(const char* p_vertex_file_name, const char* p_fragment_file_name, const char* p_geometry_file_name, const char* p_tess_control_file_name, const char* p_tess_evaluation_file_name)
{
	GLuint vertex_shader = 0;				//�o�[�e�b�N�X�V�F�[�_�[�̃I�u�W�F�N�g
	GLuint fragment_shader = 0;				//�t���O�����g�V�F�[�_�[�̃I�u�W�F�N�g
	GLuint geometry_shader = 0;				//�W�I���g���V�F�[�_�[�̃I�u�W�F�N�g
	GLuint tess_control_shader = 0;			//�e�b�Z���[�V�����R���g���[���V�F�[�_�[�̃I�u�W�F�N�g
	GLuint tess_evaluation_shader = 0;		//�e�b�Z���[�V�����]���V�F�[�_�[�̃I�u�W�F�N�g

	//////////////////////////////////////
	// �ǂݍ��ރV�F�[�_�[�����L��

	strcpy(m_vertex_file_name, p_vertex_file_name);
	strcpy(m_fragment_file_name, p_fragment_file_name); 
	//�W�I���g���V�F�[�_�[���w�肳��Ă���ꍇ�i�w�肳��Ă���ꍇ�j
	if (NULL != p_geometry_file_name)
	{
		strcpy(m_geometry_file_name, p_geometry_file_name);
	}
	//�e�b�Z���[�V�����R���g���[���V�F�[�_�[���w�肳��Ă���ꍇ�i�w�肳��Ă���ꍇ�j
	if (NULL != p_tess_control_file_name)
	{
		strcpy(m_tess_control_file_name, p_tess_control_file_name);
	}
	//�e�b�Z���[�V�����]���V�F�[�_�[�̓ǂݍ��݁i�w�肳��Ă���ꍇ�j
	if (NULL != p_tess_evaluation_file_name)
	{
		strcpy(m_tess_evaluation_file_name, p_tess_evaluation_file_name);
	}

	//////////////////////////////////////

	//�o�[�e�b�N�X�̃V�F�[�_�[�I�u�W�F�N�g�쐬
	vertex_shader = CreateShader(p_vertex_file_name, GL_VERTEX_SHADER);
	//�G���[�`�F�b�N
	if (0 == vertex_shader)
	{
		//�G���[�Ȃ̂Ńv���O�����I�u�W�F�N�g�ɂ�0�ɂ���
		m_ProgramObject = 0;
		return;
	}

	//�t���O�����g�̃V�F�[�_�[�I�u�W�F�N�g�쐬
	fragment_shader = CreateShader(p_fragment_file_name, GL_FRAGMENT_SHADER);
	//�G���[�`�F�b�N
	if (0 == fragment_shader)
	{
		//���������
		glDeleteShader(vertex_shader);

		//�G���[�Ȃ̂Ńv���O�����I�u�W�F�N�g�ɂ�0�ɂ���
		m_ProgramObject = 0;
		return;
	}

	//�v���O�����I�u�W�F�N�g�̐���
	GLuint ProgramObject = glCreateProgram();
	//�G���[�`�F�b�N
	if (0 == ProgramObject)
	{
		//���������
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		//�G���[�Ȃ̂Ńv���O�����I�u�W�F�N�g�ɂ�0�ɂ���
		m_ProgramObject = 0;
		
		ERROR_MESSAGE("�v���O�����I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B");

		return;
	}

	glAttachShader(ProgramObject, vertex_shader);		// �o�[�e�b�N�X�V�F�[�_�[�ƃv���O�������֘A�t����
	glAttachShader(ProgramObject, fragment_shader);		// �t���O�����g�V�F�[�_�[�ƃv���O�������֘A�t����

	//�W�I���g���V�F�[�_�[�̓ǂݍ��݁i�w�肳��Ă���ꍇ�j
	if (NULL != p_geometry_file_name)
	{
		//�W�I���g���̃V�F�[�_�[�I�u�W�F�N�g�쐬
		geometry_shader = CreateShader(p_geometry_file_name, GL_GEOMETRY_SHADER);
		//�G���[�`�F�b�N
		if (0 == geometry_shader)
		{
			//���������
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);
			glDeleteProgram(ProgramObject);

			//�G���[�Ȃ̂Ńv���O�����I�u�W�F�N�g�ɂ�0�ɂ���
			m_ProgramObject = 0;
			return;
		}

		glAttachShader(ProgramObject, geometry_shader);		// �t���O�����g�V�F�[�_�[�ƃv���O�������֘A�t����
	}

	//�e�b�Z���[�V�����R���g���[���V�F�[�_�[�̓ǂݍ��݁i�w�肳��Ă���ꍇ�j
	if (NULL != p_tess_control_file_name)
	{
		//�W�I���g���̃V�F�[�_�[�I�u�W�F�N�g�쐬
		tess_control_shader = CreateShader(p_tess_control_file_name, GL_TESS_CONTROL_SHADER);
		//�G���[�`�F�b�N
		if (0 == tess_control_shader)
		{
			//���������
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);
			glDeleteShader(geometry_shader);
			glDeleteProgram(ProgramObject);

			//�G���[�Ȃ̂Ńv���O�����I�u�W�F�N�g�ɂ�0�ɂ���
			m_ProgramObject = 0;
			return;
		}

		glAttachShader(ProgramObject, tess_control_shader);		// �t���O�����g�V�F�[�_�[�ƃv���O�������֘A�t����
	}

	//�e�b�Z���[�V�����]���V�F�[�_�[�̓ǂݍ��݁i�w�肳��Ă���ꍇ�j
	if (NULL != p_tess_evaluation_file_name)
	{
		//�W�I���g���̃V�F�[�_�[�I�u�W�F�N�g�쐬
		tess_evaluation_shader = CreateShader(p_tess_evaluation_file_name, GL_TESS_EVALUATION_SHADER);
		//�G���[�`�F�b�N
		if (0 == tess_evaluation_shader)
		{
			//���������
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);
			glDeleteShader(geometry_shader);
			glDeleteShader(tess_control_shader);
			glDeleteProgram(ProgramObject);

			//�G���[�Ȃ̂Ńv���O�����I�u�W�F�N�g�ɂ�0�ɂ���
			m_ProgramObject = 0;
			return;
		}

		glAttachShader(ProgramObject, tess_evaluation_shader);		// �t���O�����g�V�F�[�_�[�ƃv���O�������֘A�t����
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

			//���������
			glDeleteProgram(ProgramObject);
			ProgramObject = 0;

			ERROR_MESSAGE("�V�F�[�_�[�v���O�����̃����N�Ɏ��s���܂����B");
		}
	}
	else
	{
		printf("����\n");
	}

	//////////////////////////////////////
	// �V�F�[�_�[�I�u�W�F�N�g�j��

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	//�W�I���g���V�F�[�_�[�I�u�W�F�N�g�j���i�w�肳��Ă���ꍇ�j
	if (NULL != p_geometry_file_name)
	{
		glDeleteShader(geometry_shader);
	}

	//�e�b�Z���[�V�����R���g���[���V�F�[�_�[�I�u�W�F�N�g�j���i�w�肳��Ă���ꍇ�j
	if (NULL != p_tess_control_file_name)
	{
		glDeleteShader(tess_control_shader);
	}

	//�e�b�Z���[�V�����]���V�F�[�_�[�I�u�W�F�N�g�j���i�w�肳��Ă���ꍇ�j
	if (NULL != p_tess_evaluation_file_name)
	{
		glDeleteShader(tess_evaluation_shader);
	}

	//�����N�ς݂̃v���O�������L������
	m_ProgramObject = ProgramObject;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Attribute�ϐ��̃��P�[�V�����𐶐��i�ق� glGetAttribLocation �Ɠ����ł��j
*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
*	����
*	�@p_name		�F[I/ ]�@�V�F�[�_�[�Ŏg�p����Attribute�ϐ��̖��O
*	�߂�l
*	�@Attribute�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
*-------------------------------------------------------------------------------*/
GLint ShaderManager::GetAttribLocation(const GLchar* p_name)
{
	printf("�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n", m_vertex_file_name, m_fragment_file_name);
	printf("�A�g���r���[�g�ϐ��u%s�v�̃��P�[�V�����̐������J�n���܂�... ", p_name);

	GLint Location = glGetAttribLocation(m_ProgramObject, p_name);

	if (Location < 0)
	{
		printf("���s\n\n");
		printf("������ �G���[ ������\n");
		printf("�V�F�[�_�[�ɕϐ��u%s�v����`����Ă��Ȃ��\��������܂�\n\n", p_name);
		ERROR_MESSAGE_SUB("");
	}
	else
	{ 
		printf("����\n");
	}

	//�ϐ����ƃ��P�[�V����ID��ۑ�
	memmove(m_AttribInfo[m_AttribInfoIndex].Name, p_name, strlen(p_name));
	m_AttribInfo[m_AttribInfoIndex].Location = Location;

	//�C���f�b�N�X�l��1�i�߂�
	m_AttribInfoIndex++;

	//�ۑ������C���f�b�N�X�l��Ԃ�
	return m_AttribInfoIndex - 1;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Uniform�ϐ��̃��P�[�V�����𐶐��i�ق� glGetUniformLocation �Ɠ����ł��j
*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
*	����
*	�@p_name		�F[I/ ]�@�V�F�[�_�[�Ŏg�p����Uniform�ϐ��̖��O
*	�߂�l
*	�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
*-------------------------------------------------------------------------------*/
GLint ShaderManager::GetUniformLocation(const GLchar* p_name)
{
	printf("�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n", m_vertex_file_name, m_fragment_file_name);
	printf("���j�z�[���ϐ��u%s�v�̃��P�[�V�����̐������J�n���܂�... ", p_name);

	GLint Location = glGetUniformLocation(m_ProgramObject, p_name);

	if (Location < 0)
	{
		printf("���s\n\n");
		printf("������ �G���[ ������\n");
		printf("�V�F�[�_�[�ɕϐ��u%s�v����`����Ă��Ȃ��\��������܂�\n\n", p_name);
		ERROR_MESSAGE_SUB("");

	}
	else
	{
		printf("����\n");
	}

	//�ϐ����ƃ��P�[�V����ID��ۑ�
	memmove(m_UniformInfo[m_UniformInfoIndex].Name, p_name, strlen(p_name));
	m_UniformInfo[m_UniformInfoIndex].Location = Location;

	//�C���f�b�N�X�l��1�i�߂�
	m_UniformInfoIndex++;

	//�ۑ������C���f�b�N�X�l��Ԃ�
	return m_UniformInfoIndex - 1;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Attribute�ϐ���L���ɂ��܂��B�i�ق� glEnableVertexAttribArray �Ɠ����ł��j
*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
*	����
*	�@p_index		�F[I/ ]�@Attribute�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
*							�@�iGetAttribLocation�Ŏ擾�����Ԃ�l�j
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::EnableVertexAttribArray(const GLint p_index)
{
	if (-1 == m_AttribInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n������ �G���[ ������\n"\
			"�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n"\
			"�A�g���r���[�g�ϐ��u%s�v�̗L�����Ɏ��s���܂���\n"\
			"�V�F�[�_�[�ɕϐ�����`����Ă��Ȃ��\��������܂�\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_AttribInfo[p_index].Name);
	}
	else
	{
		glEnableVertexAttribArray(m_AttribInfo[p_index].Location);
	}
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Attribute�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glVertexAttribPointer �Ɠ����ł��j
*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
*	����
*	�@p_index		�F[I/ ]�@Attribute�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
*							�@�iGetAttribLocation�Ŏ擾�����Ԃ�l�j
*	�@p_size		�F[I/ ]�@���_�f�[�^�̗v�f��
*	�@p_type		�F[I/ ]�@���_�f�[�^�̌^
*	�@p_normalized	�F[I/ ]�@���_�f�[�^�𐳋K�����Ē��_�V�F�[�_�[�ɓn���ꍇ�́uGL_TRUE�v���w��A
*							 ���͂��̂܂܂ɒ��_�V�F�[�_�[�ɓn���ꍇ�́uGL_FALSE�v���w��
*	�@p_stride		�F[I/ ]�@���_�̐擪�ʒu���Ƃ̃I�t�Z�b�g�l�A0�w��\
*	�@p_pointer		�F[I/ ]�@�֘A�t���钸�_�̐擪�|�C���^
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::VertexAttribPointer(const GLint p_index, const GLint p_size, const GLenum p_type, const GLboolean p_normalized, const GLsizei p_stride, const GLvoid *p_pointer)
{
	if (-1 == m_AttribInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n������ �G���[ ������\n"\
			"�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n"\
			"�A�g���r���[�g�ϐ��u%s�v�ւ̃f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂���\n"\
			"�V�F�[�_�[�ɕϐ�����`����Ă��Ȃ��\��������܂�\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_AttribInfo[p_index].Name);
	}
	else
	{
		glVertexAttribPointer(m_AttribInfo[p_index].Location, p_size, p_type, p_normalized, p_stride, p_pointer);
	}
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Uniform�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glUniform1f, glUniform2f, glUniform3f, glUniform4f �Ɠ����ł��j
*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
*	����
*	�@p_index		�F[I/ ]�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
*					�@		�iGetUniformLocation�Ŏ擾�����Ԃ�l�j
*	�@p_scalar		�F[I/ ]�@�]������f�[�^�̌��i�V�F�[�_�[���ϐ��̃x�N�g�������Ɠ���������́@��)[4] �� vec4�j
*							 �� �v�񂷂�� [1]���w�肷��� �� glUniform1f�A[4]���w�肷��� �� glUniform4f ���R�[������� ��
*					----------------------------------------------------------
*					���L�����ɂ��ẮA�����up_scalar�v�Ŏw�肵���������u�f�[�^1�v����l�߂ē��͂���
*					�i�g�p���Ȃ��������o�Ă���Ǝv���邪�A���̈����ɂ́u0�v���w�肷�邱�Ɓj
*	�@p_param1		�F[I/ ]�@�]������f�[�^ 1�i�V�F�[�_�[���ϐ��� X�x�N�g�������ɊY���j
*	�@p_param2		�F[I/ ]�@�]������f�[�^ 2�i�V�F�[�_�[���ϐ��� Y�x�N�g�������ɊY���j
*	�@p_param3		�F[I/ ]�@�]������f�[�^ 3�i�V�F�[�_�[���ϐ��� Z�x�N�g�������ɊY���j
*	�@p_param4		�F[I/ ]�@�]������f�[�^ 4�i�V�F�[�_�[���ϐ��� W�x�N�g�������ɊY���j
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::UniformXf(const GLint p_index, const GLint p_scalar, const GLfloat p_param1, const GLfloat p_param2, const GLfloat p_param3, const GLfloat p_param4)
{
	if (-1 == m_UniformInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n������ �G���[ ������\n"\
			"�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n"\
			"���j�t�H�[���ϐ��u%s�v�ւ̃f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂���\n"\
			"�V�F�[�_�[�ɕϐ�����`����Ă��Ȃ��\��������܂�\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_UniformInfo[p_index].Name);
	}
	else
	{
		if(1 == p_scalar)
		{
			glUniform1f(m_UniformInfo[p_index].Location, p_param1);
		}
		else if (2 == p_scalar)
		{
			glUniform2f(m_UniformInfo[p_index].Location, p_param1, p_param2);
		}
		else if (3 == p_scalar)
		{
			glUniform3f(m_UniformInfo[p_index].Location, p_param1, p_param2, p_param3);
		}
		else if (4 == p_scalar)
		{
			glUniform4f(m_UniformInfo[p_index].Location, p_param1, p_param2, p_param3, p_param4);
		}
		else
		{
			printf("\n������ �G���[ ������\n");
			printf("�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n", m_vertex_file_name, m_fragment_file_name);
			printf("���j�t�H�[���ϐ��u%s�v�ւ̃f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂���\n", m_UniformInfo[p_index].Name);
			printf("�uglUniformXf�v�֐��up_scalar�v�����̃G���[�ł�\n");
			printf("�������l���ݒ肳��Ă��܂��� �� �ݒ�l�F%d\n\n", p_scalar);
			ERROR_MESSAGE("Uniform�ϐ��ւ̃f�[�^�𑗐M�i�֘A�t���j�Ɏ��s���܂����B");
		}
	}
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Uniform�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glUniform1i, glUniform2i, glUniform3i, glUniform4i �Ɠ����ł��j
*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
*	����
*	�@p_index		�F[I/ ]�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
*					�@		�iGetUniformLocation�Ŏ擾�����Ԃ�l�j
*	�@p_scalar		�F[I/ ]�@�]������f�[�^�̌��i�V�F�[�_�[���ϐ��̃x�N�g�������Ɠ���������́@��)[4] �� ivec4�j
*							 �� �v�񂷂�� [1]���w�肷��� �� glUniform1i�A[4]���w�肷��� �� glUniform4i ���R�[������� ��
*					----------------------------------------------------------
*					���L�����ɂ��ẮA�����up_scalar�v�Ŏw�肵���������u�f�[�^1�v����l�߂ē��͂���
*					�i�g�p���Ȃ��������o�Ă���Ǝv���邪�A���̈����ɂ́u0�v���w�肷�邱�Ɓj
*	�@p_param1		�F[I/ ]�@�]������f�[�^ 1�i�V�F�[�_�[���ϐ��� X�x�N�g�������ɊY���j
*	�@p_param2		�F[I/ ]�@�]������f�[�^ 2�i�V�F�[�_�[���ϐ��� Y�x�N�g�������ɊY���j
*	�@p_param3		�F[I/ ]�@�]������f�[�^ 3�i�V�F�[�_�[���ϐ��� Z�x�N�g�������ɊY���j
*	�@p_param4		�F[I/ ]�@�]������f�[�^ 4�i�V�F�[�_�[���ϐ��� W�x�N�g�������ɊY���j
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::UniformXi(const GLint p_index, const GLint p_scalar, const GLint p_param1, const GLint p_param2, const GLint p_param3, const GLint p_param4)
{
	if (-1 == m_UniformInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n������ �G���[ ������\n"\
			"�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n"\
			"���j�t�H�[���ϐ��u%s�v�ւ̃f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂���\n"\
			"�V�F�[�_�[�ɕϐ�����`����Ă��Ȃ��\��������܂�\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_UniformInfo[p_index].Name);
	}
	else
	{
		if (1 == p_scalar)
		{
			glUniform1i(m_UniformInfo[p_index].Location, p_param1);
		}
		else if (2 == p_scalar)
		{
			glUniform2i(m_UniformInfo[p_index].Location, p_param1, p_param2);
		}
		else if (3 == p_scalar)
		{
			glUniform3i(m_UniformInfo[p_index].Location, p_param1, p_param2, p_param3);
		}
		else if (4 == p_scalar)
		{
			glUniform4i(m_UniformInfo[p_index].Location, p_param1, p_param2, p_param3, p_param4);
		}
		else
		{
			printf("\n������ �G���[ ������\n");
			printf("�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n", m_vertex_file_name, m_fragment_file_name);
			printf("���j�t�H�[���ϐ��u%s�v�ւ̃f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂���\n", m_UniformInfo[p_index].Name);
			printf("�uglUniformXi�v�֐��up_scalar�v�����̃G���[�ł�\n");
			printf("�������l���ݒ肳��Ă��܂��� �� �ݒ�l�F%d\n\n", p_scalar);
			ERROR_MESSAGE("Uniform�ϐ��ւ̃f�[�^�𑗐M�i�֘A�t���j�Ɏ��s���܂����B");
		}
	}
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Uniform�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glUniform1fv, glUniform2fv, glUniform3fv, glUniform4fv �Ɠ����ł��j
*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
*	����
*	�@p_index		�F[I/ ]�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
*					�@		�iGetUniformLocation�Ŏ擾�����Ԃ�l�j
*	�@p_scalar		�F[I/ ]�@�]������f�[�^�̌��i�V�F�[�_�[���ϐ��̃x�N�g�������Ɠ���������́@��)[4] �� vec4�j
*							 �� �v�񂷂�� [1]���w�肷��� �� glUniform1fv�A[4]���w�肷��� �� glUniform4fv ���R�[������� ��
*					----------------------------------------------------------
*	�@p_count		�F[I/ ]�@�]������f�[�^�̔z�񐔁i�up_scalar�v�����Őݒ肵���f�[�^�̌������Z�b�g���邩�@��)[4] �� vec? Example[4]�j
*	�@value			�F[I/ ]�@�]������f�[�^�̐擪�|�C���^
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::UniformXfv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLfloat *p_value)
{
	if (-1 == m_UniformInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n������ �G���[ ������\n"\
			"�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n"\
			"���j�t�H�[���ϐ��u%s�v�ւ̃f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂���\n"\
			"�V�F�[�_�[�ɕϐ�����`����Ă��Ȃ��\��������܂�\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_UniformInfo[p_index].Name);
	}
	else
	{
		if (1 == p_scalar)
		{
			glUniform1fv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (2 == p_scalar)
		{
			glUniform2fv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (3 == p_scalar)
		{
			glUniform3fv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (4 == p_scalar)
		{
			glUniform4fv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else
		{
			printf("\n������ �G���[ ������\n");
			printf("�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n", m_vertex_file_name, m_fragment_file_name);
			printf("���j�t�H�[���ϐ��u%s�v�ւ̃f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂���\n", m_UniformInfo[p_index].Name);
			printf("�uglUniformXfv�v�֐��up_scalar�v�����̃G���[�ł�\n");
			printf("�������l���ݒ肳��Ă��܂��� �� �ݒ�l�F%d\n\n", p_scalar);
			ERROR_MESSAGE("Uniform�ϐ��ւ̃f�[�^�𑗐M�i�֘A�t���j�Ɏ��s���܂����B");
		}
	}
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Uniform�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glUniform1iv, glUniform2iv, glUniform3iv, glUniform4iv �Ɠ����ł��j
*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
*	����
*	�@p_index		�F[I/ ]�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
*					�@		�iGetUniformLocation�Ŏ擾�����Ԃ�l�j
*	�@p_scalar		�F[I/ ]�@�]������f�[�^�̌��i�V�F�[�_�[���ϐ��̃x�N�g�������Ɠ���������́@��)[4] �� ivec4�j
*							 �� �v�񂷂�� [1]���w�肷��� �� glUniform1iv�A[4]���w�肷��� �� glUniform4iv ���R�[������� ��
*					----------------------------------------------------------
*	�@p_count		�F[I/ ]�@�]������f�[�^�̔z�񐔁i�up_scalar�v�����Őݒ肵���f�[�^�̌������Z�b�g���邩�@��)[4] �� ivec? Example[4]�j
*	�@value			�F[I/ ]�@�]������f�[�^�̐擪�|�C���^
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::UniformXiv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLint *p_value)
{
	if (-1 == m_UniformInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n������ �G���[ ������\n"\
			"�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n"\
			"���j�t�H�[���ϐ��u%s�v�ւ̃f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂���\n"\
			"�V�F�[�_�[�ɕϐ�����`����Ă��Ȃ��\��������܂�\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_UniformInfo[p_index].Name);
	}
	else
	{
		if (1 == p_scalar)
		{
			glUniform1iv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (2 == p_scalar)
		{
			glUniform2iv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (3 == p_scalar)
		{
			glUniform3iv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (4 == p_scalar)
		{
			glUniform4iv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else
		{
			printf("\n������ �G���[ ������\n");
			printf("�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n", m_vertex_file_name, m_fragment_file_name);
			printf("���j�t�H�[���ϐ��u%s�v�ւ̃f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂���\n", m_UniformInfo[p_index].Name);
			printf("�uglUniformXiv�v�֐��up_scalar�v�����̃G���[�ł�\n");
			printf("�������l���ݒ肳��Ă��܂��� �� �ݒ�l�F%d\n\n", p_scalar);
			ERROR_MESSAGE("Uniform�ϐ��ւ̃f�[�^�𑗐M�i�֘A�t���j�Ɏ��s���܂����B");
		}
	}
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Uniform�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glUniformMatrix2fv, glUniformMatrix3fv, glUniformMatrix4fv �Ɠ����ł��j
*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
*	����
*	�@p_index		�F[I/ ]�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
*					�@		�iGetUniformLocation�Ŏ擾�����Ԃ�l�j
*	�@p_scalar		�F[I/ ]�@�]������s��̃T�C�Y�i�H�~�H �� [�H]�̕����j�i�V�F�[�_�[���ϐ��̃x�N�g�������Ɠ���������́@��)[4] �� mat4�j
*							 �� �v�񂷂�� [2]���w�肷��� �� glUniformMatrix2fv�A[4]���w�肷��� �� glUniformMatrix4fv ���R�[������� ��
*					----------------------------------------------------------
*	�@p_count		�F[I/ ]�@�]������̍s��̔z�񐔁i�up_scalar�v�����Őݒ肵���s��̃T�C�Y�����Z�b�g���邩�@��)[4] �� mat? Example[4]�j
*	�@p_transpose	�F[I/ ]�@���_�f�[�^��]�u���ăV�F�[�_�[�ɓn���ꍇ�́uGL_TRUE�v���w��A
*								 ���͂��̂܂܂ɒ��_�V�F�[�_�[�ɓn���ꍇ�́uGL_FALSE�v���w��
*	�@value			�F[I/ ]�@�]������f�[�^�̐擪�|�C���^
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::UniformMatrixXfv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLboolean p_transpose, const GLfloat *p_value)
{
	if (-1 == m_UniformInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n������ �G���[ ������\n"\
			"�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n"\
			"���j�t�H�[���ϐ��u%s�v�ւ̃f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂���\n"\
			"�V�F�[�_�[�ɕϐ�����`����Ă��Ȃ��\��������܂�\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_UniformInfo[p_index].Name);
	}
	else
	{
		if (2 == p_scalar)
		{
			glUniformMatrix2fv(m_UniformInfo[p_index].Location, p_count, p_transpose, p_value);
		}
		else if (3 == p_scalar)
		{
			glUniformMatrix3fv(m_UniformInfo[p_index].Location, p_count, p_transpose, p_value);
		}
		else if (4 == p_scalar)
		{
			glUniformMatrix4fv(m_UniformInfo[p_index].Location, p_count, p_transpose, p_value);
		}
		else
		{
			printf("\n������ �G���[ ������\n");
			printf("�V�F�[�_�[�u%s�v�y�сu%s�v�p��\n", m_vertex_file_name, m_fragment_file_name);
			printf("���j�t�H�[���ϐ��u%s�v�ւ̃f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂���\n", m_UniformInfo[p_index].Name);
			printf("�uglUniformMatrixXfv�v�֐��up_scalar�v�����̃G���[�ł�\n");
			printf("�������l���ݒ肳��Ă��܂��� �� �ݒ�l�F%d\n\n", p_scalar);
			ERROR_MESSAGE("Uniform�ϐ��ւ̃f�[�^�𑗐M�i�֘A�t���j�Ɏ��s���܂����B");
		}
	}
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�V�F�[�_�[�v���O�����̗��p���J�n����i�ق� glUseProgram �Ɠ����ł��j
*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void ShaderManager::UseProgram(void)
{
	//�L���ȃv���O�����I�u�W�F�N�g�̏ꍇ
	if (0 != m_ProgramObject)
	{
		// �V�F�[�_�[�v���O�����̗��p���J�n����
		glUseProgram(m_ProgramObject);
	}
	else
	{
		printf("�V�F�[�_�[�u%s�v�y�сu%s�v�p�̏����ŃG���[���������܂����B\n", m_vertex_file_name, m_fragment_file_name);
		ERROR_MESSAGE("�V�F�[�_�[�v���O�����̗��p�Ɏ��s���܂����B");
	}
}


/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�V�F�[�_�[�I�u�W�F�N�g�̍쐬���s��
*	����
*	�@p_file_name		�F[I/ ]�@�V�F�[�_�[�̃t�@�C����
*	�@gl_xxxx_shader	�F[I/ ]�@�쐬����V�F�[�_�[�I�u�W�F�N�g�̎��
*								�iGL_GEOMETRY_SHADER or GL_FRAGMENT_SHADER or GL_VERTEX_SHADER�j
*	�߂�l
*	�@�V�F�[�_�[�I�u�W�F�N�g
*-------------------------------------------------------------------------------*/
GLuint ShaderManager::CreateShader(const char* p_file_name, const GLuint p_gl_xxxx_shader)
{
	//�t�@�C������V�F�[�_�[�\�[�X��ǂݍ��ށi�uShader�v�t�H���_�z���Ɋi�[����Ă���K�v������܂��j
	GLchar *shader_source = ShaderFileLoad(p_file_name);

	//�V�F�[�_�[�I�u�W�F�N�g�̐���
	GLuint shader = glCreateShader(p_gl_xxxx_shader);
	if (0 == shader)
	{
		ERROR_MESSAGE("�V�F�[�_�[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���");

		//���������
		free(shader_source);

		return 0;
	}

	//�\�[�X�v���O������ǂݍ���
	glShaderSource(shader, 1, &shader_source, NULL);

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
			
			//���������
			free((void*)message);
			glDeleteShader(shader);
			shader = 0;

			ERROR_MESSAGE("�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B");

		}
	}
	else
	{
		printf("����\n");
	}

	//�V�F�[�_�[�\�[�X�p�̃��������
	free((void*)shader_source);

	return shader;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�V�F�[�_�[�t�@�C���̓ǂݍ��݂��s��
*	����
*	�@p_file_name		�F[I/ ]�@�V�F�[�_�[�̃t�@�C����
*
*	��[Shader]�t�H���_�ȍ~�̃t�@�C���p�X����͂��Ă�������
*	�@�f�B���N�g�����܂����Ƃ��́u\\�v�ŋ�؂��Ă��������B�i��uxxx\\xxx.vert�v)
*
*	�߂�l
*	�@�V�F�[�_�[�\�[�X�ւ̐擪�|�C���^
*-------------------------------------------------------------------------------*/
char* ShaderManager::ShaderFileLoad(const char* p_file_name)
{
	FILE *fp = NULL;		//�t�@�C���|�C���^�錾

	char shader_dir_file_name[SHADER_FILE_NAME_MAX] = SHADER_FILE_DIR;

	strcat(shader_dir_file_name, p_file_name);

	//�t�@�C���̃I�[�v��
	printf("�u%s�v�V�F�[�_�[�t�@�C���̓ǂݍ��݂��J�n���܂�... ", p_file_name);
	
	fp = fopen(shader_dir_file_name, "r");
	if (NULL == fp)
	{
		printf("���s\n");
		ERROR_MESSAGE("�V�F�[�_�[�t�@�C���̃I�[�v���Ɏ��s���܂����B\n"\
			"�uShader�v�t�H���_�Ɋi�[����Ă��܂����H\n"\
			"�t�@�C�������Ԉ���Ă��܂��񂩁H");

		return NULL;
	}

	//�t�@�C���̃T�C�Y���擾����
	fseek(fp, 0, SEEK_END);
	int FileSize = ftell(fp);
	//��t�@�C���̏ꍇ
	if (0 == FileSize)
	{
		printf("���s\n");
		ERROR_MESSAGE("��t�@�C���ł��B");

		//�t�@�C���N���[�Y
		fclose(fp);

		return NULL;
	}

	//�t�@�C���T�C�Y�擾�����������̂Ő擪�ɖ߂�
	fseek(fp, 0, SEEK_SET);

	//�t�@�C���̓ǂݍ��݁i�I�[�𖾊m�ɂ��邽�� +1 ����B[\0]�ƂȂ�j
	GLchar *shader_source = (GLchar*)calloc(FileSize + 1, sizeof(char));
	fread((void*)shader_source, sizeof(char), FileSize, fp);

	//�t�@�C���N���[�Y
	fclose(fp);

	printf("����\n");

	return shader_source;
}
