#ifndef SHADERCREATEPROGRAM_H
#define SHAdERCREATEPROGRAM_H

//include��`
#include "Common.h"

//Define��`
#define SHADER_STRING_LINE_MAX		256			//�V�F�[�_�[��1�s�̍ő啶����
#define SHADER_STRING_ALL_MAX		10240		//�V�F�[�_�[�̑S���̍ő啶����
#define SHADER_FILE_NAME_MAX		64			//�V�F�[�_�[�̃t�@�C�����ő啶�����i�f�B���N�g�����܂ށj
#define ATTRIB_INFO_MAX				128			//�A�g���r���[�g�ϐ��Ǘ��p�̍ő吔
#define ATTRIB_INFO_NAME_MAX		64			//�A�g���r���[�g�ϐ����̍ő啶����
#define UNIFORM_INFO_MAX			128			//���j�t�H�[���ϐ��Ǘ��p�̍ő吔
#define UNIFORM_INFO_NAME_MAX		64			//���j�t�H�[���ϐ����̍ő啶����

class ShaderManager
{

public:

	//�R���X�g���N�^
	ShaderManager();

	//�f�X�g���N�^
	~ShaderManager();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�o�[�e�b�N�X�E�t���O�����g�V�F�[�_�[�̃\�[�X���w�肳�ꂽ�t�@�C������ǂݍ��݁A
	*	�@�R���p�C���y�у����N���āA�v���O�����I�u�W�F�N�g���쐬����
	*	����
	*	�@p_vertex_file_name		�F[I/ ]�@�o�[�e�b�N�X�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
	*	�@p_fragment_file_name		�F[I/ ]�@�t���O�����g�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void CreateShaderProgram(const char* p_vertex_file_name, const char* p_fragment_file_name);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Attribute�ϐ��̃��P�[�V�����𐶐��i�ق� glGetAttribLocation �Ɠ����ł��j
	*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
	*	����
	*	�@p_name		�F[I/ ]�@�V�F�[�_�[�Ŏg�p����Attribute�ϐ��̖��O
	*	�߂�l
	*	�@Attribute�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
	*
	*	�@�C���f�b�N�X�l�ł͂Ȃ��A�f��Attribute�ϐ��̃��P�[�V�������擾�������ꍇ�́A
	*	�@�{�֐����s��ɁuGetAttribLocationOriginal�v�֐��𗘗p���擾���Ă��������B
	*-------------------------------------------------------------------------------*/
	GLint GetAttribLocation(const GLchar* p_name);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Uniform�ϐ��̃��P�[�V�����𐶐��i�ق� glGetUniformLocation �Ɠ����ł��j
	*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
	*	����
	*	�@p_name		�F[I/ ]�@�V�F�[�_�[�Ŏg�p����Uniform�ϐ��̖��O
	*	�߂�l
	*	�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
	*
	*	�@�C���f�b�N�X�l�ł͂Ȃ��A�f��Uniform�ϐ��̃��P�[�V�������擾�������ꍇ�́A
	*	�@�{�֐����s��ɁuGetUniformLocationOriginal�v�֐��𗘗p���擾���Ă��������B
	*-------------------------------------------------------------------------------*/
	GLint GetUniformLocation(const GLchar* p_name);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Attribute�ϐ���L���ɂ��܂��B�i�ق� glEnableVertexAttribArray �Ɠ����ł��j
	*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
	*	����
	*	�@p_index		�F[I/ ]�@Attribute�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
	*					�@		�iGetAttribLocation�Ŏ擾�����Ԃ�l�j
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void EnableVertexAttribArray(const GLint p_index);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Attribute�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glVertexAttribPointer �Ɠ����ł��j
	*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
	*	����
	*	�@p_index		�F[I/ ]�@Attribute�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
	*					�@		�iGetAttribLocation�Ŏ擾�����Ԃ�l�j
	*	�@p_size		�F[I/ ]�@���_�f�[�^�̗v�f��
	*	�@p_type		�F[I/ ]�@���_�f�[�^�̌^
	*	�@p_normalized	�F[I/ ]�@���_�f�[�^�𐳋K�����Ē��_�V�F�[�_�[�ɓn���ꍇ�́uGL_TRUE�v���w��A
	*							 ���͂��̂܂܂ɒ��_�V�F�[�_�[�ɓn���ꍇ�́uGL_FALSE�v���w��
	*	�@p_stride		�F[I/ ]�@���_�̐擪�ʒu���Ƃ̃I�t�Z�b�g�l�A0�w��\
	*	�@p_pointe		�F[I/ ]�@�֘A�t���钸�_�̐擪�|�C���^
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void VertexAttribPointer(const GLint p_index, const GLint p_size, const GLenum p_type, const GLboolean p_normalized, const GLsizei p_stride, const GLvoid *p_pointe);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Uniform�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glUniform1f, glUniform2f, glUniform3f, glUniform4f �Ɠ����ł��j
	*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
	*	����
	*	�@p_index		�F[I/ ]�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
	*					�@		�iGetUniformLocation�Ŏ擾�����Ԃ�l�j
	*	�@p_scalar		�F[I/ ]�@�]������f�[�^�̌��i�V�F�[�_�[���ϐ��̃x�N�g�������Ɠ���������́@��)[4] �� vec4�j
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
	void UniformXf(const GLint p_index, const GLint p_scalar, const GLfloat p_param1, const GLfloat p_param2, const GLfloat p_param3, const GLfloat p_param4);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Uniform�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glUniform1i, glUniform2i, glUniform3i, glUniform4i �Ɠ����ł��j
	*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
	*	����
	*	�@p_index		�F[I/ ]�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
	*					�@		�iGetUniformLocation�Ŏ擾�����Ԃ�l�j
	*	�@p_scalar		�F[I/ ]�@�]������f�[�^�̌��i�V�F�[�_�[���ϐ��̃x�N�g�������Ɠ���������́@��)[4] �� ivec4�j
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
	void UniformXi(const GLint p_index, const GLint p_scalar, const GLint p_param1, const GLint p_param2, const GLint p_param3, const GLint p_param4);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Uniform�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glUniform1fv, glUniform2fv, glUniform3fv, glUniform4fv �Ɠ����ł��j
	*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
	*	����
	*	�@p_index		�F[I/ ]�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
	*					�@		�iGetUniformLocation�Ŏ擾�����Ԃ�l�j
	*	�@p_scalar		�F[I/ ]�@�]������f�[�^�̌��i�V�F�[�_�[���ϐ��̃x�N�g�������Ɠ���������́@��)[4] �� vec4�j
	*	�@p_count		�F[I/ ]�@�]������f�[�^�̔z�񐔁i�up_scalar�v�����Őݒ肵���f�[�^�̌������Z�b�g���邩�@��)[4] �� vec? Example[4]�j
	*	�@value			�F[I/ ]�@�]������f�[�^�ւ̃|�C���^
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void UniformXfv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLfloat *p_value);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Uniform�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glUniform1iv, glUniform2iv, glUniform3iv, glUniform4iv �Ɠ����ł��j
	*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
	*	����
	*	�@p_index		�F[I/ ]�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
	*					�@		�iGetUniformLocation�Ŏ擾�����Ԃ�l�j
	*	�@p_scalar		�F[I/ ]�@�]������f�[�^�̌��i�V�F�[�_�[���ϐ��̃x�N�g�������Ɠ���������́@��)[4] �� ivec4�j
	*	�@p_count		�F[I/ ]�@�]������f�[�^�̔z�񐔁i�up_scalar�v�����Őݒ肵���f�[�^�̌������Z�b�g���邩�@��)[4] �� ivec? Example[4]�j
	*	�@value			�F[I/ ]�@�]������f�[�^�ւ̃|�C���^
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void UniformXiv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLint *p_value);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Uniform�ϐ��փf�[�^�𑗐M�i�֘A�t���j���܂��B�i�ق� glUniformMatrix2fv, glUniformMatrix3fv, glUniformMatrix4fv �Ɠ����ł��j
	*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
	*	����
	*	�@p_index		�F[I/ ]�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
	*					�@		�iGetUniformLocation�Ŏ擾�����Ԃ�l�j
	*	�@p_scalar		�F[I/ ]�@�]������s��̃T�C�Y�i�H�~�H �� [�H]�̕����j�i�V�F�[�_�[���ϐ��̃x�N�g�������Ɠ���������́@��)[4] �� mat4�j
	*	�@p_count		�F[I/ ]�@�]������̍s��̌��i�up_scalar�v�����Őݒ肵���s��̃T�C�Y�����Z�b�g���邩�@��)[4] �� mat? Example[4]�j
	*	�@p_transpose	�F[I/ ]�@���_�f�[�^��]�u���ăV�F�[�_�[�ɓn���ꍇ�́uGL_TRUE�v���w��A
	*								 ���͂��̂܂܂ɒ��_�V�F�[�_�[�ɓn���ꍇ�́uGL_FALSE�v���w��
	*	�@value			�F[I/ ]�@�]������f�[�^�ւ̃|�C���^
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void UniformMatrixXfv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLboolean p_transpose, const GLfloat *p_value);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�V�F�[�_�[�v���O�����̗��p���J�n����i�ق� glUseProgram �Ɠ����ł��j
	*	�@�G���[����Ǘ����ꌳ�����ė��֐��̌����}���Ă��܂��B
	*	����
	*	�@�Ȃ�
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void UseProgram(void);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�v���O�����I�u�W�F�N�g���擾����
	*	����
	*	�@�Ȃ�
	*	�߂�l
	*	�@�V�F�[�_�[�̃v���O�����I�u�W�F�N�g
	*-------------------------------------------------------------------------------*/
	inline GLint GetProgramObject(void)
	{
		return m_ProgramObject;
	}

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Attribute�ϐ��̃��P�[�V�������擾����
	*	�@�{�֐��͊��ɐ����������P�[�V�������擾���邽�߂̊֐��ł��B
	*
	*	�@�V�K��Attribute�ϐ��̃��P�[�V�����𐶐��������ꍇ�́A�uGetAttribLocation�v�֐��𗘗p���Ă��������B
	*	����
	*	�@p_index		�F[I/ ]�@Attribute�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
	*						�@		�iGetAttribLocation�Ŏ擾�����Ԃ�l�j
	*	�߂�l
	*	�@Attribute�ϐ��̃��P�[�V����
	*-------------------------------------------------------------------------------*/
	inline GLint GetAttribLocationOriginal(GLint p_index)
	{
		return m_AttribInfo[p_index].Location;
	}

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Uniform�ϐ��̃��P�[�V�������擾����
	*	�@�{�֐��͊��ɐ����������P�[�V�������擾���邽�߂̊֐��ł��B
	*
	*	�@�V�K��Uniform�ϐ��̃��P�[�V�����𐶐��������ꍇ�́A�uGetUniformLocation�v�֐��𗘗p���Ă��������B
	*	����
	*	�@p_index		�F[I/ ]�@Uniform�ϐ��̃��P�[�V�������Ăяo�����߂̃C���f�b�N�X�l
	*						�@		�iGetUniformLocation�Ŏ擾�����Ԃ�l�j
	*	�߂�l
	*	�@Attribute�ϐ��̃��P�[�V����
	*-------------------------------------------------------------------------------*/
	inline GLint GetUniformLocationOriginal(GLint p_index)
	{
		return m_UniformInfo[p_index].Location;
	}

private:

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�V�F�[�_�[�t�@�C���̓ǂݍ��݂��s��
	*	����
	*	�@p_file_name		�F[I/ ]�@�e�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
	*	�@p_shader_source	�F[ /O]�@�e�V�F�[�_�[�̃\�[�X
	*	�@source_size		�F[I/ ]�@�V�F�[�_�[�̑S���̍ő啶����
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void Shader_FileLoad(const char* p_file_name, char* p_shader_source, const int p_source_size);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�V�F�[�_�[�\�[�X�̓ǂݍ��݂��s��
	*	����
	*	�@shader_source		�F[I/ ]�@�e�V�F�[�_�[�̃\�[�X�f�[�^
	*	�@gl_xxxx_shader	�F[I/ ]�@�쐬����V�F�[�_�[�I�u�W�F�N�g�i�o�[�e�b�N�X or �t���O�����g�j
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	GLint Shader_SourceLoad(const char* p_shader_source, const GLuint p_gl_xxxx_shader);

	
	//�\���̒�`

	//�A�g���r���[�g�ϐ��Ǘ��p�̍\����
	typedef struct
	{
		char Name[ATTRIB_INFO_NAME_MAX];			//�ϐ���
		GLint Location;								//���P�[�V����
	}AttribInfo;

	//���j�t�H�[���ϐ��Ǘ��p�̍\����
	typedef struct
	{
		char Name[UNIFORM_INFO_NAME_MAX];				//�ϐ���
		GLint Location;									//���P�[�V����
	}UniformInfo;


	//�ϐ���`
	GLint m_ProgramObject;		//�v���O�����I�u�W�F�N�g
	char m_vertex_file_name[SHADER_FILE_NAME_MAX];		//�o�[�e�b�N�X�V�F�[�_�[�t�@�C����
	char m_fragment_file_name[SHADER_FILE_NAME_MAX];	//�t���O�����g�V�F�[�_�[�t�@�C����
	
	AttribInfo m_AttribInfo[ATTRIB_INFO_MAX];			//�A�g���r���[�g�ϐ��Ǘ��p�̕ϐ�
	int m_AttribInfoIndex = 0;							//�A�g���r���[�g�ϐ��Ǘ��p�̃C���f�b�N�X�l
	UniformInfo m_UniformInfo[UNIFORM_INFO_MAX];		//���j�t�H�[���ϐ��Ǘ��p�̕ϐ�
	int m_UniformInfoIndex = 0;							//���j�t�H�[���ϐ��Ǘ��p�̃C���f�b�N�X�l
};
#endif